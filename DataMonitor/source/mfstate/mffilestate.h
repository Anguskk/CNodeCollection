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
#ifndef CMFFILESTATE_H
#define CMFFILESTATE_H

#include "mfbaseletstate.h"

class CMFFileState:public CMFBaseState
{
	Q_OBJECT
public:
	/************************************************************************
	Function:       CMFFileState()
	Description:    ���캯��
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CMFFileState(QMenuBar * _menuBar, QMap<QString, QToolBar *> *_toolBars, QMainWindow* _mainWindow, QStatusBar*_mainStatusBar);

	/************************************************************************
	Function:       ~CMFFileState()
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	~CMFFileState();

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
