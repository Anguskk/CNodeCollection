/********************************************************************
Copyright (C), 2016, 电子科技大学.
FileName:    graphicsview.cpp
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
#include "graphicsview.h"

#include <QEvent>
#include <QMouseEvent>

#include "monitorwindow.h"
#include "graphicsviewstate.h"

//数据保存类
class CGraphicsViewPrivate
{
	Q_DECLARE_PUBLIC(CGraphicsView)
public:
	/************************************************************************
	Function:       CGraphicsViewPrivate()
	Description:    构造函数
	Input:          parent 父窗口
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CGraphicsViewPrivate(QWidget *window,CGraphicsView *parent);

	/************************************************************************
	Function:       ~CGraphicsViewPrivate()
	Description:    析构函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	virtual ~CGraphicsViewPrivate(){}

private:
	CMonitorWindow*                     m_window          = nullptr;     //主窗口
	int                                 m_margin          = 10;          //边界宽度
	int                                 m_spacing         = 10;          //间隔
	QGraphicsScene*                     m_scene;                         //画布

	CGraphicsView*                      q_ptr;                           //父类
};

CGraphicsViewPrivate::CGraphicsViewPrivate(QWidget *window, CGraphicsView *parent)
	:q_ptr(parent)
{
	m_window = static_cast<CMonitorWindow*>(window);
}

/************************************************************************
Function:       CGraphicsView()
Description:    构造函数
Input:          parent 父窗口
Output:         无
Return:         无
Others:         无
************************************************************************/
CGraphicsView::CGraphicsView(QWidget *parent)
	: QGraphicsView(parent),d_ptr(new CGraphicsViewPrivate(parent,this))
{
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	d_ptr->m_scene = new QGraphicsScene(this);
	setScene(d_ptr->m_scene);
	setInteractive(true);

	//setAlignment(Qt::AlignLeft| Qt::AlignTop);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

/************************************************************************
Function:       ~CGraphicsView()
Description:    析构函数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CGraphicsView::~CGraphicsView()
{
}

/************************************************************************
Function:       getMarginAndSpacing()
Description:    获取边界和间距
Input:          无
Output:         margin 边界,spacing 间距
Return:         无
Others:         无
************************************************************************/
void CGraphicsView::getMarginAndSpacing(int &margin, int &spacing)
{
	Q_D(CGraphicsView);
	margin = d->m_margin;
	spacing = d->m_spacing;
}

/************************************************************************
Function:       calculateSize()
Description:    重新排列架子
Input:          event 事件
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsView::calculateSize()
{
	Q_D(CGraphicsView);
	if (nullptr != d->m_window) {
		auto t_activeState = d->m_window->getActiveState();
		if (t_activeState == nullptr)
			t_activeState = d->m_window->getBaseState();
		if (NULL != t_activeState)
			t_activeState->resize();
	}
}

/************************************************************************
Function:       onViewEvent()
Description:    执行父类事件
Input:          event 事件
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsView::onViewEvent(QEvent *event)
{
	//防止为空
	if (NULL == event)
		return;
	switch (event->type())
	{
	case QEvent::MouseButtonPress:
	{
		QMouseEvent *t_event = dynamic_cast<QMouseEvent *>(event);
		if (NULL != t_event)
			QGraphicsView::mousePressEvent(t_event);
	}
	break;
	case QEvent::MouseMove:
	{
		QMouseEvent *t_event = dynamic_cast<QMouseEvent *>(event);
		if (NULL != t_event)
			QGraphicsView::mouseMoveEvent(t_event);
	}
	break;
	case QEvent::MouseButtonRelease:
	{
		QMouseEvent *t_event = dynamic_cast<QMouseEvent *>(event);
		if (NULL != t_event)
			QGraphicsView::mouseReleaseEvent(t_event);
	}
	break;
	case QEvent::MouseButtonDblClick:
	{
		QMouseEvent *t_event = dynamic_cast<QMouseEvent *>(event);
		if (NULL != t_event)
			QGraphicsView::mouseDoubleClickEvent(t_event);
	}
	break;
	case QEvent::Wheel:
	{
		QWheelEvent *t_event = dynamic_cast<QWheelEvent *>(event);
		if (NULL != t_event)
			QGraphicsView::wheelEvent(t_event);
	}
	break;
	case QEvent::KeyPress:
	{
		QKeyEvent *t_event = dynamic_cast<QKeyEvent *>(event);
		if (NULL != t_event)
			QGraphicsView::keyPressEvent(t_event);
	}
	break;
	case QEvent::KeyRelease:
	{
		QKeyEvent *t_event = dynamic_cast<QKeyEvent *>(event);
		if (NULL != t_event)
			QGraphicsView::keyReleaseEvent(t_event);
	}
	break;
	case QEvent::FocusIn:
	{
		QFocusEvent *t_event = dynamic_cast<QFocusEvent *>(event);
		if (NULL != t_event)
			QGraphicsView::focusInEvent(t_event);
	}
	break;
	case QEvent::FocusOut:
	{
		QFocusEvent *t_event = dynamic_cast<QFocusEvent *>(event);
		if (NULL != t_event)
			QGraphicsView::focusOutEvent(t_event);
	}
	break;
	case QEvent::Enter:
	{
		QGraphicsView::enterEvent(event);
	}
	break;
	case QEvent::Leave:
	{
		QGraphicsView::leaveEvent(event);
	}
	break;
	case QEvent::ContextMenu:
	{
		QContextMenuEvent *t_event = dynamic_cast<QContextMenuEvent *>(event);
		if (NULL != t_event)
			QGraphicsView::contextMenuEvent(t_event);
	}
	break;
	default:
		break;
	}
}

/************************************************************************
Function:       mousePressEvent()
Description:    鼠标点击事件
Input:          event 事件
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsView::mousePressEvent(QMouseEvent *event)
{
	Q_D(CGraphicsView);
	if (nullptr != d->m_window) {
		auto t_activeState = d->m_window->getActiveState();
		if (t_activeState == nullptr)
			t_activeState = d->m_window->getBaseState();
		if (NULL != t_activeState)
			t_activeState->mousePressEvent(event);
	}

	if (!event->isAccepted())
		QGraphicsView::mousePressEvent(event);
}

/************************************************************************
Function:       mouseReleaseEvent()
Description:    鼠标释放事件
Input:          event 事件
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
	Q_D(CGraphicsView);
	if (nullptr != d->m_window) {
		auto t_activeState = d->m_window->getActiveState();
		if (t_activeState == nullptr)
			t_activeState = d->m_window->getBaseState();
		if (NULL != t_activeState)
			t_activeState->mouseReleaseEvent(event);
	}

	if (!event->isAccepted())
		QGraphicsView::mouseReleaseEvent(event);
}

/************************************************************************
Function:       mouseDoubleClickEvent()
Description:    鼠标双击事件
Input:          event 事件
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
	Q_D(CGraphicsView);
	if (nullptr != d->m_window) {
		auto t_activeState = d->m_window->getActiveState();
		if (t_activeState == nullptr)
			t_activeState = d->m_window->getBaseState();
		if (NULL != t_activeState)
			t_activeState->mouseDoubleClickEvent(event);
	}

	if (!event->isAccepted())
		QGraphicsView::mouseDoubleClickEvent(event);
}

/************************************************************************
Function:       mouseMoveEvent()
Description:    鼠标移动事件
Input:          event 事件
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
	Q_D(CGraphicsView);
	if (nullptr != d->m_window) {
		auto t_activeState = d->m_window->getActiveState();
		if (t_activeState == nullptr)
			t_activeState = d->m_window->getBaseState();
		if (NULL != t_activeState)
			t_activeState->mouseMoveEvent(event);
	}

	if (!event->isAccepted())
		QGraphicsView::mouseMoveEvent(event);
}

#ifndef QT_NO_WHEELEVENT
/************************************************************************
Function:       wheelEvent()
Description:    鼠标滚轮事件
Input:          event 事件
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsView::wheelEvent(QWheelEvent *event)
{
	Q_D(CGraphicsView);
	if (nullptr != d->m_window) {
		auto t_activeState = d->m_window->getActiveState();
		if (t_activeState == nullptr)
			t_activeState = d->m_window->getBaseState();
		if (NULL != t_activeState)
			t_activeState->wheelEvent(event);
	}

	if (!event->isAccepted())
		QGraphicsView::wheelEvent(event);
}
#endif

/************************************************************************
Function:       keyPressEvent()
Description:    键盘按下事件
Input:          event 事件
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsView::keyPressEvent(QKeyEvent *event)
{
	Q_D(CGraphicsView);
	if (nullptr != d->m_window) {
		auto t_activeState = d->m_window->getActiveState();
		if (t_activeState == nullptr)
			t_activeState = d->m_window->getBaseState();
		if (NULL != t_activeState)
			t_activeState->keyPressEvent(event);
	}

	if (!event->isAccepted())
		QGraphicsView::keyPressEvent(event);
}

/************************************************************************
Function:       keyReleaseEvent()
Description:    键盘释放事件
Input:          event 事件
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
	Q_D(CGraphicsView);
	if (nullptr != d->m_window) {
		auto t_activeState = d->m_window->getActiveState();
		if (t_activeState == nullptr)
			t_activeState = d->m_window->getBaseState();
		if (NULL != t_activeState)
			t_activeState->keyReleaseEvent(event);
	}

	if (!event->isAccepted())
		QGraphicsView::keyReleaseEvent(event);
}

/************************************************************************
Function:       focusInEvent()
Description:    进入focus事件
Input:          event 事件
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsView::focusInEvent(QFocusEvent *event)
{
	Q_D(CGraphicsView);
	if (nullptr != d->m_window) {
		auto t_activeState = d->m_window->getActiveState();
		if (t_activeState == nullptr)
			t_activeState = d->m_window->getBaseState();
		if (NULL != t_activeState)
			t_activeState->focusInEvent(event);
	}

	if (!event->isAccepted())
		QGraphicsView::focusInEvent(event);
}

/************************************************************************
Function:       focusOutEvent()
Description:    退出focus事件
Input:          event 事件
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsView::focusOutEvent(QFocusEvent *event)
{
	Q_D(CGraphicsView);
	if (nullptr != d->m_window) {
		auto t_activeState = d->m_window->getActiveState();
		if (t_activeState == nullptr)
			t_activeState = d->m_window->getBaseState();
		if (NULL != t_activeState)
			t_activeState->focusOutEvent(event);
	}

	if (!event->isAccepted())
		QGraphicsView::focusOutEvent(event);
}

/************************************************************************
Function:       enterEvent()
Description:    鼠标进入事件
Input:          event 事件
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsView::enterEvent(QEvent *event)
{
	Q_D(CGraphicsView);
	if (nullptr != d->m_window) {
		auto t_activeState = d->m_window->getActiveState();
		if (t_activeState == nullptr)
			t_activeState = d->m_window->getBaseState();
		if (NULL != t_activeState)
			t_activeState->enterEvent(event);
	}

	if (!event->isAccepted())
		QGraphicsView::enterEvent(event);
}

/************************************************************************
Function:       leaveEvent()
Description:    鼠标离开事件
Input:          event 事件
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsView::leaveEvent(QEvent *event)
{
	Q_D(CGraphicsView);
	if (nullptr != d->m_window) {
		auto t_activeState = d->m_window->getActiveState();
		if (t_activeState == nullptr)
			t_activeState = d->m_window->getBaseState();
		if (NULL != t_activeState)
			t_activeState->leaveEvent(event);
	}

	if (!event->isAccepted())
		QGraphicsView::leaveEvent(event);
}

/************************************************************************
Function:       contextMenuEvent()
Description:    右键菜单事件
Input:          event 事件
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
	Q_D(CGraphicsView);
	if (nullptr != d->m_window) {
		auto t_activeState = d->m_window->getActiveState();
		if (t_activeState == nullptr)
			t_activeState = d->m_window->getBaseState();
		if (NULL != t_activeState)
			t_activeState->contextMenuEvent(event);
	}

	if (!event->isAccepted())
		QGraphicsView::contextMenuEvent(event);
}

/************************************************************************
Function:       resizeEvent()
Description:    大小变化事件
Input:          event 事件
Output:         无
Return:         无
Others:         无
************************************************************************/
void CGraphicsView::resizeEvent(QResizeEvent *event)
{
	Q_D(CGraphicsView);
	if (nullptr != d->m_window) {
		auto t_activeState = d->m_window->getActiveState();
		if (t_activeState == nullptr)
			t_activeState = d->m_window->getBaseState();
		if (NULL != t_activeState)
			t_activeState->resizeEvent(event);
	}

	if (!event->isAccepted())
		QGraphicsView::resizeEvent(event);
}
