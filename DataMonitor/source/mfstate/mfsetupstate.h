/********************************************************************
Copyright (C), 2013, ���ӿƼ���ѧ.
FileName:    mfeditstate.h
Author:      LYH
Version:     V1.0
Date:        2013/09/11
Description:             ///ģ������
                            ���ļ���Ҫ�����Ա�����ϵ����������.
Other:                   ///����������
Function List:           ///��Ҫ�������书��
History:                 ///��ʷ�޸ļ�¼
<author>    <time>    <version>     <desc>
********************************************************************/
#ifndef CMFSETUPSTATE_H
#define CMFSETUPSTATE_H

#include "mfbaseletstate.h"

class CMFSetupState:public CMFBaseState
{
	Q_OBJECT
public:
	/************************************************************************
	Function:       CMFSetupState()
	Description:    ���캯��
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CMFSetupState(QMenuBar * _menuBar,QMap<QString,QToolBar *> *_toolBars,QMainWindow* _mainWindow,QStatusBar*_mainStatusBar);

	/************************************************************************
	Function:       ~CMFSetupState()
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	~CMFSetupState();

private:
	/************************************************************************
	Function:       creatAction()
	Description:    ������ť
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void creatAction();
};

#endif
