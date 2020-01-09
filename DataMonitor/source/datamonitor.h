/********************************************************************
Copyright (C), 2013, ���ӿƼ���ѧ.
FileName:    datamonitor.h
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
#pragma once

#include <QMainWindow>
#include <QMap>

class QMenuBar;
class Ui_DataMonitorClass;
class CMessageProcessManage;
class CMonitorMsgManage;
class CMFBaseState;
class CFileManageView;
class CInfoBoardView;
class CMonitorWindow;

class CDataMonitor : public QMainWindow
{
	Q_OBJECT

public:
	/************************************************************************
	Function:       CDataMonitor()
	Description:    ���캯��
	Input:          parent ������
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CDataMonitor(QWidget *parent = Q_NULLPTR);

	/************************************************************************
	Function:       ~CDataMonitor()
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	~CDataMonitor();

	/************************************************************************
	Function:       closeWD()
	Description:    �ر����д򿪵Ĵ���
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void closeWD();

	/************************************************************************
	Function:       setIsCloseStartNewProgress()
	Description:    �����ڹرյ�ʱ���Ƿ�������һ���³���
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void setIsCloseStartNewProgress(bool flag) { m_isCloseStartNewProgress = flag; }

	/************************************************************************
	Function:       getMonitorWindow()
	Description:    ��ȡ����
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CMonitorWindow *getMonitorWindow() { return m_window; }

	/************************************************************************
	Function:       getInfoBoardDock()
	Description:    ��ȡ��Ϣ��
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	QDockWidget *getInfoBoardDock();

	/************************************************************************
	Function:       getNodeInfoDock()
	Description:    ��ȡ�ڵ���Ϣ��
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	QDockWidget *getNodeInfoDock();

	/************************************************************************
	Function:       addInfoDockWidget()
	Description:    �����Ϣ��
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void addInfoDockWidget(bool infoFlag=true);

	/************************************************************************
	Function:       removeInfoDockWidget()
	Description:    �޳���Ϣ��
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void removeInfoDockWidget();

protected:
	/************************************************************************
	Function:       closeEvent()
	Description:    �˳��¼�
	Input:          event �¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void closeEvent(QCloseEvent * event);

	bool nativeEvent(const QByteArray &eventType, void *message, long *result);
private:
	/************************************************************************
	Function:       initUI()
	Description:    ��ʼ��ui
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void initUI();

	/************************************************************************
	Function:       initMenuAction()
	Description:    ��ʼ���˵����toolbar
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void initMenuAction();

private slots:
	/************************************************************************
	Function:       changeModelTypeSlot()
	Description:    �л�ģʽ
	Input:          type ģʽ
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void changeModeTypeSlot(unsigned short type);

	/************************************************************************
	Function:       changeModelSlot()
	Description:    �л�ģʽ
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void changeModeSlot();

	/************************************************************************
	Function:       timeoutChangeModeSlot()
	Description:    �л�ģʽ
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void timeoutChangeModeSlot();

private:
	Ui_DataMonitorClass                   *ui                               = nullptr;       //ui�ļ�
	bool                                  m_isCloseStartNewProgress         = false;         //�ڹرյ�ʱ���Ƿ�������һ���³���
	CMonitorMsgManage                     *m_monitorMsgManage               = nullptr;       //��Ϣ����
	QMenuBar                              *m_menubar                        = nullptr;		 //�˵���
	QMap<QString, QToolBar *>             m_toolBars;                                        //������
	QVector<CMFBaseState *>               m_vMFstate;                                        //�˵���
	QDockWidget                           *m_infoBoardDock                  = nullptr;       //��Ϣ��ʾ
	QDockWidget                           *m_nodeInfoDock                   = nullptr;       //�ڵ���Ϣ��ʾ
	CMonitorWindow                        *m_window                         = nullptr;       //��ʾ����
	unsigned short                         nextType                         = 0;             //��һ����Ϣ
	QTimer                                *nextTypeTimer                    = nullptr;       //��һ�����ͼ��
};
