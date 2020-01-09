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
 * \brief 消息辅助处理线程
 *	      
 */
class MESSAGEPROCESSLIB_EXPORT CMessageProcessThread : public QThread
{
	Q_OBJECT

signals:
    void send_statusinfo(const SMessageBase& message);

public:
	//TODO   把AscendMQ上传的消息，传递到manage中   可以考虑加定时器，是否需要加锁
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
