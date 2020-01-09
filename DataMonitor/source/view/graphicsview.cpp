/********************************************************************
Copyright (C), 2016, ���ӿƼ���ѧ.
FileName:    graphicsview.cpp
Author:      LYH
Version:     V1.0
Date:        2019/05/24
Description:             ///ģ������
���ļ���Ҫ�����Ա�����ϵ����������.
Other:                   ///����������
Function List:           ///��Ҫ�������书��
History:                 ///��ʷ�޸ļ�¼
<author>    <time>    <version>     <desc>
********************************************************************/
#include "graphicsview.h"

#include <QEvent>
#include <QMouseEvent>

#include "monitorwindow.h"
#include "graphicsviewstate.h"

//���ݱ�����
class CGraphicsViewPrivate
{
	Q_DECLARE_PUBLIC(CGraphicsView)
public:
	/************************************************************************
	Function:       CGraphicsViewPrivate()
	Description:    ���캯��
	Input:          parent ������
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CGraphicsViewPrivate(QWidget *window,CGraphicsView *parent);

	/************************************************************************
	Function:       ~CGraphicsViewPrivate()
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	virtual ~CGraphicsViewPrivate(){}

private:
	CMonitorWindow*                     m_window          = nullptr;     //������
	int                                 m_margin          = 10;          //�߽���
	int                                 m_spacing         = 10;          //���
	QGraphicsScene*                     m_scene;                         //����

	CGraphicsView*                      q_ptr;                           //����
};

CGraphicsViewPrivate::CGraphicsViewPrivate(QWidget *window, CGraphicsView *parent)
	:q_ptr(parent)
{
	m_window = static_cast<CMonitorWindow*>(window);
}

/************************************************************************
Function:       CGraphicsView()
Description:    ���캯��
Input:          parent ������
Output:         ��
Return:         ��
Others:         ��
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
Description:    ��������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CGraphicsView::~CGraphicsView()
{
}

/************************************************************************
Function:       getMarginAndSpacing()
Description:    ��ȡ�߽�ͼ��
Input:          ��
Output:         margin �߽�,spacing ���
Return:         ��
Others:         ��
************************************************************************/
void CGraphicsView::getMarginAndSpacing(int &margin, int &spacing)
{
	Q_D(CGraphicsView);
	margin = d->m_margin;
	spacing = d->m_spacing;
}

/************************************************************************
Function:       calculateSize()
Description:    �������м���
Input:          event �¼�
Output:         ��
Return:         ��
Others:         ��
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
Description:    ִ�и����¼�
Input:          event �¼�
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CGraphicsView::onViewEvent(QEvent *event)
{
	//��ֹΪ��
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
Description:    ������¼�
Input:          event �¼�
Output:         ��
Return:         ��
Others:         ��
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
Description:    ����ͷ��¼�
Input:          event �¼�
Output:         ��
Return:         ��
Others:         ��
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
Description:    ���˫���¼�
Input:          event �¼�
Output:         ��
Return:         ��
Others:         ��
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
Description:    ����ƶ��¼�
Input:          event �¼�
Output:         ��
Return:         ��
Others:         ��
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
Description:    �������¼�
Input:          event �¼�
Output:         ��
Return:         ��
Others:         ��
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
Description:    ���̰����¼�
Input:          event �¼�
Output:         ��
Return:         ��
Others:         ��
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
Description:    �����ͷ��¼�
Input:          event �¼�
Output:         ��
Return:         ��
Others:         ��
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
Description:    ����focus�¼�
Input:          event �¼�
Output:         ��
Return:         ��
Others:         ��
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
Description:    �˳�focus�¼�
Input:          event �¼�
Output:         ��
Return:         ��
Others:         ��
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
Description:    �������¼�
Input:          event �¼�
Output:         ��
Return:         ��
Others:         ��
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
Description:    ����뿪�¼�
Input:          event �¼�
Output:         ��
Return:         ��
Others:         ��
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
Description:    �Ҽ��˵��¼�
Input:          event �¼�
Output:         ��
Return:         ��
Others:         ��
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
Description:    ��С�仯�¼�
Input:          event �¼�
Output:         ��
Return:         ��
Others:         ��
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
