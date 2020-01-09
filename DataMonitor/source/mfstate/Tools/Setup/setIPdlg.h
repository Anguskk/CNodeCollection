#pragma once

#include <QDialog>

class Ui_CSetIPdlg;

class CSetIPdlg : public QDialog
{
	Q_OBJECT

public:
	/************************************************************************
	Function:       CSetIPdlg
	Description:    ���캯��
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CSetIPdlg(QWidget *parent = Q_NULLPTR);

	/************************************************************************
	Function:       ~CSetIPdlg
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	~CSetIPdlg();

	/************************************************************************
	Function:       getIPRange
	Description:    ��ȡIP��Χ��Ϣ
	Input:          prifix ǰ׺��startIP ��ʼip��endIP ����IP
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void getIPRange(QString &prifix,int &startIP,int &endIP);

public slots:
	/************************************************************************
	Function:       on_okPushButton_clicked
	Description:    OK��ť
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void on_okPushButton_clicked();

private:
	QSharedPointer<Ui_CSetIPdlg> ui;
};
