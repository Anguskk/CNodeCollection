/*****************************************************************
**
** Copyright (C) 2016              ���ӿƼ���ѧʵ���� 
**
** ���ļ�������PlatForm�������ṩ��һЩƽ̨��صķ������Է����ȡ
**
** Provider��������չ����
** Author����֣
** Date��2008-01-08
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
** ���ܣ���ȡ����Ŀ¼
** ��������
** ���أ�����Ŀ¼
***/
QString PlatForm::getAppDir()
{
	return QCoreApplication::applicationDirPath();
}

/***
** ���ܣ���ȡɫ�����ɫ�����ļ�
** ��������
** ���أ���ɫ�����ļ�
***/
QString PlatForm::getColorSolutionPath()
{
	return QCoreApplication::applicationDirPath()+"/SysDatabase/colorsolution.dat";
}
/***
** ���ܣ���ȡƽ̨��Ĭ������
** ��������
** ���أ���
***/
QString PlatForm::getPlatformLanguage()
{
	if(platformLanguage.isEmpty())//ƽ̨����Ϊ��
	{
		PlatformConfig pc;
		pc.beginGroup();
		platformLanguage = pc.read(PlatformConfig::PLATFORM_LANGUAGE).toString();
		pc.endGroup();
		if(platformLanguage.isEmpty())//ת��
		{
		   platformLanguage = "zh";
		}
	}
	return platformLanguage;
}

/***
** ���ܣ�����ƽ̨����
** ������name:��������
** ���أ���
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
** ���ܣ���ƽ̨���й��ʻ�������Ҫָ����Ӧ���������ƣ��磺zh��en�ȣ�
**		 ��Ҫע�����ƽ̨��Ҫ�ж�Ӧ�������Ƶ����԰������û���ҵ�������
**		 �����ڲ�Ĭ������
** ������language:��������
** ���أ���
***/
void PlatForm::internationalizationForPlatform(const QString &language)
{
	if(language == "en")//Ӣ�İ������÷���
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
		if(translator->isEmpty())//������ش���
		{
			delete translator;
		}
		else
		{
			qApp->installTranslator(translator);//���뷭��
		}
	}
}


/***
** ���ܣ���ȡ�������CPU���ͺ�ID
** ����˵����
**			CPU_Tye:���ػ�ȡ��cpu������
**			CPU_Id  ���ػ�ȡ��cpu��ID
** ���أ���
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
** ���ܣ���ȡϵͳ��������ļ�·��
** ����˵�� ��
** ���أ���
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
Description:    ����
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
static bool sortAllKey(const QPair<int, QString> &s1, const QPair<int, QString> &s2)
{
	return s1.first < s2.first;
}

/************************************************************************
Function:       getAllShelfs()
Description:    ��ȡ���м���
Input:          ��
Output:         ��
Return:         ��
Others:         ��
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
Description:    �������м���
Input:          ��
Output:         ��
Return:         ��
Others:         ��
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
