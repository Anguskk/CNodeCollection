/*****************************************************************
**
** Copyright (C)          电子科技大学实验室
**
** Author：刘郑
** Date：2016-01-07
******************************************************************/
#ifndef CSELECTLANGUAGEDIALOG_H
#define CSELECTLANGUAGEDIALOG_H

#include <QDialog>

class Ui_CSelectLanguageDialogClass;

class CSelectLanguageDialog : public QDialog
{
	Q_OBJECT

public:
	CSelectLanguageDialog(QWidget *parent = 0);
	~CSelectLanguageDialog();
	QString GetLanguage(){return m_language;}
private:
	Ui_CSelectLanguageDialogClass *ui;
	QString   m_language;

private slots:
	void on_CancelButton_clicked();
	void on_OKButton_clicked();
};

#endif // CSELECTLANGUAGEDIALOG_H
