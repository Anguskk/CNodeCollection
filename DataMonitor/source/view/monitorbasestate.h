/********************************************************************
Copyright (C), 2016, 电子科技大学.
FileName:    monitorbasestate.h
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

#include "graphicsviewstate.h"

#include <QObject>
#include <QVector>
#include <QMouseEvent>

class QAction;
class QMouseEvent;
class QKeyEvent;
class QWheelEvent;
class QFocusEvent;
class QContextMenuEvent;

class CMonitorWindow;

class CMonitorBaseStatePrivate;
class CMonitorBaseState:public CGraphicsViewState
{
    Q_OBJECT

public:
    /************************************************************************
    Function:       CMonitorBaseState()
    Description:    构造函数，初始化参数
    Input:          无
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
	CMonitorBaseState(CMonitorWindow *window,bool resumable = true);

    /************************************************************************
    Function:       ~CMonitorBaseState()
    Description:    析构函数，释放数据
    Input:          无
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    ~CMonitorBaseState();

    /************************************************************************
    Function:       contextMenuEvent()
    Description:    右键菜单事件
    Input:          event 右键菜单事件，widget 事件窗口
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
	virtual void contextMenuEvent(QContextMenuEvent *event) override;

	/************************************************************************
	Function:       resizeEvent()
	Description:    窗口大小改变事件
	Input:          event 窗口大小改变事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	virtual void resizeEvent(QResizeEvent * event) override;

public slots:
    /************************************************************************
    Function:       activateCurrentStateSlot()
    Description:    激活当前状态
    Input:          无
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    virtual void activateCurrentStateSlot() override;

	/************************************************************************
	Function:       resize()
	Description:    大小改变
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	virtual void resize() override;

private:
	/************************************************************************
	Function:       calculateSize()
	Description:    重新排列架子
	Input:          event 事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void calculateSize();

private:
	Q_DECLARE_PRIVATE(CMonitorBaseState);
	QScopedPointer<CMonitorBaseStatePrivate> d_ptr;
};
