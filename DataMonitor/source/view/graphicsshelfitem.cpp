/********************************************************************
Copyright (C), 2016, ���ӿƼ���ѧ.
FileName:    graphicsshelfitem.cpp
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
#include "graphicsshelfitem.h"

#include <QObject>
#include <QPainter>

#include "graphicsnodeitem.h"

//���ݱ�����
class CGraphicsShelfItemPrivate
{
	Q_DECLARE_PUBLIC(CGraphicsShelfItem)
public:
	/************************************************************************
	Function:       CGraphicsShelfItemPrivate()
	Description:    ���캯��
	Input:          info ������Ϣ��count �ڵ�����width ���ӿ�ȣ�height ���Ӹ߶ȣ������²����ָ߶�20pixel����parent ��object
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CGraphicsShelfItemPrivate(const SShelfInfo &info, int width, int height, CGraphicsShelfItem *parent);

	/************************************************************************
	Function:       ~CGraphicsShelfItemPrivate()
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	virtual ~CGraphicsShelfItemPrivate();

	/************************************************************************
	Function:       init()
	Description:    ��ʼ��
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void init(int count);

private:
	int                               m_width;               //���
	int                               m_height;              //�߶�
	int                               m_frameWidth   = 10;   //�߽���
	int                               m_spacing      = 10;   //���
	int                               m_textHeight   = 20;   //������Ϣ�߶�

	SShelfInfo                        m_info;                //������Ϣ
	QVector<CGraphicsNodeItem *>      m_allNodes;            //���нڵ�

	CGraphicsShelfItem *q_ptr;                               //��ָ��
};

/************************************************************************
Function:       CGraphicsShelfItemPrivate()
Description:    ���캯��
Input:          info ������Ϣ��count �ڵ�����width ���ӿ�ȣ�height ���Ӹ߶ȣ������²����ָ߶�20pixel����parent ��object
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CGraphicsShelfItemPrivate::CGraphicsShelfItemPrivate(const SShelfInfo &info, int width, int height, CGraphicsShelfItem *parent)
	:m_info(info),m_width(width),m_height(height), q_ptr(parent)
{
	
}

/************************************************************************
Function:       ~CGraphicsShelfItemPrivate()
Description:    ��������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CGraphicsShelfItemPrivate::~CGraphicsShelfItemPrivate()
{

}

/************************************************************************
Function:       init()
Description:    ��ʼ��
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CGraphicsShelfItemPrivate::init(int count)
{
	int t_countX = ceil(sqrt(count));
	int t_countY = ceil((double)count / t_countX);
	int t_sWidth = (m_width - m_frameWidth * 2 - (t_countX - 1)*m_spacing) / t_countX;
	int t_sHeight = (m_height - m_textHeight - m_frameWidth * 2 - (t_countY - 1)*m_spacing) / t_countY;
	//�����ڵ�
	for (int i = 0; i < count; ++i)
	{
		int t_curX = i%t_countX;
		int t_curY = i/t_countX;
		SNoteItemInfo t_info;
		t_info.shelfID = m_info.shelfID;
		t_info.nodeID = i;
		auto t_curNode = new CGraphicsNodeItem(t_sWidth, t_sHeight, t_info, q_ptr);
		/*if (i == count - 1){
			t_curNode->setStatus(2);
			t_curNode->setProgressRate(0, i * 6);
		}
		else if (i == count - 2) {
			t_curNode->setStatus(1);
			t_curNode->setProgressRate(0, 100);
		}
		else {
			t_curNode->setStatus(qrand() % 2);
			t_curNode->setProgressRate(0, i * 6);
		}*/
		t_curNode->setPos(QPointF(m_frameWidth + t_curX*(t_sWidth + m_spacing), m_frameWidth + t_curY*(t_sHeight + m_spacing)));
		m_allNodes.append(t_curNode);
	}
}

/************************************************************************
Function:       CGraphicsShelfItem()
Description:    ���캯��
Input:          info ������Ϣ��count �ڵ�����width ���ӿ�ȣ�height ���Ӹ߶ȣ������²����ָ߶�20pixel����parent ��object
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CGraphicsShelfItem::CGraphicsShelfItem(const SShelfInfo &info, int count, int width, int height, QGraphicsItem * parent/* = nullptr*/)
	: QGraphicsObject(parent),d_ptr(new CGraphicsShelfItemPrivate(info, width, height,this))
{
	Q_D(CGraphicsShelfItem);
	d->init(count);
}

/************************************************************************
Function:       ~CGraphicsShelfItem()
Description:    ��������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CGraphicsShelfItem::~CGraphicsShelfItem()
{
}

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
bool CGraphicsShelfItem::changeModeStatus()
{
	Q_D(const CGraphicsShelfItem);
	bool t_status = true;

	for (auto curItem: d->m_allNodes)
	{
		if (!curItem->changeModeStatus()){
			t_status = false;
			break;
		}
	}

	return t_status;
}

/************************************************************************
Function:       getShelfID()
Description:    ��ȡ���Ӻţ�<1��ЧID��
Input:          ��
Output:         ��
Return:         ���Ӻ�
Others:         ��
************************************************************************/
int CGraphicsShelfItem::getShelfID()
{
	Q_D(const CGraphicsShelfItem);
	return d->m_info.shelfID;
}

/************************************************************************
Function:       clearData()
Description:    ������ݣ������л�״̬ǰ������Ŵ�0��ʼ��
Input:          nodeID �ڵ���
Output:         ��
Return:         �Ƿ�ɹ�
Others:         ��
************************************************************************/
bool CGraphicsShelfItem::clearNodeData(int nodeID)
{
	Q_D(const CGraphicsShelfItem);
	bool t_flag = false;
	if (nodeID >= 0 && nodeID < d->m_allNodes.size()) {
		d->m_allNodes[nodeID]->clearData();
		t_flag = true;
	}

	return t_flag;
}

/************************************************************************
Function:       clearData()
Description:    ������ݣ������л�״̬ǰ)
Input:          ��
Output:         ��
Return:         �Ƿ�ɹ�
Others:         ��
************************************************************************/
bool CGraphicsShelfItem::clearAllData()
{
	Q_D(const CGraphicsShelfItem);
	bool t_flag = false;

	for (auto nodeItem: d->m_allNodes){
		nodeItem->clearData();
	}

	return t_flag;
}

/************************************************************************
Function:       setNodeStatus()
Description:    ���ýڵ�����
Input:          nodeID �ڵ��ţ�name ����
Output:         ��
Return:         �Ƿ�ɹ�
Others:         ��
************************************************************************/
bool CGraphicsShelfItem::setNodeName(int nodeID, QString name)
{
	Q_D(const CGraphicsShelfItem);
	bool t_flag = false;
	if (nodeID >= 0 && nodeID < d->m_allNodes.size()) {
		d->m_allNodes[nodeID]->setName(name);
		t_flag = true;
	}

	return t_flag;
}

/************************************************************************
Function:       setNodeStatus()
Description:    ���ýڵ�״̬����Ŵ�0��ʼ��
Input:          nodeID �ڵ��ţ�status ״̬-0Ϊδ���ӣ�1���ӳɹ���2Ϊ���Ӵ���
Output:         ��
Return:         �Ƿ�ɹ�
Others:         ��
************************************************************************/
bool CGraphicsShelfItem::setNodeStatus(int nodeID, char status)
{
	Q_D(const CGraphicsShelfItem);
	bool t_flag = false;
	if (nodeID >= 0 && nodeID < d->m_allNodes.size()) {
		d->m_allNodes[nodeID]->setStatus(status);
		t_flag = true;
	}

	return t_flag;
}

/************************************************************************
Function:       setProgressRate()
Description:    ���ýڵ�״̬����
Input:          nodeID �ڵ��ţ�type ״̬���ͣ�progressRate ����
Output:         ��
Return:         �Ƿ�ɹ�
Others:         ��
************************************************************************/
bool CGraphicsShelfItem::setNodeProgressRate(int nodeID, int type, int progressRate)
{
	Q_D(const CGraphicsShelfItem);
	bool t_flag = false;
	if (nodeID >= 0 && nodeID < d->m_allNodes.size()) {
		d->m_allNodes[nodeID]->setProgressRate(type, progressRate);
		t_flag = true;
	}

	return t_flag;
}

/************************************************************************
Function:       boundingRect()
Description:    ��ȡ���η�Χ
Input:          ��
Output:         ��
Return:         ���η�Χ
Others:         ��
************************************************************************/
QRectF CGraphicsShelfItem::boundingRect() const
{
	Q_D(const CGraphicsShelfItem);
	return QRectF(0, 0, d->m_width, d->m_height);
}

/************************************************************************
Function:       shape()
Description:    ��ȡshape��Χ
Input:          ��
Output:         ��
Return:         shape��Χ
Others:         ��
************************************************************************/
QPainterPath CGraphicsShelfItem::shape() const
{
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

/************************************************************************
Function:       paint()
Description:    ���ƺ���
Input:          painter �����࣬option ������Ϣ��widget ���ƴ���
Output:         ��
Return:         shape��Χ
Others:         ��
************************************************************************/
void CGraphicsShelfItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget /*= 0*/)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

	Q_D(CGraphicsShelfItem);
	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);
	QPen pen;
	pen.setWidthF(0.5);
	painter->setPen(pen);

	QRectF t_rect(0, 0, d->m_width, d->m_height - d->m_textHeight);
	painter->drawRoundedRect(t_rect,10,10);

	QRectF textRect(0, d->m_height - d->m_textHeight, d->m_width, d->m_textHeight);
	QString t_str = tr("Shelf_%1").arg(d->m_info.shelfID);
	painter->drawText(textRect,Qt::AlignCenter, t_str);
	painter->restore();
}
