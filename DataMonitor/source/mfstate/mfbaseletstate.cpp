/********************************************************************
Copyright (C), 2013, 电子科技大学.
FileName:    mfbaseletstate.cpp
Author:      LYH
Version:     V1.0
Date:        2013/09/11
Description:             ///模块描述
                            该文件主要负责成员及类关系的声明或定义.
Other:                   ///其他的描述
Function List:           ///主要函数及其功能
History:                 ///历史修改记录
<author>    <time>    <version>     <desc>
********************************************************************/
#include "mfbaseletstate.h"

#include <QToolBar>
#include <QMenu>
#include <QMenuBar>

#include "./Tools/basetoolsofplate.h"

/************************************************************************
Function:       CMFBaseState()
Description:    构造函数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CMFBaseState::CMFBaseState()
{

}

/************************************************************************
Function:       ~CMFBaseState()
Description:    析构函数
Input:          无
Output:         无
Return:         无
Others:         无
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