/********************************************************************
Copyright (C), 2013, 电子科技大学.
FileName:    mfhelpstate.cpp
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
#include "mfhelpstate.h"

#include <QToolBar>
#include <QMenu>
#include <QMenuBar>

#include "Help/languagetool.h"
#include "help/abouttools.h"

/************************************************************************
Function:       CMFHelpState()
Description:    构造函数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CMFHelpState::CMFHelpState(QMenuBar * _menuBar,QMap<QString,QToolBar *> *_toolBars,QMainWindow* _mainWindow,QStatusBar*_mainStatusBar)
{
	m_name = "CMFHelpState";
	m_mainMenuBar = _menuBar;
	m_toolBars = _toolBars;
	m_mainWindow = _mainWindow;
	m_mainStatusBar = _mainStatusBar;

	m_menu = new QMenu(tr("Help"));
	m_mainMenuBar->addMenu(m_menu);
	creatAction();  //创建层位组Action
}

/************************************************************************
Function:       ~CMFHelpState()
Description:    析构函数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CMFHelpState::~CMFHelpState()
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
void CMFHelpState::creatAction()
{
	QToolBar *t_helpToolBar = new QToolBar(tr("Help"));
	m_toolBars->insert(QString("Help"), t_helpToolBar);

	/*CLanguageTool *t_languageTool = new CLanguageTool();
	t_languageTool->init(t_helpToolBar, m_menu, QIcon(), tr("Language"), m_mainWindow, false);
	m_Tools.append(t_languageTool);
	t_languageTool->setToolsActionState(true);*/

	CAboutTools *t_aboutTools = new CAboutTools();
	t_aboutTools->init(t_helpToolBar, m_menu, QIcon(), tr("About"), m_mainWindow);
	m_Tools.append(t_aboutTools);
	t_aboutTools->setToolsActionState(true);
}


