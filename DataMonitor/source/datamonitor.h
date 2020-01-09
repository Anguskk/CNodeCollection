/********************************************************************
Copyright (C), 2013, 电子科技大学.
FileName:    datamonitor.h
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
	Description:    构造函数
	Input:          parent 父窗口
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CDataMonitor(QWidget *parent = Q_NULLPTR);

	/************************************************************************
	Function:       ~CDataMonitor()
	Description:    析构函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	~CDataMonitor();

	/************************************************************************
	Function:       closeWD()
	Description:    关闭所有打开的窗口
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void closeWD();

	/************************************************************************
	Function:       setIsCloseStartNewProgress()
	Description:    设置在关闭的时候是否重启动一个新程序
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void setIsCloseStartNewProgress(bool flag) { m_isCloseStartNewProgress = flag; }

	/************************************************************************
	Function:       getMonitorWindow()
	Description:    获取窗口
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CMonitorWindow *getMonitorWindow() { return m_window; }

	/************************************************************************
	Function:       getInfoBoardDock()
	Description:    获取信息栏
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	QDockWidget *getInfoBoardDock();

	/************************************************************************
	Function:       getNodeInfoDock()
	Description:    获取节点信息栏
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	QDockWidget *getNodeInfoDock();

	/************************************************************************
	Function:       addInfoDockWidget()
	Description:    添加信息栏
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void addInfoDockWidget(bool infoFlag=true);

	/************************************************************************
	Function:       removeInfoDockWidget()
	Description:    剔除信息栏
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void removeInfoDockWidget();

protected:
	/************************************************************************
	Function:       closeEvent()
	Description:    退出事件
	Input:          event 事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void closeEvent(QCloseEvent * event);

	bool nativeEvent(const QByteArray &eventType, void *message, long *result);
private:
	/************************************************************************
	Function:       initUI()
	Description:    初始化ui
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void initUI();

	/************************************************************************
	Function:       initMenuAction()
	Description:    初始化菜单项和toolbar
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void initMenuAction();

private slots:
	/************************************************************************
	Function:       changeModelTypeSlot()
	Description:    切换模式
	Input:          type 模式
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void changeModeTypeSlot(unsigned short type);

	/************************************************************************
	Function:       changeModelSlot()
	Description:    切换模式
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void changeModeSlot();

	/************************************************************************
	Function:       timeoutChangeModeSlot()
	Description:    切换模式
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void timeoutChangeModeSlot();

private:
	Ui_DataMonitorClass                   *ui                               = nullptr;       //ui文件
	bool                                  m_isCloseStartNewProgress         = false;         //在关闭的时候是否重启动一个新程序
	CMonitorMsgManage                     *m_monitorMsgManage               = nullptr;       //信息管理
	QMenuBar                              *m_menubar                        = nullptr;		 //菜单栏
	QMap<QString, QToolBar *>             m_toolBars;                                        //工具栏
	QVector<CMFBaseState *>               m_vMFstate;                                        //菜单栏
	QDockWidget                           *m_infoBoardDock                  = nullptr;       //信息显示
	QDockWidget                           *m_nodeInfoDock                   = nullptr;       //节点信息显示
	CMonitorWindow                        *m_window                         = nullptr;       //显示窗口
	unsigned short                         nextType                         = 0;             //下一个消息
	QTimer                                *nextTypeTimer                    = nullptr;       //下一个类型检查
};
