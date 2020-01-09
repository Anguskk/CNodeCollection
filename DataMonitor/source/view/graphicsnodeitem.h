/********************************************************************
Copyright (C), 2016, ���ӿƼ���ѧ.
FileName:    graphicsnodeitem.h
Author:      LYH
Version:     V1.0
Date:        2019/05/24
Description:             ///ģ������
���ļ���Ҫ�����Ա�����ϵ����������.
Other:                   ///����������
Function List:           ///��Ҫ�������书��
History:                 ///��ʷ�޸ļ�¼
<author>    <time>    <version>     <desc>
********************************************************************/
#pragma once

#include <QGraphicsObject>

//�ڵ�
typedef struct _tagNodeItemInfo
{
	int                 shelfID;                  //���Ӻ�
	int                 nodeID;                   //���Ӷ˿ں�
	QString             nodeName;                 //�ڵ�����

	char                type             = 0;     //0Ϊδ���ӣ�1���ӳɹ���2Ϊ���Ӵ���
}SNoteItemInfo;

class CGraphicsNodeItemPrivate;
class CGraphicsNodeItem : public QGraphicsObject
{
	Q_OBJECT
public:
	/************************************************************************
	Function:       CGraphicsNodeItem()
	Description:    ���캯��
	Input:          width ��ȣ�height �߶ȣ�info �ڵ���Ϣ��parent ��object
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CGraphicsNodeItem(int width, int height, const SNoteItemInfo &info,QGraphicsItem * parent = nullptr);

	/************************************************************************
	Function:       ~CGraphicsNodeItem()
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	~CGraphicsNodeItem();

	/************************************************************************
	Function:       getNodeInfo()
	Description:    ��ȡ�ڵ���Ϣ
	Input:          ��
	Output:         ��
	Return:         �ڵ���Ϣ
	Others:         ��
	************************************************************************/
	SNoteItemInfo getNodeInfo();

	/************************************************************************
	Function:       changeModeStatus()
	Description:    �л�ģʽ״̬
					true--���нڵ�����ɻ��߶Ͽ����ӣ�
					false--�������ڽ��еĽڵ�
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	bool changeModeStatus();

	/************************************************************************
	Function:       clearData()
	Description:    ������ݣ������л�״̬ǰ��
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void clearData();

	/************************************************************************
	Function:       setName()
	Description:    ���ýڵ�����
	Input:          name �ڵ�����
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void setName(QString name);

	/************************************************************************
	Function:       setNodeStatus()
	Description:    ���ýڵ�״̬
	Input:          status ״̬-0Ϊδ���ӣ�1���ӳɹ���2Ϊ���Ӵ���
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void setStatus(char status);

	/************************************************************************
	Function:       getStatus()
	Description:    ��ȡ�ڵ�״̬
	Input:          ��
	Output:         ��
	Return:         ״̬-0Ϊδ���ӣ�1���ӳɹ���2Ϊ���Ӵ���
	Others:         ��
	************************************************************************/
	char getStatus();

	/************************************************************************
	Function:       setCurType()
	Description:    ���õ�ǰ����
	Input:          type ״̬����
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void setCurType(int type);

	/************************************************************************
	Function:       setProgressRate()
	Description:    ���ýڵ�״̬����
	Input:          type ״̬���ͣ�progressRate ����
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void setProgressRate(int type, int progressRate);

	/************************************************************************
	Function:       boundingRect()
	Description:    ��ȡ���η�Χ
	Input:          ��
	Output:         ��
	Return:         ���η�Χ
	Others:         ��
	************************************************************************/
	QRectF boundingRect() const override;

	/************************************************************************
	Function:       shape()
	Description:    ��ȡshape��Χ
	Input:          ��
	Output:         ��
	Return:         shape��Χ
	Others:         ��
	************************************************************************/
	QPainterPath shape() const override;

	/************************************************************************
	Function:       paint()
	Description:    ���ƺ���
	Input:          painter �����࣬option ������Ϣ��widget ���ƴ���
	Output:         ��
	Return:         shape��Χ
	Others:         ��
	************************************************************************/
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;

private:
	Q_DECLARE_PRIVATE(CGraphicsNodeItem);
	QScopedPointer<CGraphicsNodeItemPrivate> d_ptr;
};
