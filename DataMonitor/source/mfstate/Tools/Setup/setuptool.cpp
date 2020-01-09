#include "setuptool.h"

#include "datamonitor.h"
#include "Setup/setparameterdlg.h"

CSetupTool::CSetupTool()
{

}

CSetupTool::~CSetupTool()
{

}

void CSetupTool::OnInitialize()
{
	CSetParameterdlg t_setParameterdlg;
	if (t_setParameterdlg.exec() != QDialog::Accepted)
		return;
	
}