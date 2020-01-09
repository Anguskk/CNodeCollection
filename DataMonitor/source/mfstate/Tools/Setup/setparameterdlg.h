#pragma once

#include <QDialog>

class Ui_CSetParameterdlg;

class CSetParameterdlg : public QDialog
{
	Q_OBJECT

public:
	CSetParameterdlg(QWidget *parent = Q_NULLPTR);
	~CSetParameterdlg();

private:
	void initUI();

private:
	QSharedPointer<Ui_CSetParameterdlg> ui;
};
