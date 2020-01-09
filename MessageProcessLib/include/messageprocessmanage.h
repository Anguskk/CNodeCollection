#pragma once

#include <QObject>
#include "messageprocesslib_global.h"
#include "messageprocessthread.h"
#include "ascendMQ.h"
#include "descendMQ.h"
#include "messagesnodedefinition.h"
#include <QtCore/QObject>

class TcpServer;

class MESSAGEPROCESSLIB_EXPORT CMessageProcessManage :public QObject
{
	Q_OBJECT
signals:
	void enable_server();
	void shutdown_signal();
	//void ConsumeAMessageSignal(int i);
public slots:
	void send_message_test_slot();
	
public:
	CMessageProcessManage(QObject *parent);
	~CMessageProcessManage();

	void start(QVector<ShelfInfo> &vshelfs);
	void shutdown() const;	

	CMessageProcessThread * get_process_thread() const;

	/**
	 * \brief 
	 * \param message 
	 * \param shelf  架子号  -1代表所有架子
	 * \param node 节点号   -1代表所有节点
	 */
	void append_deliver_message(SMessageBase &message) const;	
    
private:
	char  pdata[1000];
	QMutex  mutex_;
	TcpServer *tcpServer;
	AscendMQ  *ascend_mq;
	DescendMQ *descend_mq;
	QTimer _timer_;
	QTimer _timer_2;	
	CMessageProcessThread *message_deliver_thread;
};
