#include "messageprocessmanage.h"

#include <QDebug>
#include "threadhandle.h"
#include "tcpserver.h"
#include "string.h"

// void CMessageProcessManage::send_message_test_slot()
// {
// 	SMessageBase message;
// 	message.type = 0x0007;
// 	message.nodeID = -1;
// 	message.shelfID = -1;
// 	char temp[]= "definable";
// 	strcpy(pdata, temp);
// 	message.data = pdata;
// 	append_deliver_message(message);
// }

CMessageProcessManage::CMessageProcessManage(QObject *parent)
	: QObject(parent)
{
	qRegisterMetaType<SMessageBase>("SMessageBase");
	qRegisterMetaType<SMessageBase>("SMessageBase&");
	qRegisterMetaType<SMessageNodeBase>("SMessageNodeBase");
	qRegisterMetaType<SMessageNodeBase>("SMessageNodeBase&");

	tcpServer = new TcpServer;	
	auto serverThread = new QThread;
	connect(this, &CMessageProcessManage::enable_server, tcpServer, &TcpServer::enable_serverSlot);
	connect(this, &CMessageProcessManage::shutdown_signal, tcpServer, &TcpServer::deleteLater);
	
	//connect(this,&CMessageProcessManage::delete_child,)
	tcpServer->moveToThread(serverThread);
	serverThread->start();
	ascend_mq = AscendMQ::GetInstance();
	auto ascend_mqThread = new QThread;	
	ascend_mq->moveToThread(ascend_mqThread);
    ascend_mqThread->start();
	//connect(this, &CMessageProcessManage::ConsumeAMessageSignal, ascend_mq, &AscendMQ::messageConsumed);
	message_deliver_thread = new CMessageProcessThread;
	message_deliver_thread->set_TCPserver(tcpServer);
	message_deliver_thread->set_Manage(this);

    //阻塞信号连接 为了  同步  AscendQ 的队列长度
    //connect(message_deliver_thread, &CMessageProcessThread::consumed, ascend_mq, &AscendMQ::consumeMessage, Qt::BlockingQueuedConnection);
    //connect(message_deliver_thread, &CMessageProcessThread::consumes, ascend_mq, &AscendMQ::consumeSome,Qt::BlockingQueuedConnection);
	connect(this, &CMessageProcessManage::shutdown_signal, message_deliver_thread, &CMessageProcessThread::deleteLater);
	connect(this, &CMessageProcessManage::shutdown_signal, ascend_mq, &AscendMQ::deleteLater);

    //connect(&_timer_, &QTimer::timeout, this, &CMessageProcessManage::send_message_test_slot);
}

CMessageProcessManage::~CMessageProcessManage()
{
	message_deliver_thread->stopThread();
	emit shutdown_signal();
	//delete serverThread;
}



void CMessageProcessManage::start(QVector<ShelfInfo> &vshelfs)
{	
	emit enable_server();

	ThreadHandle::getClass().initThreadType(ThreadHandle::HANDLESIZE, 3);
	tcpServer->set_shelfInfos(vshelfs);
    //_timer_.start(1000);
    
    message_deliver_thread->start();
}

void CMessageProcessManage::shutdown() const
{
	tcpServer->close();
}

CMessageProcessThread* CMessageProcessManage::get_process_thread() const
{
	return message_deliver_thread;
}

void CMessageProcessManage::append_deliver_message(SMessageBase& message) const
{
	tcpServer->sent_group_messages(message);
}
