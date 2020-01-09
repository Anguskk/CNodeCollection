/*****************************************************************
**
** Copyright (C) 2008          ���ӿƼ���ѧʵ����
**
** ���ļ�������PlatformConfig�������ṩ�������ƽ̨�������й����е�������Ϣ
** ������setting�ķ�ʽ���ڸ�Ŀ¼��
**
** Provider��
** Author��WangYong
** Date��2008-03-07
******************************************************************/
#ifndef PLATFORMCONFIG_H
#define PLATFORMCONFIG_H

#include <QSettings>
#include <QVariant>

class PlatformConfig
{
public:

	static const QString PRO_PROJECT_DIR;//��ǰ�������ڵ�Ŀ¼
	static const QString PRO_RECENT_PROJECT;//����򿪹�����Ŀ�ļ�
	static const QString PLATFORM_LANGUAGE;//ƽ̨��ѡ����

	/***
	** ���ܣ����췽��
	** ��������
	** ���أ���
	***/
	PlatformConfig();

	/***
	** ���ܣ���������
	** ��������
	** ���أ���
	***/
	~PlatformConfig();

	/************************************************************************
	Function:       clear()
	Description:    ���
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void clear();

	/************************************************************************
	Function:       beginGroup()
	Description:    ��ʼ����
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void beginGroup(const QString & prefix=QString());

	/************************************************************************
	Function:       endGroup()
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void endGroup();

	/************************************************************************
	Function:       allKeys()
	Description:    ��ȡ����keys
	Input:          ��
	Output:         ��
	Return:         ����keys
	Others:         ��
	************************************************************************/
	QStringList allKeys() const;

	/***
	** ���ܣ���ȡָ����key��ֵ
	** ������key:�����ԵĹؼ���
	** ���أ������Ե�ֵ
	***/
	QVariant read(const QString &key);

	/***
	** ���ܣ����ļ���д��ָ���ؼ��ֵ�����
	** ������key:�����ԵĹؼ���
	**		 value:����ֵ
	** ���أ���
	***/
	void write(const QString &key,const QVariant & value);

private:
	QSettings * setting;//���ö���
};

#endif // PLATFORMCONFIG_H
