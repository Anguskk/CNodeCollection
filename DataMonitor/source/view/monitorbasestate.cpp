/********************************************************************
Copyright (C), 2016, 电子科技大学.
FileName:    monitorbasestate.cpp
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
#include "monitorbasestate.h"

#include <QAction>
#include <QMenu>

#include "messagesnodedefinition.h"

#include "monitorwindow.h"
#include "graphicsview.h"
#include "graphicsitemmanage.h"
#include "monitormsgmanage.h"
#include "graphicsnodeitem.h"

//数据保存类
class CMonitorBaseStatePrivate
{
	Q_DECLARE_PUBLIC(CGraphicsViewState)
public:
	/************************************************************************
	Function:       CMonitorBaseStatePrivate()
	Description:    构造函数
	Input:          parent 父窗口
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CMonitorBaseStatePrivate(CGraphicsViewState *parent) :q_ptr(parent){}

	/************************************************************************
	Function:       ~CMonitorBaseStatePrivate()
	Description:    析构函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	virtual ~CMonitorBaseStatePrivate(){}

private:
	CGraphicsViewState*                      q_ptr;                    //父类
};

/************************************************************************
Function:       CMonitorBaseState()
Description:    构造函数，初始化参数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CMonitorBaseState::CMonitorBaseState(CMonitorWindow *window,bool resumable/* = true*/)
	:CGraphicsViewState(window, resumable),d_ptr(new CMonitorBaseStatePrivate(this))
{
    
}

/************************************************************************
Function:       ~CMonitorBaseState()
Description:    析构函数，释放数据
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CMonitorBaseState::~CMonitorBaseState()
{
   
}

/************************************************************************
Function:       contextMenuEvent()
Description:    右键菜单事件
Input:          event 右键菜单事件，widget 事件窗口
Output:         无
Return:         无
Others:         无
************************************************************************/
void CMonitorBaseState::contextMenuEvent(QContextMenuEvent *event)
{
	auto t_window = getWindow();

	auto t_msgManage = t_window->getMonitorMsgManage();
	if (t_msgManage == nullptr || t_msgManage->currentModeStatus() != DownloadRequestMsg)
		return;

	auto item = t_window->getView()->itemAt(event->pos());
	if (item == nullptr)
		return;

	auto nodeItem = dynamic_cast<CGraphicsNodeItem *>(item);
	if (nodeItem == nullptr)
		return;

	auto nodeInfo = nodeItem->getNodeInfo();
	auto nodeStatus = nodeItem->getStatus();
	if (nodeInfo.nodeID <0 || nodeInfo.shelfID<0 || nodeStatus != 1)
		return;

	QMenu t_menu;

	QAction t_forceDownloadAction(tr("Force Download"), &t_menu);
	connect(&t_forceDownloadAction, &QAction::triggered, this,
		[=]() {
		SMessageBase message;
		message.shelfID = nodeInfo.shelfID;
		message.nodeID = nodeInfo.nodeID + 1;
		message.type = DownloadRequestMsg;
		auto curMsg = new SRequestDownloadMessage;
		curMsg->type[0] = 1;
		message.length = sizeof(SRequestDownloadMessage);
		message.data = curMsg;
		t_msgManage->addMessage(message);
	});
	t_menu.addAction(&t_forceDownloadAction);

	t_menu.exec(event->globalPos());
}

/************************************************************************
Function:       resizeEvent()
Description:    窗口大小改变事件
Input:          event 窗口大小改变事件
Output:         无
Return:         无
Others:         无
************************************************************************/
void CMonitorBaseState::resizeEvent(QResizeEvent * event)
{
	calculateSize();
}

/************************************************************************
Function:       activateCurrentStateSlot()
Description:    激活当前状态
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CMonitorBaseState::activateCurrentStateSlot()
{

}

/************************************************************************
Function:       resize()
Description:    大小改变
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CMonitorBaseState::resize()
{
	calculateSize();
}

/************************************************************************
Function:       calculateSize()
Description:    重新排列架子
Input:          event 事件
Output:         无
Return:         无
Others:         无
************************************************************************/
void CMonitorBaseState::calculateSize()
{
	auto t_view = getWindow()->getView();
	QRect viewRect = t_view->viewport()->rect();

	int t_margin,t_spacing;
	t_view->getMarginAndSpacing(t_margin, t_spacing);

	auto t_itemManage = getWindow()->getItemManage();

	auto t_allShelfs = t_itemManage->getAllobjects();

	int t_width = viewRect.width(), t_height = viewRect.height();
	//是否有架子
	if (!t_allShelfs.isEmpty())
	{
		QRectF shelfRect = t_allShelfs.first()->boundingRect();

		//计算X方向值
		int t_startX = t_margin;
		int t_hCount = floor((viewRect.width() - t_margin * 2 + t_spacing) / (double)(shelfRect.width() + t_spacing));
		if (t_hCount == 0) {
			t_hCount = 1;
			t_width = shelfRect.width() + t_margin * 2;
			t_startX = t_margin;
		}
		else {
			if (t_hCount > t_allShelfs.size())
				t_hCount = t_allShelfs.size();

			int t_spacingX = t_hCount > 1 ? 0 : t_spacing;
			t_startX = (viewRect.width() - t_margin * 2 - t_hCount * (shelfRect.width() + t_spacingX) + t_spacingX) / 2;
		}

		//每行必须存在大于等于一个架子
		int t_vCount = ceil(t_allShelfs.size() / (double)t_hCount);
		if (t_vCount == 0)
			t_vCount = 1;

		t_height = t_margin * 2 + t_vCount * (shelfRect.height() + t_spacing) - t_spacing;
		if (t_height < viewRect.height())
			t_height = viewRect.height();

		//重新排序
		for (int i = 0; i < t_allShelfs.size(); ++i)
		{
			int t_curNumX = i % t_hCount;
			int t_curNumY = i / t_hCount;

			QPointF t_curPos(t_startX + t_curNumX * (shelfRect.width() + t_spacing), t_margin + t_curNumY*(shelfRect.height() + t_spacing));
			t_allShelfs[i]->setPos(t_curPos);
		}
	}

	QRectF t_sceneRect(0, 0, t_width, t_height);
	t_view->scene()->setSceneRect(t_sceneRect);
}
