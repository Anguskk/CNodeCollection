/*****************************************************************
**
** Copyright (C) 2016              ���ӿƼ���ѧʵ����
**
** ���ļ�������MainAdvisor�࣬������������main���������࣬���ڰ���
** ���������ƽ̨��
**
** Provider��������չ����
** Author����֣
** Date��2016-01-16
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
** ���ܣ����췽��
** ��������
** ���أ���
***/
MainAdvisor::MainAdvisor(QObject *parent)
	: QObject(parent)
{
	QPixmap pixmap(":COMGUI/splash.png");
	m_splash = new QSplashScreen(pixmap);
}

/***
** ���ܣ���������
** ��������
** ���أ���
***/
MainAdvisor::~MainAdvisor()
{
	delete m_platFormWindow;
}

/***
** ���ܣ�����ƽ̨
** ������isShowSplash:�Ƿ���ʾ����
** ���أ���
***/
void MainAdvisor::start(bool isShowSplash)
{
	if (isShowSplash)//��ʾ����
		m_splash->show();
	/**********2014-5-8��ӽ���**********/
	
	QString language = PlatForm::getPlatformLanguage();			//��ȡƽ̨��Ĭ�ϵ�����
	if(!language.isEmpty())
	{
		PlatForm::internationalizationForPlatform(language);	//���ʻ�ƽ̨
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
