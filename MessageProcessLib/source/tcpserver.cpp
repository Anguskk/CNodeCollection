#include "include/tcpserver.h"

#include <QDataStream>
#include "include/messageprocessmanage.h"
#include "include/threadhandle.h"
#include "string.h"
#include "include/tcpserver.h"

TcpServer::TcpServer(QObject *parent, int numConnections) :
    QTcpServer(parent)
{
    tcpClient = new  QHash<int, TcpSocket *>;
    MacClient = new QHash<QString, TcpSocket*>;
    setMaxPendingConnections(numConnections);
    //message_deliver_thread = new CMessageProcessThread;
    //message_deliver_thread->start();
}

TcpServer::~TcpServer()
{
    this->clear();
    //delete message_deliver_thread;
    delete tcpClient;
    delete MacClient;
}

void TcpServer::setMaxPendingConnections(int numConnections)
{
    //调用Qtcpsocket函数，设置最大连接数，主要是使maxPendingConnections()依然有效
    this->QTcpServer::setMaxPendingConnections(numConnections);
    this->maxConnections = numConnections;
}

void TcpServer::sent_group_messages(SMessageBase& message)
{
    emit sent_group_messages_signal(message);
    //给全部节点的消息缓存一下。
    if (message.shelfID == -1 && message.nodeID == -1)
    {
        cache_message = message;
    }
}

void TcpServer::set_shelfInfos(QVector<ShelfInfo>& vshelfInfos)
{
    m_vshelfInfos = vshelfInfos;    
}

void TcpServer::set_manage(CMessageProcessManage* manage)
{
    this->manage_ = manage;
}

SMessageBase TcpServer::get_cache_mode()
{
    return cache_message;
}

bool TcpServer::query_macClient(QString &mac, TcpSocket*  socket)
{
    if (MacClient->find(mac) != MacClient->end())
    {
        //已经存在
        //释放之前的连接
        TcpSocket * old = MacClient->value(mac);
        emit sentDisConnect(old->get_socketID());
        MacClient->remove(mac);
        MacClient->insert(mac, socket);
        return true;
    }
    else
    {
        MacClient->insert(mac, socket);
        return false;
    }

}

QVector<ShelfInfo> TcpServer::get_shelfInfos()
{
    return  m_vshelfInfos;
}

SMessageBase TcpServer::get_firmware()
{
    return firmware_message;
}

void TcpServer::set_firmware(SMessageBase & message)
{
    firmware_message = message;
}
//多线程必须在此函数里捕获新连接
void TcpServer::incomingConnection(qintptr socketDescriptor) 
{
    //继承重写此函数后，QTcpServer默认的判断最大连接数失效，自己实现
    if (tcpClient->size() > maxPendingConnections())
    {
        QTcpSocket tcp;
        tcp.setSocketDescriptor(socketDescriptor);
        tcp.disconnectFromHost();
        return;
    }
    //新建TcpSocket

    auto th = ThreadHandle::getClass().getThread();
    auto tcpTemp = new TcpSocket(socketDescriptor);
    //把tcp类移动到新的线程，从线程管理类中获取
    tcpTemp->moveToThread(th);
    tcpTemp->set_server(this);
    const QString ip = tcpTemp->peerAddress().toString();
    const qint16 port = tcpTemp->peerPort();

    //server向socket发送消息，充分利用多线程和槽机制，在独立线程中处理下发的消息
    connect(this, &TcpServer::sent_group_messages_signal, tcpTemp, &TcpSocket::sent_instant_message_slot);
    //自下而上 NOTE:断开连接的处理，从列表移除，并释放断开的Tcpsocket，此槽必须实现，线程管理计数也是考的他
    connect(tcpTemp, &TcpSocket::sockDisConnect, this, &TcpServer::sockDisConnectSlot);
    //断开信号 自上而下
    connect(this, &TcpServer::sentDisConnect, tcpTemp, &TcpSocket::disConTcp);
    //绑定向上消息传递
    connect(tcpTemp, &TcpSocket::handle_done,manage_->get_process_thread(), &CMessageProcessThread::appendMessage,
        Qt::QueuedConnection);
    //绑定向下群发消息
   
    connect(this, &TcpServer::sent_group_messages_signal, tcpTemp,
        &TcpSocket::sent_instant_message_slot);
    //绑定startTcp信号
    const auto connection =connect(this, &TcpServer::startTcp, tcpTemp, &TcpSocket::start_slot,Qt::UniqueConnection);
    //插入到连接信息中
    tcpClient->insert(socketDescriptor, tcpTemp);
    
    emit connectClient(socketDescriptor, ip, port);
    emit startTcp();
    disconnect(connection);

}

void TcpServer::sockDisConnectSlot(int handle, const QString & ip, quint16 port, QString& mac, QThread * th)
{
    
    tcpClient->remove(handle);
    
    //连接管理中移除断开连接的socket
    if (mac.size()==12)
    {
        MacClient->remove(mac);
    }    
    //告诉线程管理类那个线程里的连接断开了
    ThreadHandle::getClass().removeThread(th);
    emit sockDisConnect(handle, ip, port);
}

void TcpServer::clear()
{
    emit this->sentDisConnect(-1);
    ThreadHandle::getClass().clear();
    tcpClient->clear();
    MacClient->clear();
}

void TcpServer::enable_serverSlot()
{
   //TODO  修改端口
    this->listen(QHostAddress::Any, 8234);

}

