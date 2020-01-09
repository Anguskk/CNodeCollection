/********************************************************************
Copyright (C), 2016, 电子科技大学.
FileName:    graphicsview.h
Author:      LYH
Version:     V1.0
Date:        2019/05/24
Description:             ///模块描述
该文件主要负责成员及类关系的声明或定义.
Other:                   ///其他的描述
Function List:           ///主要函数及其功能
History:                 ///历史修改记录
<author>    <time>    <version>     <desc>
********************************************************************/
#pragma once

#include <QGraphicsView>

#include "messagesdefinition.h"

class CGraphicsViewPrivate;
class CGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	/************************************************************************
	Function:       CGraphicsView()
	Description:    构造函数
	Input:          parent 父窗口
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CGraphicsView(QWidget *parent);

	/************************************************************************
	Function:       ~CGraphicsView()
	Description:    析构函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	~CGraphicsView();

	/************************************************************************
	Function:       getMarginAndSpacing()
	Description:    获取边界和间距
	Input:          无
	Output:         margin 边界,spacing 间距
	Return:         无
	Others:         无
	************************************************************************/
	void getMarginAndSpacing(int &margin,int &spacing);

	/************************************************************************
	Function:       calculateSize()
	Description:    重新排列架子
	Input:          event 事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void calculateSize();

protected:
	/************************************************************************
	Function:       onViewEvent()
	Description:    执行父类事件
	Input:          event 事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void onViewEvent(QEvent *event);

	/************************************************************************
	Function:       mousePressEvent()
	Description:    鼠标点击事件
	Input:          event 事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void mousePressEvent(QMouseEvent *event);

	/************************************************************************
	Function:       mouseReleaseEvent()
	Description:    鼠标释放事件
	Input:          event 事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void mouseReleaseEvent(QMouseEvent *event);

	/************************************************************************
	Function:       mouseDoubleClickEvent()
	Description:    鼠标双击事件
	Input:          event 事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void mouseDoubleClickEvent(QMouseEvent *event);

	/************************************************************************
	Function:       mouseMoveEvent()
	Description:    鼠标移动事件
	Input:          event 事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void mouseMoveEvent(QMouseEvent *event);

#ifndef QT_NO_WHEELEVENT
	/************************************************************************
	Function:       wheelEvent()
	Description:    鼠标滚轮事件
	Input:          event 事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void wheelEvent(QWheelEvent *event);
#endif

	/************************************************************************
	Function:       keyPressEvent()
	Description:    键盘按下事件
	Input:          event 事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void keyPressEvent(QKeyEvent *event);

	/************************************************************************
	Function:       keyReleaseEvent()
	Description:    键盘释放事件
	Input:          event 事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void keyReleaseEvent(QKeyEvent *event);

	/************************************************************************
	Function:       focusInEvent()
	Description:    进入focus事件
	Input:          event 事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void focusInEvent(QFocusEvent *event);

	/************************************************************************
	Function:       focusOutEvent()
	Description:    退出focus事件
	Input:          event 事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void focusOutEvent(QFocusEvent *event);

	/************************************************************************
	Function:       enterEvent()
	Description:    鼠标进入事件
	Input:          event 事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void enterEvent(QEvent *event);

	/************************************************************************
	Function:       leaveEvent()
	Description:    鼠标离开事件
	Input:          event 事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void leaveEvent(QEvent *event);

	/************************************************************************
	Function:       contextMenuEvent()
	Description:    右键菜单事件
	Input:          event 事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void contextMenuEvent(QContextMenuEvent *event);

	/************************************************************************
	Function:       resizeEvent()
	Description:    大小变化事件
	Input:          event 事件
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void resizeEvent(QResizeEvent *event) override;

private:
	Q_DECLARE_PRIVATE(CGraphicsView);
	QScopedPointer<CGraphicsViewPrivate> d_ptr;
};
