#include "messageprocessthread.h"
#include "ascendMQ.h"
#include "messageprocessmanage.h"
#include <memory>

CMessageProcessThread::CMessageProcessThread(QObject *parent)
	:QThread(parent)
{
	isThreadOpen = true;
}

CMessageProcessThread::~CMessageProcessThread()
{
	isThreadOpen = false;
	wait(2000);
	terminate();
}


void CMessageProcessThread::set_TCPserver(TcpServer * server)
{
	this->server_ = server;
}

void CMessageProcessThread::set_Manage(CMessageProcessManage* manage)
{
	this->manage = manage;
}

void CMessageProcessThread::set_ascendq()
{
    ascend_mq_ = AscendMQ::GetInstance();

	//模拟添加节点
	/*for (int i=0;i<16;++i)
	{
		SMessageBase message_base;
		message_base.shelfID = 1;
		message_base.nodeID = i;
		message_base.type = ConnectionStatusMsg;

		auto t_connectionStatusMsg = new SConnectionStatusMsg;
		t_connectionStatusMsg->type = 1;

		message_base.data = t_connectionStatusMsg;
		ascend_mq_->addMessage(message_base);
	}

	SMessageBase message_base;
	message_base.shelfID = 1;
	message_base.nodeID = 1;
	message_base.type = ConnectionStatusMsg;

	auto t_connectionStatusMsg = new SConnectionStatusMsg;
	t_connectionStatusMsg->type = 0;

	message_base.data = t_connectionStatusMsg;
	ascend_mq_->addMessage(message_base);*/
}

void CMessageProcessThread::stopThread()
{
	isThreadOpen = false;
}

void CMessageProcessThread::run()
{
    set_ascendq();
	while (isThreadOpen){		
        QQueue<SMessageBase> tempQ = ascend_mq_->GetQueue();
        if (!tempQ.isEmpty()) {
            while (!tempQ.empty()) {
                SMessageBase message_base = tempQ.dequeue();
				emit send_statusinfo(message_base);
				qDebug() << "Success send_statusinfo  " << message_base.type;
            }
        }
	}
}
