/*****************************************************************
**
** Copyright (C) 2016              电子科技大学实验室 
**
** 该文件包含类PlatForm，该类提供了一些平台相关的方法，以方便获取
**
** Provider：技术发展中心
** Author：刘郑
** Date：2008-01-08
******************************************************************/
#ifndef PLATFORM_H
#define PLATFORM_H

#include <QString>
#include <QPair>
#include <QVector>

class PlatForm
{
public:

	/***
	** 功能：获取程序目录
	** 参数：无
	** 返回：程序目录
	***/
	static QString getAppDir();
	
	/***
	** 功能：获取色标的颜色方案文件
	** 参数：无
	** 返回：颜色方案文件
	***/
	static QString getColorSolutionPath();

	/***
	** 功能：获取平台的默认语言
	** 参数：无
	** 返回：无
	***/
	static QString getPlatformLanguage();

	/***
	** 功能：设置平台语言
	** 参数：name:语言名称
	** 返回：无
	***/
	static void setPlatformLanguage(const QString & name);

	/***
	** 功能：对平台进行国际化处理，需要指定对应的语言名称（如：zh、en等）
	**		 需要注意的是平台中要有对应语言名称的语言包，如果没有找到，则以
	**		 程序内部默认语言
	** 参数：language:语言名称
	** 返回：无
	***/
	static void internationalizationForPlatform(const QString &language);
	/***
	** 功能：获取计算机的CPU类型和ID
	** 参数说明：
	**			CPU_Tye:返回获取的cpu的类型
	**			CPU_Id  返回获取的cpu的ID
	** 返回：无
	***/
	static void getIntelCPUID(QString &cpuType,QString &cpuID);

	/***
	** 功能：获取系统插件配置文件路径
	** 参数说明 无
	** 返回：无
	***/
	static QString getSytemPluginSettingsFile();

	static QString getCharacteristicCode();

	/************************************************************************
	Function:       getAllShelfs()
	Description:    获取所有架子
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	static QVector<QPair<int,QString> > getAllShelfs();

	/************************************************************************
	Function:       setAllShelfs()
	Description:    设置所有架子
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	static void setAllShelfs(const QVector<QPair<int, QString> > &shelfs);

private:
	PlatForm();
	static QString platformLanguage;				//平台使用的默认语言
	static QString characteristicCode;
};

#endif // PLATFORM_H
