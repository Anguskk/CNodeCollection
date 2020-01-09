/********************************************************************
Copyright (C), 2013, ���ӿƼ���ѧ.
FileName:    mfhelpstate.cpp
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
#include "mfhelpstate.h"

#include <QToolBar>
#include <QMenu>
#include <QMenuBar>

#include "Help/languagetool.h"
#include "help/abouttools.h"

/************************************************************************
Function:       CMFHelpState()
Description:    ���캯��
Input:          ��
Output:         ��
Return:         ��
Others:         ��
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
	creatAction();  //������λ��Action
}

/************************************************************************
Function:       ~CMFHelpState()
Description:    ��������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CMFHelpState::~CMFHelpState()
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


