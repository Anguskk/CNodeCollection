#include "annualinspectiontool.h"

#include "datamonitor.h"

CAnnualInspectionTool::CAnnualInspectionTool()
{

}

CAnnualInspectionTool::~CAnnualInspectionTool()
{

}

void CAnnualInspectionTool::OnInitialize()
{
	dynamic_cast<CDataMonitor*>(m_pwd)->removeInfoDockWidget();
}