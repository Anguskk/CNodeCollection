/**************************************************************
Copyright (C),  2016   电子科技大学.
FileName :  monitormsgmanage.h
Author :       lz
Version : V1.0
Date : 2016/8/30
Description :        ///模块描述 
Other :              ///其他描述
Function List :      ///主要函数及其功能
History :            ///历史修改记录
<Author>    <Time>    <Version>    <Desc>
**************************************************************/
#pragma once

#include <QObject>

#include "messagesdefinition.h"

class QDockWidget;
class CMonitorWindow;

class CMonitorMsgManagePrivate;
class CMonitorMsgManage : public QObject
{
	Q_OBJECT

public:
	/************************************************************************
	Function:       CMonitorMsgManage()
	Description:    构造函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CMonitorMsgManage(CMonitorWindow *window, QDockWidget *infoBoardDock,QDockWidget *nodeInfoDock);

	/************************************************************************
	Function:       ~CMonitorMsgManage()
	Description:    析构函数，释放数据
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	~CMonitorMsgManage();

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
	Function:       currentModeStatus()
	Description:    当前模式状态
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	unsigned short currentModeStatus();

	/************************************************************************
	Function:       addMessage()
	Description:    添加消息
	Input:          message 消息
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void addMessage(SMessageBase &message);

public slots:
	/************************************************************************
	Function:       changeModeTypeSlot()
	Description:    切换模式（其中充电状态可以随时切换到其他状态）
	Input:          type 模式
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void changeModeTypeSlot(unsigned short type, QVector<QPair<int, QString> > shelfIDs);

	/************************************************************************
	Function:       changeModeSlot()
	Description:    切换模式
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void changeModeSlot();

	/************************************************************************
	Function:       processMsgSlot()
	Description:    处理消息
	Input:          message 消息
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void processMsgSlot(const SMessageBase& message);

private:
	Q_DECLARE_PRIVATE(CMonitorMsgManage);
	QScopedPointer<CMonitorMsgManagePrivate> d_ptr;
};
