/********************************************************************
Copyright (C), 2016, 电子科技大学.
FileName:    graphicsnodeitem.cpp
Author:      LYH
Version:     V1.0
Date:        2019/05/24
Description:             ///模块描述
该文件主要负责成员及类关系的声明或定义.
Other:                   ///其他的描述
Function List:           ///主要函数及其功能
History:                 ///历史修改记录
<author>    <time>    <version>     <desc>
********************************************************************/
#include "graphicsnodeitem.h"

#include <QObject>
#include <QPainter>

//数据保存类
class CGraphicsNodeItemPrivate
{
	Q_DECLARE_PUBLIC(CGraphicsNodeItem)
public:
	/************************************************************************
	Function:       CGraphicsNodeItem()
	Description:    构造函数
	Input:          width 宽度，height 高度，info 节点信息，parent 父object
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CGraphicsNodeItemPrivate(int width, int height, const SNoteItemInfo &info, CGraphicsNodeItem *parent);

	/************************************************************************
	Function:       ~CGraphicsNodeItemPrivate()
	Description:    析构函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	virtual ~CGraphicsNodeItemPrivate();

	/************************************************************************
	Function:       updateTooTip()
	Description:    更新TooTip
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void updateTooTip();

private:
	int m_width;                                                          //宽度
	int m_height;                                                         //高度

	SNoteItemInfo                 m_info;                                 //类型-灰色为未连接，白色为连接，红色出错，绿色为操作成功             
	QVector<QColor>               m_allStateColor;                        //颜色
	int                           m_curType              = 0;             //当前类型
	QMap<int, int>                m_progressRate;                         //当前状态-第一个代表类型，第二个代表进度（0~100）

	CGraphicsNodeItem *q_ptr;                                             //父指针
};

/************************************************************************
Function:       CGraphicsNodeItem()
Description:    构造函数
Input:          width 宽度，height 高度，info 节点信息，parent 父object
Output:         无
Return:         无
Others:         无
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
Description:    析构函数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CGraphicsNodeItemPrivate::~CGraphicsNodeItemPrivate()
{

}

/************************************************************************
Function:       updateTooTip()
Description:    更新TooTip
Input:          无
Output:         无
Return:         无
Others:         无
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
Description:    构造函数
Input:          width 宽度，height 高度，info 节点信息，parent 父object
Output:         无
Return:         无
Others:         无
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
Description:    析构函数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CGraphicsNodeItem::~CGraphicsNodeItem()
{
}

/************************************************************************
Function:       getNodeInfo()
Description:    获取节点信息
Input:          无
Output:         无
Return:         节点信息
Others:         无
************************************************************************/
SNoteItemInfo CGraphicsNodeItem::getNodeInfo()
{
	Q_D(CGraphicsNodeItem);
	return d->m_info;
}

/************************************************************************
Function:       changeModeStatus()
Description:    切换模式状态
				true--所有节点已完成或者断开连接，
				false--存在正在进行的节点
Input:          无
Output:         无
Return:         无
Others:         无
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
Description:    清除数据（用于切换状态前）
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsNodeItem::clearData()
{
	Q_D(CGraphicsNodeItem);
	d->m_progressRate.clear();
}

/************************************************************************
Function:       setName()
Description:    设置节点名称
Input:          name 节点名称
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsNodeItem::setName(QString name)
{
	Q_D(CGraphicsNodeItem);
	d->m_info.nodeName = name;
	d->updateTooTip();
}

/************************************************************************
Function:       setNodeStatus()
Description:    设置节点状态
Input:          status 状态-0为未连接，1连接成功，2为连接错误
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsNodeItem::setStatus(char status)
{
	Q_D(CGraphicsNodeItem);
	d->m_info.type = status;
	//断开连接删除节点名称
	if (status == 0)
		d->m_info.nodeName.clear();
	d->updateTooTip();
}

/************************************************************************
Function:       getStatus()
Description:    获取节点状态
Input:          无
Output:         无
Return:         状态-0为未连接，1连接成功，2为连接错误
Others:         无
************************************************************************/
char CGraphicsNodeItem::getStatus()
{
	Q_D(CGraphicsNodeItem);
	return d->m_info.type;
}

/************************************************************************
Function:       setCurType()
Description:    设置当前类型
Input:          type 状态类型
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsNodeItem::setCurType(int type)
{
	Q_D(CGraphicsNodeItem);
	d->m_curType = type;
	d->updateTooTip();
}

/************************************************************************
Function:       setProgressRate()
Description:    设置节点状态进度
Input:          type 状态类型，progressRate 进度
Output:         无
Return:         是否成功
Others:         无
************************************************************************/
void CGraphicsNodeItem::setProgressRate(int type, int progressRate)
{
	Q_D(CGraphicsNodeItem);
	d->m_progressRate[type] = progressRate;
	update();
}

/************************************************************************
Function:       boundingRect()
Description:    获取矩形范围
Input:          无
Output:         无
Return:         矩形范围
Others:         无
************************************************************************/
QRectF CGraphicsNodeItem::boundingRect() const
{
	return QRectF(0, 0, d_ptr->m_width, d_ptr->m_height);
}

/************************************************************************
Function:       shape()
Description:    获取shape范围
Input:          无
Output:         无
Return:         shape范围
Others:         无
************************************************************************/
QPainterPath CGraphicsNodeItem::shape() const
{
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

/************************************************************************
Function:       paint()
Description:    绘制函数
Input:          painter 绘制类，option 绘制信息，widget 绘制窗口
Output:         无
Return:         shape范围
Others:         无
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

	//绘制状态信息
	if (d->m_info.type > 0 && d->m_info.type < d->m_allStateColor.size()) {
		//绘制百分比
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
		//错误信息
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
	
	//绘制边界
	painter->save();
	painter->setPen(QPen());
	painter->setBrush(Qt::NoBrush);
	painter->drawEllipse(t_rect.center(), d_ptr->m_width / 2, d_ptr->m_height / 2);
	painter->restore();

	painter->restore();
}
