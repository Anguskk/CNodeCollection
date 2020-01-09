#pragma once
#include <qmutex.h>
#include <QQueue>
#include <string>
#include "messagesnodedefinition.h"
#include "messagesdefinition.h"
#include <qobjectdefs.h>
#include <QObject>
//上行队列数据结构   全局单例采用单例模式
class AscendMQ: public QObject
{
	Q_OBJECT
public:
	//获得实例的接口
	static AscendMQ* GetInstance();
	static QMutex* GetMutex();
private:
	AscendMQ(QObject *parent = nullptr);
public:
	~AscendMQ();

public:
	void addMessage(SMessageBase & message);  //添加消息
	SMessageBase GetAMessage();               //获得当前的任务		
	int GetQueueSize();                       //获得队列的长度
	QQueue<SMessageBase> GetQueue();       //获得队列

public slots:
	void appendMessage(SMessageBase& message);
    //void consumeMessage();
   // void consumeSome(int i);
	//void messageConsumed(int i);                      //消息被处理
private:
	QQueue<SMessageBase> m_queue;          //队列数据
	static AscendMQ* m_pointer;            //对象指针
	static QMutex  mutex;                     //现成锁
};
