/********************************************************************
Copyright (C), 2013, 电子科技大学.
FileName:    mftoolstate.cpp
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
Description:    构造函数
Input:          无
Output:         无
Return:         无
Others:         无
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
	creatAction();  //创建层位组Action
}

/************************************************************************
Function:       ~CMFToolState()
Description:    析构函数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CMFToolState::~CMFToolState()
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


