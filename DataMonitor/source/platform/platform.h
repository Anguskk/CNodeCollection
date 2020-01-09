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
#ifndef PLATFORM_H
#define PLATFORM_H

#include <QString>
#include <QPair>
#include <QVector>

class PlatForm
{
public:

	/***
	** ���ܣ���ȡ����Ŀ¼
	** ��������
	** ���أ�����Ŀ¼
	***/
	static QString getAppDir();
	
	/***
	** ���ܣ���ȡɫ�����ɫ�����ļ�
	** ��������
	** ���أ���ɫ�����ļ�
	***/
	static QString getColorSolutionPath();

	/***
	** ���ܣ���ȡƽ̨��Ĭ������
	** ��������
	** ���أ���
	***/
	static QString getPlatformLanguage();

	/***
	** ���ܣ�����ƽ̨����
	** ������name:��������
	** ���أ���
	***/
	static void setPlatformLanguage(const QString & name);

	/***
	** ���ܣ���ƽ̨���й��ʻ�������Ҫָ����Ӧ���������ƣ��磺zh��en�ȣ�
	**		 ��Ҫע�����ƽ̨��Ҫ�ж�Ӧ�������Ƶ����԰������û���ҵ�������
	**		 �����ڲ�Ĭ������
	** ������language:��������
	** ���أ���
	***/
	static void internationalizationForPlatform(const QString &language);
	/***
	** ���ܣ���ȡ�������CPU���ͺ�ID
	** ����˵����
	**			CPU_Tye:���ػ�ȡ��cpu������
	**			CPU_Id  ���ػ�ȡ��cpu��ID
	** ���أ���
	***/
	static void getIntelCPUID(QString &cpuType,QString &cpuID);

	/***
	** ���ܣ���ȡϵͳ��������ļ�·��
	** ����˵�� ��
	** ���أ���
	***/
	static QString getSytemPluginSettingsFile();

	static QString getCharacteristicCode();

	/************************************************************************
	Function:       getAllShelfs()
	Description:    ��ȡ���м���
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	static QVector<QPair<int,QString> > getAllShelfs();

	/************************************************************************
	Function:       setAllShelfs()
	Description:    �������м���
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	static void setAllShelfs(const QVector<QPair<int, QString> > &shelfs);

private:
	PlatForm();
	static QString platformLanguage;				//ƽ̨ʹ�õ�Ĭ������
	static QString characteristicCode;
};

#endif // PLATFORM_H
