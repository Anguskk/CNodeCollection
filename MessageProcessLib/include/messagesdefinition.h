#pragma once

#include <QHostAddress>

//��ڵ�����Ϣ��ʽ
typedef struct _tagMessageBase
{
	unsigned short      type;                     //����
	int                 shelfID;                  //���Ӻ�
	int                 nodeID;                   //���Ӷ˿ں�
	QString             nodeName;                 //�ڵ�����
	unsigned int        length;                   //���ݳ���
	void*               data = nullptr;           //��Ϣ����
}SMessageBase;

typedef struct _tagConnectionStatusMsg
{
	char       type;             //0Ϊδ���ӣ�1���ӳɹ���2Ϊ���Ӵ���
}SConnectionStatusMsg;


typedef struct ShelfInfoOld
{
	QString     macAddress;//macû��-
	QString       ipAddress;//macû��
	int           shelfID;
}SShelfInfoOld;

typedef struct ShelfInfo
{
	QString       ipAddress;//macû��
	int           shelfID;
}SShelfInfo;

typedef struct NodeInfo
{
	QString     macAddress;//macû��-
	int         shelfID;
	int         nodeID;
}SNodeInfo;