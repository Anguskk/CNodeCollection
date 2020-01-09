/********************************************************************
Copyright (C), 2013, 电子科技大学.
FileName:    mffilestate.h
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
#ifndef CMFBASESTATE_H
#define CMFBASESTATE_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QVector>

class QToolBar;
class QMenu;
class QStatusBar;
class QMenuBar;
class QMainWindow;
class QTextStream;
class QTextEdit;
class CBaseToolofPlate;
class CFileManageView;
class CInfoBoardView;

using namespace std;

class CMFBaseState:public QObject
{
	Q_OBJECT
public:
	/************************************************************************
	Function:       CMFBaseState()
	Description:    构造函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CMFBaseState();

	/************************************************************************
	Function:       ~CMFBaseState()
	Description:    析构函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	virtual ~CMFBaseState();
		
public:
	/************************************************************************
	Function:       creatAction()
	Description:    创建按钮
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	virtual void creatAction() = 0;

	/************************************************************************
	Function:       setToolsState()
	Description:    设置工具是否可用
	Input:          flag true 可用 false 不可用
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void setToolsState(bool flag);

	virtual void closeSubWd();

	QString  getName();

protected:
	QString                                m_name;
	QMenuBar                               *m_mainMenuBar         = nullptr;         //菜单组
	QMap<QString,QToolBar *>               *m_toolBars            = nullptr;         //工具栏
	QMainWindow                            *m_mainWindow          = nullptr;         //主窗口
	QStatusBar                             *m_mainStatusBar       = nullptr;         //主状态栏
	QMenu                                  *m_menu                = nullptr;         //菜单栏
	QVector<CBaseToolofPlate*>             m_Tools;                                  //工具栏
};

#endif
