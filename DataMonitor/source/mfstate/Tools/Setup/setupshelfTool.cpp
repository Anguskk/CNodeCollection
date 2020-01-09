#include "setupshelfTool.h"

#include "datamonitor.h"
#include "setShelfsdlg.h"
#include "platform.h"
CSetupShelfTool::CSetupShelfTool()
{
}

CSetupShelfTool::~CSetupShelfTool()
{
}

void CSetupShelfTool::OnInitialize()
{
	//��ȡ���м���
	QVector< QPair<int, QString> > t_vIP;
	t_vIP = PlatForm::getAllShelfs();
	CSetShelfsdlg t_setShelfsdlg(t_vIP);
	if (t_setShelfsdlg.exec() != QDialog::Accepted)
		return;
	//��ȡ����е�����
	QVector< QPair<int, QString> > t_getAllTabShelfs;
	t_setShelfsdlg.getIPTab(t_getAllTabShelfs);
	PlatForm::setAllShelfs(t_getAllTabShelfs);
}
