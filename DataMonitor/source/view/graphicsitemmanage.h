/**************************************************************
Copyright (C),  2016   电子科技大学.
FileName :  graphicsitemmanage.h
Author :       lz
Version : V1.0
Date : 2016/8/30
Description :        ///模块描述 图元管理库
Other :              ///其他描述
Function List :      ///主要函数及其功能
History :            ///历史修改记录
<Author>    <Time>    <Version>    <Desc>
**************************************************************/
#pragma once

#include <QGraphicsItem>

class CGraphicsItemManagePrivate;
class CGraphicsItemManage
{
public:
	/******
	功能:  构造函数
	参数:  无
	返回值: 无
	******/
	CGraphicsItemManage();
	/******
	功能:  析构函数
	参数:  无
	返回值: 无
	******/
	~CGraphicsItemManage();

	/******
	功能:添加数据到图层
	参数:_data 数据
	返回值:-1失败 1 成功
	******/
	int addData(QGraphicsItem* _data);

	/******
	功能:  获取单个对象
	参数:  vindex 对象索引
	返回值: 对象数据
	******/
	const QGraphicsItem* getObjectByIndex(const int vindex);

	/******
	功能:  获取单个对象索引
	参数:  _object 单个对象
	返回值: 图层索引 -1 失败 否则为正常索引
	******/
	const int getIndexByObject(const QGraphicsItem * _object);

	/******
	功能:  删除对象
	参数:  vindex 删除对象索引
	返回值: true 成功  false 失败
	******/
	bool deleteObjectByIndex(const int vindex);

	/******
	功能:删除数据
	参数:_data 单个数据
	返回值:-1失败 1 成功
	******/
	int  deleteData(QGraphicsItem * _data);

	/******
	功能:从列表中剔除不删除数据
	参数:_data 单个数据
	返回值:-1失败 1 成功
	******/
	int eraseData(QGraphicsItem * _data);

	QVector<QGraphicsItem*> &getAllobjects();

private:
	Q_DECLARE_PRIVATE(CGraphicsItemManage);
	QScopedPointer<CGraphicsItemManagePrivate> d_ptr;
};
