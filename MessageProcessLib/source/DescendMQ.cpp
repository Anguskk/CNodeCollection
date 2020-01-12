//#include "descendMQ.h"
#include <cstddef>
#include <qmutex.h>
#include <QObject>
#include "include/descendMQ.h"
DescendMQ* DescendMQ::m_pointer = NULL;
QMutex  DescendMQ::mutex;


DescendMQ* DescendMQ::GetInstance()
{
	if (m_pointer == nullptr)
	{
		QMutexLocker locker(&mutex);
		if (m_pointer == nullptr)
		{
			m_pointer = new DescendMQ;
		}
	}
	return m_pointer;
}

DescendMQ::DescendMQ(QObject* parent):QObject(parent)
{
	
}

DescendMQ::~DescendMQ()
{
}

void DescendMQ::PushTask(SMessageBase& message)
{
}

void DescendMQ::addMessage(SMessageBase& message)
{
	m_queue.enqueue(message);
}

SMessageBase DescendMQ::GetMessage()
{
	return  m_queue.dequeue();
}

void DescendMQ::Finished()
{
	
}

int DescendMQ::GetQueueSize()
{
	return m_queue.size();
}

QQueue<SMessageBase> DescendMQ::GetQueue()
{
	return m_queue;
}

// void DescendMQ::appendMessage(SMessageBase& message)
// {
// }
