/********************************************************************
Copyright (C), 2016, 电子科技大学.
FileName:    graphicsshelfitem.h
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
	Description:    构造函数
	Input:          info 架子信息，count 节点数，width 架子宽度，height 架子高度（包含下部文字高度20pixel），parent 父object
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CGraphicsShelfItem(const SShelfInfo &info,int count,int width, int height, QGraphicsItem * parent = nullptr);

	/************************************************************************
	Function:       ~CGraphicsShelfItem()
	Description:    析构函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	~CGraphicsShelfItem();

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
	bool changeModeStatus();

	/************************************************************************
	Function:       getShelfID()
	Description:    获取架子号（<1无效ID）
	Input:          无
	Output:         无
	Return:         架子号
	Others:         无
	************************************************************************/
	int getShelfID();

	/************************************************************************
	Function:       clearData()
	Description:    清除数据（用于切换状态前）（编号从0开始）
	Input:          nodeID 节点编号
	Output:         无
	Return:         是否成功
	Others:         无
	************************************************************************/
	bool clearNodeData(int nodeID);

	/************************************************************************
	Function:       clearData()
	Description:    清除数据（用于切换状态前
	Input:          无
	Output:         无
	Return:         是否成功
	Others:         无
	************************************************************************/
	bool clearAllData();

	/************************************************************************
	Function:       setNodeStatus()
	Description:    设置节点名称
	Input:          nodeID 节点编号，name 名称
	Output:         无
	Return:         是否成功
	Others:         无
	************************************************************************/
	bool setNodeName(int nodeID, QString name);

	/************************************************************************
	Function:       setNodeStatus()
	Description:    设置节点状态（编号从0开始）
	Input:          nodeID 节点编号，status 状态-0为未连接，1连接成功，2为连接错误
	Output:         无
	Return:         是否成功
	Others:         无
	************************************************************************/
	bool setNodeStatus(int nodeID, char status);

	/************************************************************************
	Function:       setProgressRate()
	Description:    设置节点状态进度
	Input:          nodeID 节点编号，type 状态类型，progressRate 进度
	Output:         无
	Return:         是否成功
	Others:         无
	************************************************************************/
	bool setNodeProgressRate(int nodeID, int type, int progressRate);

	/************************************************************************
	Function:       boundingRect()
	Description:    获取矩形范围
	Input:          无
	Output:         无
	Return:         矩形范围
	Others:         无
	************************************************************************/
	QRectF boundingRect() const override;

	/************************************************************************
	Function:       shape()
	Description:    获取shape范围
	Input:          无
	Output:         无
	Return:         shape范围
	Others:         无
	************************************************************************/
	QPainterPath shape() const override;

	/************************************************************************
	Function:       paint()
	Description:    绘制函数
	Input:          painter 绘制类，option 绘制信息，widget 绘制窗口
	Output:         无
	Return:         shape范围
	Others:         无
	************************************************************************/
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;

private:
	Q_DECLARE_PRIVATE(CGraphicsShelfItem);
	QScopedPointer<CGraphicsShelfItemPrivate> d_ptr;
};
