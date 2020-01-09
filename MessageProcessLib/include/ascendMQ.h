#pragma once
#include <qmutex.h>
#include <QQueue>
#include <string>
#include "messagesnodedefinition.h"
#include "messagesdefinition.h"
#include <qobjectdefs.h>
#include <QObject>
//���ж������ݽṹ   ȫ�ֵ������õ���ģʽ
class AscendMQ: public QObject
{
	Q_OBJECT
public:
	//���ʵ���Ľӿ�
	static AscendMQ* GetInstance();
	static QMutex* GetMutex();
private:
	AscendMQ(QObject *parent = nullptr);
public:
	~AscendMQ();

public:
	void addMessage(SMessageBase & message);  //�����Ϣ
	SMessageBase GetAMessage();               //��õ�ǰ������		
	int GetQueueSize();                       //��ö��еĳ���
	QQueue<SMessageBase> GetQueue();       //��ö���

public slots:
	void appendMessage(SMessageBase& message);
    //void consumeMessage();
   // void consumeSome(int i);
	//void messageConsumed(int i);                      //��Ϣ������
private:
	QQueue<SMessageBase> m_queue;          //��������
	static AscendMQ* m_pointer;            //����ָ��
	static QMutex  mutex;                     //�ֳ���
};
