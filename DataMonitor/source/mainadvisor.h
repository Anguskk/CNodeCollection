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
	** ���ܣ�����ƽ̨
	** ������isShowSplash:�Ƿ���ʾ������Ĭ����ʾ
	** ���أ���
	***/
	void start(bool isShowSplash = true);

private:
	CDataMonitor * m_platFormWindow;//ƽ̨��
	QSplashScreen *m_splash;					//��������
};
