/********************************************************************
Copyright (C), 2016, ���ӿƼ���ѧ.
FileName:    graphicsviewstate.h
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
    Description:    ���캯������ʼ������
    Input:          ��
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
	CGraphicsViewState(CMonitorWindow *window,bool resumable = true);

    /************************************************************************
    Function:       ~CGraphicsViewState()
    Description:    �����������ͷ�����
    Input:          ��
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    ~CGraphicsViewState();

	/************************************************************************
	Function:       getName()
	Description:    ��ȡ����
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	QString getName();

    /************************************************************************
    Function:       initialize()
    Description:    ��ʼ��
    Input:          ��
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    virtual void initialize(){}

    /************************************************************************
    Function:       getAction()
    Description:    ��ȡ��ǰ������ť
    Input:          ��
    Output:         ��
    Return:         ��ǰ������ť
    Others:         ��
    ************************************************************************/
	QAction *getAction();

    /************************************************************************
    Function:       trigger()
    Description:    ���ǰ��ť
    Input:          ��
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    void trigger();

    /************************************************************************
    Function:       getResumable()
    Description:    ��ȡ״̬�Ƿ�ɻָ�
    Input:          ��
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
	bool getResumable();

    /************************************************************************
    Function:       setInitFlag()
    Description:    �����Ƿ����״̬
    Input:          _initFlag ���״̬
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
	void setInitFlag(bool _initFlag);

    /************************************************************************
    Function:       getInitFlag()
    Description:    ��ȡ�Ƿ����״̬
    Input:          ��
    Output:         ��
    Return:         ���״̬
    Others:         ��
    ************************************************************************/
	bool getInitFlag();

    /************************************************************************
    Function:       setWindow()
    Description:    ����������
    Input:          _window ������
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    void setWindow(CMonitorWindow *_window);

	/************************************************************************
	Function:       getWindow()
	Description:    ��ȡ������
	Input:          ��
	Output:         ��
	Return:         ������
	Others:         ��
	************************************************************************/
	CMonitorWindow *getWindow();

    /************************************************************************
    Function:       linkProcess()
    Description:    ����ʱ�����д�����������
    Input:          ��
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    virtual void linkProcess(){}

    /************************************************************************
    Function:       mousePressEvent()
    Description:    ��갴���¼�
    Input:          event ����¼���widget �¼�����
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    virtual void mousePressEvent(QMouseEvent *event){}

    /************************************************************************
    Function:       mouseReleaseEvent()
    Description:    ����ͷ��¼�
    Input:          event ����¼���widget �¼�����
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    virtual void mouseReleaseEvent(QMouseEvent *event){}

    /************************************************************************
    Function:       mouseDoubleClickEvent()
    Description:    ���˫���¼�
    Input:          event ����¼���widget �¼�����
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    virtual void mouseDoubleClickEvent(QMouseEvent *event){}

    /************************************************************************
    Function:       mouseMoveEvent()
    Description:    ����ƶ��¼�
    Input:          event ����¼���widget �¼�����
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    virtual void mouseMoveEvent(QMouseEvent *event){}

#ifndef QT_NO_WHEELEVENT
    /************************************************************************
    Function:       wheelEvent()
    Description:    �������¼�
    Input:          event �����¼���widget �¼�����
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    virtual void wheelEvent(QWheelEvent *event);
#endif

    /************************************************************************
    Function:       keyPressEvent()
    Description:    ���̰����¼�
    Input:          event �����¼���widget �¼�����
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
	virtual void keyPressEvent(QKeyEvent *event);

    /************************************************************************
    Function:       keyReleaseEvent()
    Description:    �����ͷ��¼�
    Input:          event �����¼���widget �¼�����
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    virtual void keyReleaseEvent(QKeyEvent *event){}

    /************************************************************************
    Function:       focusInEvent()
    Description:    ��������¼�
    Input:          event �����¼���widget �¼�����
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    virtual void focusInEvent(QFocusEvent *event){}

    /************************************************************************
    Function:       focusOutEvent()
    Description:    �����뿪�¼�
    Input:          event �����¼���widget �¼�����
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    virtual void focusOutEvent(QFocusEvent *event){}

    /************************************************************************
    Function:       enterEvent()
    Description:    �����¼�
    Input:          event �¼���widget �¼�����
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    virtual void enterEvent(QEvent *event){}

    /************************************************************************
    Function:       leaveEvent()
    Description:    �뿪�¼�
    Input:          event �¼���widget �¼�����
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    virtual void leaveEvent(QEvent *event){}

    /************************************************************************
    Function:       contextMenuEvent()
    Description:    �Ҽ��˵��¼�
    Input:          event �Ҽ��˵��¼���widget �¼�����
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    virtual void contextMenuEvent(QContextMenuEvent *event){}

	/************************************************************************
	Function:       resizeEvent()
	Description:    ���ڴ�С�ı��¼�
	Input:          event ���ڴ�С�ı��¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	virtual void resizeEvent(QResizeEvent * event){}

public slots:
    /************************************************************************
    Function:       activateCurrentStateSlot()
    Description:    ���ǰ״̬
    Input:          ��
    Output:         ��
    Return:         ��
    Others:         ��
    ************************************************************************/
    virtual void activateCurrentStateSlot(){}

	/************************************************************************
	Function:       resize()
	Description:    ��С�ı�
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	virtual void resize() {}

private:
	Q_DECLARE_PRIVATE(CGraphicsViewState);
	QScopedPointer<CGraphicsViewStatePrivate> d_ptr;
};
