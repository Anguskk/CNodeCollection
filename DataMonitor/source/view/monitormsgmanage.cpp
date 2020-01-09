/**************************************************************
Copyright (C),  2016   ���ӿƼ���ѧ.
FileName :  monitormsgmanage.cpp
Author :       lz
Version : V1.0
Date : 2016/8/30
Description :        ///ģ������
Other :              ///��������
Function List :      ///��Ҫ�������书��
History :            ///��ʷ�޸ļ�¼
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

//���ݱ�����
class CMonitorMsgManagePrivate
{
	Q_DECLARE_PUBLIC(CMonitorMsgManage)

public:
	/************************************************************************
	Function:       CGraphicsNodeItem()
	Description:    ���캯��
	Input:          width ��ȣ�height �߶ȣ�info �ڵ���Ϣ��parent ��object
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CMonitorMsgManagePrivate(CMonitorWindow *window, QDockWidget *infoBoardDock, QDockWidget *nodeInfoDock,CMonitorMsgManage *parent);

	/************************************************************************
	Function:       ~CGraphicsNodeItemPrivate()
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	virtual ~CMonitorMsgManagePrivate();

	/************************************************************************
	Function:       getShelfItem()
	Description:    ��ȡ����
	Input:          shelfID ����ID
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CGraphicsShelfItem* getShelfItem(int shelfID);

private:
	/************************************************************************
	Function:       initConntion()
	Description:    ��ʼ������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void initConntion();

private:
	unsigned short               type                         = AnnualInspectionRequestMsg;    //ģʽ����
	CMonitorWindow               *m_window                    = nullptr;                       //��ʾ����
	CMessageProcessManage        *m_messageProcessManage      = nullptr;                       //��Ϣ�����߳�
	QDockWidget                  *m_infoBoardDock             = nullptr;                       //��Ϣ��ʾ
	QDockWidget                  *m_nodeInfoDock              = nullptr;                       //�ڵ���Ϣ��ʾ
	unsigned short               nextType                     = AnnualInspectionRequestMsg;    //��һ��ģʽ
	QVector<QPair<int, QString> > nextShelfIDs;                                                //��һ��������Ϣ

	CMonitorMsgManage            *q_ptr                       = nullptr;                       //��ָ��
};

/************************************************************************
Function:       CGraphicsNodeItem()
Description:    ���캯��
Input:          width ��ȣ�height �߶ȣ�info �ڵ���Ϣ��parent ��object
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CMonitorMsgManagePrivate::CMonitorMsgManagePrivate(CMonitorWindow *window, QDockWidget *infoBoardDock, QDockWidget *nodeInfoDock, CMonitorMsgManage *parent)
	:q_ptr(parent), m_window(window), m_infoBoardDock(infoBoardDock), m_nodeInfoDock(nodeInfoDock),m_messageProcessManage(new CMessageProcessManage(parent))
{
	initConntion();
}

/************************************************************************
Function:       ~CGraphicsNodeItemPrivate()
Description:    ��������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CMonitorMsgManagePrivate::~CMonitorMsgManagePrivate()
{
	
}

/************************************************************************
Function:       getShelfItem()
Description:    ��ȡ����
Input:          shelfID ����ID
Output:         ��
Return:         ��
Others:         ��
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
Description:    ��ʼ������
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CMonitorMsgManagePrivate::initConntion()
{
	Q_Q(CMonitorMsgManage);
	q->connect(m_messageProcessManage->get_process_thread(), &CMessageProcessThread::send_statusinfo, 
		q, &CMonitorMsgManage::processMsgSlot);
}

/************************************************************************
Function:       CMonitorMsgManage()
Description:    ���캯��
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CMonitorMsgManage::CMonitorMsgManage(CMonitorWindow *window, QDockWidget *infoBoardDock, QDockWidget *nodeInfoDock)
	:d_ptr(new CMonitorMsgManagePrivate(window, infoBoardDock, nodeInfoDock,this))
{
}

/************************************************************************
Function:       ~CMonitorMsgManage()
Description:    �����������ͷ�����
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
CMonitorMsgManage::~CMonitorMsgManage()
{
	Q_D(CMonitorMsgManage);
	d->m_messageProcessManage->shutdown();
}

/************************************************************************
Function:       changeModeStatus()
Description:    �л�ģʽ״̬
				true--���нڵ�����ɻ��߶Ͽ����ӣ�
				false--�������ڽ��еĽڵ�
Input:          ��
Output:         ��
Return:         ��
Others:         ��
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
Description:    ��ǰģʽ״̬
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
unsigned short CMonitorMsgManage::currentModeStatus()
{
	Q_D(CMonitorMsgManage);
	return d->type;
}

/************************************************************************
Function:       addMessage()
Description:    �����Ϣ
Input:          message ��Ϣ
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CMonitorMsgManage::addMessage(SMessageBase &message)
{
	Q_D(CMonitorMsgManage);
	d->m_messageProcessManage->append_deliver_message(message);
}

/************************************************************************
Function:       changeModelType()
Description:    �л�ģʽ�����г��״̬������ʱ�л�������״̬��
Input:          type ģʽ
Output:         ��
Return:         ��
Others:         ��
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
Description:    �л�ģʽ
Input:          ��
Output:         ��
Return:         ��
Others:         ��
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
	//ɾ����Ч����
	for (auto curShelfID : allShelfIDs)
	{
		d->m_window->deleteShelf(curShelfID);
	}

	//�������
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

	//���·ַ���Ч���ӵ���Ϣ
	SMessageBase message_base;
	message_base.shelfID = -1;
	message_base.nodeID = -1;
	message_base.type = d->nextType;

	switch (d->nextType)
	{
	case AnnualInspectionRequestMsg://���
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
	case AnnualInspectionDownloadRequestMsg://�������
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
	case ChargingRequestMsg://���
		{
			auto curMsg = new SRequestChargingMessage;
			curMsg->monitoring[0] = 1;
			message_base.length = sizeof(SRequestChargingMessage);
			message_base.data = curMsg;
		}
		break;
	case DownloadRequestMsg://����
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
Description:    ������Ϣ
Input:          message ��Ϣ
Output:         ��
Return:         ��
Others:         ��
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
	case AnnualInspectionConfirmMsg: {//���ģʽ
		auto t_msg = static_cast<SConfirmAnnualInspectionMessage *>(message.data);
		if (t_msg->type[0] == 1)
			t_curShelfItem->setNodeStatus(message.nodeID - 1, 2);
		else if (t_msg->type[0] == 2)
			t_curShelfItem->setNodeProgressRate(message.nodeID - 1, 0, 100);
		else
			t_curShelfItem->setNodeProgressRate(message.nodeID - 1, 0, 0);
		}
		break;
	case AnnualInspectionStateInfoMsg: {//������
		auto t_msg = static_cast<SInfoAnnualInspectionStateMessage *>(message.data);
		t_curShelfItem->setNodeProgressRate(message.nodeID - 1, 0, t_msg->rate[0]);
		delete t_msg;
		}
		break;
	case AnnualInspectionDownloadConfirmMsg: {//�������ģʽ
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
	case AnnualInspectionDownloadStateInfoMsg: {//������ؽ���
		auto t_msg = static_cast<SInfoAnnualInspectionDownloadStateMessage *>(message.data);
		if (t_msg->rate[0] == 1)
			t_curShelfItem->setNodeStatus(message.nodeID - 1, 2);
		else
			t_curShelfItem->setNodeProgressRate(message.nodeID - 1, 0, 100);
		delete t_msg;
		}
		break;
	case ChargingConfirmMsg: {//���ģʽ
		auto t_msg = static_cast<SConfirmChargingMessage *>(message.data);
		if (t_msg->type[0] == 1)
			t_curShelfItem->setNodeStatus(message.nodeID - 1, 2);
		else
			t_curShelfItem->setNodeProgressRate(message.nodeID - 1, 0, 0);
		delete t_msg;
		}
		break;
	case ChargingStateInfoMsg: {//������
		auto t_msg = static_cast<SInfoChargingStateMessage *>(message.data);
		t_curShelfItem->setNodeProgressRate(message.nodeID - 1, 0, t_msg->electricity[0]);
		delete t_msg;
		}
		break;
	case DownloadConfirmMsg: {//����ģʽ
		auto t_msg = static_cast<SConfirmDownloadMessage *>(message.data);
		if (t_msg->type[0] == 1)
			t_curShelfItem->setNodeStatus(message.nodeID - 1, 2);
		else
			t_curShelfItem->setNodeProgressRate(message.nodeID - 1, 0, 0);
		delete t_msg;
		}
		break;
	case DownloadStateInfoMsg: {//���ؽ���
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
