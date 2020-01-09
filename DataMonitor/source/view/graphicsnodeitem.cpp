/********************************************************************
Copyright (C), 2016, ���ӿƼ���ѧ.
FileName:    graphicsnodeitem.cpp
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
#include "graphicsnodeitem.h"

#include <QObject>
#include <QPainter>

//���ݱ�����
class CGraphicsNodeItemPrivate
{
	Q_DECLARE_PUBLIC(CGraphicsNodeItem)
public:
	/************************************************************************
	Function:       CGraphicsNodeItem()
	Description:    ���캯��
	Input:          width ��ȣ�height �߶ȣ�info �ڵ���Ϣ��parent ��object
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CGraphicsNodeItemPrivate(int width, int height, const SNoteItemInfo &info, CGraphicsNodeItem *parent);

	/************************************************************************
	Function:       ~CGraphicsNodeItemPrivate()
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	virtual ~CGraphicsNodeItemPrivate();

	/************************************************************************
	Function:       updateTooTip()
	Description:    ����TooTip
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void updateTooTip();

private:
	int m_width;                                                          //���
	int m_height;                                                         //�߶�

	SNoteItemInfo                 m_info;                                 //����-��ɫΪδ���ӣ���ɫΪ���ӣ���ɫ������ɫΪ�����ɹ�             
	QVector<QColor>               m_allStateColor;                        //��ɫ
	int                           m_curType              = 0;             //��ǰ����
	QMap<int, int>                m_progressRate;                         //��ǰ״̬-��һ���������ͣ��ڶ���������ȣ�0~100��

	CGraphicsNodeItem *q_ptr;                                             //��ָ��
};

/************************************************************************
Function:       CGraphicsNodeItem()
Description:    ���캯��
Input:          width ��ȣ�height �߶ȣ�info �ڵ���Ϣ��parent ��object
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CGraphicsNodeItemPrivate::CGraphicsNodeItemPrivate(int width, int height, const SNoteItemInfo &info, CGraphicsNodeItem *parent)
	:m_width(width),m_height(height), m_info(info), q_ptr(parent)
{
	m_allStateColor.append(Qt::lightGray);
	m_allStateColor.append(Qt::white);
	m_allStateColor.append(Qt::red);
	m_allStateColor.append(Qt::green);
}

/************************************************************************
Function:       ~CGraphicsNodeItemPrivate()
Description:    ��������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CGraphicsNodeItemPrivate::~CGraphicsNodeItemPrivate()
{

}

/************************************************************************
Function:       updateTooTip()
Description:    ����TooTip
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CGraphicsNodeItemPrivate::updateTooTip()
{
	Q_Q(CGraphicsNodeItem);

	QString t_statusStr;
	if (m_info.type == 1)
		t_statusStr = CGraphicsNodeItem::tr("Connected");
	else if (m_info.type == 2)
		t_statusStr = CGraphicsNodeItem::tr("Error");
	else
		t_statusStr = CGraphicsNodeItem::tr("Disconnected");

	QString tooTipStr = CGraphicsNodeItem::tr("Node ID:%1\nShelft ID:%2\nStatus:%3").arg(m_info.nodeID+1).arg(m_info.shelfID).arg(t_statusStr);

	q->setToolTip(tooTipStr);
	q->update();
}

/************************************************************************
Function:       CGraphicsNodeItem()
Description:    ���캯��
Input:          width ��ȣ�height �߶ȣ�info �ڵ���Ϣ��parent ��object
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CGraphicsNodeItem::CGraphicsNodeItem(int width, int height, const SNoteItemInfo &info, QGraphicsItem * parent/* = nullptr*/)
	: QGraphicsObject(parent),d_ptr(new CGraphicsNodeItemPrivate(width, height, info,this))
{
	Q_D(CGraphicsNodeItem);
	setAcceptHoverEvents(true);
	d->updateTooTip();
}

/************************************************************************
Function:       ~CGraphicsNodeItem()
Description:    ��������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CGraphicsNodeItem::~CGraphicsNodeItem()
{
}

/************************************************************************
Function:       getNodeInfo()
Description:    ��ȡ�ڵ���Ϣ
Input:          ��
Output:         ��
Return:         �ڵ���Ϣ
Others:         ��
************************************************************************/
SNoteItemInfo CGraphicsNodeItem::getNodeInfo()
{
	Q_D(CGraphicsNodeItem);
	return d->m_info;
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
bool CGraphicsNodeItem::changeModeStatus()
{
	Q_D(CGraphicsNodeItem);
	bool t_status = true;

	if (d->m_info.type == 1){
		if (!d->m_progressRate.isEmpty() && d->m_progressRate[d->m_curType] != 100)
			t_status = false;
	}

	return t_status;
}

/************************************************************************
Function:       clearData()
Description:    ������ݣ������л�״̬ǰ��
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CGraphicsNodeItem::clearData()
{
	Q_D(CGraphicsNodeItem);
	d->m_progressRate.clear();
}

/************************************************************************
Function:       setName()
Description:    ���ýڵ�����
Input:          name �ڵ�����
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CGraphicsNodeItem::setName(QString name)
{
	Q_D(CGraphicsNodeItem);
	d->m_info.nodeName = name;
	d->updateTooTip();
}

/************************************************************************
Function:       setNodeStatus()
Description:    ���ýڵ�״̬
Input:          status ״̬-0Ϊδ���ӣ�1���ӳɹ���2Ϊ���Ӵ���
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CGraphicsNodeItem::setStatus(char status)
{
	Q_D(CGraphicsNodeItem);
	d->m_info.type = status;
	//�Ͽ�����ɾ���ڵ�����
	if (status == 0)
		d->m_info.nodeName.clear();
	d->updateTooTip();
}

/************************************************************************
Function:       getStatus()
Description:    ��ȡ�ڵ�״̬
Input:          ��
Output:         ��
Return:         ״̬-0Ϊδ���ӣ�1���ӳɹ���2Ϊ���Ӵ���
Others:         ��
************************************************************************/
char CGraphicsNodeItem::getStatus()
{
	Q_D(CGraphicsNodeItem);
	return d->m_info.type;
}

/************************************************************************
Function:       setCurType()
Description:    ���õ�ǰ����
Input:          type ״̬����
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CGraphicsNodeItem::setCurType(int type)
{
	Q_D(CGraphicsNodeItem);
	d->m_curType = type;
	d->updateTooTip();
}

/************************************************************************
Function:       setProgressRate()
Description:    ���ýڵ�״̬����
Input:          type ״̬���ͣ�progressRate ����
Output:         ��
Return:         �Ƿ�ɹ�
Others:         ��
************************************************************************/
void CGraphicsNodeItem::setProgressRate(int type, int progressRate)
{
	Q_D(CGraphicsNodeItem);
	d->m_progressRate[type] = progressRate;
	update();
}

/************************************************************************
Function:       boundingRect()
Description:    ��ȡ���η�Χ
Input:          ��
Output:         ��
Return:         ���η�Χ
Others:         ��
************************************************************************/
QRectF CGraphicsNodeItem::boundingRect() const
{
	return QRectF(0, 0, d_ptr->m_width, d_ptr->m_height);
}

/************************************************************************
Function:       shape()
Description:    ��ȡshape��Χ
Input:          ��
Output:         ��
Return:         shape��Χ
Others:         ��
************************************************************************/
QPainterPath CGraphicsNodeItem::shape() const
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
void CGraphicsNodeItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget /*= 0*/)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

	Q_D(CGraphicsNodeItem);

	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setRenderHint(QPainter::HighQualityAntialiasing);

	QColor fillColor = d->m_allStateColor.first();
	if (d->m_info.type >= 0 && d->m_info.type < d->m_allStateColor.size())
		fillColor = d->m_allStateColor[d->m_info.type];

	painter->save();
	painter->setPen(Qt::NoPen);
	painter->setBrush(fillColor);
	QRectF t_rect(0, 0, d_ptr->m_width, d_ptr->m_height);
	painter->drawEllipse(t_rect.center(), d_ptr->m_width / 2, d_ptr->m_height / 2);
	painter->restore();

	//����״̬��Ϣ
	if (d->m_info.type > 0 && d->m_info.type < d->m_allStateColor.size()) {
		//���ưٷֱ�
		if (d->m_progressRate.contains(d->m_curType))
		{
			painter->save();
			painter->setPen(Qt::NoPen);
			painter->setBrush(QColor("#F5F579"));
			if (d->m_progressRate[d->m_curType] == 100)
				painter->setBrush(Qt::green);

			int t_curRate = d->m_progressRate[d->m_curType] / 100.0 * 360;
			painter->drawPie(t_rect, 90 * 16, -t_curRate* 16);
			painter->restore();

			painter->save();
			QFont font;
			font.setPointSize(15);
			painter->setFont(font);
			painter->drawText(t_rect,Qt::AlignCenter,QString("%1").arg(d->m_progressRate[d->m_curType])+"%");
			painter->restore();
		}
		//������Ϣ
		if (d->m_info.type == 2)
		{
			painter->save();
			painter->setPen(Qt::NoPen);
			QColor t_errorClor(Qt::red);
			painter->setBrush(t_errorClor);
			painter->drawEllipse(t_rect.center(), d_ptr->m_width / 2, d_ptr->m_height / 2);
			painter->restore();

			painter->save();
			QFont font;
			font.setPointSize(15);
			painter->setFont(font);
			painter->drawText(t_rect, Qt::AlignCenter, QString("%1").arg(d->m_progressRate[d->m_curType]) + "%");
			painter->restore();
		}
	}
	
	//���Ʊ߽�
	painter->save();
	painter->setPen(QPen());
	painter->setBrush(Qt::NoBrush);
	painter->drawEllipse(t_rect.center(), d_ptr->m_width / 2, d_ptr->m_height / 2);
	painter->restore();

	painter->restore();
}
