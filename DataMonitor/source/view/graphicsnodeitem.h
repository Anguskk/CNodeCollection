/********************************************************************
Copyright (C), 2016, 电子科技大学.
FileName:    graphicsnodeitem.h
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

//节点
typedef struct _tagNodeItemInfo
{
	int                 shelfID;                  //架子号
	int                 nodeID;                   //架子端口号
	QString             nodeName;                 //节点名称

	char                type             = 0;     //0为未连接，1连接成功，2为连接错误
}SNoteItemInfo;

class CGraphicsNodeItemPrivate;
class CGraphicsNodeItem : public QGraphicsObject
{
	Q_OBJECT
public:
	/************************************************************************
	Function:       CGraphicsNodeItem()
	Description:    构造函数
	Input:          width 宽度，height 高度，info 节点信息，parent 父object
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CGraphicsNodeItem(int width, int height, const SNoteItemInfo &info,QGraphicsItem * parent = nullptr);

	/************************************************************************
	Function:       ~CGraphicsNodeItem()
	Description:    析构函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	~CGraphicsNodeItem();

	/************************************************************************
	Function:       getNodeInfo()
	Description:    获取节点信息
	Input:          无
	Output:         无
	Return:         节点信息
	Others:         无
	************************************************************************/
	SNoteItemInfo getNodeInfo();

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
	Function:       clearData()
	Description:    清除数据（用于切换状态前）
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void clearData();

	/************************************************************************
	Function:       setName()
	Description:    设置节点名称
	Input:          name 节点名称
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void setName(QString name);

	/************************************************************************
	Function:       setNodeStatus()
	Description:    设置节点状态
	Input:          status 状态-0为未连接，1连接成功，2为连接错误
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void setStatus(char status);

	/************************************************************************
	Function:       getStatus()
	Description:    获取节点状态
	Input:          无
	Output:         无
	Return:         状态-0为未连接，1连接成功，2为连接错误
	Others:         无
	************************************************************************/
	char getStatus();

	/************************************************************************
	Function:       setCurType()
	Description:    设置当前类型
	Input:          type 状态类型
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void setCurType(int type);

	/************************************************************************
	Function:       setProgressRate()
	Description:    设置节点状态进度
	Input:          type 状态类型，progressRate 进度
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void setProgressRate(int type, int progressRate);

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
	Q_DECLARE_PRIVATE(CGraphicsNodeItem);
	QScopedPointer<CGraphicsNodeItemPrivate> d_ptr;
};
