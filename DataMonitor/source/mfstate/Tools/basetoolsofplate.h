/*
* Copyright (c) 2018,���ӿƼ���ѧ��ѧ��ϢЭͬ�������ĸ��Ӷ�ά��Ϣ�����Ŷ�
* All rights reserved.
* 
* �ļ����ƣ�basemodel.h
* �ļ���ʶ�������ù���ƻ���
* ժ    Ҫ��ƽ̨�������ߣ���Ҫ���������ı��桢���Լ����ݵĵ��뵼����
* 
* ��ǰ�汾��1.0
* ��    �ߣ�³��
* ������ڣ�2018��5��20��
*
*/
#pragma once

#include <QAction>
#include <QToolBar>
#include <QMenu>
#include <QIcon>

class CDataLibManage;
class CBaseToolofPlate: public QObject
{
	Q_OBJECT

public:
	CBaseToolofPlate();
	virtual ~CBaseToolofPlate();

	void init(QToolBar * toolbar,QMenu * menu,QIcon icon,QString text,QMainWindow *pwd,bool bActionchecked = false,QActionGroup *actionGroup=nullptr);

	void setToolsState(bool flag);

	void setToolsActionState(bool flag);
	
	virtual void closeSubWd();

public slots:
	virtual void OnInitialize(){}

protected:
    QAction*            m_action;               //����Action
	QMainWindow *       m_pwd;                  //������
	bool                m_bActicon;             //��״̬����action�����ⲿ���� true Ĭ�Ͽ��� 
	bool                m_bupdateDataFlag;      // �Ƿ�������ݹ����
};
