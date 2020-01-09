/********************************************************************
Copyright (C), 2013, 电子科技大学.
FileName:    datamonitor.cpp
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
#include "datamonitor.h"

#include <QProcess>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDockWidget>
#include <QTimer>

#include "messagesnodedefinition.h"

#include "ui_datamonitor.h"
#include "platform.h"
#include "mffilestate.h"
#include "mfsetupstate.h"
#include "mftoolstate.h"
#include "mfhelpstate.h"
#include "infoboardview.h"
#include "monitorwindow.h"
#include "graphicsshelfitem.h"
#include "monitormsgmanage.h"
#include <qt_windows.h>
const ULONG_PTR CUSTOM_TYPE = 10000;
/************************************************************************
Function:       CDataMonitor()
Description:    构造函数
Input:          parent 父窗口
Output:         无
Return:         无
Others:         无
************************************************************************/
CDataMonitor::CDataMonitor(QWidget *parent)
	: QMainWindow(parent)
{
	ui = new Ui_DataMonitorClass;
	ui->setupUi(this);

	nextTypeTimer = new QTimer(this);
	connect(nextTypeTimer, SIGNAL(timeout()), this, SLOT(timeoutChangeModeSlot()));

	initUI();
	//initMenuAction();
}

/************************************************************************
Function:       ~CDataMonitor()
Description:    析构函数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CDataMonitor::~CDataMonitor()
{
	//释放ui
	if (ui != nullptr) {
		delete ui;
		ui = nullptr;
	}

	//释放view
	if (m_window != nullptr) {
		delete m_window;
		m_window = nullptr;
	}

	//是否重启
	if (m_isCloseStartNewProgress) {
		QStringList arguments = QCoreApplication::arguments();
		arguments.removeAt(0);
		QProcess::startDetached(QCoreApplication::applicationFilePath(), arguments, QCoreApplication::applicationDirPath());
	}
}

/************************************************************************
Function:       closeWD()
Description:    关闭所有打开的窗口
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CDataMonitor::closeWD()
{

}

/************************************************************************
Function:       getInfoBoardDock()
Description:    获取信息栏
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
QDockWidget * CDataMonitor::getInfoBoardDock()
{
	return m_infoBoardDock;
}

/************************************************************************
Function:       getNodeInfoDock()
Description:    获取节点信息栏
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
QDockWidget *CDataMonitor::getNodeInfoDock()
{
	return m_nodeInfoDock;
}

/************************************************************************
Function:       addInfoDockWidget()
Description:    添加信息栏
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CDataMonitor::addInfoDockWidget(bool infoFlag/* = true*/)
{
	if (nullptr != m_infoBoardDock) {
		addDockWidget(Qt::BottomDockWidgetArea, m_infoBoardDock);
		m_infoBoardDock->show();
	}
	if (!infoFlag) {
		if (nullptr != m_nodeInfoDock) {
			addDockWidget(Qt::BottomDockWidgetArea, m_nodeInfoDock);
			m_nodeInfoDock->show();
			tabifyDockWidget(m_infoBoardDock, m_nodeInfoDock);
		}
	}
	m_infoBoardDock->raise();
}

/************************************************************************
Function:       removeInfoDockWidget()
Description:    剔除信息栏
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CDataMonitor::removeInfoDockWidget()
{
	if (nullptr != m_infoBoardDock) {
		removeDockWidget(m_infoBoardDock);
		m_infoBoardDock->hide();
	}
	if (nullptr != m_nodeInfoDock) {
		removeDockWidget(m_nodeInfoDock);
		m_nodeInfoDock->hide();
	}
}

/************************************************************************
Function:       closeEvent()
Description:    退出事件
Input:          event 事件
Output:         无
Return:         无
Others:         无
************************************************************************/
void CDataMonitor::closeEvent(QCloseEvent * event)
{
	int res = QMessageBox::information(this, tr("System Message"), tr("Are you sure exit this application?"), QMessageBox::Yes | QMessageBox::No);
	if (res == QMessageBox::No) {
		event->ignore();
	} else {
		closeWD();
		event->accept();
	}
}

/************************************************************************
Function:       initUI()
Description:    初始化ui
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CDataMonitor::initUI()
{
	m_infoBoardDock = new QDockWidget(this);
	m_infoBoardDock->setWindowTitle(tr("Information"));
	m_infoBoardDock->setAllowedAreas(Qt::BottomDockWidgetArea);
	auto infoBoardView = new CInfoBoardView(this);
	m_infoBoardDock->setWidget(infoBoardView);
	m_infoBoardDock->hide();

	m_nodeInfoDock = new QDockWidget(this);
	m_nodeInfoDock->setWindowTitle(tr("Download"));
	m_nodeInfoDock->setAllowedAreas(Qt::BottomDockWidgetArea);
	auto nodeInfoView = new CInfoBoardView(this);
	m_nodeInfoDock->setWidget(nodeInfoView);
	m_nodeInfoDock->hide();

	m_window = new CMonitorWindow;
	setCentralWidget(m_window);

	m_monitorMsgManage = new CMonitorMsgManage(m_window,m_infoBoardDock,m_nodeInfoDock);

	m_window->setMonitorMsgManage(m_monitorMsgManage);

	changeModeTypeSlot(DownloadRequestMsg);
}

/************************************************************************
Function:       initMenuAction()
Description:    初始化菜单项和toolbar
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CDataMonitor::initMenuAction()
{
	m_menubar = menuBar();

	CMFFileState *t_MFFileState = new CMFFileState(m_menubar, &m_toolBars, this, statusBar());
	m_vMFstate.append(t_MFFileState);

	CMFSetupState *t_MFSetupState = new CMFSetupState(m_menubar, &m_toolBars, this, statusBar());
	m_vMFstate.append(t_MFSetupState);

	CMFToolState *t_MFToolState = new CMFToolState(m_menubar, &m_toolBars, this, statusBar());
	m_vMFstate.append(t_MFToolState);

	CMFHelpState *t_MFHelpState = new CMFHelpState(m_menubar, &m_toolBars, this, statusBar());
	m_vMFstate.append(t_MFHelpState);

	addToolBar(m_toolBars["File"]);
	addToolBar(m_toolBars["Setup"]);
	addToolBar(m_toolBars["Tools"]);
}

/************************************************************************
Function:       changeModeTypeSlot()
Description:    切换模式
Input:          type 模式
Output:         无
Return:         无
Others:         无
************************************************************************/
void CDataMonitor::changeModeTypeSlot(unsigned short type)
{
	QVector<QPair<int, QString> > t_shelfIDs;
	t_shelfIDs = PlatForm::getAllShelfs();
	if (t_shelfIDs.isEmpty()) {
		QMessageBox::information(this, tr("Note"), tr("Please configure the shelf IP!"));
		return;
	}
	nextType = type;
	if (type == ChargingRequestMsg){
		changeModeSlot();
	} else {
		if (m_monitorMsgManage->changeModeStatus())
			changeModeSlot();
		else
			nextTypeTimer->start(1000);
	}
}

/************************************************************************
Function:       changeModelSlot()
Description:    切换模式
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CDataMonitor::changeModeSlot()
{
	QVector<QPair<int, QString> > t_shelfIDs;
	t_shelfIDs = PlatForm::getAllShelfs();

	m_monitorMsgManage->changeModeTypeSlot(nextType, t_shelfIDs);

	if (nextType == AnnualInspectionDownloadRequestMsg || nextType == DownloadRequestMsg)
		addInfoDockWidget(false);
	else
		addInfoDockWidget();

	nextType = 0;
}

/************************************************************************
Function:       timeoutChangeModeSlot()
Description:    切换模式
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CDataMonitor::timeoutChangeModeSlot()
{
	if (!m_monitorMsgManage->changeModeStatus())
		return;
	
	changeModeSlot();
	nextTypeTimer->stop();
}

bool CDataMonitor::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	MSG *param = static_cast<MSG *>(message);

	switch (param->message)
	{
	case WM_COPYDATA:
	{
		COPYDATASTRUCT *cds = reinterpret_cast<COPYDATASTRUCT*>(param->lParam);
		if (cds->dwData == CUSTOM_TYPE)
		{
			QString strMessage = QString::fromUtf8(reinterpret_cast<char*>(cds->lpData), cds->cbData);
			//四个模式
			if (strMessage == "DOWNLOAD") //下载
			{
			}
			else if (strMessage == "ANNUALINSPECTION") //年检
			{
			}
			else if (strMessage == "ANNUALINSPECTIONDOWNLOAD") //年检下载
			{
			}
			else if (strMessage == "CHARGING") //充电
			{
			}
			*result = 1;
			return true;
		}
	}
	}

	return QWidget::nativeEvent(eventType, message, result);
}
