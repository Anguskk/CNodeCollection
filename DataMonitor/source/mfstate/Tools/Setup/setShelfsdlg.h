#pragma once

#include <QDialog>

class Ui_CSetShelfsdlg;

class CSetShelfsdlg : public QDialog
{
	Q_OBJECT

public:
	/************************************************************************
	Function:       CSetShelfsdlg
	Description:    构造函数
	Input:          vIP
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	CSetShelfsdlg(QVector< QPair<int, QString> > vIP,QWidget *parent = Q_NULLPTR);

	/************************************************************************
	Function:       CSetShelfsdlg
	Description:    析构函数
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	~CSetShelfsdlg();

	/************************************************************************
	Function:       initIPTab
	Description:    初始化表格
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void initIPTab();

	/************************************************************************
	Function:       getIPTab
	Description:    获取表格内容
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void getIPTab(QVector< QPair<int, QString> > &vIP);

private :
	/************************************************************************
	Function:       updataTableWidget
	Description:    更新表格
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void updataTableWidget();

private slots:
	/************************************************************************
	Function:       slotBatchAdd
	Description:    批量增加
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
void on_batchAddPushButton_clicked();

	/************************************************************************
	Function:       slotAdd
	Description:    单行增加
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void on_addPushButton_clicked();

	/************************************************************************
	Function:       slotRemove
	Description:    删除
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void on_removePushButton_clicked();

	/************************************************************************
	Function:       slotClear
	Description:    清空
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void on_clearPushButton_clicked();

	/************************************************************************
	Function:       slotGetPreIP
	Description:    获取表格内容改变前的内容
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void slotGetPreIP(int row, int column);

	/************************************************************************
	Function:       slotValueChanged
	Description:    表格内容改变是否合理
	Input:          无
	Output:         无
	Return:         无
	Others:         无
	************************************************************************/
	void slotValueChanged(int row, int column);
private:
	QSharedPointer<Ui_CSetShelfsdlg> ui;
	QString                      m_preIP;
	QVector< QPair<int, QString> > m_vIP;
	QVector<QString>              m_allShelfID;
};
