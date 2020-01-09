#pragma once

#include <QDialog>

class Ui_CSetIPdlg;

class CSetIPdlg : public QDialog
{
	Q_OBJECT

public:
	/************************************************************************
	Function:       CSetIPdlg
	Description:    构造函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CSetIPdlg(QWidget *parent = Q_NULLPTR);

	/************************************************************************
	Function:       ~CSetIPdlg
	Description:    析构函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	~CSetIPdlg();

	/************************************************************************
	Function:       getIPRange
	Description:    获取IP范围信息
	Input:          prifix 前缀，startIP 开始ip，endIP 结束IP
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void getIPRange(QString &prifix,int &startIP,int &endIP);

public slots:
	/************************************************************************
	Function:       on_okPushButton_clicked
	Description:    OK按钮
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void on_okPushButton_clicked();

private:
	QSharedPointer<Ui_CSetIPdlg> ui;
};
