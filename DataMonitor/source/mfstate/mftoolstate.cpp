/********************************************************************
Copyright (C), 2013, ���ӿƼ���ѧ.
FileName:    mftoolstate.cpp
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
#include "mftoolstate.h"

#include <QToolBar>
#include <QMenu>
#include <QMenuBar>

#include "Tools/annualinspectiontool.h"
#include "Tools/annualinspectionreporttool.h"
#include "Tools/annualinspectiondownloadtool.h"
#include "Tools/downloadtool.h"
#include "Tools/chargingtool.h"

/************************************************************************
Function:       CMFToolState()
Description:    ���캯��
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CMFToolState::CMFToolState(QMenuBar * _menuBar,QMap<QString,QToolBar *> *_toolBars,QMainWindow* _mainWindow,QStatusBar*_mainStatusBar)
{
	m_name = "CMFToolState";
	m_mainMenuBar = _menuBar;
	m_toolBars = _toolBars;
	m_mainWindow = _mainWindow;
	m_mainStatusBar = _mainStatusBar;

	m_menu = new QMenu(tr("Tools"));
	m_mainMenuBar->addMenu(m_menu);
	creatAction();  //������λ��Action
}

/************************************************************************
Function:       ~CMFToolState()
Description:    ��������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CMFToolState::~CMFToolState()
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
void CMFToolState::creatAction()
{
	QToolBar *t_toolBar = new QToolBar(tr("Tools"));
	m_toolBars->insert(QString("Tools"), t_toolBar);

	QActionGroup *actionGroup = new QActionGroup(this);

	CAnnualInspectionTool *t_annualInspectionTool = new CAnnualInspectionTool();
	t_annualInspectionTool->init(t_toolBar, m_menu, QIcon(":/DataMonitor/annualinspection.png"), tr("Annual Inspection"), m_mainWindow,true, actionGroup);
	m_Tools.append(t_annualInspectionTool);
	t_annualInspectionTool->setToolsActionState(true);

	CAnnualInspectionDownloadTool *t_annualInspectionDownloadTool = new CAnnualInspectionDownloadTool();
	t_annualInspectionDownloadTool->init(t_toolBar, m_menu, QIcon(":/DataMonitor/annualinspectiondownload.png"), tr("Annual Inspection Download"), m_mainWindow, true, actionGroup);
	m_Tools.append(t_annualInspectionDownloadTool);
	t_annualInspectionDownloadTool->setToolsActionState(true);

	CAnnualInspectionReportTool *t_annualInspectionReportTool = new CAnnualInspectionReportTool();
	t_annualInspectionReportTool->init(t_toolBar, m_menu, QIcon(":/DataMonitor/annualinspectionreport.png"), tr("Annual Inspection Report"), m_mainWindow);
	m_Tools.append(t_annualInspectionReportTool);
	t_annualInspectionReportTool->setToolsActionState(true);

	m_menu->addSeparator();
	CDownloadTool *t_downloadTool = new CDownloadTool();
	t_downloadTool->init(t_toolBar, m_menu, QIcon(":/DataMonitor/chargingdownload.png"), tr("Charging/Download"), m_mainWindow, true, actionGroup);
	m_Tools.append(t_downloadTool);
	t_downloadTool->setToolsActionState(true);

	/*m_menu->addSeparator();
	CChargingTool *t_chargingTool = new CChargingTool();
	t_chargingTool->init(t_toolBar, m_menu, QIcon(":/DataMonitor/charging.png"), tr("Charging"), m_mainWindow);
	m_Tools.append(t_chargingTool);
	t_chargingTool->setToolsActionState(true);*/
}


