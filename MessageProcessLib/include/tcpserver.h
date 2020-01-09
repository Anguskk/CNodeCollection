#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QHash>

#include "tcpsocket.h"
#include "client.h"
#include "ascendMQ.h"
#include  "tcpserver.h"
#include "messagesnodedefinition.h"
#include "messagesdefinition.h"
//继承QTCPSERVER以实现多线程TCPscoket的服务器。
//如果socket的信息处理直接处理的话，很多新建的信号和槽是用不到的
class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0, int numConnections = 10000);
    ~TcpServer();
    void setMaxPendingConnections(int numConnections);//重写设置最大连接数函数
    void sent_group_messages(SMessageBase &message);
    void set_shelfInfos(QVector<ShelfInfo>& vshelfInfos);
    QVector<ShelfInfo> get_shelfInfos();
    SMessageBase get_firmware();
    void  set_firmware(SMessageBase &message);
    SMessageBase get_cache_mode();
    bool query_macClient(QString &mac, TcpSocket*  socket);
signals:
    //发送新用户连接信息
    void connectClient(const int, const QString &, const quint16);
    //发送获得用户发过来的数据
    void readData(const int, const QString &, quint16, const QByteArray &);
    //断开连接的用户信息
    void sockDisConnect(int, QString, quint16);
    void sentData(const QByteArray &, const int);//向scoket发送消息

    /**
     * \brief 断开特定连接，并释放资源，-1为断开所有
     *         自上向下的信号
     * \param i
     *
     */
    void sentDisConnect(int i);
    //触发socket的开始连接应答
    void startTcp();
    /**
     * \brief
     * \param message
     * \param shelfId
     * \param nodeId
     * //向scoket发送消息
     */
    void sent_group_messages_signal(SMessageBase &message);
    //void destoryThread();
public slots:
    //断开所有连接，线程计数器请0
    void clear();
    void enable_serverSlot();

protected slots:

    /**
     * \brief
     * \param handle
     * \param ip
     * \param port
     * \param th
     * Socket发出断开信号，TCPserver执行，自下而上
     *
     */
    void sockDisConnectSlot(int handle, const QString & ip, quint16 port, QString &mac, QThread *th);//断开连接的用户信息

protected:
    void incomingConnection(qintptr socketDescriptor) override;//覆盖已获取多线程
private:
    QHash<int, TcpSocket *> * tcpClient;//管理连接的map
    //由架子号查找逻辑Socket位置
    /**
     * \brief Hash表   MAC-->该socket是否已经存在
     */
    QHash<QString, TcpSocket *> *MacClient;

    QVector<ShelfInfo> m_vshelfInfos;
    int maxConnections;
    SMessageBase  firmware_message;
    SMessageBase  cache_message;

};

#endif // TCPSERVER_H
