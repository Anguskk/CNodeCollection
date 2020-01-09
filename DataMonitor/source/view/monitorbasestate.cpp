/********************************************************************
Copyright (C), 2016, ���ӿƼ���ѧ.
FileName:    monitorbasestate.cpp
Author:      LYH
Version:     V1.0
Date:        2019/05/24
Description:             ///ģ������
���ļ���Ҫ�����Ա�����ϵ����������.
Other:                   ///����������
Function List:           ///��Ҫ�������书��
History:                 ///��ʷ�޸ļ�¼
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

//���ݱ�����
class CMonitorBaseStatePrivate
{
	Q_DECLARE_PUBLIC(CGraphicsViewState)
public:
	/************************************************************************
	Function:       CMonitorBaseStatePrivate()
	Description:    ���캯��
	Input:          parent ������
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CMonitorBaseStatePrivate(CGraphicsViewState *parent) :q_ptr(parent){}

	/************************************************************************
	Function:       ~CMonitorBaseStatePrivate()
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	virtual ~CMonitorBaseStatePrivate(){}

private:
	CGraphicsViewState*                      q_ptr;                    //����
};

/************************************************************************
Function:       CMonitorBaseState()
Description:    ���캯������ʼ������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CMonitorBaseState::CMonitorBaseState(CMonitorWindow *window,bool resumable/* = true*/)
	:CGraphicsViewState(window, resumable),d_ptr(new CMonitorBaseStatePrivate(this))
{
    
}

/************************************************************************
Function:       ~CMonitorBaseState()
Description:    �����������ͷ�����
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CMonitorBaseState::~CMonitorBaseState()
{
   
}

/************************************************************************
Function:       contextMenuEvent()
Description:    �Ҽ��˵��¼�
Input:          event �Ҽ��˵��¼���widget �¼�����
Output:         ��
Return:         ��
Others:         ��
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
Description:    ���ڴ�С�ı��¼�
Input:          event ���ڴ�С�ı��¼�
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CMonitorBaseState::resizeEvent(QResizeEvent * event)
{
	calculateSize();
}

/************************************************************************
Function:       activateCurrentStateSlot()
Description:    ���ǰ״̬
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CMonitorBaseState::activateCurrentStateSlot()
{

}

/************************************************************************
Function:       resize()
Description:    ��С�ı�
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CMonitorBaseState::resize()
{
	calculateSize();
}

/************************************************************************
Function:       calculateSize()
Description:    �������м���
Input:          event �¼�
Output:         ��
Return:         ��
Others:         ��
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
	//�Ƿ��м���
	if (!t_allShelfs.isEmpty())
	{
		QRectF shelfRect = t_allShelfs.first()->boundingRect();

		//����X����ֵ
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

		//ÿ�б�����ڴ��ڵ���һ������
		int t_vCount = ceil(t_allShelfs.size() / (double)t_hCount);
		if (t_vCount == 0)
			t_vCount = 1;

		t_height = t_margin * 2 + t_vCount * (shelfRect.height() + t_spacing) - t_spacing;
		if (t_height < viewRect.height())
			t_height = viewRect.height();

		//��������
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
