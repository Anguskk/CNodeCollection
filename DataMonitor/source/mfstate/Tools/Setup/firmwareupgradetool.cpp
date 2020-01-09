#include "firmwareupgradetool.h"

#include <QFileDialog>


CFirmwareUpgradeTool::CFirmwareUpgradeTool()
{
}

CFirmwareUpgradeTool::~CFirmwareUpgradeTool()
{
}

void CFirmwareUpgradeTool::OnInitialize()
{
	QFileDialog::getOpenFileName(NULL, tr("Open File"), ".", "*.system;;*.*");
}
