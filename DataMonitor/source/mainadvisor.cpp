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
#include "mainadvisor.h"
#include <QPixmap>
#include <QSplashScreen>
#include <QSettings>
#include <QStringList>
#include <QLibrary>
#include <QDir>

#include "datamonitor.h"
#include "platform.h"

/***
** 功能：构造方法
** 参数：无
** 返回：无
***/
MainAdvisor::MainAdvisor(QObject *parent)
	: QObject(parent)
{
	QPixmap pixmap(":COMGUI/splash.png");
	m_splash = new QSplashScreen(pixmap);
}

/***
** 功能：析构方法
** 参数：无
** 返回：无
***/
MainAdvisor::~MainAdvisor()
{
	delete m_platFormWindow;
}

/***
** 功能：启动平台
** 参数：isShowSplash:是否显示闪屏
** 返回：无
***/
void MainAdvisor::start(bool isShowSplash)
{
	if (isShowSplash)//显示闪屏
		m_splash->show();
	/**********2014-5-8添加结束**********/
	
	QString language = PlatForm::getPlatformLanguage();			//获取平台的默认的语言
	if(!language.isEmpty())
	{
		PlatForm::internationalizationForPlatform(language);	//国际化平台
		m_splash->showMessage(tr("loading language package..."),Qt::AlignLeft | Qt::AlignBottom);
	}

	m_splash->showMessage(tr("checking the plugin register..."),Qt::AlignLeft | Qt::AlignBottom);
	
	m_platFormWindow = new CDataMonitor();
  
	m_splash->showMessage(tr("init finished."),Qt::AlignLeft | Qt::AlignBottom);
	m_platFormWindow->showMaximized();
	m_splash->finish(m_platFormWindow);
	delete m_splash;
	m_splash = NULL;
}
