#pragma once

#include <QThread>
#include <QQueue>
#include <Qmutex>
#include <QTimer>

#include "messageprocesslib_global.h"
#include "descendMQ.h"
#include "messagesdefinition.h"

class TcpServer;
class CMessageProcessManage;
class AscendMQ;
/**
 * \brief ��Ϣ���������߳�
 *	      
 */
class MESSAGEPROCESSLIB_EXPORT CMessageProcessThread : public QThread
{
	Q_OBJECT

signals:
    void send_statusinfo(const SMessageBase& message);

public:
	
	CMessageProcessThread(QObject *parent = nullptr);
	~CMessageProcessThread();
	void set_TCPserver(TcpServer * server);
	void set_Manage(CMessageProcessManage * manage);
    void set_ascendq();
    QQueue<SMessageBase>* GetQueue();       //��ö���
    SMessageBase GetAMessage();
	void stopThread();
	void run() override;
public slots:
    void appendMessage(SMessageBase& message);
private:
	bool isThreadOpen;
    CMessageProcessManage* manage;
	TcpServer  *server_;
    AscendMQ  * ascend_mq_;
	//QQueue<SMessageNodeBase> messageQueue;
    QQueue<SMessageBase> *m_queue;          //��������
    QMutex mutex_;
	QTimer timer_;
};
