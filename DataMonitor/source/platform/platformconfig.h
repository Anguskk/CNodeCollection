/*****************************************************************
**
** Copyright (C) 2008          电子科技大学实验室
**
** 该文件包含类PlatformConfig，该类提供整个插件平台的在运行过程中的配置信息
** 配置以setting的方式存在根目录下
**
** Provider：
** Author：WangYong
** Date：2008-03-07
******************************************************************/
#ifndef PLATFORMCONFIG_H
#define PLATFORMCONFIG_H

#include <QSettings>
#include <QVariant>

class PlatformConfig
{
public:

	static const QString PRO_PROJECT_DIR;//当前工区所在的目录
	static const QString PRO_RECENT_PROJECT;//最近打开过的项目文件
	static const QString PLATFORM_LANGUAGE;//平台首选语言

	/***
	** 功能：构造方法
	** 参数：无
	** 返回：无
	***/
	PlatformConfig();

	/***
	** 功能：析构方法
	** 参数：无
	** 返回：无
	***/
	~PlatformConfig();

	/************************************************************************
	Function:       clear()
	Description:    清除
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void clear();

	/************************************************************************
	Function:       beginGroup()
	Description:    开始分组
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void beginGroup(const QString & prefix=QString());

	/************************************************************************
	Function:       endGroup()
	Description:    结束分组
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void endGroup();

	/************************************************************************
	Function:       allKeys()
	Description:    获取所有keys
	Input:          无
	Output:         无
	Return:         所有keys
	Others:         无
	************************************************************************/
	QStringList allKeys() const;

	/***
	** 功能：读取指定的key的值
	** 参数：key:该属性的关键字
	** 返回：该属性的值
	***/
	QVariant read(const QString &key);

	/***
	** 功能：向文件中写入指定关键字的属性
	** 参数：key:该属性的关键字
	**		 value:属性值
	** 返回：无
	***/
	void write(const QString &key,const QVariant & value);

private:
	QSettings * setting;//配置对象
};

#endif // PLATFORMCONFIG_H
