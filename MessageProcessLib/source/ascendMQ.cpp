
#include <QDebug>
#include <qmutex.h>
#include "include/ascendMQ.h"
AscendMQ* AscendMQ::m_pointer = nullptr;
QMutex  AscendMQ::mutex;

//线程安全Lazy初始化
AscendMQ* AscendMQ::GetInstance()
{
	if (m_pointer == nullptr)
	{
		QMutexLocker locker(&mutex);
        
		if (m_pointer == nullptr)
		{
			m_pointer = new AscendMQ;
		}
	}
	return m_pointer;
}

QMutex* AscendMQ::GetMutex()
{
	return &mutex;
}

AscendMQ::AscendMQ(QObject* parent):QObject(parent)
{
	
}

AscendMQ::~AscendMQ()
{
	m_pointer = nullptr;
	// if (m_pointer != nullptr)
	// {
	// 	delete m_pointer;
	// 	m_pointer = nullptr;
	// }
}

void AscendMQ::addMessage(SMessageBase & message)
{
    QMutexLocker locker(&mutex);
	m_queue.append(message);
	
}
// assert  队列至少一个元素
SMessageBase AscendMQ::GetAMessage()
{

	return m_queue.dequeue();
}

int AscendMQ::GetQueueSize()
{
    
	return m_queue.size();
}

QQueue<SMessageBase>  AscendMQ::GetQueue()
{
    QQueue<SMessageBase> q;
    QMutexLocker locker(&mutex);
    {        
        while (!m_queue.isEmpty())
        {
            q.append(m_queue.dequeue());
        }
    }
    return  q;
	
}

void AscendMQ::appendMessage(SMessageBase& message)
{
   // QMutexLocker locker(&mutex);
   if (mutex.tryLock())
   {
       m_queue.append(message);
	   mutex.unlock();
   }
   else
   {
       mutex.lock();
       m_queue.append(message);
       mutex.unlock();
   }
}

//void AscendMQ::consumeMessage()
//{
//    m_queue.pop_front();
//}
//
//void AscendMQ::consumeSome(int i)
//{
//    QMutexLocker locker(&mutex);
//    for (int ii = 0; ii < i; ++ii)
//    {
//        m_queue.pop_front();
//    }
//}
