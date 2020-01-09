/********************************************************************
Copyright (C), 2013, 电子科技大学.
FileName:    mffilestate.cpp
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
#include "mffilestate.h"

#include <QToolBar>
#include <QMenu>
#include <QMenuBar>

#include "file/exittool.h"
#include "file/connecttool.h"

/************************************************************************
Function:       CMFFileState()
Description:    构造函数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CMFFileState::CMFFileState(QMenuBar * _menuBar,QMap<QString,QToolBar *> *_toolBars,QMainWindow* _mainWindow,QStatusBar*_mainStatusBar)
{
	m_name = "CMFFileState";
	m_mainMenuBar = _menuBar;
	m_toolBars = _toolBars;
	m_mainWindow = _mainWindow;
	m_mainStatusBar = _mainStatusBar;

	m_menu = new QMenu(tr("File"));
	m_mainMenuBar->addMenu(m_menu);
	creatAction();  //创建层位组Action
}

/************************************************************************
Function:       ~CMFFileState()
Description:    析构函数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CMFFileState::~CMFFileState()
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
void CMFFileState::creatAction()
{
	QToolBar *t_fileToolBar = new QToolBar(tr("File"));
	m_toolBars->insert(QString("File"), t_fileToolBar);

	CConnectTool *t_connectTool = new CConnectTool();
	t_connectTool->init(t_fileToolBar, m_menu, QIcon(":/DataMonitor/connect.png"), tr("Connect"), m_mainWindow);
	m_Tools.append(t_connectTool);
	t_connectTool->setToolsActionState(true);

	m_menu->addSeparator();
	CExitTool *t_ExitTool = new CExitTool();
	t_ExitTool->init(NULL, m_menu, QIcon(), tr("Exit"), m_mainWindow);
	m_Tools.append(t_ExitTool);
	t_ExitTool->setToolsActionState(true);
}


