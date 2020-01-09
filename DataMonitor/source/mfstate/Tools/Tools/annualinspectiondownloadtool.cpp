#include "annualinspectiondownloadtool.h"

#include "datamonitor.h"

CAnnualInspectionDownloadTool::CAnnualInspectionDownloadTool()
{
}

CAnnualInspectionDownloadTool::~CAnnualInspectionDownloadTool()
{
}

void CAnnualInspectionDownloadTool::OnInitialize()
{
	dynamic_cast<CDataMonitor*>(m_pwd)->addInfoDockWidget();
}