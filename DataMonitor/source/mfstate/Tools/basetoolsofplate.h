/*
* Copyright (c) 2018,电子科技大学地学信息协同创新中心复杂多维信息处理团队
* All rights reserved.
* 
* 文件名称：basemodel.h
* 文件标识：见配置管理计划书
* 摘    要：平台操作工具，主要包括工区的保存、打开以及数据的导入导出等
* 
* 当前版本：1.0
* 作    者：鲁才
* 完成日期：2018年5月20日
*
*/
#pragma once

#include <QAction>
#include <QToolBar>
#include <QMenu>
#include <QIcon>

class CDataLibManage;
class CBaseToolofPlate: public QObject
{
	Q_OBJECT

public:
	CBaseToolofPlate();
	virtual ~CBaseToolofPlate();

	void init(QToolBar * toolbar,QMenu * menu,QIcon icon,QString text,QMainWindow *pwd,bool bActionchecked = false,QActionGroup *actionGroup=nullptr);

	void setToolsState(bool flag);

	void setToolsActionState(bool flag);
	
	virtual void closeSubWd();

public slots:
	virtual void OnInitialize(){}

protected:
    QAction*            m_action;               //触发Action
	QMainWindow *       m_pwd;                  //主窗口
	bool                m_bActicon;             //该状态控制action不受外部控制 true 默认控制 
	bool                m_bupdateDataFlag;      // 是否更新数据管理库
};
