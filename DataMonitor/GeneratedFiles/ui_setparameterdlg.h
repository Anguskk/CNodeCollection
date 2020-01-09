/********************************************************************************
** Form generated from reading UI file 'setparameterdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETPARAMETERDLG_H
#define UI_SETPARAMETERDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CSetParameterdlg
{
public:
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox;
    QTimeEdit *timeEdit;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox_2;
    QTimeEdit *timeEdit_2;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBox_3;
    QTimeEdit *timeEdit_3;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBox_4;
    QTimeEdit *timeEdit_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_4;
    QLabel *label;
    QLineEdit *lineEdit_4;
    QLabel *label_6;
    QLabel *label_2;
    QLineEdit *lineEdit_5;
    QLabel *label_7;
    QLabel *label_3;
    QLineEdit *lineEdit_6;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *okPushButton;
    QPushButton *cancelPushButton;

    void setupUi(QWidget *CSetParameterdlg)
    {
        if (CSetParameterdlg->objectName().isEmpty())
            CSetParameterdlg->setObjectName(QString::fromUtf8("CSetParameterdlg"));
        CSetParameterdlg->resize(279, 320);
        gridLayout_3 = new QGridLayout(CSetParameterdlg);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox = new QGroupBox(CSetParameterdlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy);
        checkBox->setChecked(true);

        horizontalLayout_2->addWidget(checkBox);

        timeEdit = new QTimeEdit(groupBox);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setCurrentSection(QDateTimeEdit::HourSection);

        horizontalLayout_2->addWidget(timeEdit);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        checkBox_2 = new QCheckBox(groupBox);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        sizePolicy.setHeightForWidth(checkBox_2->sizePolicy().hasHeightForWidth());
        checkBox_2->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(checkBox_2);

        timeEdit_2 = new QTimeEdit(groupBox);
        timeEdit_2->setObjectName(QString::fromUtf8("timeEdit_2"));
        timeEdit_2->setCurrentSection(QDateTimeEdit::HourSection);
        timeEdit_2->setTime(QTime(6, 0, 0));

        horizontalLayout_3->addWidget(timeEdit_2);


        gridLayout_2->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        checkBox_3 = new QCheckBox(groupBox);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        sizePolicy.setHeightForWidth(checkBox_3->sizePolicy().hasHeightForWidth());
        checkBox_3->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(checkBox_3);

        timeEdit_3 = new QTimeEdit(groupBox);
        timeEdit_3->setObjectName(QString::fromUtf8("timeEdit_3"));
        timeEdit_3->setCurrentSection(QDateTimeEdit::HourSection);
        timeEdit_3->setTime(QTime(12, 0, 0));

        horizontalLayout_4->addWidget(timeEdit_3);


        gridLayout_2->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        checkBox_4 = new QCheckBox(groupBox);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        sizePolicy.setHeightForWidth(checkBox_4->sizePolicy().hasHeightForWidth());
        checkBox_4->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(checkBox_4);

        timeEdit_4 = new QTimeEdit(groupBox);
        timeEdit_4->setObjectName(QString::fromUtf8("timeEdit_4"));
        timeEdit_4->setCurrentSection(QDateTimeEdit::HourSection);
        timeEdit_4->setTime(QTime(18, 0, 0));

        horizontalLayout_5->addWidget(timeEdit_4);


        gridLayout_2->addLayout(horizontalLayout_5, 3, 0, 1, 1);


        verticalLayout_4->addWidget(groupBox);

        groupBox_2 = new QGroupBox(CSetParameterdlg);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        lineEdit_4 = new QLineEdit(groupBox_2);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setEnabled(false);
        lineEdit_4->setReadOnly(true);

        gridLayout_4->addWidget(lineEdit_4, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_4->addWidget(label_6, 0, 2, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_5 = new QLineEdit(groupBox_2);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setEnabled(false);
        lineEdit_5->setReadOnly(true);

        gridLayout_4->addWidget(lineEdit_5, 1, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_4->addWidget(label_7, 1, 2, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_6 = new QLineEdit(groupBox_2);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setEnabled(false);
        lineEdit_6->setReadOnly(true);

        gridLayout_4->addWidget(lineEdit_6, 2, 1, 1, 1);


        gridLayout->addLayout(gridLayout_4, 0, 1, 1, 1);


        verticalLayout_4->addWidget(groupBox_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame = new QFrame(CSetParameterdlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout_3->addWidget(frame);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        okPushButton = new QPushButton(CSetParameterdlg);
        okPushButton->setObjectName(QString::fromUtf8("okPushButton"));

        horizontalLayout_6->addWidget(okPushButton);

        cancelPushButton = new QPushButton(CSetParameterdlg);
        cancelPushButton->setObjectName(QString::fromUtf8("cancelPushButton"));

        horizontalLayout_6->addWidget(cancelPushButton);


        verticalLayout_3->addLayout(horizontalLayout_6);


        verticalLayout_4->addLayout(verticalLayout_3);


        gridLayout_3->addLayout(verticalLayout_4, 0, 0, 1, 1);


        retranslateUi(CSetParameterdlg);

        QMetaObject::connectSlotsByName(CSetParameterdlg);
    } // setupUi

    void retranslateUi(QWidget *CSetParameterdlg)
    {
        CSetParameterdlg->setWindowTitle(QApplication::translate("CSetParameterdlg", "Setting Parameters", nullptr));
        groupBox->setTitle(QApplication::translate("CSetParameterdlg", "Daily test set", nullptr));
        checkBox->setText(QString());
        timeEdit->setDisplayFormat(QApplication::translate("CSetParameterdlg", "HH:mm:ss", nullptr));
        checkBox_2->setText(QString());
        timeEdit_2->setDisplayFormat(QApplication::translate("CSetParameterdlg", "HH:mm:ss", nullptr));
        checkBox_3->setText(QString());
        timeEdit_3->setDisplayFormat(QApplication::translate("CSetParameterdlg", "HH:mm:ss", nullptr));
        checkBox_4->setText(QString());
        timeEdit_4->setDisplayFormat(QApplication::translate("CSetParameterdlg", "HH:mm:ss", nullptr));
        groupBox_2->setTitle(QApplication::translate("CSetParameterdlg", "Parameter display", nullptr));
        label->setText(QApplication::translate("CSetParameterdlg", "Sampling: ", nullptr));
        lineEdit_4->setText(QApplication::translate("CSetParameterdlg", "1", nullptr));
        label_6->setText(QApplication::translate("CSetParameterdlg", "ms", nullptr));
        label_2->setText(QApplication::translate("CSetParameterdlg", "Gain:", nullptr));
        lineEdit_5->setText(QApplication::translate("CSetParameterdlg", "0", nullptr));
        label_7->setText(QApplication::translate("CSetParameterdlg", "dB", nullptr));
        label_3->setText(QApplication::translate("CSetParameterdlg", "Filter type:", nullptr));
        lineEdit_6->setText(QApplication::translate("CSetParameterdlg", "Linear", nullptr));
        okPushButton->setText(QApplication::translate("CSetParameterdlg", "OK", nullptr));
        cancelPushButton->setText(QApplication::translate("CSetParameterdlg", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CSetParameterdlg: public Ui_CSetParameterdlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETPARAMETERDLG_H
