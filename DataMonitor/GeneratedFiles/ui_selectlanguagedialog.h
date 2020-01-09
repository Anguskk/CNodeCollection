/********************************************************************************
** Form generated from reading UI file 'selectlanguagedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLANGUAGEDIALOG_H
#define UI_SELECTLANGUAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CSelectLanguageDialogClass
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *OKButton;
    QPushButton *CancelButton;

    void setupUi(QDialog *CSelectLanguageDialogClass)
    {
        if (CSelectLanguageDialogClass->objectName().isEmpty())
            CSelectLanguageDialogClass->setObjectName(QString::fromUtf8("CSelectLanguageDialogClass"));
        CSelectLanguageDialogClass->resize(261, 324);
        verticalLayout_2 = new QVBoxLayout(CSelectLanguageDialogClass);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(CSelectLanguageDialogClass);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        OKButton = new QPushButton(CSelectLanguageDialogClass);
        OKButton->setObjectName(QString::fromUtf8("OKButton"));

        horizontalLayout->addWidget(OKButton);

        CancelButton = new QPushButton(CSelectLanguageDialogClass);
        CancelButton->setObjectName(QString::fromUtf8("CancelButton"));

        horizontalLayout->addWidget(CancelButton);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(CSelectLanguageDialogClass);

        QMetaObject::connectSlotsByName(CSelectLanguageDialogClass);
    } // setupUi

    void retranslateUi(QDialog *CSelectLanguageDialogClass)
    {
        CSelectLanguageDialogClass->setWindowTitle(QApplication::translate("CSelectLanguageDialogClass", "Select Language", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("CSelectLanguageDialogClass", "English", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("CSelectLanguageDialogClass", "Chinese", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

        OKButton->setText(QApplication::translate("CSelectLanguageDialogClass", "&OK", nullptr));
        CancelButton->setText(QApplication::translate("CSelectLanguageDialogClass", "&Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CSelectLanguageDialogClass: public Ui_CSelectLanguageDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLANGUAGEDIALOG_H
