#pragma once
#pragma once
#include <qmutex.h>
#include <QQueue>
#include <qobjectdefs.h>
#include <QObject>

#include "messagesnodedefinition.h"
#include "messagesdefinition.h"

//���ж������ݽṹ ���´�����Ϣ   ȫ�ֵ������õ���ģʽ
class DescendMQ:public QObject
{
	Q_OBJECT
public:
	//���ʵ���Ľӿ�
	static DescendMQ* GetInstance();
private:
	DescendMQ(QObject *parent = nullptr);
public:
	~DescendMQ();

public:
	void PushTask(SMessageBase & message);  //����������������
	void addMessage(SMessageBase & message);  //�����Ϣ
	SMessageBase GetMessage();                        //��õ�ǰ������
	void Finished();                      //�������
	int GetQueueSize();                       //��ö��еĳ���
	QQueue<SMessageBase> GetQueue();       //��ö���
public slots:
	//void appendMessage(SMessageBase& message);
private:
	QQueue<SMessageBase> m_queue;          //��������
	static DescendMQ* m_pointer;            //����ָ��
	static QMutex  mutex;                     //�ֳ���

};

