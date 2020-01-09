/*****************************************************************
**
** Copyright (C) 2008          电子科技大学实验室
**
** 该文件包含类PlatformConfig，该类提供整个插件平台的在运行过程中的配置信息
** 配置以setting的方式存在根目录下
**
** Provider：
** Author：
** Date：
******************************************************************/
#include "platformconfig.h"
#include <QDir>
#include <QApplication>
const QString PlatformConfig::PRO_PROJECT_DIR = "pro_project_dir";
const QString PlatformConfig::PRO_RECENT_PROJECT = "pro_recent_project";
const QString PlatformConfig::PLATFORM_LANGUAGE = "platform_language";//平台首选语言

/***
** 功能：构造方法
** 参数：无
** 返回：无
***/
PlatformConfig::PlatformConfig()
{
	QString path = QDir::homePath() +QDir::separator()+ "datamonitorconfig.ini";
	setting = new QSettings(path,QSettings::IniFormat);
}

/***
** 功能：析构方法
** 参数：无
** 返回：无
***/
PlatformConfig::~PlatformConfig()
{
	delete setting;
}

/************************************************************************
Function:       clear()
Description:    清除
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void PlatformConfig::clear()
{
	setting->clear();
}

/************************************************************************
Function:       beginGroup()
Description:    开始分组
Input:          无
Output:         无
Return:         无
Others:         无
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
Description:    结束分组
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void PlatformConfig::endGroup()
{
	setting->endGroup();
}

/************************************************************************
Function:       allKeys()
Description:    获取所有keys
Input:          无
Output:         无
Return:         所有keys
Others:         无
************************************************************************/
QStringList PlatformConfig::allKeys() const
{
	return setting->allKeys();
}

/***
** 功能：读取指定的key的值
** 参数：key:该属性的关键字
** 返回：该属性的值
***/
QVariant PlatformConfig::read(const QString &key)
{
	return setting->value(key);
}

/***
** 功能：向文件中写入指定关键字的属性
** 参数：key:该属性的关键字
**		 value:属性值
** 返回：无
***/
void PlatformConfig::write(const QString &key,const QVariant & value)
{
	setting->setValue(key,value);
}
