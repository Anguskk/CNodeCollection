#include "include/messageprocessthread.h"
#include "include/ascendMQ.h"
#include "include/messageprocessmanage.h"
#include <memory>

CMessageProcessThread::CMessageProcessThread(QObject *parent)
	:QThread(parent)
{
	isThreadOpen = true;
    m_queue = new QQueue<SMessageBase>;
}

CMessageProcessThread::~CMessageProcessThread()
{
    stopThread();
    delete m_queue;
    m_queue = nullptr;
    exit();
    wait(2000);
   
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

QQueue<SMessageBase>* CMessageProcessThread::GetQueue()
{
    QQueue<SMessageBase>* q=new QQueue<SMessageBase>;
    QMutexLocker locker(&mutex_);
    {
        while (!m_queue->isEmpty())
        {
            q->append(m_queue->dequeue());
        }
    }
    return  q;
}

SMessageBase CMessageProcessThread::GetAMessage()
{
    QMutexLocker locker(&mutex_);
    return m_queue->dequeue();
}

void CMessageProcessThread::stopThread()
{
    mutex_.lock();
	isThreadOpen = false;
    mutex_.unlock();
}

void CMessageProcessThread::run()
{
    //set_ascendq();
	while (isThreadOpen){		
        QQueue<SMessageBase>* tempQ = GetQueue();
        if (!tempQ->isEmpty()) {
            while (!tempQ->empty()) {
                SMessageBase message_base = tempQ->dequeue();
				emit send_statusinfo(message_base);
				qDebug() << "Success send_statusinfo  " << message_base.type;
            }
            delete tempQ;
            tempQ = nullptr;
        }else
        {
            msleep(100);
        }

	}
}

void CMessageProcessThread::appendMessage(SMessageBase& message)
{
    if (mutex_.tryLock())
    {
        m_queue->append(message);
        mutex_.unlock();
    }
    else
    {
        mutex_.lock();
        m_queue->append(message);
        mutex_.unlock();
    }

}
