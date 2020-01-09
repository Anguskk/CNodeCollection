/********************************************************************
Copyright (C), 2013, ���ӿƼ���ѧ.
FileName:    mffilestate.h
Author:      LYH
Version:     V1.0
Date:        2013/09/11
Description:             ///ģ������
                            ���ļ���Ҫ�����Ա�����ϵ����������.
Other:                   ///����������
Function List:           ///��Ҫ�������书��
History:                 ///��ʷ�޸ļ�¼
<author>    <time>    <version>     <desc>
********************************************************************/
#ifndef CMFBASESTATE_H
#define CMFBASESTATE_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QVector>

class QToolBar;
class QMenu;
class QStatusBar;
class QMenuBar;
class QMainWindow;
class QTextStream;
class QTextEdit;
class CBaseToolofPlate;
class CFileManageView;
class CInfoBoardView;

using namespace std;

class CMFBaseState:public QObject
{
	Q_OBJECT
public:
	/************************************************************************
	Function:       CMFBaseState()
	Description:    ���캯��
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CMFBaseState();

	/************************************************************************
	Function:       ~CMFBaseState()
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	virtual ~CMFBaseState();
		
public:
	/************************************************************************
	Function:       creatAction()
	Description:    ������ť
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	virtual void creatAction() = 0;

	/************************************************************************
	Function:       setToolsState()
	Description:    ���ù����Ƿ����
	Input:          flag true ���� false ������
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void setToolsState(bool flag);

	virtual void closeSubWd();

	QString  getName();

protected:
	QString                                m_name;
	QMenuBar                               *m_mainMenuBar         = nullptr;         //�˵���
	QMap<QString,QToolBar *>               *m_toolBars            = nullptr;         //������
	QMainWindow                            *m_mainWindow          = nullptr;         //������
	QStatusBar                             *m_mainStatusBar       = nullptr;         //��״̬��
	QMenu                                  *m_menu                = nullptr;         //�˵���
	QVector<CBaseToolofPlate*>             m_Tools;                                  //������
};

#endif
