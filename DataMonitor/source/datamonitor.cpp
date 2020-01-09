/********************************************************************
Copyright (C), 2013, ���ӿƼ���ѧ.
FileName:    datamonitor.cpp
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
Description:    ���캯��
Input:          parent ������
Output:         ��
Return:         ��
Others:         ��
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
Description:    ��������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CDataMonitor::~CDataMonitor()
{
	//�ͷ�ui
	if (ui != nullptr) {
		delete ui;
		ui = nullptr;
	}

	//�ͷ�view
	if (m_window != nullptr) {
		delete m_window;
		m_window = nullptr;
	}

	//�Ƿ�����
	if (m_isCloseStartNewProgress) {
		QStringList arguments = QCoreApplication::arguments();
		arguments.removeAt(0);
		QProcess::startDetached(QCoreApplication::applicationFilePath(), arguments, QCoreApplication::applicationDirPath());
	}
}

/************************************************************************
Function:       closeWD()
Description:    �ر����д򿪵Ĵ���
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CDataMonitor::closeWD()
{

}

/************************************************************************
Function:       getInfoBoardDock()
Description:    ��ȡ��Ϣ��
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
QDockWidget * CDataMonitor::getInfoBoardDock()
{
	return m_infoBoardDock;
}

/************************************************************************
Function:       getNodeInfoDock()
Description:    ��ȡ�ڵ���Ϣ��
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
QDockWidget *CDataMonitor::getNodeInfoDock()
{
	return m_nodeInfoDock;
}

/************************************************************************
Function:       addInfoDockWidget()
Description:    �����Ϣ��
Input:          ��
Output:         ��
Return:         ��
Others:         ��
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
Description:    �޳���Ϣ��
Input:          ��
Output:         ��
Return:         ��
Others:         ��
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
Description:    �˳��¼�
Input:          event �¼�
Output:         ��
Return:         ��
Others:         ��
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
Description:    ��ʼ��ui
Input:          ��
Output:         ��
Return:         ��
Others:         ��
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
Description:    ��ʼ���˵����toolbar
Input:          ��
Output:         ��
Return:         ��
Others:         ��
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
Description:    �л�ģʽ
Input:          type ģʽ
Output:         ��
Return:         ��
Others:         ��
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
Description:    �л�ģʽ
Input:          ��
Output:         ��
Return:         ��
Others:         ��
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
Description:    �л�ģʽ
Input:          ��
Output:         ��
Return:         ��
Others:         ��
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
			//�ĸ�ģʽ
			if (strMessage == "DOWNLOAD") //����
			{
			}
			else if (strMessage == "ANNUALINSPECTION") //���
			{
			}
			else if (strMessage == "ANNUALINSPECTIONDOWNLOAD") //�������
			{
			}
			else if (strMessage == "CHARGING") //���
			{
			}
			*result = 1;
			return true;
		}
	}
	}

	return QWidget::nativeEvent(eventType, message, result);
}
