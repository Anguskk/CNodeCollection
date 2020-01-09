/********************************************************************
Copyright (C), 2013, ���ӿƼ���ѧ.
FileName:    mfbaseletstate.cpp
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
#include "mfbaseletstate.h"

#include <QToolBar>
#include <QMenu>
#include <QMenuBar>

#include "./Tools/basetoolsofplate.h"

/************************************************************************
Function:       CMFBaseState()
Description:    ���캯��
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CMFBaseState::CMFBaseState()
{

}

/************************************************************************
Function:       ~CMFBaseState()
Description:    ��������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CMFBaseState::~CMFBaseState()
{
	for (int i = 0; i < m_Tools.size(); i++)
	{
		delete m_Tools[i];
		m_Tools[i] = NULL;
	}
	m_Tools.clear();
}

void CMFBaseState::setToolsState( bool flag )
{
	for (int i = 0; i < m_Tools.size(); i++)
	{
		m_Tools[i]->setToolsState(flag);
	}
}

QString CMFBaseState::getName()
{
   return m_name;
}

void CMFBaseState::closeSubWd()
{
	for (int i = 0; i < m_Tools.size(); i++)
	{
		m_Tools[i]->closeSubWd();
	}
}