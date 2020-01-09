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
Description:    ��ȡIP��Χ��Ϣ
Input:          prifix ǰ׺��startIP ��ʼip��endIP ����IP
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CSetIPdlg::getIPRange(QString &prifix, int &startIP, int &endIP)
{
	startIP = ui->satrtSpinBox->value();
	endIP = ui->endSpinBox->value();
	prifix = ui->label->text();
}

/************************************************************************
Function:       on_okPushButton_clicked
Description:    OK��ť
Input:          ��
Output:         ��
Return:         ��
Others:         ��
************************************************************************/
void CSetIPdlg::on_okPushButton_clicked()
{
	accept();
}
