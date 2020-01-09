#include "annualinspectionreporttool.h"

#include "datamonitor.h"

#include <QFileDialog>

CAnnualInspectionReportTool::CAnnualInspectionReportTool()
{

}

CAnnualInspectionReportTool::~CAnnualInspectionReportTool()
{

}

void CAnnualInspectionReportTool::OnInitialize()
{
	QFileDialog::getSaveFileName(NULL, tr("Save File"), ".", "*.xls;;*.*");
}