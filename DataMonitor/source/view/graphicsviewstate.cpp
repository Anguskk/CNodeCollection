/********************************************************************
Copyright (C), 2016, ���ӿƼ���ѧ.
FileName:    graphicsviewstate.cpp
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
#include "graphicsviewstate.h"

#include <QAction>

#include "monitorwindow.h"

//���ݱ�����
class CGraphicsViewStatePrivate
{
	Q_DECLARE_PUBLIC(CGraphicsViewState)
public:
	/************************************************************************
	Function:       CGraphicsViewStatePrivate()
	Description:    ���캯��
	Input:          parent ������
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CGraphicsViewStatePrivate(CMonitorWindow *window, bool resumable, CGraphicsViewState *parent);

	/************************************************************************
	Function:       ~CGraphicsViewPrivate()
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	virtual ~CGraphicsViewStatePrivate();

private:
	QAction*                                 m_action;                 //�󶨰�ť
	QString                                  m_name;                   //state������
	CMonitorWindow *                         m_window;                 //���а�������
	bool                                     m_resumable;              //״̬�Ƿ�ɻָ�
	bool                                     m_initFlag;               //�Ƿ����״̬

	CGraphicsViewState*                      q_ptr;                    //����
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
	//ɾ����ť
	if (NULL != m_action)
	{
		delete m_action;
		m_action = NULL;
	}
}

/************************************************************************
Function:       CGraphicsViewState()
Description:    ���캯������ʼ������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CGraphicsViewState::CGraphicsViewState(CMonitorWindow *window,bool resumable/* = true*/)
	:d_ptr(new CGraphicsViewStatePrivate(window, resumable,this))
{
    
}

/************************************************************************
Function:       ~CGraphicsViewState()
Description:    �����������ͷ�����
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CGraphicsViewState::~CGraphicsViewState()
{
   
}

/************************************************************************
Function:       getName()
Description:    ��ȡ����
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
QString CGraphicsViewState::getName()
{
	Q_D(const CGraphicsViewState);
	return d->m_name;
}

/************************************************************************
Function:       setWindow()
Description:    ����������
Input:          _window ������
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CGraphicsViewState::setWindow(CMonitorWindow *_window )
{
	Q_D(CGraphicsViewState);
	d->m_window = _window;
}

/************************************************************************
Function:       getWindow()
Description:    ��ȡ������
Input:          ��
Output:         ��
Return:         ������
Others:         ��
************************************************************************/
CMonitorWindow * CGraphicsViewState::getWindow()
{
	Q_D(CGraphicsViewState);
	return d->m_window;
}

/************************************************************************
Function:       getAction()
Description:    ��ȡ��ǰ������ť
Input:          ��
Output:         ��
Return:         ��ǰ������ť
Others:         ��
************************************************************************/
QAction * CGraphicsViewState::getAction()
{
	Q_D(const CGraphicsViewState);
	return d->m_action;
}

/************************************************************************
Function:       trigger()
Description:    ���ǰ��ť
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CGraphicsViewState::trigger()
{
	Q_D(const CGraphicsViewState);
    if (NULL != d->m_action)
		d->m_action->trigger();
}

/************************************************************************
Function:       getResumable()
Description:    ��ȡ״̬�Ƿ�ɻָ�
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
bool CGraphicsViewState::getResumable()
{
	Q_D(const CGraphicsViewState);
	return d->m_resumable;
}

/************************************************************************
Function:       setInitFlag()
Description:    �����Ƿ����״̬
Input:          _initFlag ���״̬
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CGraphicsViewState::setInitFlag(bool _initFlag)
{
	Q_D(CGraphicsViewState);
	d->m_initFlag = _initFlag;
}

/************************************************************************
Function:       getInitFlag()
Description:    ��ȡ�Ƿ����״̬
Input:          ��
Output:         ��
Return:         ���״̬
Others:         ��
************************************************************************/
bool CGraphicsViewState::getInitFlag()
{
	Q_D(const CGraphicsViewState);
	return d->m_initFlag;
}

#ifndef QT_NO_WHEELEVENT
/************************************************************************
Function:       wheelEvent()
Description:    �������¼�
Input:          event �����¼���widget �¼�����
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CGraphicsViewState::wheelEvent(QWheelEvent *event)
{
	
}
#endif

/************************************************************************
Function:       keyPressEvent()
Description:    ���̰����¼�
Input:          event �����¼���widget �¼�����
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CGraphicsViewState::keyPressEvent( QKeyEvent *event )
{
	
}
