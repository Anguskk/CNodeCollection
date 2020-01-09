#include "setIPdlg.h"

#include "ui_setIPdlg.h"

CSetIPdlg::CSetIPdlg(QWidget *parent)
	: QDialog(parent), ui(new Ui_CSetIPdlg)
{
	ui->setupUi(this);

	connect(ui->cancelPushButton, &QPushButton::clicked, this, &QDialog::close);
}

CSetIPdlg::~CSetIPdlg()
{
}

/************************************************************************
Function:       getIPRange
Description:    获取IP范围信息
Input:          prifix 前缀，startIP 开始ip，endIP 结束IP
Output:         无
Return:         无
Others:         无
************************************************************************/
void CSetIPdlg::getIPRange(QString &prifix, int &startIP, int &endIP)
{
	startIP = ui->satrtSpinBox->value();
	endIP = ui->endSpinBox->value();
	prifix = ui->label->text();
}

/************************************************************************
Function:       on_okPushButton_clicked
Description:    OK按钮
Input:          无
Output:         无
Return:         无
Others:         无
************************************************************************/
void CSetIPdlg::on_okPushButton_clicked()
{
	accept();
}
