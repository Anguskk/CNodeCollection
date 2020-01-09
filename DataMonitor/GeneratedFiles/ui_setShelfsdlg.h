/********************************************************************************
** Form generated from reading UI file 'setShelfsdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETSHELFSDLG_H
#define UI_SETSHELFSDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CSetShelfsdlg
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *ipTableWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *batchAddPushButton;
    QPushButton *addPushButton;
    QPushButton *removePushButton;
    QPushButton *clearPushButton;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *OkPushButton;
    QPushButton *cancelPushButton;

    void setupUi(QWidget *CSetShelfsdlg)
    {
        if (CSetShelfsdlg->objectName().isEmpty())
            CSetShelfsdlg->setObjectName(QString::fromUtf8("CSetShelfsdlg"));
        CSetShelfsdlg->resize(384, 401);
        gridLayout = new QGridLayout(CSetShelfsdlg);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        ipTableWidget = new QTableWidget(CSetShelfsdlg);
        if (ipTableWidget->columnCount() < 2)
            ipTableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        ipTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        ipTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        ipTableWidget->setObjectName(QString::fromUtf8("ipTableWidget"));

        horizontalLayout_2->addWidget(ipTableWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        batchAddPushButton = new QPushButton(CSetShelfsdlg);
        batchAddPushButton->setObjectName(QString::fromUtf8("batchAddPushButton"));

        verticalLayout->addWidget(batchAddPushButton);

        addPushButton = new QPushButton(CSetShelfsdlg);
        addPushButton->setObjectName(QString::fromUtf8("addPushButton"));

        verticalLayout->addWidget(addPushButton);

        removePushButton = new QPushButton(CSetShelfsdlg);
        removePushButton->setObjectName(QString::fromUtf8("removePushButton"));

        verticalLayout->addWidget(removePushButton);

        clearPushButton = new QPushButton(CSetShelfsdlg);
        clearPushButton->setObjectName(QString::fromUtf8("clearPushButton"));

        verticalLayout->addWidget(clearPushButton);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2->setStretch(0, 3);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_2);

        frame = new QFrame(CSetShelfsdlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        OkPushButton = new QPushButton(CSetShelfsdlg);
        OkPushButton->setObjectName(QString::fromUtf8("OkPushButton"));

        horizontalLayout->addWidget(OkPushButton);

        cancelPushButton = new QPushButton(CSetShelfsdlg);
        cancelPushButton->setObjectName(QString::fromUtf8("cancelPushButton"));

        horizontalLayout->addWidget(cancelPushButton);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(CSetShelfsdlg);

        QMetaObject::connectSlotsByName(CSetShelfsdlg);
    } // setupUi

    void retranslateUi(QWidget *CSetShelfsdlg)
    {
        CSetShelfsdlg->setWindowTitle(QApplication::translate("CSetShelfsdlg", "CSetShelfsdlg", nullptr));
        QTableWidgetItem *___qtablewidgetitem = ipTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CSetShelfsdlg", "Shelf ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = ipTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CSetShelfsdlg", "IP Address", nullptr));
        batchAddPushButton->setText(QApplication::translate("CSetShelfsdlg", "Batch addition", nullptr));
        addPushButton->setText(QApplication::translate("CSetShelfsdlg", "Add", nullptr));
        removePushButton->setText(QApplication::translate("CSetShelfsdlg", "Remove", nullptr));
        clearPushButton->setText(QApplication::translate("CSetShelfsdlg", "Clear", nullptr));
        OkPushButton->setText(QApplication::translate("CSetShelfsdlg", "OK", nullptr));
        cancelPushButton->setText(QApplication::translate("CSetShelfsdlg", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CSetShelfsdlg: public Ui_CSetShelfsdlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETSHELFSDLG_H
