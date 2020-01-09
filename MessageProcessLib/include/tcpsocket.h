#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <QTcpSocket>
#include <QQueue>
#include <QByteArray>
#include <QTime>
#include <QtCore/qobjectdefs.h>
#include <QtCore/qfuturewatcher.h>
#include "messageprocessthread.h"
#include <qtimer.h>
#include "messagesdefinition.h"
#include "messagesnodedefinition.h"
#include "client.h"

class QThread;
class TcpServer;
class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpSocket(qintptr socketDescriptor, QObject *parent = nullptr);
    void handleData(SMessageNodeBase& ori_message);
    void setShelfNode();
    void write_SMessageNodeBase(SMessageNodeBase& node_message);
	void parse_SMessageNodeBase(QByteArray &raw, SMessageNodeBase & node_message);
    void parse_SMessageNodeBase(QByteArray &raw, QVector<SMessageNodeBase> & node_message);
	QString getMacAddress(); 
    QTimer* get_timer();
    qintptr get_socketID() const;
    void setMACAddress(SMessageNodeBase& ori_message);
    void send_connection(SMessageBase& message);
    void set_server(TcpServer * server);
    void set_status(quint16 status);
    ~TcpSocket();

signals:
    //void readData(const int,const QString &,const quint16,const QByteArray &);
    //NOTE:断开连接的用户信息，此信号必须发出！线程管理类根据信号计数的

    void sockDisConnect(const int ,const QString &,const quint16, QString &, QThread *);
    void handle_done(SMessageBase& );

public slots:    
    void sent_instant_message_slot( SMessageBase& message);//发送信号的槽
    void disConTcp(int i);
    void readData();//接收数据

	void start_slot();

private:
    /**
     * \brief 常规消息转换 
     * \param message_base 
     * \return 
     */
     SMessageBase smessage_node_base2smessage_base(SMessageNodeBase& node_message);
     SMessageNodeBase smessage_base2smessage_node_base(SMessageBase& message_base);
     void  blocked_send_reiceive(SMessageBase& message);
private slots:
    void time_out_slot();
    void error_slot(QAbstractSocket::SocketError);
     
protected slots:
    
   // void startNext();//处理下一个
protected:
    
    
private:
    qintptr socketID;
    bool  heartbeat;
    quint16         response_flag;
    TcpServer     *tcp_server;
    int                shelfID;                  //架子号
    int                nodeID;                   //节点号
    QString            MacAddress;
    QMetaObject::Connection dis;
    QMetaObject::Connection read_signal;
    QQueue<QByteArray> messages;
    QTimer  * timer_=nullptr;
};


#endif // TCPSOCKET_H
