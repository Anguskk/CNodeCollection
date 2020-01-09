/********************************************************************
Copyright (C), 2016, 电子科技大学.
FileName:    graphicsshelfitem.cpp
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
#include "graphicsshelfitem.h"

#include <QObject>
#include <QPainter>

#include "graphicsnodeitem.h"

//数据保存类
class CGraphicsShelfItemPrivate
{
	Q_DECLARE_PUBLIC(CGraphicsShelfItem)
public:
	/************************************************************************
	Function:       CGraphicsShelfItemPrivate()
	Description:    构造函数
	Input:          info 架子信息，count 节点数，width 架子宽度，height 架子高度（包含下部文字高度20pixel），parent 父object
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CGraphicsShelfItemPrivate(const SShelfInfo &info, int width, int height, CGraphicsShelfItem *parent);

	/************************************************************************
	Function:       ~CGraphicsShelfItemPrivate()
	Description:    析构函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	virtual ~CGraphicsShelfItemPrivate();

	/************************************************************************
	Function:       init()
	Description:    初始化
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void init(int count);

private:
	int                               m_width;               //宽度
	int                               m_height;              //高度
	int                               m_frameWidth   = 10;   //边界宽度
	int                               m_spacing      = 10;   //间隔
	int                               m_textHeight   = 20;   //描述信息高度

	SShelfInfo                        m_info;                //架子信息
	QVector<CGraphicsNodeItem *>      m_allNodes;            //所有节点

	CGraphicsShelfItem *q_ptr;                               //父指针
};

/************************************************************************
Function:       CGraphicsShelfItemPrivate()
Description:    构造函数
Input:          info 架子信息，count 节点数，width 架子宽度，height 架子高度（包含下部文字高度20pixel），parent 父object
Output:         无
Return:         无
Others:         无
************************************************************************/
CGraphicsShelfItemPrivate::CGraphicsShelfItemPrivate(const SShelfInfo &info, int width, int height, CGraphicsShelfItem *parent)
	:m_info(info),m_width(width),m_height(height), q_ptr(parent)
{
	
}

/************************************************************************
Function:       ~CGraphicsShelfItemPrivate()
Description:    析构函数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CGraphicsShelfItemPrivate::~CGraphicsShelfItemPrivate()
{

}

/************************************************************************
Function:       init()
Description:    初始化
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsShelfItemPrivate::init(int count)
{
	int t_countX = ceil(sqrt(count));
	int t_countY = ceil((double)count / t_countX);
	int t_sWidth = (m_width - m_frameWidth * 2 - (t_countX - 1)*m_spacing) / t_countX;
	int t_sHeight = (m_height - m_textHeight - m_frameWidth * 2 - (t_countY - 1)*m_spacing) / t_countY;
	//创建节点
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
Description:    构造函数
Input:          info 架子信息，count 节点数，width 架子宽度，height 架子高度（包含下部文字高度20pixel），parent 父object
Output:         无
Return:         无
Others:         无
************************************************************************/
CGraphicsShelfItem::CGraphicsShelfItem(const SShelfInfo &info, int count, int width, int height, QGraphicsItem * parent/* = nullptr*/)
	: QGraphicsObject(parent),d_ptr(new CGraphicsShelfItemPrivate(info, width, height,this))
{
	Q_D(CGraphicsShelfItem);
	d->init(count);
}

/************************************************************************
Function:       ~CGraphicsShelfItem()
Description:    析构函数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CGraphicsShelfItem::~CGraphicsShelfItem()
{
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
Description:    获取架子号（<1无效ID）
Input:          无
Output:         无
Return:         架子号
Others:         无
************************************************************************/
int CGraphicsShelfItem::getShelfID()
{
	Q_D(const CGraphicsShelfItem);
	return d->m_info.shelfID;
}

/************************************************************************
Function:       clearData()
Description:    清除数据（用于切换状态前）（编号从0开始）
Input:          nodeID 节点编号
Output:         无
Return:         是否成功
Others:         无
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
Description:    清除数据（用于切换状态前)
Input:          无
Output:         无
Return:         是否成功
Others:         无
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
Description:    设置节点名称
Input:          nodeID 节点编号，name 名称
Output:         无
Return:         是否成功
Others:         无
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
Description:    设置节点状态（编号从0开始）
Input:          nodeID 节点编号，status 状态-0为未连接，1连接成功，2为连接错误
Output:         无
Return:         是否成功
Others:         无
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
Description:    设置节点状态进度
Input:          nodeID 节点编号，type 状态类型，progressRate 进度
Output:         无
Return:         是否成功
Others:         无
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
Description:    获取矩形范围
Input:          无
Output:         无
Return:         矩形范围
Others:         无
************************************************************************/
QRectF CGraphicsShelfItem::boundingRect() const
{
	Q_D(const CGraphicsShelfItem);
	return QRectF(0, 0, d->m_width, d->m_height);
}

/************************************************************************
Function:       shape()
Description:    获取shape范围
Input:          无
Output:         无
Return:         shape范围
Others:         无
************************************************************************/
QPainterPath CGraphicsShelfItem::shape() const
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
