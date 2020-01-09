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
#include "platform.h"
#include <QApplication>
#include "platformconfig.h"
#include <QTranslator>
#include <QStringList>
#include <QDir>
#include <QDate>
#include <QTime>
#include <QSysInfo>
#include "md5.h"

QString PlatForm::platformLanguage = "";
QString PlatForm::characteristicCode = "";

/***
** 功能：获取程序目录
** 参数：无
** 返回：程序目录
***/
QString PlatForm::getAppDir()
{
	return QCoreApplication::applicationDirPath();
}

/***
** 功能：获取色标的颜色方案文件
** 参数：无
** 返回：颜色方案文件
***/
QString PlatForm::getColorSolutionPath()
{
	return QCoreApplication::applicationDirPath()+"/SysDatabase/colorsolution.dat";
}
/***
** 功能：获取平台的默认语言
** 参数：无
** 返回：无
***/
QString PlatForm::getPlatformLanguage()
{
	if(platformLanguage.isEmpty())//平台语言为空
	{
		PlatformConfig pc;
		pc.beginGroup();
		platformLanguage = pc.read(PlatformConfig::PLATFORM_LANGUAGE).toString();
		pc.endGroup();
		if(platformLanguage.isEmpty())//转换
		{
		   platformLanguage = "zh";
		}
	}
	return platformLanguage;
}

/***
** 功能：设置平台语言
** 参数：name:语言名称
** 返回：无
***/
void PlatForm::setPlatformLanguage(const QString & name)
{
	PlatformConfig pc;
	pc.beginGroup();
	pc.write(PlatformConfig::PLATFORM_LANGUAGE,name);
	pc.endGroup();
	platformLanguage = name;
}

/***
** 功能：对平台进行国际化处理，需要指定对应的语言名称（如：zh、en等）
**		 需要注意的是平台中要有对应语言名称的语言包，如果没有找到，则以
**		 程序内部默认语言
** 参数：language:语言名称
** 返回：无
***/
void PlatForm::internationalizationForPlatform(const QString &language)
{
	if(language == "en")//英文包均不用翻译
		return;
	QString languagePath = getAppDir()+"/Language/"+language;
	QDir dir(languagePath);
	if(!dir.exists())
		return;
	QStringList fileNames = dir.entryList(QStringList("*.qm"), QDir::Files,QDir::Name);
	foreach(const QString &name,fileNames)
	{
		QTranslator *translator = new QTranslator;
		translator->load(name,languagePath);
		if(translator->isEmpty())//翻译加载错误
		{
			delete translator;
		}
		else
		{
			qApp->installTranslator(translator);//插入翻译
		}
	}
}


/***
** 功能：获取计算机的CPU类型和ID
** 参数说明：
**			CPU_Tye:返回获取的cpu的类型
**			CPU_Id  返回获取的cpu的ID
** 返回：无
***/
void PlatForm::getIntelCPUID(QString &CPU_Type,QString &CPU_ID)
{
	#ifdef Q_WS_WIN//Windwos
		CPU_ID = getCharacteristicCode();
	#else
		#ifdef Q_WS_X11//Linux
			
			CPU_Type = "";
			CPU_ID = "";
		#else
			CPU_Type = "UnKnow";
			CPU_ID = "0000-0000-0000-0000";
		#endif
	#endif

	
}

/***
** 功能：获取系统插件配置文件路径
** 参数说明 无
** 返回：无
***/
QString PlatForm::getSytemPluginSettingsFile()
{
	return QCoreApplication::applicationDirPath()+"/systemplugins.ini";
}

QString PlatForm::getCharacteristicCode()
{
	if(characteristicCode == "")
	{
		#ifdef Q_WS_WIN
		QDir currentDir = QDir::root();
		if(currentDir.cd("WINDOWS"))
		{
			QSysInfo::WinVersion winVersion = QSysInfo::windowsVersion();
			if(winVersion == QSysInfo::WV_XP || winVersion == QSysInfo::WV_2003)
			{
				if(!currentDir.cd("WinSxS"))
				{
					currentDir.mkdir("WinSxS");
					currentDir.cd("WinSxS");
				}
			}
		}
		QString filePath = currentDir.absoluteFilePath(".characteristic");
		QFile tmpFile(filePath);
		if(tmpFile.exists())
		{
			tmpFile.open(QIODevice::ReadOnly);
			QByteArray byteArray = tmpFile.readAll();
			characteristicCode = QString(byteArray);
		}
		else
		{
			MD5 md5;
			QString orian = QDate::currentDate().toString() + QTime::currentTime().toString();
			md5.setOriginalStr(orian);
			characteristicCode = md5.getEncodeStr();
			tmpFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
			tmpFile.write(characteristicCode.toAscii());
		}
		#else
		#endif
	}
	return characteristicCode;
}

/************************************************************************
Function:       sortAllKey()
Description:    排序
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
static bool sortAllKey(const QPair<int, QString> &s1, const QPair<int, QString> &s2)
{
	return s1.first < s2.first;
}

/************************************************************************
Function:       getAllShelfs()
Description:    获取所有架子
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
QVector<QPair<int, QString> > PlatForm::getAllShelfs()
{
	QVector<QPair<int,QString> > t_allShelfs;
	PlatformConfig pc;
	pc.beginGroup("ShelfID");
	for (auto key: pc.allKeys())
	{
		bool t_flag = false;
		int t_curID = key.toInt(&t_flag);
		if (t_flag)
			t_allShelfs.append(qMakePair(t_curID, pc.read(key).toString()));
	}
	pc.endGroup();

	qSort(t_allShelfs.begin(), t_allShelfs.end(), sortAllKey);

	return t_allShelfs;
}

/************************************************************************
Function:       setAllShelfs()
Description:    设置所有架子
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void PlatForm::setAllShelfs(const QVector<QPair<int, QString> > &shelfs)
{
	PlatformConfig pc;
	pc.beginGroup("ShelfID");
	pc.clear();
	for (auto curShelf : shelfs)
	{
		pc.write(QString::number(curShelf.first), curShelf.second);
	}
	pc.endGroup();
}

PlatForm::PlatForm()
{
}
