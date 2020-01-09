#include "tcpsocket.h"
#include <QtConcurrent/QtConcurrent>
#include <QHostAddress>
#include <QDebug>
#include "tcpserver.h"


TcpSocket::TcpSocket(qintptr socketDescriptor, QObject *parent) : //构造函数在主线程执行，lambda在子线程
    QTcpSocket(parent),socketID(socketDescriptor)
{
    this->setSocketDescriptor(socketDescriptor);
  //  response_flag = 0x0000;
    heartbeat = true;
    dis = connect(this,&TcpSocket::disconnected,
        [&](){
        // dicCOnnect响应
            qDebug() << "disconnect："<< this->peerAddress().toString()<<":"<<this->peerPort();
            //发送断开连接的用户信息
            emit sockDisConnect(socketID,this->peerAddress().toString(),this->peerPort(),MacAddress,QThread::currentThread());
            this->deleteLater();
			/*SMessageBase message;
			message.shelfID = shelfID; message.nodeID = nodeID;
			auto t_connectionStatusMsg = new SConnectionStatusMsg;
			t_connectionStatusMsg->type = 0;
			message.data = t_connectionStatusMsg;
			message.type = ConnectionStatusMsg;
			emit handle_done(message);*/

            
        });
	
    //错误处理
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error_slot(QAbstractSocket::SocketError)));
	//启动心跳计时器
	//connect(&timer_, &QTimer::timeout, this, &TcpSocket::time_out_slot);
	//connect(&timer_, SIGNAL(timeout()), this, SLOT(time_out_slot()));
       
}

void TcpSocket::handleData(SMessageNodeBase& ori_message)
{
    //TODO  重组上层消息,*data内容不拆
    SMessageBase  new_message = smessage_node_base2smessage_base(ori_message);
    emit handle_done(new_message);    
    // QString  str(static_cast<char*>(new_message.data));
    // qDebug() << str << '\n';
}

void TcpSocket::setShelfNode()
{
    // MAC 和 Shelf  查 Node号
    //根据MAC去匹配
    SNodeInfo SNode_info;
	SNode_info.shelfID = 0;
	SNode_info.nodeID = 0;
	//thread()->msleep(1000);
	auto allNodeInfos = getNodeInfo(tcp_server->get_shelfInfos());
	for (const auto& node_info : allNodeInfos)
	{
		if (node_info.macAddress == getMacAddress())
		{
			SNode_info = node_info;
			break;
		}
	}
    this->shelfID = SNode_info.shelfID;
    this->nodeID = SNode_info.nodeID;
}

QString TcpSocket::getMacAddress()
{    
    return this->MacAddress;
}

QTimer* TcpSocket::get_timer()
{
    return timer_;
}

qintptr TcpSocket::get_socketID() const
{
    return socketID;
}


void TcpSocket::setMACAddress(SMessageNodeBase& ori_message)
{
	auto curMacinfo = static_cast<const unsigned char*>(ori_message.data);
	this->MacAddress.clear();
	this->MacAddress = QString("%1%2%3%4%5%6").arg(curMacinfo[5], 2, 16, QLatin1Char('0'))
		.arg(curMacinfo[4], 2, 16, QLatin1Char('0'))
		.arg(curMacinfo[3], 2, 16, QLatin1Char('0'))
		.arg(curMacinfo[2], 2, 16, QLatin1Char('0'))
		.arg(curMacinfo[1], 2, 16, QLatin1Char('0'))
		.arg(curMacinfo[0], 2, 16, QLatin1Char('0'));
}
void TcpSocket::send_connection(SMessageBase& message)
{
    emit handle_done(message);

}

void TcpSocket::set_server(TcpServer * server)
{
    tcp_server = server;
}

void TcpSocket::set_status(quint16 status)
{
    response_flag = status;
}

TcpSocket::~TcpSocket()
{
    //delete timer_;
}



void TcpSocket::sent_instant_message_slot(SMessageBase& message)
{
    //设置等待消息位            
    if (message.shelfID == -1 && message.nodeID ==-1 )
    {
        //全发
        blocked_send_reiceive(message);
    }
    else
    {
        if (message.shelfID == -1 &&  message.nodeID !=-1)
        {
            if (message.nodeID == nodeID)
            {
                blocked_send_reiceive(message);
            }
        }
        else if (message.shelfID !=-1  &&  message.nodeID == -1)
        {
            if (message.shelfID == shelfID)
            {
                blocked_send_reiceive(message);
            }
        }
        else
        {
            if (message.shelfID == this->shelfID &&  message.nodeID == this->nodeID)
            {
                blocked_send_reiceive(message);
            }
        }
    }
    
}

void TcpSocket::disConTcp(int i)
{
	
	
    if (i == socketID)
    {
        if (shelfID > 0 && nodeID > 0)
        {
            SMessageBase message;
            message.shelfID = shelfID; message.nodeID = nodeID;
            auto t_connectionStatusMsg = new SConnectionStatusMsg;
            t_connectionStatusMsg->type = 0;
            message.data = t_connectionStatusMsg;
            message.type = ConnectionStatusMsg;
            emit handle_done(message);
        }
        this->disconnectFromHost();        
    }
    else if (i == -1) //-1为全部断开
    {
        //断开信号槽
        disconnect(dis); //先断开连接的信号槽，防止二次析构
        this->disconnectFromHost();
        this->deleteLater();
    }
}

SMessageNodeBase TcpSocket::smessage_base2smessage_node_base(SMessageBase& message_base)
{
    SMessageNodeBase result;
    result.data = message_base.data;
    result.header.checkNum = 0xA5A5;
    result.header.type = message_base.type;
    result.header.length = message_base.length;
    return result;
}

void TcpSocket::blocked_send_reiceive(SMessageBase& message)
{   
	if (message.nodeID == -1 && message.shelfID == -1)
	{
		
		timer_->stop();
		//请求停止发送心跳包;
		SMessageNodeBase query;
		query.header.checkNum = 0xA5A5;
		query.header.type = ChargingRequestMsg; query.header.length = sizeof(SRequestChargingMessage);
		SRequestChargingMessage t_requestChargingMessage;
		t_requestChargingMessage.monitoring[0] = 0;
		query.data = &t_requestChargingMessage;
		write_SMessageNodeBase(query);
		//TODO  是否还要接收  命令的回复 ChargingConfirmMsg
		//收到回复
		//断开连接信号
        if (disconnect(read_signal) == false)
        {
            //断开连接信号
            //信号没有断开
            return;
        }
		//正式 问答 开始 发送请求
		SMessageNodeBase node_message = smessage_base2smessage_node_base(message);
		write_SMessageNodeBase(node_message);

		//从缓存中读取回复
		bool isSuccess = false;
		SMessageNodeBase receive;
		QByteArray  data;
		QDataStream in(data);
		in.setByteOrder(QDataStream::LittleEndian);
        //3次执行，即3秒
        for (short i = 0; i < 3; i++)
        {
            this->waitForReadyRead(1000);
            auto sum = bytesAvailable();
            data = this->readAll();
            do
            {
                SMessageNodeBase receive;
                in >> receive.header.checkNum >> receive.header.type >> receive.header.length;
                in.readRawData(static_cast<char*>(receive.data), receive.header.length);
                if (receive.header.type == message.type + 1)
                {
                    data.clear();
                    isSuccess = true;
                    break;
                }
                //丢掉无用消息              
                sum = sum - 8 - receive.header.length;
            } while (sum > 0);
            if (isSuccess)
            {
                break;
            }
            else
            {
                QThread::currentThread()->sleep(500);
            }
        }
        //异常判断
        if (!isSuccess)
        {
            disConTcp(socketID);
            qDebug() << "error  no response  receive";
        }
		//重新请求发送心跳包    
		query.header.type = ChargingRequestMsg; query.header.length = sizeof(SRequestChargingMessage);
		t_requestChargingMessage.monitoring[0] = 1;
		query.data = &t_requestChargingMessage;
		write_SMessageNodeBase(query);
		read_signal = connect(this, &TcpSocket::readyRead, this, &TcpSocket::readData);
		timer_->start(3000);
		//timer_.setSingleShot(true);
	}
	else if (message.nodeID == nodeID && message.shelfID == shelfID)
	{
		//正式 问答 开始 发送请求
		SMessageNodeBase node_message = smessage_base2smessage_node_base(message);
		write_SMessageNodeBase(node_message);
	}
}

void TcpSocket::write_SMessageNodeBase(SMessageNodeBase& node_message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
	out.setByteOrder(QDataStream::LittleEndian);
    //碾平SMessageNodeBase，stream化
    out << node_message.header.checkNum << node_message.header.type << node_message.header.length;
    out.writeRawData(static_cast<const char*>(node_message.data), node_message.header.length);
	
	write(block);
}


SMessageBase TcpSocket::smessage_node_base2smessage_base(SMessageNodeBase& node_message)
{
    SMessageBase new_message;
    new_message.type = node_message.header.type;
    new_message.shelfID = this->shelfID, new_message.nodeID = this->nodeID;
    new_message.data = node_message.data;
	new_message.length = node_message.header.length;
    return new_message;
}

void TcpSocket::parse_SMessageNodeBase(QByteArray &raw, QVector<SMessageNodeBase>& node_message)
{
    //解析
    QDataStream in(raw);
	in.setByteOrder(QDataStream::LittleEndian);
	while (!in.atEnd())
	{
		SMessageNodeBase curNodeBase;
		in >> curNodeBase.header.checkNum >> curNodeBase.header.type >> curNodeBase.header.length;
		curNodeBase.data = new char[curNodeBase.header.length];
		in.readRawData(static_cast<char*>(curNodeBase.data), curNodeBase.header.length);
		node_message.append(curNodeBase);
	}
}

void TcpSocket::parse_SMessageNodeBase(QByteArray &raw, SMessageNodeBase & node_message)
{
	//解析
	QDataStream in(raw);
	in.setByteOrder(QDataStream::LittleEndian);
	in >> node_message.header.checkNum >> node_message.header.type >> node_message.header.length;
	node_message.data = new char[node_message.header.length];
	in.readRawData(static_cast<char*>(node_message.data), node_message.header.length);
}

void TcpSocket::time_out_slot()
{
    //检查是否还收到心跳（充电）消息
    if (heartbeat == false)
    {
        qDebug() << "connection failed ";
        timer_->stop();
        disConTcp(socketID);
    }
    else
    {
        heartbeat = false;
    }
    if (response_flag != 0)
    {
        qDebug() << "didn't execute cache task ";
        timer_->stop();
        disConTcp(socketID);
    }
}

void TcpSocket::error_slot(QAbstractSocket::SocketError)
{
    //向上层报告socket异常
    qDebug() << errorString() << '\n';
}


//QDataStream operator>>(const QDataStream& lhs, char* const& rhs);
//读取数据
void TcpSocket::readData()
{
    int size = this->bytesAvailable();    

	QDataStream in(this);
	in.setByteOrder(QDataStream::LittleEndian);
	while (!atEnd())
	{
		SMessageNodeBase ori_message;
		in >> ori_message.header.checkNum >> ori_message.header.type >> ori_message.header.length;
		ori_message.data = new char[ori_message.header.length];
		in.readRawData(static_cast<char*>(ori_message.data), ori_message.header.length);

		if (ori_message.header.checkNum != 0xA5A5)
		{
			//检验位不对，重发或者丢弃
			qDebug() << "Checksum  wrong";
			continue;
		}
		SMessageBase cache = tcp_server->get_cache_mode();
        if (ori_message.header.type == cache.type + 1)
        {
            response_flag = 0;
        }
		//需要上传的及时消息
		if (ori_message.header.type == AnnualInspectionConfirmMsg || ori_message.header.type == AnnualInspectionDownloadConfirmMsg
			|| ori_message.header.type == ChargingConfirmMsg || ori_message.header.type == DownloadConfirmMsg)
		{
			if (ori_message.header.type != ChargingConfirmMsg || cache.type == ChargingRequestMsg)
				handleData(ori_message);
		}
		//不定时消息处理  上传消息队列    
		if (ori_message.header.type >= 0x0101 && ori_message.header.type <= 0x0104)
		{
			if (ori_message.header.type == ChargingStateInfoMsg)
			{
				heartbeat = true;
			}
			if (ori_message.header.type != ChargingStateInfoMsg || cache.type == ChargingRequestMsg)
				handleData(ori_message);
            
		}
	}
}

void TcpSocket::start_slot()
{
    bool flag = true;
    QByteArray rawdata;
	SMessageNodeBase ori_message;
	SMessageNodeBase query;
    //发送MAC查询消息    
    query.header.checkNum = 0xA5A5; query.header.type = NoteInfoRequestMsg; query.header.length = 0;
    query.data = nullptr;
    write_SMessageNodeBase(query);
    //阻塞等待3秒
    this->waitForReadyRead(3000);    
    rawdata = this->readAll();    
    parse_SMessageNodeBase(rawdata, ori_message);   
	if (ori_message.header.type != NoteInfoConfirmMsg)
    {
        qDebug() << "type mismatch NoteInfoConfirmMsg\n";
        disConTcp(socketID);
        return;
    }
    setMACAddress(ori_message);

    // 查找MAC是否已经存在的情况
   // 没有存在 继续执行
   // 已经存在  删除之前的，替换为当前的
    if (tcp_server->query_macClient(this->MacAddress, this))
    {
        //True为存在old
        qDebug() << "already exist a same MAC";
    }

    setShelfNode();
    shelfID = 3;
    if (shelfID == 0 && nodeID == 0) {
        qDebug() << "fail to set ShelfNodeID \n";
        disConTcp(socketID);
        return;
    }
    //固件情况查询
    SMessageBase firmware = tcp_server->get_firmware();
    if (firmware.type == FirmwareUpgradeRequestMsg)
    {
        //发送固件升级消息
        SMessageNodeBase send_query = smessage_base2smessage_node_base(firmware);
        write_SMessageNodeBase(send_query);
        //阻塞等待3秒
        this->waitForReadyRead(3000);
        rawdata = this->readAll();
        parse_SMessageNodeBase(rawdata, ori_message);
        if (ori_message.header.type != FirmwareUpgradeConfirmMsg)
        {
            qDebug() << "type mismatch FirmwareUpgradeConfirmMsg\n";
            disConTcp(socketID);
            return;
        }
        //检查固件版本  
        quint32 type = *(static_cast<unsigned char*>(ori_message.data));
        if (type == 2)
        {
            //需要升级
            disConTcp(socketID);
            qDebug() << "firm need upgrade \n";
            return;
        }
    }
    //连接成功
    if (flag)
    {        
        read_signal = connect(this, &TcpSocket::readyRead, this, &TcpSocket::readData);
        //完成固件信息检查，成功连接
        SMessageBase message;
        message.shelfID = shelfID; message.nodeID = nodeID;
        auto t_connectionStatusMsg = new SConnectionStatusMsg;
        t_connectionStatusMsg->type = 1;
        message.data = t_connectionStatusMsg;
        message.type = ConnectionStatusMsg;
        emit handle_done(message);
        //执行新连接的缓存模式任务 发送请求消息
        SMessageBase cache = tcp_server->get_cache_mode();
        if (cache.type != 0)
        {
            SMessageNodeBase message = smessage_base2smessage_node_base(cache);
            write_SMessageNodeBase(message);
        }
		if (cache.type != ChargingRequestMsg) {
			//开始请求发送充电消息
			query.header.type = ChargingRequestMsg; query.header.length = sizeof(SRequestChargingMessage);
			SRequestChargingMessage t_requestChargingMessage;
			t_requestChargingMessage.monitoring[0] = 1;
			query.data = &t_requestChargingMessage;
			write_SMessageNodeBase(query);
		}
		
		timer_ = new QTimer;
		connect(timer_, SIGNAL(timeout()), this, SLOT(time_out_slot()));
		heartbeat = false;
		timer_->start(3000);
		
    }
   
}
