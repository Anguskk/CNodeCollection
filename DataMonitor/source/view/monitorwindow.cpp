/********************************************************************
Copyright (C), 2016, ���ӿƼ���ѧ.
FileName:    monitorwindow.cpp
Author:      LYH
Version:     V1.0
Date:        2016/05/24
Description:             ///���ڻ���
Other:                   ///��
Function List:           ///��Ҫ�������书��
History:                 ///��ʷ�޸ļ�¼
<author>    <time>    <version>     <desc>
********************************************************************/
#include "monitorwindow.h"

#include <QToolBar>
#include <QCloseEvent>

#include "graphicsview.h"
#include "graphicsviewstate.h"
#include "monitorbasestate.h"
#include "graphicsitemmanage.h"
#include "graphicsshelfitem.h"

//���ݱ�����
class CMonitorWindowPrivate
{
	Q_DECLARE_PUBLIC(CMonitorWindow)
public:
	/************************************************************************
	Function:       CMonitorWindowPrivate()
	Description:    ���캯��
	Input:          parent ������
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CMonitorWindowPrivate(CMonitorWindow *parent);

	/************************************************************************
	Function:       ~CGraphicsViewPrivate()
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	virtual ~CMonitorWindowPrivate();

	/************************************************************************
	Function:       init()
	Description:    ��ʼ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void init();

	/************************************************************************
	Function:       createToolBar()
	Description:    ��ӹ�����
	Input:          _toolBarName ���������ƣ�area ���λ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	QToolBar *createToolBarFromName(QString _toolBarName, Qt::ToolBarArea area);

private:
	QVector<QToolBar *>                       m_allToolBars;                          //���й�����
	CGraphicsView*                            m_view              = nullptr;          //view����
	CGraphicsItemManage*                      m_itemManage        = nullptr;          //���ݹ���
	CMonitorMsgManage *                       monitorMsgManage    = nullptr;          //��Ϣ����

	QMap<QString, CGraphicsViewState *>       m_allStates;                            //����state
	CGraphicsViewState *                      m_saveState         = nullptr;          //����state
	CGraphicsViewState *                      m_activeState       = nullptr;          //����state
	CGraphicsViewState *                      m_baseState         = nullptr;          //����state
	CMonitorWindow*                           q_ptr;                                  //����
};

CMonitorWindowPrivate::CMonitorWindowPrivate(CMonitorWindow *parent)
	:q_ptr(parent), m_itemManage(new CGraphicsItemManage())
{

}

/************************************************************************
Function:       ~CGraphicsViewPrivate()
Description:    ��������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CMonitorWindowPrivate::~CMonitorWindowPrivate()
{
	//������������state
	for(CGraphicsViewState * t_ViewState: m_allStates)
	{
		delete t_ViewState;
	}
	if (nullptr != m_itemManage)
	{
		delete m_itemManage;
		m_itemManage = nullptr;
	}
	m_allStates.clear();
	m_saveState = nullptr;          //����state
	m_activeState = nullptr;          //����state
	m_baseState = nullptr;          //����state
}

/************************************************************************
Function:       init()
Description:    ��ʼ��������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CMonitorWindowPrivate::init()
{
	Q_Q(CMonitorWindow);
	auto t_monitorBaseState = new CMonitorBaseState(q);
	q->addViewState(t_monitorBaseState);
	m_baseState = t_monitorBaseState;
	m_activeState = t_monitorBaseState;
}

/************************************************************************
Function:       createToolBar()
Description:    ��ӹ�����
Input:          _toolBarName ���������ƣ�area ���λ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
QToolBar * CMonitorWindowPrivate::createToolBarFromName(QString _toolBarName, Qt::ToolBarArea area)
{
	if (_toolBarName.isEmpty())
		return NULL;

	QToolBar *t_toolBar = NULL;
	for(QToolBar *t_curToolBar: m_allToolBars) {
		//���ҹ�����
		if (t_curToolBar->windowTitle() == _toolBarName) {
			t_toolBar = t_curToolBar;
			break;
		}
	}
	return t_toolBar;
}

/************************************************************************
Function:       CMonitorWindow()
Description:    ���캯������ʼ������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CMonitorWindow::CMonitorWindow(QWidget *parent)
    : QMainWindow(parent), d_ptr(new CMonitorWindowPrivate(this))
{
	setAttribute(Qt::WA_DeleteOnClose);
	initUI();
}

/************************************************************************
Function:       ~CMonitorWindow()
Description:    �����������ͷ�����
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CMonitorWindow::~CMonitorWindow()
{
	
}

/************************************************************************
Function:       getView()
Description:    ��ȡ����View
Input:          ��
Output:         ��
Return:         ����View
Others:         ��
************************************************************************/
CGraphicsView * CMonitorWindow::getView()
{
	Q_D(const CMonitorWindow);
	return d->m_view;
}

/************************************************************************
Function:       addShelf()
Description:    ��Ӽ���
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CMonitorWindow::addShelf(const SShelfInfo &shelf)
{
	Q_D(CMonitorWindow);
	auto t_curItem = new CGraphicsShelfItem(shelf, 16, 400, 420);
	d->m_view->scene()->addItem(t_curItem);
	d->m_itemManage->addData(t_curItem);
	d->m_view->calculateSize();
}

/************************************************************************
Function:       deleteShelf()
Description:    ɾ������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CMonitorWindow::deleteShelf(const int &shelfId)
{
	Q_D(CMonitorWindow);

	auto allObjects = d->m_itemManage->getAllobjects();
	for (int i =0;i<allObjects.size();++i)
	{
		auto t_curItem = dynamic_cast<CGraphicsShelfItem *>(allObjects[i]);
		if(t_curItem == nullptr)
			continue;
		if (t_curItem->getShelfID() == shelfId) {
			d->m_itemManage->deleteData(t_curItem);
			break;
		}	
	}
	d->m_view->calculateSize();
}

/************************************************************************
Function:       getAllShelfIDs()
Description:    ��ȡ���м��Ӻ�
Input:          ��
Output:         ��
Return:         ���м��Ӻ�
Others:         ��
************************************************************************/
QVector<int> CMonitorWindow::getAllShelfIDs()
{
	Q_D(CMonitorWindow);

	QVector<int> allIDs;
	auto allObjects = d->m_itemManage->getAllobjects();
	for (int i = 0; i < allObjects.size(); ++i)
	{
		auto t_curItem = dynamic_cast<CGraphicsShelfItem *>(allObjects[i]);
		if (t_curItem == nullptr)
			continue;
		allIDs.append(t_curItem->getShelfID());
	}

	return allIDs;
}

/************************************************************************
Function:       addViewState()
Description:    ���state
Input:          _state ����state��_toolBarName toolbar���ƣ�_toolBarArea toolbarλ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CMonitorWindow::addViewState(CGraphicsViewState *_state, QString _toolBarName, Qt::ToolBarArea _toolBarArea /*= Qt::TopToolBarArea*/)
{
	Q_D(CMonitorWindow);
	if (_state->getAction() && !_toolBarName.isEmpty())
	{
		d->createToolBarFromName(_toolBarName, _toolBarArea)->addAction(_state->getAction());
		connect(_state->getAction(), SIGNAL(triggered()), this, SIGNAL(activePublicStateChangedSig()));
	}
	d->m_allStates.insert(_state->getName(), _state);
}

/************************************************************************
Function:       getStateFromName()
Description:    ͨ�����ƻ�ȡstate
Input:          _name state����
Output:         ��
Return:         state
Others:         ��
************************************************************************/
CGraphicsViewState * CMonitorWindow::getStateFromName(const QString &_name)
{
	Q_D(CMonitorWindow);
	CGraphicsViewState *t_curState = nullptr;
	for (auto t_state : d->m_allStates)
	{
		if (t_state->getName() == _name)
		{
			t_curState = t_state;
			break;
		}
	}
	return t_curState;
}

/************************************************************************
Function:       setActiveState()
Description:    ���ü���state
Input:          _state ����state
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CMonitorWindow::setActiveState(CGraphicsViewState *_state)
{
	Q_D(CMonitorWindow);
	//��ֹΪ��
	if (nullptr == _state || d->m_activeState == _state)
		return;

	for(auto t_state: d->m_allStates)
	{
		if (NULL != t_state && t_state->getInitFlag()) {
			t_state->initialize();
		}
	}
	d->m_activeState = _state;
}

/************************************************************************
Function:       setActiveState()
Description:    ���ü���state
Input:          _stateName ����state����
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CMonitorWindow::setActiveState(const QString &_stateName)
{
	Q_D(CMonitorWindow);
	if (!d->m_allStates.contains(_stateName))
		return;

	auto t_state = d->m_allStates[_stateName];
	//��ֹΪ��
	if (NULL == t_state || NULL == t_state->getAction())
		return;

	t_state->getAction()->activate(QAction::Trigger);
}

/************************************************************************
Function:       getActiveState()
Description:    ͨ������state
Input:          ��
Output:         ��
Return:         state
Others:         ��
************************************************************************/
CGraphicsViewState * CMonitorWindow::getActiveState()
{
	Q_D(CMonitorWindow);
	return d->m_activeState;
}

/************************************************************************
Function:       setBaseState()
Description:    ���û���state(Ĭ��״̬)
Input:          _state ����state����
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CMonitorWindow::setBaseState(CGraphicsViewState *_state)
{
	Q_D(CMonitorWindow);
	d->m_baseState = _state;
	if (NULL != d->m_baseState->getAction()) {
		d->m_baseState->getAction()->activate(QAction::Trigger);
	}
}

/************************************************************************
Function:       getBaseState()
Description:    ͨ������state
Input:          ��
Output:         ��
Return:         state
Others:         ��
************************************************************************/
CGraphicsViewState * CMonitorWindow::getBaseState()
{
	Q_D(CMonitorWindow);
	return d->m_baseState;
}

/************************************************************************
Function:       resetState()
Description:    �ָ�����state
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CMonitorWindow::resetState()
{
	Q_D(CMonitorWindow);
	CGraphicsViewState * t_preState;
	//��ֹ�ظ�����base״̬
	if (d->m_activeState == d->m_baseState)
	{
		if (NULL != d->m_baseState->getAction()) {
			d->m_baseState->getAction()->activate(QAction::Trigger);
		}
		return;
	}
	//������һ��״̬
	if (nullptr != d->m_baseState) {
		t_preState = d->m_baseState;
	}
	else { //��ֹδ����״̬ʱ�޷�����ԭʼ״̬
		setViewFlag();
	}
	setActiveState(t_preState);
	if (nullptr != d->m_baseState->getAction()) {
		d->m_baseState->getAction()->activate(QAction::Trigger);
	}
}

/************************************************************************
Function:       saveActivePublicState()
Description:    ���漤��state
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CMonitorWindow::saveActiveState()
{
	Q_D(CMonitorWindow);
	if (d->m_activeState == nullptr)
		return;
	//����state
	if (d->m_activeState->getResumable()) {
		d->m_activeState->setInitFlag(false);
		d->m_saveState = d->m_activeState;
	}
}

/************************************************************************
Function:       restoreActiveState()
Description:    �ָ�����state
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CGraphicsViewState *CMonitorWindow::restoreActiveState()
{
	Q_D(CMonitorWindow);
	CGraphicsViewState * t_preState = nullptr;
	//��ֹ�ظ�����base״̬
	if (d->m_activeState == d->m_baseState)
	{
		if (nullptr != d->m_baseState->getAction()) {
			d->m_baseState->getAction()->activate(QAction::Trigger);
		}
		return t_preState;
	}

	//������һ��״̬
	if (d->m_saveState != nullptr) {
		t_preState = d->m_saveState;
		d->m_saveState = nullptr;
	}
	else if (nullptr != d->m_baseState) {
		t_preState = d->m_baseState;
	}
	else { //��ֹδ����״̬ʱ�޷�����ԭʼ״̬
		setViewFlag();
	}
	setActiveState(t_preState);
	//�ָ���ǰ״̬
	if (nullptr != t_preState && t_preState->getResumable()) {
		t_preState->setInitFlag(true);
		if (nullptr != t_preState->getAction()) {
			t_preState->getAction()->activate(QAction::Trigger);
		}
		t_preState->activateCurrentStateSlot();
	}
	return t_preState;
}

/************************************************************************
Function:       setViewFlag()
Description:    ����view��־
Input:          cursor �����״��mode ��ק״̬��allowed �¼�����
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CMonitorWindow::setViewFlag(const QCursor &cursor, QGraphicsView::DragMode mode /*= QGraphicsView::NoDrag*/, bool allowed /*= true*/)
{
	Q_D(CMonitorWindow);
	if (NULL == d->m_view)
		return;

	d->m_view->setDragMode(mode);
	d->m_view->setInteractive(allowed);
	d->m_view->setCursor(cursor);
}

/************************************************************************
Function:       getItemManage()
Description:    ��ȡ���ݹ���
Input:          ��
Output:         ��
Return:         ���ݹ���
Others:         ��
************************************************************************/
CGraphicsItemManage* CMonitorWindow::getItemManage()
{
	Q_D(CMonitorWindow);
	return d->m_itemManage;
}

/************************************************************************
Function:       setMonitorMsgManage()
Description:    ������Ϣ����
Input:          monitorMsgManage ���ݹ���
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CMonitorWindow::setMonitorMsgManage(CMonitorMsgManage *monitorMsgManage)
{
	Q_D(CMonitorWindow);
	d->monitorMsgManage = monitorMsgManage;
}

/************************************************************************
Function:       getMonitorMsgManage()
Description:    ��ȡ��Ϣ����
Input:          ��
Output:         ��
Return:         ���ݹ���
Others:         ��
************************************************************************/
CMonitorMsgManage * CMonitorWindow::getMonitorMsgManage()
{
	Q_D(CMonitorWindow);
	return d->monitorMsgManage;
}

/************************************************************************
Function:       initUI()
Description:    ��ʼ��ui
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CMonitorWindow::initUI()
{
	Q_D(CMonitorWindow);

	resize(600, 400);

	d->m_view = new CGraphicsView(this);
	setCentralWidget(d->m_view);

	d->init();
}
