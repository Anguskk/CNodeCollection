/********************************************************************
Copyright (C), 2013, ���ӿƼ���ѧ.
FileName:    mffilestate.cpp
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
#include "mffilestate.h"

#include <QToolBar>
#include <QMenu>
#include <QMenuBar>

#include "file/exittool.h"
#include "file/connecttool.h"

/************************************************************************
Function:       CMFFileState()
Description:    ���캯��
Input:          ��
Output:         ��
Return:         ��
Others:         ��
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
	creatAction();  //������λ��Action
}

/************************************************************************
Function:       ~CMFFileState()
Description:    ��������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CMFFileState::~CMFFileState()
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


