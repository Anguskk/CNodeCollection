#include "downloadtool.h"

#include "datamonitor.h"

CDownloadTool::CDownloadTool()
{

}

CDownloadTool::~CDownloadTool()
{

}

void CDownloadTool::OnInitialize()
{
	dynamic_cast<CDataMonitor*>(m_pwd)->addInfoDockWidget();
}