/********************************************************************
Copyright (C), 2016, ���ӿƼ���ѧ.
FileName:    graphicsshelfitem.h
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

#include "messagesdefinition.h"

class CGraphicsShelfItemPrivate;
class CGraphicsShelfItem : public QGraphicsObject
{
	Q_OBJECT
public:
	/************************************************************************
	Function:       CGraphicsShelfItem()
	Description:    ���캯��
	Input:          info ������Ϣ��count �ڵ�����width ���ӿ�ȣ�height ���Ӹ߶ȣ������²����ָ߶�20pixel����parent ��object
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CGraphicsShelfItem(const SShelfInfo &info,int count,int width, int height, QGraphicsItem * parent = nullptr);

	/************************************************************************
	Function:       ~CGraphicsShelfItem()
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	~CGraphicsShelfItem();

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
	Function:       getShelfID()
	Description:    ��ȡ���Ӻţ�<1��ЧID��
	Input:          ��
	Output:         ��
	Return:         ���Ӻ�
	Others:         ��
	************************************************************************/
	int getShelfID();

	/************************************************************************
	Function:       clearData()
	Description:    ������ݣ������л�״̬ǰ������Ŵ�0��ʼ��
	Input:          nodeID �ڵ���
	Output:         ��
	Return:         �Ƿ�ɹ�
	Others:         ��
	************************************************************************/
	bool clearNodeData(int nodeID);

	/************************************************************************
	Function:       clearData()
	Description:    ������ݣ������л�״̬ǰ
	Input:          ��
	Output:         ��
	Return:         �Ƿ�ɹ�
	Others:         ��
	************************************************************************/
	bool clearAllData();

	/************************************************************************
	Function:       setNodeStatus()
	Description:    ���ýڵ�����
	Input:          nodeID �ڵ��ţ�name ����
	Output:         ��
	Return:         �Ƿ�ɹ�
	Others:         ��
	************************************************************************/
	bool setNodeName(int nodeID, QString name);

	/************************************************************************
	Function:       setNodeStatus()
	Description:    ���ýڵ�״̬����Ŵ�0��ʼ��
	Input:          nodeID �ڵ��ţ�status ״̬-0Ϊδ���ӣ�1���ӳɹ���2Ϊ���Ӵ���
	Output:         ��
	Return:         �Ƿ�ɹ�
	Others:         ��
	************************************************************************/
	bool setNodeStatus(int nodeID, char status);

	/************************************************************************
	Function:       setProgressRate()
	Description:    ���ýڵ�״̬����
	Input:          nodeID �ڵ��ţ�type ״̬���ͣ�progressRate ����
	Output:         ��
	Return:         �Ƿ�ɹ�
	Others:         ��
	************************************************************************/
	bool setNodeProgressRate(int nodeID, int type, int progressRate);

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
	Q_DECLARE_PRIVATE(CGraphicsShelfItem);
	QScopedPointer<CGraphicsShelfItemPrivate> d_ptr;
};
