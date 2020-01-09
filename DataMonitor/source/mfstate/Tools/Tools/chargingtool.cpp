#include "chargingtool.h"

#include "datamonitor.h"

CChargingTool::CChargingTool()
{

}

CChargingTool::~CChargingTool()
{

}

void CChargingTool::OnInitialize()
{
	dynamic_cast<CDataMonitor*>(m_pwd)->addInfoDockWidget();
}