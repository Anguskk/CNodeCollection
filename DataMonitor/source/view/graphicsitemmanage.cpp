/**************************************************************
Copyright (C),  2016   电子科技大学.
FileName :  graphicsitemmanage.cpp
Author :       lz
Version : V1.0
Date : 2016/8/30
Description :        ///模块描述 层位剖面和三维属性管理库
Other :              ///其他描述
Function List :      ///主要函数及其功能
History :            ///历史修改记录
<Author>    <Time>    <Version>    <Desc>
**************************************************************/
#include "graphicsitemmanage.h"

//数据保存类
class CGraphicsItemManagePrivate
{
	Q_DECLARE_PUBLIC(CGraphicsItemManage)
public:
	/************************************************************************
	Function:       CGraphicsNodeItem()
	Description:    构造函数
	Input:          width 宽度，height 高度，info 节点信息，parent 父object
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CGraphicsItemManagePrivate(CGraphicsItemManage *parent):q_ptr(parent){}

	/************************************************************************
	Function:       ~CGraphicsNodeItemPrivate()
	Description:    析构函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	virtual ~CGraphicsItemManagePrivate(){}

private:
	QVector<QGraphicsItem*>      m_allItems;                                // 图层属性映射

	CGraphicsItemManage           *q_ptr;                                   //父指针
};

/******
功能:  构造函数
参数:  无
返回值: 无
******/
CGraphicsItemManage::CGraphicsItemManage()
	:d_ptr(new CGraphicsItemManagePrivate(this))
{
}

/******
功能:  析构函数
参数:  无
返回值: 无
******/
CGraphicsItemManage::~CGraphicsItemManage()
{
	Q_D(CGraphicsItemManage);
	for (int t_index = 0; t_index < d->m_allItems.size(); t_index++)
	{
		delete d->m_allItems[t_index];
		d->m_allItems[t_index] = NULL;
	}
	d->m_allItems.clear();
}
/******
功能:添加数据到图层
参数:_data 数据
返回值:-1失败 1 成功
******/
int CGraphicsItemManage::addData(QGraphicsItem* _data )
{
	Q_D(CGraphicsItemManage);
	if (getIndexByObject(_data) != -1)
		return -1;
	 d->m_allItems.append(_data);
	 return d->m_allItems.size() -1;
}
/******
功能:  获取单个对象
参数:  vindex 对象索引
返回值: 对象数据
******/
const QGraphicsItem* CGraphicsItemManage::getObjectByIndex( const int vindex )
{
	Q_D(CGraphicsItemManage);
	if (vindex < 0 || vindex >= d->m_allItems.size()) 
		return nullptr;

    return d->m_allItems.at(vindex);
}
/******
功能:  获取单个对象索引
参数:  _object 单个对象
返回值: 图层索引 -1 失败 否则为正常索引
******/
const int CGraphicsItemManage::getIndexByObject( const QGraphicsItem * _object )
{
	Q_D(CGraphicsItemManage);
	for (int t_index = 0; t_index < d->m_allItems.size(); t_index++)
	{
        if (d->m_allItems.at(t_index) == _object)
			return t_index;
	}
	return -1;
}
/******
功能:  删除对象
参数:  vindex 删除对象索引
返回值: true 成功  false 失败
******/
bool CGraphicsItemManage::deleteObjectByIndex( const int vindex )
{
	Q_D(CGraphicsItemManage);
	if (vindex < 0 || vindex >= d->m_allItems.size()) 
		return false;
    delete d->m_allItems[vindex];
	d->m_allItems[vindex] = nullptr;
	d->m_allItems.remove(vindex);
	return true;
}
/******
功能:删除数据
参数:_data 单个数据
返回值:-1失败 1 成功
******/
int CGraphicsItemManage::deleteData(QGraphicsItem * _data )
{
	Q_D(CGraphicsItemManage);
	for (int t_index = 0; t_index < d->m_allItems.size(); t_index++)
	{
		if (d->m_allItems.at(t_index) == _data){
			delete d->m_allItems[t_index];
			d->m_allItems[t_index] = nullptr;
			d->m_allItems.remove(t_index);
			return 1;
		}
	}
	return -1;
}

/******
功能:从列表中剔除不删除数据
参数:_data 单个数据
返回值:-1失败 1 成功
******/
int CGraphicsItemManage::eraseData(QGraphicsItem * _data )
{
	Q_D(CGraphicsItemManage);
	for (int t_index = 0; t_index < d->m_allItems.size(); t_index++)
	{
		if (d->m_allItems[t_index] == _data){
			d->m_allItems.remove(t_index);
			return 1;
		}
	}
	return -1;
}

QVector<QGraphicsItem*> & CGraphicsItemManage::getAllobjects()
{
	Q_D(CGraphicsItemManage);
	return d->m_allItems;
}
