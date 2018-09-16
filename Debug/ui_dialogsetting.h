/********************************************************************************
** Form generated from reading UI file 'dialogsetting.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSETTING_H
#define UI_DIALOGSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogSetting
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *TcpAddress;
    QLabel *label;
    QLineEdit *TcpServer;
    QLabel *label_2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_3;
    QLabel *label_28;
    QLineEdit *holdReg_8;
    QLineEdit *holdReg_0;
    QLineEdit *holdReg_9;
    QLabel *label_24;
    QLabel *label_9;
    QLabel *label_17;
    QLabel *label_19;
    QLabel *label_18;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_20;
    QLabel *address_lable;
    QLabel *label_27;
    QLineEdit *holdReg_1;
    QLineEdit *holdReg_3;
    QLineEdit *holdReg_2;
    QLineEdit *holdReg_5;
    QLineEdit *holdReg_4;
    QLineEdit *holdReg_6;
    QLineEdit *holdReg_7;
    QLabel *holdingRegisters_3;
    QPushButton *HeartBeatControl;
    QLabel *label_3;

    void setupUi(QDialog *DialogSetting)
    {
        if (DialogSetting->objectName().isEmpty())
            DialogSetting->setObjectName(QStringLiteral("DialogSetting"));
        DialogSetting->resize(319, 473);
        buttonBox = new QDialogButtonBox(DialogSetting);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(0, 430, 301, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        TcpAddress = new QLineEdit(DialogSetting);
        TcpAddress->setObjectName(QStringLiteral("TcpAddress"));
        TcpAddress->setGeometry(QRect(20, 30, 121, 21));
        label = new QLabel(DialogSetting);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 72, 15));
        TcpServer = new QLineEdit(DialogSetting);
        TcpServer->setObjectName(QStringLiteral("TcpServer"));
        TcpServer->setGeometry(QRect(20, 80, 121, 21));
        label_2 = new QLabel(DialogSetting);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 60, 91, 16));
        layoutWidget = new QWidget(DialogSetting);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 120, 281, 301));
        gridLayout_3 = new QGridLayout(layoutWidget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_28 = new QLabel(layoutWidget);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_28, 1, 0, 1, 1);

        holdReg_8 = new QLineEdit(layoutWidget);
        holdReg_8->setObjectName(QStringLiteral("holdReg_8"));
        holdReg_8->setStyleSheet(QStringLiteral("background-color: rgb(235, 235, 235);"));
        holdReg_8->setMaxLength(32767);

        gridLayout_3->addWidget(holdReg_8, 9, 1, 1, 1);

        holdReg_0 = new QLineEdit(layoutWidget);
        holdReg_0->setObjectName(QStringLiteral("holdReg_0"));
        holdReg_0->setMaxLength(32767);

        gridLayout_3->addWidget(holdReg_0, 1, 1, 1, 1);

        holdReg_9 = new QLineEdit(layoutWidget);
        holdReg_9->setObjectName(QStringLiteral("holdReg_9"));
        holdReg_9->setStyleSheet(QStringLiteral("background-color: rgb(235, 235, 235);"));
        holdReg_9->setMaxLength(32767);

        gridLayout_3->addWidget(holdReg_9, 10, 1, 1, 1);

        label_24 = new QLabel(layoutWidget);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_24, 3, 0, 1, 1);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_9, 5, 0, 1, 1);

        label_17 = new QLabel(layoutWidget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_17, 4, 0, 1, 1);

        label_19 = new QLabel(layoutWidget);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_19, 10, 0, 1, 1);

        label_18 = new QLabel(layoutWidget);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_18, 6, 0, 1, 1);

        label_25 = new QLabel(layoutWidget);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_25, 2, 0, 1, 1);

        label_26 = new QLabel(layoutWidget);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_26, 8, 0, 1, 1);

        label_20 = new QLabel(layoutWidget);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_20, 7, 0, 1, 1);

        address_lable = new QLabel(layoutWidget);
        address_lable->setObjectName(QStringLiteral("address_lable"));
        address_lable->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(address_lable, 0, 0, 1, 1);

        label_27 = new QLabel(layoutWidget);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_27, 9, 0, 1, 1);

        holdReg_1 = new QLineEdit(layoutWidget);
        holdReg_1->setObjectName(QStringLiteral("holdReg_1"));
        holdReg_1->setMaxLength(32767);

        gridLayout_3->addWidget(holdReg_1, 2, 1, 1, 1);

        holdReg_3 = new QLineEdit(layoutWidget);
        holdReg_3->setObjectName(QStringLiteral("holdReg_3"));
        holdReg_3->setMaxLength(32767);

        gridLayout_3->addWidget(holdReg_3, 4, 1, 1, 1);

        holdReg_2 = new QLineEdit(layoutWidget);
        holdReg_2->setObjectName(QStringLiteral("holdReg_2"));
        holdReg_2->setMaxLength(32767);

        gridLayout_3->addWidget(holdReg_2, 3, 1, 1, 1);

        holdReg_5 = new QLineEdit(layoutWidget);
        holdReg_5->setObjectName(QStringLiteral("holdReg_5"));
        holdReg_5->setStyleSheet(QStringLiteral("background-color: rgb(235, 235, 235);"));
        holdReg_5->setMaxLength(32767);

        gridLayout_3->addWidget(holdReg_5, 6, 1, 1, 1);

        holdReg_4 = new QLineEdit(layoutWidget);
        holdReg_4->setObjectName(QStringLiteral("holdReg_4"));
        holdReg_4->setMaxLength(32767);

        gridLayout_3->addWidget(holdReg_4, 5, 1, 1, 1);

        holdReg_6 = new QLineEdit(layoutWidget);
        holdReg_6->setObjectName(QStringLiteral("holdReg_6"));
        holdReg_6->setStyleSheet(QStringLiteral("background-color: rgb(235, 235, 235);"));
        holdReg_6->setMaxLength(32767);

        gridLayout_3->addWidget(holdReg_6, 7, 1, 1, 1);

        holdReg_7 = new QLineEdit(layoutWidget);
        holdReg_7->setObjectName(QStringLiteral("holdReg_7"));
        holdReg_7->setStyleSheet(QStringLiteral("background-color: rgb(235, 235, 235);"));
        holdReg_7->setMaxLength(32767);

        gridLayout_3->addWidget(holdReg_7, 8, 1, 1, 1);

        holdingRegisters_3 = new QLabel(layoutWidget);
        holdingRegisters_3->setObjectName(QStringLiteral("holdingRegisters_3"));
        holdingRegisters_3->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(holdingRegisters_3, 0, 1, 1, 1);

        HeartBeatControl = new QPushButton(DialogSetting);
        HeartBeatControl->setObjectName(QStringLiteral("HeartBeatControl"));
        HeartBeatControl->setGeometry(QRect(220, 80, 75, 21));
        label_3 = new QLabel(DialogSetting);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(220, 60, 91, 16));

        retranslateUi(DialogSetting);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogSetting, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogSetting, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogSetting);
    } // setupUi

    void retranslateUi(QDialog *DialogSetting)
    {
        DialogSetting->setWindowTitle(QApplication::translate("DialogSetting", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("DialogSetting", "IP\345\234\260\345\235\200\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogSetting", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232", Q_NULLPTR));
        label_28->setText(QApplication::translate("DialogSetting", "X\345\201\217\347\247\273\345\235\220\346\240\207", Q_NULLPTR));
        holdReg_8->setPlaceholderText(QApplication::translate("DialogSetting", "Hexadecimal A-F, a-f, 0-9.", Q_NULLPTR));
        holdReg_0->setPlaceholderText(QApplication::translate("DialogSetting", "Hexadecimal A-F, a-f, 0-9.", Q_NULLPTR));
        holdReg_9->setPlaceholderText(QApplication::translate("DialogSetting", "Hexadecimal A-F, a-f, 0-9.", Q_NULLPTR));
        label_24->setText(QApplication::translate("DialogSetting", "\346\213\215\347\205\247\345\256\214\346\210\220", Q_NULLPTR));
        label_9->setText(QApplication::translate("DialogSetting", "\345\244\207\347\224\250", Q_NULLPTR));
        label_17->setText(QApplication::translate("DialogSetting", "\345\277\203\350\267\263\344\277\241\345\217\267", Q_NULLPTR));
        label_19->setText(QApplication::translate("DialogSetting", "\345\244\207\347\224\250", Q_NULLPTR));
        label_18->setText(QApplication::translate("DialogSetting", "\346\211\271\345\244\264\345\217\267", Q_NULLPTR));
        label_25->setText(QApplication::translate("DialogSetting", "Y\345\201\217\347\247\273\345\235\220\346\240\207", Q_NULLPTR));
        label_26->setText(QApplication::translate("DialogSetting", "\346\213\215\347\205\247\344\275\277\350\203\275", Q_NULLPTR));
        label_20->setText(QApplication::translate("DialogSetting", "\350\236\272\344\270\235\345\217\267", Q_NULLPTR));
        address_lable->setText(QApplication::translate("DialogSetting", "Address", Q_NULLPTR));
        label_27->setText(QApplication::translate("DialogSetting", "\346\216\245\346\224\266\345\256\214\346\210\220", Q_NULLPTR));
        holdReg_1->setPlaceholderText(QApplication::translate("DialogSetting", "Hexadecimal A-F, a-f, 0-9.", Q_NULLPTR));
        holdReg_3->setPlaceholderText(QApplication::translate("DialogSetting", "Hexadecimal A-F, a-f, 0-9.", Q_NULLPTR));
        holdReg_2->setPlaceholderText(QApplication::translate("DialogSetting", "Hexadecimal A-F, a-f, 0-9.", Q_NULLPTR));
        holdReg_5->setPlaceholderText(QApplication::translate("DialogSetting", "Hexadecimal A-F, a-f, 0-9.", Q_NULLPTR));
        holdReg_4->setPlaceholderText(QApplication::translate("DialogSetting", "Hexadecimal A-F, a-f, 0-9.", Q_NULLPTR));
        holdReg_6->setPlaceholderText(QApplication::translate("DialogSetting", "Hexadecimal A-F, a-f, 0-9.", Q_NULLPTR));
        holdReg_7->setPlaceholderText(QApplication::translate("DialogSetting", "Hexadecimal A-F, a-f, 0-9.", Q_NULLPTR));
        holdingRegisters_3->setText(QApplication::translate("DialogSetting", "Holding Registers", Q_NULLPTR));
        HeartBeatControl->setText(QApplication::translate("DialogSetting", "Stop", Q_NULLPTR));
        label_3->setText(QApplication::translate("DialogSetting", "\345\277\203\350\267\263\346\216\247\345\210\266", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogSetting: public Ui_DialogSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSETTING_H
