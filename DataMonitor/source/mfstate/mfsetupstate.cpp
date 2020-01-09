/********************************************************************
Copyright (C), 2013, ���ӿƼ���ѧ.
FileName:    mfsetupstate.cpp
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
#include "mfsetupstate.h"

#include <QToolBar>
#include <QMenu>
#include <QMenuBar>

#include "Setup/setuptool.h"
#include "Setup/setupshelfTool.h"
#include "Setup/firmwareupgradetool.h"

/************************************************************************
Function:       CMFSetupState()
Description:    ���캯��
Input:          ��
Output:         ��
Return:         ��
Others:         ��
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
	creatAction();  //������λ��Action
}

/************************************************************************
Function:       ~CMFSetupState()
Description:    ��������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CMFSetupState::~CMFSetupState()
{

}

/************************************************************************
Function:       creatAction()
Description:    ������ť
Input:          ��
Output:         ��
Return:         ��
Others:         ��
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


