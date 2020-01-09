#pragma once
#pragma once
#include <qmutex.h>
#include <QQueue>
#include <qobjectdefs.h>
#include <QObject>

#include "messagesnodedefinition.h"
#include "messagesdefinition.h"

//下行队列数据结构 向下传递消息   全局单例采用单例模式
class DescendMQ:public QObject
{
	Q_OBJECT
public:
	//获得实例的接口
	static DescendMQ* GetInstance();
private:
	DescendMQ(QObject *parent = nullptr);
public:
	~DescendMQ();

public:
	void PushTask(SMessageBase & message);  //向队列中添加新任务
	void addMessage(SMessageBase & message);  //添加消息
	SMessageBase GetMessage();                        //获得当前的任务
	void Finished();                      //任务完成
	int GetQueueSize();                       //获得队列的长度
	QQueue<SMessageBase> GetQueue();       //获得队列
public slots:
	//void appendMessage(SMessageBase& message);
private:
	QQueue<SMessageBase> m_queue;          //队列数据
	static DescendMQ* m_pointer;            //对象指针
	static QMutex  mutex;                     //现成锁

};

