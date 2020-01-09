#pragma once

#include <QHostAddress>

//与节点仪消息格式
typedef struct _tagMessageBase
{
	unsigned short      type;                     //类型
	int                 shelfID;                  //架子号
	int                 nodeID;                   //架子端口号
	QString             nodeName;                 //节点名称
	unsigned int        length;                   //数据长度
	void*               data = nullptr;           //消息内容
}SMessageBase;

typedef struct _tagConnectionStatusMsg
{
	char       type;             //0为未连接，1连接成功，2为连接错误
}SConnectionStatusMsg;


typedef struct ShelfInfoOld
{
	QString     macAddress;//mac没有-
	QString       ipAddress;//mac没有
	int           shelfID;
}SShelfInfoOld;

typedef struct ShelfInfo
{
	QString       ipAddress;//mac没有
	int           shelfID;
}SShelfInfo;

typedef struct NodeInfo
{
	QString     macAddress;//mac没有-
	int         shelfID;
	int         nodeID;
}SNodeInfo;