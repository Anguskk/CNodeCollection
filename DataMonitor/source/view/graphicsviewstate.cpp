/********************************************************************
Copyright (C), 2016, 电子科技大学.
FileName:    graphicsviewstate.cpp
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
#include "graphicsviewstate.h"

#include <QAction>

#include "monitorwindow.h"

//数据保存类
class CGraphicsViewStatePrivate
{
	Q_DECLARE_PUBLIC(CGraphicsViewState)
public:
	/************************************************************************
	Function:       CGraphicsViewStatePrivate()
	Description:    构造函数
	Input:          parent 父窗口
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CGraphicsViewStatePrivate(CMonitorWindow *window, bool resumable, CGraphicsViewState *parent);

	/************************************************************************
	Function:       ~CGraphicsViewPrivate()
	Description:    析构函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	virtual ~CGraphicsViewStatePrivate();

private:
	QAction*                                 m_action;                 //绑定按钮
	QString                                  m_name;                   //state类名称
	CMonitorWindow *                         m_window;                 //所有绑定主窗口
	bool                                     m_resumable;              //状态是否可恢复
	bool                                     m_initFlag;               //是否清除状态

	CGraphicsViewState*                      q_ptr;                    //父类
};

CGraphicsViewStatePrivate::CGraphicsViewStatePrivate(CMonitorWindow *window, bool resumable, CGraphicsViewState *parent)
	:q_ptr(parent), m_window(window), m_resumable(resumable), m_initFlag(true)
{
	Q_Q(const CGraphicsViewState);
	m_action = NULL;
	m_window = window;
	q->connect(m_window, SIGNAL(activeWindowChangeSignal(CView2DWidget *)), q, SLOT(updateStateSlot(CView2DWidget *)));
}

CGraphicsViewStatePrivate::~CGraphicsViewStatePrivate()
{
	//删除按钮
	if (NULL != m_action)
	{
		delete m_action;
		m_action = NULL;
	}
}

/************************************************************************
Function:       CGraphicsViewState()
Description:    构造函数，初始化参数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CGraphicsViewState::CGraphicsViewState(CMonitorWindow *window,bool resumable/* = true*/)
	:d_ptr(new CGraphicsViewStatePrivate(window, resumable,this))
{
    
}

/************************************************************************
Function:       ~CGraphicsViewState()
Description:    析构函数，释放数据
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CGraphicsViewState::~CGraphicsViewState()
{
   
}

/************************************************************************
Function:       getName()
Description:    获取名称
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
QString CGraphicsViewState::getName()
{
	Q_D(const CGraphicsViewState);
	return d->m_name;
}

/************************************************************************
Function:       setWindow()
Description:    设置主窗口
Input:          _window 主窗口
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsViewState::setWindow(CMonitorWindow *_window )
{
	Q_D(CGraphicsViewState);
	d->m_window = _window;
}

/************************************************************************
Function:       getWindow()
Description:    获取主窗口
Input:          无
Output:         无
Return:         主窗口
Others:         无
************************************************************************/
CMonitorWindow * CGraphicsViewState::getWindow()
{
	Q_D(CGraphicsViewState);
	return d->m_window;
}

/************************************************************************
Function:       getAction()
Description:    获取当前操作按钮
Input:          无
Output:         无
Return:         当前操作按钮
Others:         无
************************************************************************/
QAction * CGraphicsViewState::getAction()
{
	Q_D(const CGraphicsViewState);
	return d->m_action;
}

/************************************************************************
Function:       trigger()
Description:    激活当前按钮
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsViewState::trigger()
{
	Q_D(const CGraphicsViewState);
    if (NULL != d->m_action)
		d->m_action->trigger();
}

/************************************************************************
Function:       getResumable()
Description:    获取状态是否可恢复
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
bool CGraphicsViewState::getResumable()
{
	Q_D(const CGraphicsViewState);
	return d->m_resumable;
}

/************************************************************************
Function:       setInitFlag()
Description:    设置是否清除状态
Input:          _initFlag 清除状态
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsViewState::setInitFlag(bool _initFlag)
{
	Q_D(CGraphicsViewState);
	d->m_initFlag = _initFlag;
}

/************************************************************************
Function:       getInitFlag()
Description:    获取是否清除状态
Input:          无
Output:         无
Return:         清除状态
Others:         无
************************************************************************/
bool CGraphicsViewState::getInitFlag()
{
	Q_D(const CGraphicsViewState);
	return d->m_initFlag;
}

#ifndef QT_NO_WHEELEVENT
/************************************************************************
Function:       wheelEvent()
Description:    鼠标滚轮事件
Input:          event 滚轮事件，widget 事件窗口
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsViewState::wheelEvent(QWheelEvent *event)
{
	
}
#endif

/************************************************************************
Function:       keyPressEvent()
Description:    键盘按下事件
Input:          event 键盘事件，widget 事件窗口
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsViewState::keyPressEvent( QKeyEvent *event )
{
	
}
