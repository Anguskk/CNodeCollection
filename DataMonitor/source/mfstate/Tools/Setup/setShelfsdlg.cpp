#include "setShelfsdlg.h"

#include <QMessageBox>

#include "ui_setShelfsdlg.h"

#include "setIPdlg.h"
#include "platform.h"

CSetShelfsdlg::CSetShelfsdlg(QVector< QPair<int, QString> > vIP,QWidget *parent)
	: QDialog(parent),ui(new Ui_CSetShelfsdlg)
{
	ui->setupUi(this);
	m_vIP = vIP;
	initIPTab();

	connect(ui->cancelPushButton, &QPushButton::clicked, this, &QDialog::close);
	connect(ui->ipTableWidget, &QTableWidget::cellDoubleClicked, this, &CSetShelfsdlg::slotGetPreIP);
	connect(ui->ipTableWidget, &QTableWidget::cellChanged, this, &CSetShelfsdlg::slotValueChanged);
	connect(ui->OkPushButton, &QPushButton::clicked, [=]() {
		int t_msg = QMessageBox::warning(this, tr("Warning"), tr("Whether to confirm the modification?"), QMessageBox::Ok, QMessageBox::No);
		if (t_msg == QMessageBox::Ok)
			accept();
	});
}

CSetShelfsdlg::~CSetShelfsdlg()
{

}

//初始化表格
void CSetShelfsdlg::initIPTab()
{
	int t_count = m_vIP.size();
	ui->ipTableWidget->setRowCount(t_count);
	for (int i = 0; i < t_count; i++)
	{
		ui->ipTableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(m_vIP[i].first)));
		ui->ipTableWidget->setItem(i, 1, new QTableWidgetItem(m_vIP[i].second));
		ui->ipTableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
		ui->ipTableWidget->item(i, 1)->setTextAlignment(Qt::AlignCenter);
	}
	int t_rowCount = ui->ipTableWidget->rowCount();
	if (t_rowCount == 0)
	{
		ui->removePushButton->setEnabled(false);
		ui->clearPushButton->setEnabled(false);
	}
	else
	{
		ui->removePushButton->setEnabled(true);
		ui->clearPushButton->setEnabled(true);
	}
	if (t_rowCount == 16)
	{
		ui->batchAddPushButton->setEnabled(false);
		ui->addPushButton->setEnabled(false);
	}

	ui->ipTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//行选中模式
}

//批量增加IP
void CSetShelfsdlg::on_batchAddPushButton_clicked()
{
	CSetIPdlg t_setIPdlg;
	if (t_setIPdlg.exec() != QDialog::Accepted)
		return;
	int t_startIndex = -1, t_endIndex = -1;
	QString t_IP;
	t_setIPdlg.getIPRange(t_IP, t_startIndex, t_endIndex);
	int t_count = t_endIndex - t_startIndex + 1;
	int t_rowCount = ui->ipTableWidget->rowCount();
	QVector<QString> t_allIPs;
	for (int i = 0; i < t_rowCount; i++)
		t_allIPs.append(ui->ipTableWidget->item(i, 1)->text());

	for (int i = t_startIndex; i <= t_endIndex; i++)
	{
		QString t_curIP = t_IP + QString::number(i);
		if (t_allIPs.contains(t_curIP))
			continue;

		t_rowCount = ui->ipTableWidget->rowCount();
		ui->ipTableWidget->insertRow(t_rowCount);
		ui->ipTableWidget->setItem(t_rowCount, 0, new QTableWidgetItem(QString::number(i - 1)));
		ui->ipTableWidget->setItem(t_rowCount, 1, new QTableWidgetItem(t_curIP));
		ui->ipTableWidget->item(t_rowCount, 0)->setTextAlignment(Qt::AlignCenter);
		ui->ipTableWidget->item(t_rowCount, 1)->setTextAlignment(Qt::AlignCenter);

		t_allIPs.append(t_curIP);
	}
	updataTableWidget();
	if (t_rowCount + 1 > 15)
	{
		ui->batchAddPushButton->setEnabled(false);
		ui->addPushButton->setEnabled(false);
	}
	ui->removePushButton->setEnabled(true);
	ui->clearPushButton->setEnabled(true);
}

//添加一行
void CSetShelfsdlg::on_addPushButton_clicked()
{
	QVector< QPair<int, QString> > t_allShelfs;
	t_allShelfs = PlatForm::getAllShelfs();

	QString t_IP = "192.168.1.";
	int t_rowCount = ui->ipTableWidget->rowCount();
	ui->ipTableWidget->insertRow(t_rowCount);
	if (t_rowCount == 0)
	{
		ui->ipTableWidget->setItem(t_rowCount, 0, new QTableWidgetItem(QString::number(1)));
		ui->ipTableWidget->setItem(t_rowCount, 1, new QTableWidgetItem(t_IP + QString::number(2)));
		ui->ipTableWidget->item(t_rowCount, 0)->setTextAlignment(Qt::AlignCenter);
		ui->ipTableWidget->item(t_rowCount, 1)->setTextAlignment(Qt::AlignCenter);
	}
	else
	{
		QVector<int> t_allShelfID;
		for (int i = 0; i < t_rowCount; i++)
		{
			int t_shelfID = ui->ipTableWidget->item(i, 0)->text().toInt();
			t_allShelfID.append(t_shelfID);
		}

		int t_ID = ui->ipTableWidget->item(t_rowCount-1,0)->text().toInt();
		while (t_ID < 17)
		{
			if (!t_allShelfID.contains(t_ID))
			{
				ui->ipTableWidget->setItem(t_rowCount, 0, new QTableWidgetItem(QString::number(t_ID)));
				ui->ipTableWidget->setItem(t_rowCount, 1, new QTableWidgetItem(t_IP + QString::number(t_ID + 1)));
				ui->ipTableWidget->item(t_rowCount, 0)->setTextAlignment(Qt::AlignCenter);
				ui->ipTableWidget->item(t_rowCount, 1)->setTextAlignment(Qt::AlignCenter);
				break;
			}
			else if (t_ID == 16)
				t_ID =  1;
			else
				t_ID++;
		}
	}
	
	if (t_rowCount + 1 > 0)
	{
		ui->removePushButton->setEnabled(true);
		ui->clearPushButton->setEnabled(true);
	}

	if (t_rowCount + 1 > 15)
	{
		ui->addPushButton->setEnabled(false);
		ui->batchAddPushButton->setEnabled(false);
		return;
	}
}

//删除
void CSetShelfsdlg::on_removePushButton_clicked()
{
	QList<QTableWidgetSelectionRange> t_ranges = ui->ipTableWidget->selectedRanges();
	if (t_ranges.isEmpty())
	{
		QMessageBox::information(this, tr("Information"), tr("Please select rows!"));
		return;
	}
	int t_count = t_ranges.count();
	QVector<int> t_index;
	if (!t_ranges.isEmpty())
	{
		for (int i = 0; i < t_count; i++)
		{
			int t_topRow = t_ranges.at(i).topRow();
			int t_bottomRow = t_ranges.at(i).bottomRow();
			for (int j = t_topRow; j <= t_bottomRow; j++)
				t_index.append(j);
		}
		qSort(t_index.begin(), t_index.end());
		for (int ii = t_index.size() - 1; ii >= 0; ii--)
			ui->ipTableWidget->removeRow(t_index[ii]);
	}
	updataTableWidget();
	int t_rowCount = ui->ipTableWidget->rowCount();
	if (t_rowCount == 0)
	{
		ui->batchAddPushButton->setEnabled(true);
		ui->addPushButton->setEnabled(true);
		ui->removePushButton->setEnabled(false);
		ui->clearPushButton->setEnabled(false);
	}
}

//清空表格
void CSetShelfsdlg::on_clearPushButton_clicked()
{
	ui->ipTableWidget->setRowCount(0);
	ui->ipTableWidget->clearContents();
	ui->batchAddPushButton->setEnabled(true);
	ui->addPushButton->setEnabled(true);
	ui->removePushButton->setEnabled(false);
	ui->clearPushButton->setEnabled(false);
}

//删除后进行排序
bool sortAllShelfs(const QPair<int, QString> &s1, const QPair<int, QString> &s2)
{
	return s1.first < s2.first;
}

//更新表格
void CSetShelfsdlg::updataTableWidget()
{
	QVector< QPair<int, QString> > t_allShelfs;
	getIPTab(t_allShelfs);
	qSort(t_allShelfs.begin(), t_allShelfs.end(), sortAllShelfs);
	for (int i = 0; i < t_allShelfs.size(); i++)
	{
		ui->ipTableWidget->item(i, 0)->setText(QString::number(t_allShelfs[i].first));
		ui->ipTableWidget->item(i, 1)->setText(t_allShelfs[i].second);
	}
}

//获取变化前的内容
void CSetShelfsdlg::slotGetPreIP(int row, int column)
{
	m_allShelfID.clear();
	int t_rowCount = ui->ipTableWidget->rowCount();
	for (int i = 0; i < t_rowCount; i++)
		m_allShelfID.append(ui->ipTableWidget->item(i, 0)->text());
	if (column == 1)
		m_preIP = ui->ipTableWidget->item(row, column)->text();
}

//单元格的内容改变是否正确
void CSetShelfsdlg::slotValueChanged(int row, int column)
{
	if (column == 0 && !m_allShelfID.isEmpty())
	{
		QString t_currentID = ui->ipTableWidget->item(row, column)->text();
		if (m_allShelfID.contains(t_currentID))
			ui->ipTableWidget->item(row, column)->setText(m_allShelfID[row]);
	}
	if (column == 1 && !m_preIP.isEmpty())
	{
		QString t_currrentIP = ui->ipTableWidget->item(row, column)->text();
		QStringList t_currrentIPList = t_currrentIP.split(".");
		if (t_currrentIPList.isEmpty())
			return;
		int t_lastNum = t_currrentIPList[3].toInt();
		if (t_lastNum < 2 || t_lastNum > 17)
			ui->ipTableWidget->item(row, column)->setText(m_preIP);
	}
}

//得到表格里的内容
void CSetShelfsdlg::getIPTab(QVector< QPair<int, QString> > &vIP)
{
	int t_rowCount = ui->ipTableWidget->rowCount();
	vIP.resize(t_rowCount);
	for (int i = 0; i < t_rowCount; i++)
	{
		vIP[i].first = ui->ipTableWidget->item(i, 0)->text().toInt();
		vIP[i].second = ui->ipTableWidget->item(i, 1)->text();
	}
}