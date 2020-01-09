/*****************************************************************
**
** Copyright (C) 2016              电子科技大学实验室
**
** 该文件包含了MainAdvisor类，该类是主程序main函数的向导类，用于帮助
** 启动插件和平台。
**
** Provider：技术发展中心
** Author：刘郑
** Date：2016-01-16
******************************************************************/
#pragma once

#include <QObject>

class QSplashScreen;
class CDataMonitor;

class MainAdvisor : public QObject
{
	Q_OBJECT

public:
	MainAdvisor(QObject *parent = 0);
	~MainAdvisor();

	/***
	** 功能：启动平台
	** 参数：isShowSplash:是否显示闪屏，默认显示
	** 返回：无
	***/
	void start(bool isShowSplash = true);

private:
	CDataMonitor * m_platFormWindow;//平台向导
	QSplashScreen *m_splash;					//闪屏对象
};
