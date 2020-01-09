#include "setparameterdlg.h"

#include "ui_setparameterdlg.h"

#include "messagesnodedefinition.h"

#include "QMessageBox"

CSetParameterdlg::CSetParameterdlg(QWidget *parent)
	: QDialog(parent),ui(new Ui_CSetParameterdlg)
{
	ui->setupUi(this);
	initUI();

	connect(ui->cancelPushButton, &QPushButton::clicked, this, &CSetParameterdlg::close);
	connect(ui->okPushButton, &QPushButton::clicked, [=]() {
		int t_msg = QMessageBox::warning(this, tr("Warning"), tr("Whether to confirm the modification?"), QMessageBox::Ok, QMessageBox::No);
		if (t_msg == QMessageBox::Ok)
			accept();
	});
}

CSetParameterdlg::~CSetParameterdlg()
{

}

void CSetParameterdlg::initUI()
{
// 	//采样率
// 	ui->samplingComboBox->addItem("Selected...");
// 	ui->samplingComboBox->addItem("ADS_SPS_250");
// 	ui->samplingComboBox->addItem("ADS_SPS_500");
// 	ui->samplingComboBox->addItem("ADS_SPS_1000");
// 	ui->samplingComboBox->addItem("ADS_SPS_2000");
// 	ui->samplingComboBox->addItem("ADS_SPS_4000");
// 
// 	//增益
// 	ui->gainComboBox->addItem("Selected...");
// 	ui->gainComboBox->addItem("ADS_GAIN_1");
// 	ui->gainComboBox->addItem("ADS_GAIN_2");
// 	ui->gainComboBox->addItem("ADS_GAIN_4");
// 	ui->gainComboBox->addItem("ADS_GAIN_8");
// 	ui->gainComboBox->addItem("ADS_GAIN_16");
// 	ui->gainComboBox->addItem("ADS_GAIN_32");
// 	ui->gainComboBox->addItem("ADS_GAIN_64");
// 	
// 	//滤波器类型
// 	ui->filterTypeComboBox->addItem("Linear");
// 	ui->filterTypeComboBox->addItem("Minimum Phase");
}