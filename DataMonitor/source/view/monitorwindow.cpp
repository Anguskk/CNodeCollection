/********************************************************************
Copyright (C), 2016, 电子科技大学.
FileName:    monitorwindow.cpp
Author:      LYH
Version:     V1.0
Date:        2016/05/24
Description:             ///窗口基类
Other:                   ///无
Function List:           ///主要函数及其功能
History:                 ///历史修改记录
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

//数据保存类
class CMonitorWindowPrivate
{
	Q_DECLARE_PUBLIC(CMonitorWindow)
public:
	/************************************************************************
	Function:       CMonitorWindowPrivate()
	Description:    构造函数
	Input:          parent 父窗口
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CMonitorWindowPrivate(CMonitorWindow *parent);

	/************************************************************************
	Function:       ~CGraphicsViewPrivate()
	Description:    析构函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	virtual ~CMonitorWindowPrivate();

	/************************************************************************
	Function:       init()
	Description:    初始化工具栏
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void init();

	/************************************************************************
	Function:       createToolBar()
	Description:    添加工具栏
	Input:          _toolBarName 工具栏名称，area 添加位置
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	QToolBar *createToolBarFromName(QString _toolBarName, Qt::ToolBarArea area);

private:
	QVector<QToolBar *>                       m_allToolBars;                          //所有工具栏
	CGraphicsView*                            m_view              = nullptr;          //view窗口
	CGraphicsItemManage*                      m_itemManage        = nullptr;          //数据管理
	CMonitorMsgManage *                       monitorMsgManage    = nullptr;          //消息管理

	QMap<QString, CGraphicsViewState *>       m_allStates;                            //所有state
	CGraphicsViewState *                      m_saveState         = nullptr;          //保存state
	CGraphicsViewState *                      m_activeState       = nullptr;          //激活state
	CGraphicsViewState *                      m_baseState         = nullptr;          //基本state
	CMonitorWindow*                           q_ptr;                                  //父类
};

CMonitorWindowPrivate::CMonitorWindowPrivate(CMonitorWindow *parent)
	:q_ptr(parent), m_itemManage(new CGraphicsItemManage())
{

}

/************************************************************************
Function:       ~CGraphicsViewPrivate()
Description:    析构函数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CMonitorWindowPrivate::~CMonitorWindowPrivate()
{
	//析构公有所有state
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
	m_saveState = nullptr;          //保存state
	m_activeState = nullptr;          //激活state
	m_baseState = nullptr;          //基本state
}

/************************************************************************
Function:       init()
Description:    初始化工具栏
Input:          无
Output:         无
Return:         无
Others:         无
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
Description:    添加工具栏
Input:          _toolBarName 工具栏名称，area 添加位置
Output:         无
Return:         无
Others:         无
************************************************************************/
QToolBar * CMonitorWindowPrivate::createToolBarFromName(QString _toolBarName, Qt::ToolBarArea area)
{
	if (_toolBarName.isEmpty())
		return NULL;

	QToolBar *t_toolBar = NULL;
	for(QToolBar *t_curToolBar: m_allToolBars) {
		//查找工具栏
		if (t_curToolBar->windowTitle() == _toolBarName) {
			t_toolBar = t_curToolBar;
			break;
		}
	}
	return t_toolBar;
}

/************************************************************************
Function:       CMonitorWindow()
Description:    构造函数，初始化参数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CMonitorWindow::CMonitorWindow(QWidget *parent)
    : QMainWindow(parent), d_ptr(new CMonitorWindowPrivate(this))
{
	setAttribute(Qt::WA_DeleteOnClose);
	initUI();
}

/************************************************************************
Function:       ~CMonitorWindow()
Description:    析构函数，释放数据
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CMonitorWindow::~CMonitorWindow()
{
	
}

/************************************************************************
Function:       getView()
Description:    获取绘制View
Input:          无
Output:         无
Return:         绘制View
Others:         无
************************************************************************/
CGraphicsView * CMonitorWindow::getView()
{
	Q_D(const CMonitorWindow);
	return d->m_view;
}

/************************************************************************
Function:       addShelf()
Description:    添加架子
Input:          无
Output:         无
Return:         无
Others:         无
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
Description:    删除架子
Input:          无
Output:         无
Return:         无
Others:         无
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
Description:    获取所有架子号
Input:          无
Output:         无
Return:         所有架子号
Others:         无
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
Description:    添加state
Input:          _state 操作state，_toolBarName toolbar名称，_toolBarArea toolbar位置
Output:         无
Return:         无
Others:         无
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
Description:    通过名称获取state
Input:          _name state名称
Output:         无
Return:         state
Others:         无
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
Description:    设置激活state
Input:          _state 操作state
Output:         无
Return:         无
Others:         无
************************************************************************/
void CMonitorWindow::setActiveState(CGraphicsViewState *_state)
{
	Q_D(CMonitorWindow);
	//防止为空
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
Description:    设置激活state
Input:          _stateName 操作state名称
Output:         无
Return:         无
Others:         无
************************************************************************/
void CMonitorWindow::setActiveState(const QString &_stateName)
{
	Q_D(CMonitorWindow);
	if (!d->m_allStates.contains(_stateName))
		return;

	auto t_state = d->m_allStates[_stateName];
	//防止为空
	if (NULL == t_state || NULL == t_state->getAction())
		return;

	t_state->getAction()->activate(QAction::Trigger);
}

/************************************************************************
Function:       getActiveState()
Description:    通过激活state
Input:          无
Output:         无
Return:         state
Others:         无
************************************************************************/
CGraphicsViewState * CMonitorWindow::getActiveState()
{
	Q_D(CMonitorWindow);
	return d->m_activeState;
}

/************************************************************************
Function:       setBaseState()
Description:    设置基本state(默认状态)
Input:          _state 操作state名称
Output:         无
Return:         无
Others:         无
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
Description:    通过基本state
Input:          无
Output:         无
Return:         state
Others:         无
************************************************************************/
CGraphicsViewState * CMonitorWindow::getBaseState()
{
	Q_D(CMonitorWindow);
	return d->m_baseState;
}

/************************************************************************
Function:       resetState()
Description:    恢复基本state
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CMonitorWindow::resetState()
{
	Q_D(CMonitorWindow);
	CGraphicsViewState * t_preState;
	//防止重复设置base状态
	if (d->m_activeState == d->m_baseState)
	{
		if (NULL != d->m_baseState->getAction()) {
			d->m_baseState->getAction()->activate(QAction::Trigger);
		}
		return;
	}
	//集合上一次状态
	if (nullptr != d->m_baseState) {
		t_preState = d->m_baseState;
	}
	else { //防止未保存状态时无法返回原始状态
		setViewFlag();
	}
	setActiveState(t_preState);
	if (nullptr != d->m_baseState->getAction()) {
		d->m_baseState->getAction()->activate(QAction::Trigger);
	}
}

/************************************************************************
Function:       saveActivePublicState()
Description:    保存激活state
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CMonitorWindow::saveActiveState()
{
	Q_D(CMonitorWindow);
	if (d->m_activeState == nullptr)
		return;
	//保存state
	if (d->m_activeState->getResumable()) {
		d->m_activeState->setInitFlag(false);
		d->m_saveState = d->m_activeState;
	}
}

/************************************************************************
Function:       restoreActiveState()
Description:    恢复激活state
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CGraphicsViewState *CMonitorWindow::restoreActiveState()
{
	Q_D(CMonitorWindow);
	CGraphicsViewState * t_preState = nullptr;
	//防止重复设置base状态
	if (d->m_activeState == d->m_baseState)
	{
		if (nullptr != d->m_baseState->getAction()) {
			d->m_baseState->getAction()->activate(QAction::Trigger);
		}
		return t_preState;
	}

	//集合上一次状态
	if (d->m_saveState != nullptr) {
		t_preState = d->m_saveState;
		d->m_saveState = nullptr;
	}
	else if (nullptr != d->m_baseState) {
		t_preState = d->m_baseState;
	}
	else { //防止未保存状态时无法返回原始状态
		setViewFlag();
	}
	setActiveState(t_preState);
	//恢复当前状态
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
Description:    设置view标志
Input:          cursor 鼠标形状，mode 拖拽状态，allowed 事件接受
Output:         无
Return:         无
Others:         无
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
Description:    获取数据管理
Input:          无
Output:         无
Return:         数据管理
Others:         无
************************************************************************/
CGraphicsItemManage* CMonitorWindow::getItemManage()
{
	Q_D(CMonitorWindow);
	return d->m_itemManage;
}

/************************************************************************
Function:       setMonitorMsgManage()
Description:    设置消息管理
Input:          monitorMsgManage 数据管理
Output:         无
Return:         无
Others:         无
************************************************************************/
void CMonitorWindow::setMonitorMsgManage(CMonitorMsgManage *monitorMsgManage)
{
	Q_D(CMonitorWindow);
	d->monitorMsgManage = monitorMsgManage;
}

/************************************************************************
Function:       getMonitorMsgManage()
Description:    获取消息管理
Input:          无
Output:         无
Return:         数据管理
Others:         无
************************************************************************/
CMonitorMsgManage * CMonitorWindow::getMonitorMsgManage()
{
	Q_D(CMonitorWindow);
	return d->monitorMsgManage;
}

/************************************************************************
Function:       initUI()
Description:    初始化ui
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CMonitorWindow::initUI()
{
	Q_D(CMonitorWindow);

	resize(600, 400);

	d->m_view = new CGraphicsView(this);
	setCentralWidget(d->m_view);

	d->init();
}
