/********************************************************************
Copyright (C), 2016, ���ӿƼ���ѧ.
FileName:    monitorbasestate.h
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
    Description:    ���캯������ʼ������
    Input:          ��
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
	CMonitorBaseState(CMonitorWindow *window,bool resumable = true);

    /************************************************************************
    Function:       ~CMonitorBaseState()
    Description:    �����������ͷ�����
    Input:          ��
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    ~CMonitorBaseState();

    /************************************************************************
    Function:       contextMenuEvent()
    Description:    �Ҽ��˵��¼�
    Input:          event �Ҽ��˵��¼���widget �¼�����
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
	virtual void contextMenuEvent(QContextMenuEvent *event) override;

	/************************************************************************
	Function:       resizeEvent()
	Description:    ���ڴ�С�ı��¼�
	Input:          event ���ڴ�С�ı��¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	virtual void resizeEvent(QResizeEvent * event) override;

public slots:
    /************************************************************************
    Function:       activateCurrentStateSlot()
    Description:    ���ǰ״̬
    Input:          ��
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    virtual void activateCurrentStateSlot() override;

	/************************************************************************
	Function:       resize()
	Description:    ��С�ı�
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	virtual void resize() override;

private:
	/************************************************************************
	Function:       calculateSize()
	Description:    �������м���
	Input:          event �¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void calculateSize();

private:
	Q_DECLARE_PRIVATE(CMonitorBaseState);
	QScopedPointer<CMonitorBaseStatePrivate> d_ptr;
};
