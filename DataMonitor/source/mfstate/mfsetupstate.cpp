/********************************************************************
Copyright (C), 2013, 电子科技大学.
FileName:    mfsetupstate.cpp
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
#include "mfsetupstate.h"

#include <QToolBar>
#include <QMenu>
#include <QMenuBar>

#include "Setup/setuptool.h"
#include "Setup/setupshelfTool.h"
#include "Setup/firmwareupgradetool.h"

/************************************************************************
Function:       CMFSetupState()
Description:    构造函数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CMFSetupState::CMFSetupState(QMenuBar * _menuBar,QMap<QString,QToolBar *> *_toolBars,QMainWindow* _mainWindow,QStatusBar*_mainStatusBar)
{
	m_name = "CMFSetupState";
	m_mainMenuBar = _menuBar;
	m_toolBars = _toolBars;
	m_mainWindow = _mainWindow;
	m_mainStatusBar = _mainStatusBar;

	m_menu = new QMenu(tr("Setup"));
	m_mainMenuBar->addMenu(m_menu);
	creatAction();  //创建层位组Action
}

/************************************************************************
Function:       ~CMFSetupState()
Description:    析构函数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CMFSetupState::~CMFSetupState()
{

}

/************************************************************************
Function:       creatAction()
Description:    创建按钮
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CMFSetupState::creatAction()
{
	//setting
	QToolBar *t_setupToolBar = new QToolBar(tr("Setup"));
	m_toolBars->insert(QString("Setup"), t_setupToolBar);

	CSetupShelfTool *t_setupShelfTool = new CSetupShelfTool();
	t_setupShelfTool->init(t_setupToolBar, m_menu, QIcon(":/DataMonitor/setshelfs.png"), tr("Setup Shelf"), m_mainWindow);
	m_Tools.append(t_setupShelfTool);
	t_setupShelfTool->setToolsActionState(true);

	CFirmwareUpgradeTool *t_firmwareUpgradeTool = new CFirmwareUpgradeTool();
	t_firmwareUpgradeTool->init(t_setupToolBar, m_menu, QIcon(":/DataMonitor/firmwareupgrade.png"), tr("Firmware Upgrade"), m_mainWindow);
	m_Tools.append(t_firmwareUpgradeTool);
	t_firmwareUpgradeTool->setToolsActionState(true);

	CSetupTool *t_setupTool = new CSetupTool();
	t_setupTool->init(t_setupToolBar, m_menu, QIcon(":/DataMonitor/setup.png"), tr("Setting"), m_mainWindow);
	m_Tools.append(t_setupTool);
	t_setupTool->setToolsActionState(true);
}


