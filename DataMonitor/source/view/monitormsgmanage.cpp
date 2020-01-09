/**************************************************************
Copyright (C),  2016   电子科技大学.
FileName :  monitormsgmanage.cpp
Author :       lz
Version : V1.0
Date : 2016/8/30
Description :        ///模块描述
Other :              ///其他描述
Function List :      ///主要函数及其功能
History :            ///历史修改记录
<Author>    <Time>    <Version>    <Desc>
**************************************************************/
#include "monitormsgmanage.h"

#include <QDockWidget>
#include <QDate>

#include "messagesnodedefinition.h"
#include "messageprocessmanage.h"

#include "monitorwindow.h"
#include "graphicsshelfitem.h"
#include "graphicsitemmanage.h"

//数据保存类
class CMonitorMsgManagePrivate
{
	Q_DECLARE_PUBLIC(CMonitorMsgManage)

public:
	/************************************************************************
	Function:       CGraphicsNodeItem()
	Description:    构造函数
	Input:          width 宽度，height 高度，info 节点信息，parent 父object
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CMonitorMsgManagePrivate(CMonitorWindow *window, QDockWidget *infoBoardDock, QDockWidget *nodeInfoDock,CMonitorMsgManage *parent);

	/************************************************************************
	Function:       ~CGraphicsNodeItemPrivate()
	Description:    析构函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	virtual ~CMonitorMsgManagePrivate();

	/************************************************************************
	Function:       getShelfItem()
	Description:    获取架子
	Input:          shelfID 架子ID
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CGraphicsShelfItem* getShelfItem(int shelfID);

private:
	/************************************************************************
	Function:       initConntion()
	Description:    初始化连接
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void initConntion();

private:
	unsigned short               type                         = AnnualInspectionRequestMsg;    //模式类型
	CMonitorWindow               *m_window                    = nullptr;                       //显示窗口
	CMessageProcessManage        *m_messageProcessManage      = nullptr;                       //信息处理线程
	QDockWidget                  *m_infoBoardDock             = nullptr;                       //信息显示
	QDockWidget                  *m_nodeInfoDock              = nullptr;                       //节点信息显示
	unsigned short               nextType                     = AnnualInspectionRequestMsg;    //下一个模式
	QVector<QPair<int, QString> > nextShelfIDs;                                                //下一个架子信息

	CMonitorMsgManage            *q_ptr                       = nullptr;                       //父指针
};

/************************************************************************
Function:       CGraphicsNodeItem()
Description:    构造函数
Input:          width 宽度，height 高度，info 节点信息，parent 父object
Output:         无
Return:         无
Others:         无
************************************************************************/
CMonitorMsgManagePrivate::CMonitorMsgManagePrivate(CMonitorWindow *window, QDockWidget *infoBoardDock, QDockWidget *nodeInfoDock, CMonitorMsgManage *parent)
	:q_ptr(parent), m_window(window), m_infoBoardDock(infoBoardDock), m_nodeInfoDock(nodeInfoDock),m_messageProcessManage(new CMessageProcessManage(parent))
{
	initConntion();
}

/************************************************************************
Function:       ~CGraphicsNodeItemPrivate()
Description:    析构函数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CMonitorMsgManagePrivate::~CMonitorMsgManagePrivate()
{
	
}

/************************************************************************
Function:       getShelfItem()
Description:    获取架子
Input:          shelfID 架子ID
Output:         无
Return:         无
Others:         无
************************************************************************/
CGraphicsShelfItem* CMonitorMsgManagePrivate::getShelfItem(int shelfID)
{
	auto t_itemManage = m_window->getItemManage();
	auto t_allItems = t_itemManage->getAllobjects();
	CGraphicsShelfItem* shelfItem = nullptr;
	for (auto curItem: t_allItems)
	{
		auto curShelfItem = dynamic_cast<CGraphicsShelfItem*>(curItem);
		if (curShelfItem != nullptr && curShelfItem->getShelfID() == shelfID) {
			shelfItem = curShelfItem;
			break;
		}
	}
	return shelfItem;
}

/************************************************************************
Function:       initConntion()
Description:    初始化连接
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CMonitorMsgManagePrivate::initConntion()
{
	Q_Q(CMonitorMsgManage);
	q->connect(m_messageProcessManage->get_process_thread(), &CMessageProcessThread::send_statusinfo, 
		q, &CMonitorMsgManage::processMsgSlot);
}

/************************************************************************
Function:       CMonitorMsgManage()
Description:    构造函数
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CMonitorMsgManage::CMonitorMsgManage(CMonitorWindow *window, QDockWidget *infoBoardDock, QDockWidget *nodeInfoDock)
	:d_ptr(new CMonitorMsgManagePrivate(window, infoBoardDock, nodeInfoDock,this))
{
}

/************************************************************************
Function:       ~CMonitorMsgManage()
Description:    析构函数，释放数据
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
CMonitorMsgManage::~CMonitorMsgManage()
{
	Q_D(CMonitorMsgManage);
	d->m_messageProcessManage->shutdown();
}

/************************************************************************
Function:       changeModeStatus()
Description:    切换模式状态
				true--所有节点已完成或者断开连接，
				false--存在正在进行的节点
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
bool CMonitorMsgManage::changeModeStatus()
{
	Q_D(CMonitorMsgManage);
	bool t_status = true;

	auto t_itemManage = d->m_window->getItemManage();
	auto t_allItems = t_itemManage->getAllobjects();
	CGraphicsShelfItem* shelfItem = nullptr;
	for (auto curItem : t_allItems)
	{
		auto curShelfItem = dynamic_cast<CGraphicsShelfItem*>(curItem);
		if (!curShelfItem->changeModeStatus()){
			t_status = false;
			break;
		}
	}

	return t_status;
}

/************************************************************************
Function:       currentModeStatus()
Description:    当前模式状态
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
unsigned short CMonitorMsgManage::currentModeStatus()
{
	Q_D(CMonitorMsgManage);
	return d->type;
}

/************************************************************************
Function:       addMessage()
Description:    添加消息
Input:          message 消息
Output:         无
Return:         无
Others:         无
************************************************************************/
void CMonitorMsgManage::addMessage(SMessageBase &message)
{
	Q_D(CMonitorMsgManage);
	d->m_messageProcessManage->append_deliver_message(message);
}

/************************************************************************
Function:       changeModelType()
Description:    切换模式（其中充电状态可以随时切换到其他状态）
Input:          type 模式
Output:         无
Return:         无
Others:         无
************************************************************************/
void CMonitorMsgManage::changeModeTypeSlot(unsigned short type, QVector<QPair<int, QString> > shelfIDs)
{
	Q_D(CMonitorMsgManage);
	d->nextType = type;
	d->nextShelfIDs = shelfIDs;
	changeModeSlot();
}

/************************************************************************
Function:       changeModelSlot()
Description:    切换模式
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CMonitorMsgManage::changeModeSlot()
{
	Q_D(CMonitorMsgManage);

	auto allShelfIDs = d->m_window->getAllShelfIDs();

	QVector<int> t_shelfs;
	QVector<ShelfInfo> v_trueShelfs;
	for (auto curShelfID : d->nextShelfIDs)
	{
		ShelfInfo shelf_info;
		shelf_info.ipAddress = curShelfID.second;
		shelf_info.shelfID = curShelfID.first;
		v_trueShelfs.append(shelf_info);

		if (allShelfIDs.contains(curShelfID.first)) {
			allShelfIDs.removeOne(curShelfID.first);
			continue;
		}

		ShelfInfo t_curShelf;
		t_curShelf.shelfID = curShelfID.first;
		t_curShelf.ipAddress = curShelfID.second;
		d->m_window->addShelf(t_curShelf);
	}
	//删除无效架子
	for (auto curShelfID : allShelfIDs)
	{
		d->m_window->deleteShelf(curShelfID);
	}

	//清除数据
	auto t_itemManage = d->m_window->getItemManage();
	auto t_allItems = t_itemManage->getAllobjects();
	CGraphicsShelfItem* shelfItem = nullptr;
	for (auto curItem : t_allItems)
	{
		auto curShelfItem = dynamic_cast<CGraphicsShelfItem*>(curItem);
		if (curShelfItem != nullptr) {
			curShelfItem->clearAllData();
		}
	}

	//向下分发有效架子的信息
	SMessageBase message_base;
	message_base.shelfID = -1;
	message_base.nodeID = -1;
	message_base.type = d->nextType;

	switch (d->nextType)
	{
	case AnnualInspectionRequestMsg://年检
		{
			auto curMsg = new SRequestAnnualInspectionMessage;
			auto dateStr = QDate::currentDate().toString("yyyyMMdd");
			for (int i = 0; i < dateStr.size(); ++i) {
				curMsg->date[i] = dateStr[i].toLatin1();
			}

			message_base.length = sizeof(SRequestAnnualInspectionMessage);
			message_base.data = curMsg;
		}
		break;
	case AnnualInspectionDownloadRequestMsg://年检下载
		{
			auto curMsg = new SRequestAnnualInspectionDownloadMessage;
			auto dateStr = QDate::currentDate().toString("yyyyMMdd");
			for (int i = 0; i < dateStr.size(); ++i) {
				curMsg->date[i] = dateStr[i].toLatin1();
			}

			message_base.length = sizeof(SRequestAnnualInspectionDownloadMessage);
			message_base.data = curMsg;
		}
		break;
	case ChargingRequestMsg://充电
		{
			auto curMsg = new SRequestChargingMessage;
			curMsg->monitoring[0] = 1;
			message_base.length = sizeof(SRequestChargingMessage);
			message_base.data = curMsg;
		}
		break;
	case DownloadRequestMsg://下载
		{
			auto curMsg = new SRequestDownloadMessage;
			curMsg->type[0] = 0;
			message_base.length = sizeof(SRequestDownloadMessage);
			message_base.data = curMsg;
		}
		break;
	default:
		return;
	}

	d->m_messageProcessManage->append_deliver_message(message_base);
	d->m_messageProcessManage->start(v_trueShelfs);
	d->type = d->nextType;
}

/************************************************************************
Function:       processMsg()
Description:    处理消息
Input:          message 消息
Output:         无
Return:         无
Others:         无
************************************************************************/
void CMonitorMsgManage::processMsgSlot(const SMessageBase& message)
{
	Q_D(CMonitorMsgManage);
	auto t_curShelfItem = d->getShelfItem(message.shelfID);
	if (t_curShelfItem == nullptr)
		return;
	switch (message.type)
	{
	case ConnectionStatusMsg:{
			auto t_msg = static_cast<SConnectionStatusMsg *>(message.data);
			t_curShelfItem->setNodeName(message.nodeID - 1, message.nodeName);
			t_curShelfItem->setNodeStatus(message.nodeID - 1, t_msg->type);
			delete t_msg;
		}
		break;
	case AnnualInspectionConfirmMsg: {//年检模式
		auto t_msg = static_cast<SConfirmAnnualInspectionMessage *>(message.data);
		if (t_msg->type[0] == 1)
			t_curShelfItem->setNodeStatus(message.nodeID - 1, 2);
		else if (t_msg->type[0] == 2)
			t_curShelfItem->setNodeProgressRate(message.nodeID - 1, 0, 100);
		else
			t_curShelfItem->setNodeProgressRate(message.nodeID - 1, 0, 0);
		}
		break;
	case AnnualInspectionStateInfoMsg: {//年检进度
		auto t_msg = static_cast<SInfoAnnualInspectionStateMessage *>(message.data);
		t_curShelfItem->setNodeProgressRate(message.nodeID - 1, 0, t_msg->rate[0]);
		delete t_msg;
		}
		break;
	case AnnualInspectionDownloadConfirmMsg: {//年检下载模式
		auto t_msg = static_cast<SConfirmAnnualInspectionDownloadMessage *>(message.data);
		if (t_msg->type[0] == 1)
			t_curShelfItem->setNodeStatus(message.nodeID - 1, 2);
		else if (t_msg->type[0] == 2)
			t_curShelfItem->setNodeStatus(message.nodeID - 1, 2);
		else
			t_curShelfItem->setNodeProgressRate(message.nodeID - 1, 0, 0);
		delete t_msg;
		}
		break;
	case AnnualInspectionDownloadStateInfoMsg: {//年检下载进度
		auto t_msg = static_cast<SInfoAnnualInspectionDownloadStateMessage *>(message.data);
		if (t_msg->rate[0] == 1)
			t_curShelfItem->setNodeStatus(message.nodeID - 1, 2);
		else
			t_curShelfItem->setNodeProgressRate(message.nodeID - 1, 0, 100);
		delete t_msg;
		}
		break;
	case ChargingConfirmMsg: {//充电模式
		auto t_msg = static_cast<SConfirmChargingMessage *>(message.data);
		if (t_msg->type[0] == 1)
			t_curShelfItem->setNodeStatus(message.nodeID - 1, 2);
		else
			t_curShelfItem->setNodeProgressRate(message.nodeID - 1, 0, 0);
		delete t_msg;
		}
		break;
	case ChargingStateInfoMsg: {//充电进度
		auto t_msg = static_cast<SInfoChargingStateMessage *>(message.data);
		t_curShelfItem->setNodeProgressRate(message.nodeID - 1, 0, t_msg->electricity[0]);
		delete t_msg;
		}
		break;
	case DownloadConfirmMsg: {//下载模式
		auto t_msg = static_cast<SConfirmDownloadMessage *>(message.data);
		if (t_msg->type[0] == 1)
			t_curShelfItem->setNodeStatus(message.nodeID - 1, 2);
		else
			t_curShelfItem->setNodeProgressRate(message.nodeID - 1, 0, 0);
		delete t_msg;
		}
		break;
	case DownloadStateInfoMsg: {//下载进度
		auto t_msg = static_cast<SInfoDownloadStateMessage *>(message.data);
		int t_rate = 100;
		if (t_msg->count > 0)
			t_rate = t_msg->curNum * 100 / t_msg->count;
		t_curShelfItem->setNodeProgressRate(message.nodeID - 1, 0, t_rate);
		delete t_msg;
		}
		break;
	default:
		break;
	}
}
