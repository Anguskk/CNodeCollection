/********************************************************************************
** Form generated from reading UI file 'datamonitor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAMONITOR_H
#define UI_DATAMONITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataMonitorClass
{
public:
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DataMonitorClass)
    {
        if (DataMonitorClass->objectName().isEmpty())
            DataMonitorClass->setObjectName(QString::fromUtf8("DataMonitorClass"));
        DataMonitorClass->resize(600, 400);
        centralWidget = new QWidget(DataMonitorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        DataMonitorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(DataMonitorClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        DataMonitorClass->setStatusBar(statusBar);

        retranslateUi(DataMonitorClass);

        QMetaObject::connectSlotsByName(DataMonitorClass);
    } // setupUi

    void retranslateUi(QMainWindow *DataMonitorClass)
    {
        DataMonitorClass->setWindowTitle(QApplication::translate("DataMonitorClass", "Data Monitor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataMonitorClass: public Ui_DataMonitorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAMONITOR_H
