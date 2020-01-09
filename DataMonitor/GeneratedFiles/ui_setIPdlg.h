/********************************************************************************
** Form generated from reading UI file 'setIPdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETIPDLG_H
#define UI_SETIPDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CSetIPdlg
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *satrtSpinBox;
    QLabel *label_2;
    QSpinBox *endSpinBox;
    QSpacerItem *verticalSpacer_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *okPushButton;
    QPushButton *cancelPushButton;

    void setupUi(QWidget *CSetIPdlg)
    {
        if (CSetIPdlg->objectName().isEmpty())
            CSetIPdlg->setObjectName(QString::fromUtf8("CSetIPdlg"));
        CSetIPdlg->resize(349, 126);
        gridLayout = new QGridLayout(CSetIPdlg);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(CSetIPdlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        satrtSpinBox = new QSpinBox(CSetIPdlg);
        satrtSpinBox->setObjectName(QString::fromUtf8("satrtSpinBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(satrtSpinBox->sizePolicy().hasHeightForWidth());
        satrtSpinBox->setSizePolicy(sizePolicy);
        satrtSpinBox->setMinimum(2);
        satrtSpinBox->setMaximum(17);

        horizontalLayout->addWidget(satrtSpinBox);

        label_2 = new QLabel(CSetIPdlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_2);

        endSpinBox = new QSpinBox(CSetIPdlg);
        endSpinBox->setObjectName(QString::fromUtf8("endSpinBox"));
        sizePolicy.setHeightForWidth(endSpinBox->sizePolicy().hasHeightForWidth());
        endSpinBox->setSizePolicy(sizePolicy);
        endSpinBox->setMinimum(2);
        endSpinBox->setMaximum(17);
        endSpinBox->setValue(5);

        horizontalLayout->addWidget(endSpinBox);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        verticalLayout_2->addLayout(verticalLayout);

        frame = new QFrame(CSetIPdlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(frame);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        okPushButton = new QPushButton(CSetIPdlg);
        okPushButton->setObjectName(QString::fromUtf8("okPushButton"));

        horizontalLayout_2->addWidget(okPushButton);

        cancelPushButton = new QPushButton(CSetIPdlg);
        cancelPushButton->setObjectName(QString::fromUtf8("cancelPushButton"));

        horizontalLayout_2->addWidget(cancelPushButton);


        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(CSetIPdlg);

        QMetaObject::connectSlotsByName(CSetIPdlg);
    } // setupUi

    void retranslateUi(QWidget *CSetIPdlg)
    {
        CSetIPdlg->setWindowTitle(QApplication::translate("CSetIPdlg", "Rang IP", nullptr));
        label->setText(QApplication::translate("CSetIPdlg", "192.168.1.", nullptr));
        label_2->setText(QApplication::translate("CSetIPdlg", "to", nullptr));
        okPushButton->setText(QApplication::translate("CSetIPdlg", "OK", nullptr));
        cancelPushButton->setText(QApplication::translate("CSetIPdlg", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CSetIPdlg: public Ui_CSetIPdlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETIPDLG_H
