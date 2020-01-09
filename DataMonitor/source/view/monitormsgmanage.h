/**************************************************************
Copyright (C),  2016   ���ӿƼ���ѧ.
FileName :  monitormsgmanage.h
Author :       lz
Version : V1.0
Date : 2016/8/30
Description :        ///ģ������ 
Other :              ///��������
Function List :      ///��Ҫ�������书��
History :            ///��ʷ�޸ļ�¼
<Author>    <Time>    <Version>    <Desc>
**************************************************************/
#pragma once

#include <QObject>

#include "messagesdefinition.h"

class QDockWidget;
class CMonitorWindow;

class CMonitorMsgManagePrivate;
class CMonitorMsgManage : public QObject
{
	Q_OBJECT

public:
	/************************************************************************
	Function:       CMonitorMsgManage()
	Description:    ���캯��
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CMonitorMsgManage(CMonitorWindow *window, QDockWidget *infoBoardDock,QDockWidget *nodeInfoDock);

	/************************************************************************
	Function:       ~CMonitorMsgManage()
	Description:    �����������ͷ�����
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	~CMonitorMsgManage();

	/************************************************************************
	Function:       changeModeStatus()
	Description:    �л�ģʽ״̬
					true--���нڵ�����ɻ��߶Ͽ����ӣ�
					false--�������ڽ��еĽڵ�
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	bool changeModeStatus();

	/************************************************************************
	Function:       currentModeStatus()
	Description:    ��ǰģʽ״̬
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	unsigned short currentModeStatus();

	/************************************************************************
	Function:       addMessage()
	Description:    �����Ϣ
	Input:          message ��Ϣ
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void addMessage(SMessageBase &message);

public slots:
	/************************************************************************
	Function:       changeModeTypeSlot()
	Description:    �л�ģʽ�����г��״̬������ʱ�л�������״̬��
	Input:          type ģʽ
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void changeModeTypeSlot(unsigned short type, QVector<QPair<int, QString> > shelfIDs);

	/************************************************************************
	Function:       changeModeSlot()
	Description:    �л�ģʽ
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void changeModeSlot();

	/************************************************************************
	Function:       processMsgSlot()
	Description:    ������Ϣ
	Input:          message ��Ϣ
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void processMsgSlot(const SMessageBase& message);

private:
	Q_DECLARE_PRIVATE(CMonitorMsgManage);
	QScopedPointer<CMonitorMsgManagePrivate> d_ptr;
};
