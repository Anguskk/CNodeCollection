#include "exittool.h"

#include "datamonitor.h"

CExitTool::CExitTool()
{

}

CExitTool::~CExitTool()
{

}

void CExitTool::OnInitialize()
{
	dynamic_cast<CDataMonitor*>(m_pwd)->close();
}