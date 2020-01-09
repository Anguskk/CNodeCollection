#include "connecttool.h"

#include <QMessageBox>

#include "client.h"

#include "platform.h"
#include "datamonitor.h"
#include "messageprocessmanage.h"
#include "monitorwindow.h"

CConnectTool::CConnectTool()
{

}

CConnectTool::~CConnectTool()
{

}

void CConnectTool::OnInitialize()
{
	QVector<QPair<int, QString> > t_shelfIDs;
	t_shelfIDs = PlatForm::getAllShelfs();
	if (t_shelfIDs.isEmpty())
	{
		QMessageBox::information(m_pwd, tr("Note"), tr("Please configure the shelf IP!"));
		return;
	}

	auto monitorWindow = dynamic_cast<CDataMonitor*>(m_pwd)->getMonitorWindow();
	auto allShelfIDs = monitorWindow->getAllShelfIDs();
	
	QVector<int> t_shelfs;
	QVector<ShelfInfo> v_trueShelfs;
	for (auto curShelfID: t_shelfIDs)
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
		monitorWindow->addShelf(t_curShelf);
	}
	//É¾³ýÎÞÐ§¼Ü×Ó
	for (auto curShelfID : allShelfIDs)
	{
		monitorWindow->deleteShelf(curShelfID);
	}
}