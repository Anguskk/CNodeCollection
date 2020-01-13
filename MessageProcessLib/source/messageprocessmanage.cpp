#include "./include/messageprocessmanage.h"

#include <QDebug>
#include "./include/threadhandle.h"
#include "./include/tcpserver.h"
#include "string.h"
#include "include/messageprocessmanage.h"
//#include "../../DataMonitor/source/datamonitor.h"

void CMessageProcessManage::send_message_test_slot()
{
    
	SMessageBase message;
	message.type = DownloadRequestMsg;
	message.nodeID = -1;
	message.shelfID = -1;
    SRequestDownloadMessage request;
    request.type[0] = 0;
    message.length = sizeof(request);
    message.data = &request;	
	append_deliver_message(message);
}

CMessageProcessManage::CMessageProcessManage(QObject *parent)
	: QObject(parent)
{

	qRegisterMetaType<SMessageBase>("SMessageBase");
	qRegisterMetaType<SMessageBase>("SMessageBase&");
	qRegisterMetaType<SMessageNodeBase>("SMessageNodeBase");
	qRegisterMetaType<SMessageNodeBase>("SMessageNodeBase&");
    qRegisterMetaType<QString>("QString&");
	tcpServer = new TcpServer;	
	auto serverThread = new QThread;
	connect(this, &CMessageProcessManage::enable_server, tcpServer, &TcpServer::enable_serverSlot);
	connect(this, &CMessageProcessManage::shutdown_signal, tcpServer, &TcpServer::deleteLater);
		
    tcpServer->set_manage(this);
	tcpServer->moveToThread(serverThread);
	serverThread->start();
	// ascend_mq = AscendMQ::GetInstance();
	// auto ascend_mqThread = new QThread;	
	// ascend_mq->moveToThread(ascend_mqThread);
 //    ascend_mqThread->start();
	
	message_deliver_thread = new CMessageProcessThread;
	message_deliver_thread->set_TCPserver(tcpServer);
	message_deliver_thread->set_Manage(this);
   
	connect(this, &CMessageProcessManage::shutdown_signal, message_deliver_thread, &CMessageProcessThread::deleteLater);
	//connect(this, &CMessageProcessManage::shutdown_signal, ascend_mq, &AscendMQ::deleteLater);

    connect(&_timer_, &QTimer::timeout, this, &CMessageProcessManage::send_message_test_slot);
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
    //TODO  修改线程池模式
	ThreadHandle::getClass().initThreadType(ThreadHandle::HANDLESIZE, 3);
	tcpServer->set_shelfInfos(vshelfs);
    //_timer_.start(1000);    
    message_deliver_thread->start();
    //_timer_.setSingleShot(true);
    _timer_.start(10000);
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
    //tcpserver和manage没在一个线程，是否需要使用信号机制
	tcpServer->sent_group_messages(message);
}
