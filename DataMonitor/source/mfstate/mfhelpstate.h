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
#ifndef CMFHELPSTATE_H
#define CMFHELPSTATE_H
#include "mfbaseletstate.h"

class CMFHelpState:public CMFBaseState
{
	Q_OBJECT
public:
	/************************************************************************
	Function:       CMFHelpState()
	Description:    ���캯��
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CMFHelpState(QMenuBar * _menuBar,QMap<QString,QToolBar *> *_toolBars,QMainWindow* _mainWindow,QStatusBar*_mainStatusBar);

	/************************************************************************
	Function:       ~CMFHelpState()
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	~CMFHelpState();

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
