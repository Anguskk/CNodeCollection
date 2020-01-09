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
	//TODO   ��AscendMQ�ϴ�����Ϣ�����ݵ�manage��   ���Կ��ǼӶ�ʱ�����Ƿ���Ҫ����
	CMessageProcessThread(QObject *parent = nullptr);
	~CMessageProcessThread();
	void set_TCPserver(TcpServer * server);
	void set_Manage(CMessageProcessManage * manage);
    void set_ascendq();
	void stopThread();
	void run() override;
	
private:
	bool isThreadOpen;
    CMessageProcessManage* manage;
	TcpServer  *server_;
    AscendMQ  * ascend_mq_;
	//QQueue<SMessageNodeBase> messageQueue;
	QMutex mutex_;
	QTimer timer_;
};
