#pragma once

#include <QDialog>

class Ui_CSetShelfsdlg;

class CSetShelfsdlg : public QDialog
{
	Q_OBJECT

public:
	/************************************************************************
	Function:       CSetShelfsdlg
	Description:    ���캯��
	Input:          vIP
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CSetShelfsdlg(QVector< QPair<int, QString> > vIP,QWidget *parent = Q_NULLPTR);

	/************************************************************************
	Function:       CSetShelfsdlg
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	~CSetShelfsdlg();

	/************************************************************************
	Function:       initIPTab
	Description:    ��ʼ�����
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void initIPTab();

	/************************************************************************
	Function:       getIPTab
	Description:    ��ȡ�������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void getIPTab(QVector< QPair<int, QString> > &vIP);

private :
	/************************************************************************
	Function:       updataTableWidget
	Description:    ���±��
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void updataTableWidget();

private slots:
	/************************************************************************
	Function:       slotBatchAdd
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
void on_batchAddPushButton_clicked();

	/************************************************************************
	Function:       slotAdd
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void on_addPushButton_clicked();

	/************************************************************************
	Function:       slotRemove
	Description:    ɾ��
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void on_removePushButton_clicked();

	/************************************************************************
	Function:       slotClear
	Description:    ���
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void on_clearPushButton_clicked();

	/************************************************************************
	Function:       slotGetPreIP
	Description:    ��ȡ������ݸı�ǰ������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void slotGetPreIP(int row, int column);

	/************************************************************************
	Function:       slotValueChanged
	Description:    ������ݸı��Ƿ����
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void slotValueChanged(int row, int column);
private:
	QSharedPointer<Ui_CSetShelfsdlg> ui;
	QString                      m_preIP;
	QVector< QPair<int, QString> > m_vIP;
	QVector<QString>              m_allShelfID;
};
