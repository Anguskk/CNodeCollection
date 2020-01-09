/*****************************************************************
**
** Copyright (C)          电子科技大学实验室
**
** Author：刘郑
** Date：2016-01-07
******************************************************************/
#include "selectlanguagedialog.h"

#include <QMessageBox>

#include "platform.h"
#include "ui_selectlanguagedialog.h"

CSelectLanguageDialog::CSelectLanguageDialog(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui_CSelectLanguageDialogClass;
	ui->setupUi(this);

	QString language = PlatForm::getPlatformLanguage();
	if (language == "en")
	{
		ui->listWidget->setCurrentRow(0,QItemSelectionModel::SelectCurrent);
	}
	else
	{
		ui->listWidget->setCurrentRow(1,QItemSelectionModel::SelectCurrent);
	}
}

CSelectLanguageDialog::~CSelectLanguageDialog()
{
	if (ui != nullptr)
	{
		delete ui;
		ui = nullptr;
	}
}


void CSelectLanguageDialog::on_OKButton_clicked()
{
	QList<QListWidgetItem*> t_listiem = ui->listWidget->selectedItems();
	if (t_listiem.count() == 0)
	{
		QMessageBox::warning(this,tr("Warning"),tr("Please select language!"));
		return;
	}
	QString t_str = t_listiem.at(0)->text();
	if (t_str == tr("Chinese"))
	{
		m_language = "zh";
	}
	else
	{
		m_language = "en";
	}
    accept();
}

void CSelectLanguageDialog::on_CancelButton_clicked()
{
   reject();
}