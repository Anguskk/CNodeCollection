/*****************************************************************
**
** Copyright (C) 2008          ���ӿƼ���ѧʵ����
**
** ���ļ�������PlatformConfig�������ṩ�������ƽ̨�������й����е�������Ϣ
** ������setting�ķ�ʽ���ڸ�Ŀ¼��
**
** Provider��
** Author��
** Date��
******************************************************************/
#include "platformconfig.h"
#include <QDir>
#include <QApplication>
const QString PlatformConfig::PRO_PROJECT_DIR = "pro_project_dir";
const QString PlatformConfig::PRO_RECENT_PROJECT = "pro_recent_project";
const QString PlatformConfig::PLATFORM_LANGUAGE = "platform_language";//ƽ̨��ѡ����

/***
** ���ܣ����췽��
** ��������
** ���أ���
***/
PlatformConfig::PlatformConfig()
{
	QString path = QDir::homePath() +QDir::separator()+ "datamonitorconfig.ini";
	setting = new QSettings(path,QSettings::IniFormat);
}

/***
** ���ܣ���������
** ��������
** ���أ���
***/
PlatformConfig::~PlatformConfig()
{
	delete setting;
}

/************************************************************************
Function:       clear()
Description:    ���
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void PlatformConfig::clear()
{
	setting->clear();
}

/************************************************************************
Function:       beginGroup()
Description:    ��ʼ����
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void PlatformConfig::beginGroup(const QString & prefix)
{
	QString t_curPrefix = prefix;
	if (t_curPrefix.isEmpty())
		t_curPrefix = "General";
	setting->beginGroup(prefix);
}

/************************************************************************
Function:       endGroup()
Description:    ��������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void PlatformConfig::endGroup()
{
	setting->endGroup();
}

/************************************************************************
Function:       allKeys()
Description:    ��ȡ����keys
Input:          ��
Output:         ��
Return:         ����keys
Others:         ��
************************************************************************/
QStringList PlatformConfig::allKeys() const
{
	return setting->allKeys();
}

/***
** ���ܣ���ȡָ����key��ֵ
** ������key:�����ԵĹؼ���
** ���أ������Ե�ֵ
***/
QVariant PlatformConfig::read(const QString &key)
{
	return setting->value(key);
}

/***
** ���ܣ����ļ���д��ָ���ؼ��ֵ�����
** ������key:�����ԵĹؼ���
**		 value:����ֵ
** ���أ���
***/
void PlatformConfig::write(const QString &key,const QVariant & value)
{
	setting->setValue(key,value);
}
