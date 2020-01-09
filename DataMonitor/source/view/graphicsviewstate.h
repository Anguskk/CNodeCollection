/********************************************************************
Copyright (C), 2016, 电子科技大学.
FileName:    graphicsviewstate.h
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

class CGraphicsViewStatePrivate;
class CGraphicsViewState:public QObject
{
    Q_OBJECT

public:
    /************************************************************************
    Function:       CGraphicsViewState()
    Description:    构造函数，初始化参数
    Input:          无
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
	CGraphicsViewState(CMonitorWindow *window,bool resumable = true);

    /************************************************************************
    Function:       ~CGraphicsViewState()
    Description:    析构函数，释放数据
    Input:          无
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    ~CGraphicsViewState();

	/************************************************************************
	Function:       getName()
	Description:    获取名称
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	QString getName();

    /************************************************************************
    Function:       initialize()
    Description:    初始化
    Input:          无
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    virtual void initialize(){}

    /************************************************************************
    Function:       getAction()
    Description:    获取当前操作按钮
    Input:          无
    Output:         无
    Return:         当前操作按钮
    Others:         无
    ************************************************************************/
	QAction *getAction();

    /************************************************************************
    Function:       trigger()
    Description:    激活当前按钮
    Input:          无
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    void trigger();

    /************************************************************************
    Function:       getResumable()
    Description:    获取状态是否可恢复
    Input:          无
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
	bool getResumable();

    /************************************************************************
    Function:       setInitFlag()
    Description:    设置是否清除状态
    Input:          _initFlag 清除状态
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
	void setInitFlag(bool _initFlag);

    /************************************************************************
    Function:       getInitFlag()
    Description:    获取是否清除状态
    Input:          无
    Output:         无
    Return:         清除状态
    Others:         无
    ************************************************************************/
	bool getInitFlag();

    /************************************************************************
    Function:       setWindow()
    Description:    设置主窗口
    Input:          _window 主窗口
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    void setWindow(CMonitorWindow *_window);

	/************************************************************************
	Function:       getWindow()
	Description:    获取主窗口
	Input:          无
	Output:         无
	Return:         主窗口
	Others:         无
	************************************************************************/
	CMonitorWindow *getWindow();

    /************************************************************************
    Function:       linkProcess()
    Description:    联动时将所有窗口联动处理
    Input:          无
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    virtual void linkProcess(){}

    /************************************************************************
    Function:       mousePressEvent()
    Description:    鼠标按下事件
    Input:          event 鼠标事件，widget 事件窗口
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    virtual void mousePressEvent(QMouseEvent *event){}

    /************************************************************************
    Function:       mouseReleaseEvent()
    Description:    鼠标释放事件
    Input:          event 鼠标事件，widget 事件窗口
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    virtual void mouseReleaseEvent(QMouseEvent *event){}

    /************************************************************************
    Function:       mouseDoubleClickEvent()
    Description:    鼠标双击事件
    Input:          event 鼠标事件，widget 事件窗口
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    virtual void mouseDoubleClickEvent(QMouseEvent *event){}

    /************************************************************************
    Function:       mouseMoveEvent()
    Description:    鼠标移动事件
    Input:          event 鼠标事件，widget 事件窗口
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    virtual void mouseMoveEvent(QMouseEvent *event){}

#ifndef QT_NO_WHEELEVENT
    /************************************************************************
    Function:       wheelEvent()
    Description:    鼠标滚轮事件
    Input:          event 滚轮事件，widget 事件窗口
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    virtual void wheelEvent(QWheelEvent *event);
#endif

    /************************************************************************
    Function:       keyPressEvent()
    Description:    键盘按下事件
    Input:          event 键盘事件，widget 事件窗口
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
	virtual void keyPressEvent(QKeyEvent *event);

    /************************************************************************
    Function:       keyReleaseEvent()
    Description:    键盘释放事件
    Input:          event 键盘事件，widget 事件窗口
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    virtual void keyReleaseEvent(QKeyEvent *event){}

    /************************************************************************
    Function:       focusInEvent()
    Description:    焦点进入事件
    Input:          event 焦点事件，widget 事件窗口
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    virtual void focusInEvent(QFocusEvent *event){}

    /************************************************************************
    Function:       focusOutEvent()
    Description:    焦点离开事件
    Input:          event 焦点事件，widget 事件窗口
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    virtual void focusOutEvent(QFocusEvent *event){}

    /************************************************************************
    Function:       enterEvent()
    Description:    进入事件
    Input:          event 事件，widget 事件窗口
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    virtual void enterEvent(QEvent *event){}

    /************************************************************************
    Function:       leaveEvent()
    Description:    离开事件
    Input:          event 事件，widget 事件窗口
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    virtual void leaveEvent(QEvent *event){}

    /************************************************************************
    Function:       contextMenuEvent()
    Description:    右键菜单事件
    Input:          event 右键菜单事件，widget 事件窗口
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    virtual void contextMenuEvent(QContextMenuEvent *event){}

	/************************************************************************
	Function:       resizeEvent()
	Description:    窗口大小改变事件
	Input:          event 窗口大小改变事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	virtual void resizeEvent(QResizeEvent * event){}

public slots:
    /************************************************************************
    Function:       activateCurrentStateSlot()
    Description:    激活当前状态
    Input:          无
    Output:         无
    Return:         无
    Others:         无
    ************************************************************************/
    virtual void activateCurrentStateSlot(){}

	/************************************************************************
	Function:       resize()
	Description:    大小改变
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	virtual void resize() {}

private:
	Q_DECLARE_PRIVATE(CGraphicsViewState);
	QScopedPointer<CGraphicsViewStatePrivate> d_ptr;
};
