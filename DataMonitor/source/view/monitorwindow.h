/********************************************************************
Copyright (C), 2016, 电子科技大学.
FileName:    monitorwindow.h
Author:      LYH
Version:     V1.0
Date:        2016/05/24
Description:             ///窗口基类
Other:                   ///无
Function List:           ///主要函数及其功能
History:                 ///历史修改记录
<author>    <time>    <version>     <desc>
********************************************************************/
#pragma once

#include <QMainWindow>
#include <QGraphicsView>

#include "messagesdefinition.h"

class CGraphicsView;
class CGraphicsViewState;
class CGraphicsItemManage;
class CMonitorMsgManage;

class CMonitorWindowPrivate;
class CMonitorWindow : public QMainWindow
{
    Q_OBJECT

public:
	/************************************************************************
	Function:       CMonitorWindow()
	Description:    构造函数，初始化参数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CMonitorWindow(QWidget *parent = 0);

	/************************************************************************
	Function:       ~CMonitorWindow()
	Description:    析构函数，释放数据
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
    ~CMonitorWindow();

	/************************************************************************
	Function:       getView()
	Description:    获取绘制View
	Input:          无
	Output:         无
	Return:         绘制View
	Others:         无
	************************************************************************/
	CGraphicsView *getView();

	/************************************************************************
	Function:       addShelf()
	Description:    添加架子
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void addShelf(const SShelfInfo &shelf);

	/************************************************************************
	Function:       deleteShelf()
	Description:    删除架子
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void deleteShelf(const int &shelfId);

	/************************************************************************
	Function:       getAllShelfIDs()
	Description:    获取所有架子号
	Input:          无
	Output:         无
	Return:         所有架子号
	Others:         无
	************************************************************************/
	QVector<int> getAllShelfIDs();

	/************************************************************************
	Function:       addViewState()
	Description:    添加state
	Input:          _state 操作state，_toolBarName toolbar名称，_toolBarArea toolbar位置
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void addViewState(CGraphicsViewState *_state, QString _toolBarName=QString(),
		Qt::ToolBarArea _toolBarArea = Qt::TopToolBarArea);

	/************************************************************************
	Function:       getStateFromName()
	Description:    通过名称获取state
	Input:          _name state名称
	Output:         无
	Return:         state
	Others:         无
	************************************************************************/
	CGraphicsViewState * getStateFromName(const QString &_name);

	/************************************************************************
	Function:       setActiveState()
	Description:    设置激活state
	Input:          _state 操作state
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void setActiveState(CGraphicsViewState *_state);

	/************************************************************************
	Function:       setActiveState()
	Description:    设置激活state
	Input:          _stateName 操作state名称
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void setActiveState(const QString &_stateName);

	/************************************************************************
	Function:       getActiveState()
	Description:    通过激活state
	Input:          无
	Output:         无
	Return:         state
	Others:         无
	************************************************************************/
	CGraphicsViewState * getActiveState();

	/************************************************************************
	Function:       setBaseState()
	Description:    设置基本state(默认状态)
	Input:          _state 操作state名称
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void setBaseState(CGraphicsViewState *_state);

	/************************************************************************
	Function:       getBaseState()
	Description:    通过基本state
	Input:          无
	Output:         无
	Return:         state
	Others:         无
	************************************************************************/
	CGraphicsViewState * getBaseState();

	/************************************************************************
	Function:       resetState()
	Description:    恢复基本state
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void resetState();

	/************************************************************************
	Function:       saveActivePublicState()
	Description:    保存激活state
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void saveActiveState();

	/************************************************************************
	Function:       restoreActiveState()
	Description:    恢复激活state
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CGraphicsViewState* restoreActiveState();

	/************************************************************************
	Function:       setViewFlag()
	Description:    设置view标志
	Input:          cursor 鼠标形状，mode 拖拽状态，allowed 
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void setViewFlag(const QCursor &cursor = Qt::ArrowCursor, QGraphicsView::DragMode mode = QGraphicsView::NoDrag, bool allowed = true);

	/************************************************************************
	Function:       getItemManage()
	Description:    获取数据管理
	Input:          无
	Output:         无
	Return:         数据管理
	Others:         无
	************************************************************************/
	CGraphicsItemManage* getItemManage();

	/************************************************************************
	Function:       setMonitorMsgManage()
	Description:    设置消息管理
	Input:          monitorMsgManage 数据管理
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void setMonitorMsgManage(CMonitorMsgManage *monitorMsgManage);

	/************************************************************************
	Function:       getMonitorMsgManage()
	Description:    获取消息管理
	Input:          无
	Output:         无
	Return:         数据管理
	Others:         无
	************************************************************************/
	CMonitorMsgManage *getMonitorMsgManage();

private:
	/************************************************************************
	Function:       initUI()
	Description:    初始化ui
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void initUI();

private:
	Q_DECLARE_PRIVATE(CMonitorWindow);
	QScopedPointer<CMonitorWindowPrivate> d_ptr;
};
