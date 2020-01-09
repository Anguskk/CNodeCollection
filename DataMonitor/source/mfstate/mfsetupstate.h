/********************************************************************
Copyright (C), 2013, 电子科技大学.
FileName:    mfeditstate.h
Author:      LYH
Version:     V1.0
Date:        2013/09/11
Description:             ///模块描述
                            该文件主要负责成员及类关系的声明或定义.
Other:                   ///其他的描述
Function List:           ///主要函数及其功能
History:                 ///历史修改记录
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
	Description:    构造函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CMFSetupState(QMenuBar * _menuBar,QMap<QString,QToolBar *> *_toolBars,QMainWindow* _mainWindow,QStatusBar*_mainStatusBar);

	/************************************************************************
	Function:       ~CMFSetupState()
	Description:    析构函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	~CMFSetupState();

private:
	/************************************************************************
	Function:       creatAction()
	Description:    创建按钮
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void creatAction();
};

#endif
