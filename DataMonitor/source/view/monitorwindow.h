/********************************************************************
Copyright (C), 2016, ���ӿƼ���ѧ.
FileName:    monitorwindow.h
Author:      LYH
Version:     V1.0
Date:        2016/05/24
Description:             ///���ڻ���
Other:                   ///��
Function List:           ///��Ҫ�������书��
History:                 ///��ʷ�޸ļ�¼
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
	Description:    ���캯������ʼ������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CMonitorWindow(QWidget *parent = 0);

	/************************************************************************
	Function:       ~CMonitorWindow()
	Description:    �����������ͷ�����
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
    ~CMonitorWindow();

	/************************************************************************
	Function:       getView()
	Description:    ��ȡ����View
	Input:          ��
	Output:         ��
	Return:         ����View
	Others:         ��
	************************************************************************/
	CGraphicsView *getView();

	/************************************************************************
	Function:       addShelf()
	Description:    ��Ӽ���
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void addShelf(const SShelfInfo &shelf);

	/************************************************************************
	Function:       deleteShelf()
	Description:    ɾ������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void deleteShelf(const int &shelfId);

	/************************************************************************
	Function:       getAllShelfIDs()
	Description:    ��ȡ���м��Ӻ�
	Input:          ��
	Output:         ��
	Return:         ���м��Ӻ�
	Others:         ��
	************************************************************************/
	QVector<int> getAllShelfIDs();

	/************************************************************************
	Function:       addViewState()
	Description:    ���state
	Input:          _state ����state��_toolBarName toolbar���ƣ�_toolBarArea toolbarλ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void addViewState(CGraphicsViewState *_state, QString _toolBarName=QString(),
		Qt::ToolBarArea _toolBarArea = Qt::TopToolBarArea);

	/************************************************************************
	Function:       getStateFromName()
	Description:    ͨ�����ƻ�ȡstate
	Input:          _name state����
	Output:         ��
	Return:         state
	Others:         ��
	************************************************************************/
	CGraphicsViewState * getStateFromName(const QString &_name);

	/************************************************************************
	Function:       setActiveState()
	Description:    ���ü���state
	Input:          _state ����state
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void setActiveState(CGraphicsViewState *_state);

	/************************************************************************
	Function:       setActiveState()
	Description:    ���ü���state
	Input:          _stateName ����state����
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void setActiveState(const QString &_stateName);

	/************************************************************************
	Function:       getActiveState()
	Description:    ͨ������state
	Input:          ��
	Output:         ��
	Return:         state
	Others:         ��
	************************************************************************/
	CGraphicsViewState * getActiveState();

	/************************************************************************
	Function:       setBaseState()
	Description:    ���û���state(Ĭ��״̬)
	Input:          _state ����state����
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void setBaseState(CGraphicsViewState *_state);

	/************************************************************************
	Function:       getBaseState()
	Description:    ͨ������state
	Input:          ��
	Output:         ��
	Return:         state
	Others:         ��
	************************************************************************/
	CGraphicsViewState * getBaseState();

	/************************************************************************
	Function:       resetState()
	Description:    �ָ�����state
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void resetState();

	/************************************************************************
	Function:       saveActivePublicState()
	Description:    ���漤��state
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void saveActiveState();

	/************************************************************************
	Function:       restoreActiveState()
	Description:    �ָ�����state
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CGraphicsViewState* restoreActiveState();

	/************************************************************************
	Function:       setViewFlag()
	Description:    ����view��־
	Input:          cursor �����״��mode ��ק״̬��allowed 
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void setViewFlag(const QCursor &cursor = Qt::ArrowCursor, QGraphicsView::DragMode mode = QGraphicsView::NoDrag, bool allowed = true);

	/************************************************************************
	Function:       getItemManage()
	Description:    ��ȡ���ݹ���
	Input:          ��
	Output:         ��
	Return:         ���ݹ���
	Others:         ��
	************************************************************************/
	CGraphicsItemManage* getItemManage();

	/************************************************************************
	Function:       setMonitorMsgManage()
	Description:    ������Ϣ����
	Input:          monitorMsgManage ���ݹ���
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void setMonitorMsgManage(CMonitorMsgManage *monitorMsgManage);

	/************************************************************************
	Function:       getMonitorMsgManage()
	Description:    ��ȡ��Ϣ����
	Input:          ��
	Output:         ��
	Return:         ���ݹ���
	Others:         ��
	************************************************************************/
	CMonitorMsgManage *getMonitorMsgManage();

private:
	/************************************************************************
	Function:       initUI()
	Description:    ��ʼ��ui
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void initUI();

private:
	Q_DECLARE_PRIVATE(CMonitorWindow);
	QScopedPointer<CMonitorWindowPrivate> d_ptr;
};
