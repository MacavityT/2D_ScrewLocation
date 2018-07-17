/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *widget;
    QPushButton *pushButtonSnapOne;
    QPushButton *pushButtonPicOne;
    QPushButton *pushButtonCalibra;
    QGroupBox *groupBox;
    QPushButton *pushButton_StdW;
    QTextEdit *textEdit_wStdx;
    QTextEdit *textEdit_wStdy;
    QPushButton *pushButton_Stdpix;
    QTextEdit *textEdit_pStdx;
    QTextEdit *textEdit_pStdy;
    QTextEdit *textEdit_ShangStdx;
    QTextEdit *textEdit_ShangStdy;
    QPushButton *pushButton_ShangStd;
    QGroupBox *groupBox_2;
    QPushButton *pushButton1_stdw;
    QTextEdit *textEdit1_wx;
    QTextEdit *textEdit1_wy;
    QPushButton *pushButton1_stdp;
    QTextEdit *textEdit1_px;
    QTextEdit *textEdit1_py;
    QGroupBox *groupBox_3;
    QPushButton *pushButton2_stdw;
    QTextEdit *textEdit2_wx;
    QTextEdit *textEdit2_wy;
    QPushButton *pushButton2_stdp;
    QTextEdit *textEdit2_px;
    QTextEdit *textEdit2_py;
    QGroupBox *groupBox_4;
    QPushButton *pushButton3_stdw;
    QTextEdit *textEdit3_wx;
    QTextEdit *textEdit3_wy;
    QPushButton *pushButton3_stdp;
    QTextEdit *textEdit3_px;
    QTextEdit *textEdit3_py;
    QGroupBox *groupBox_5;
    QPushButton *pushButton4_stdw;
    QTextEdit *textEdit4_wx;
    QTextEdit *textEdit4_wy;
    QPushButton *pushButton4_stdp;
    QTextEdit *textEdit4_px;
    QTextEdit *textEdit4_py;
    QTextEdit *textEdit_Data;
    QPushButton *pushButton_Test;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(1206, 676);
        widget = new QWidget(Dialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 741, 521));
        pushButtonSnapOne = new QPushButton(Dialog);
        pushButtonSnapOne->setObjectName(QStringLiteral("pushButtonSnapOne"));
        pushButtonSnapOne->setGeometry(QRect(840, 20, 111, 61));
        pushButtonPicOne = new QPushButton(Dialog);
        pushButtonPicOne->setObjectName(QStringLiteral("pushButtonPicOne"));
        pushButtonPicOne->setGeometry(QRect(1040, 20, 111, 61));
        pushButtonCalibra = new QPushButton(Dialog);
        pushButtonCalibra->setObjectName(QStringLiteral("pushButtonCalibra"));
        pushButtonCalibra->setGeometry(QRect(1020, 570, 111, 61));
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 560, 831, 91));
        pushButton_StdW = new QPushButton(groupBox);
        pushButton_StdW->setObjectName(QStringLiteral("pushButton_StdW"));
        pushButton_StdW->setGeometry(QRect(300, 30, 80, 30));
        textEdit_wStdx = new QTextEdit(groupBox);
        textEdit_wStdx->setObjectName(QStringLiteral("textEdit_wStdx"));
        textEdit_wStdx->setGeometry(QRect(390, 30, 81, 31));
        textEdit_wStdy = new QTextEdit(groupBox);
        textEdit_wStdy->setObjectName(QStringLiteral("textEdit_wStdy"));
        textEdit_wStdy->setGeometry(QRect(480, 30, 81, 31));
        pushButton_Stdpix = new QPushButton(groupBox);
        pushButton_Stdpix->setObjectName(QStringLiteral("pushButton_Stdpix"));
        pushButton_Stdpix->setEnabled(true);
        pushButton_Stdpix->setGeometry(QRect(570, 30, 80, 30));
        textEdit_pStdx = new QTextEdit(groupBox);
        textEdit_pStdx->setObjectName(QStringLiteral("textEdit_pStdx"));
        textEdit_pStdx->setGeometry(QRect(660, 30, 71, 31));
        textEdit_pStdy = new QTextEdit(groupBox);
        textEdit_pStdy->setObjectName(QStringLiteral("textEdit_pStdy"));
        textEdit_pStdy->setGeometry(QRect(740, 30, 71, 31));
        textEdit_ShangStdx = new QTextEdit(groupBox);
        textEdit_ShangStdx->setObjectName(QStringLiteral("textEdit_ShangStdx"));
        textEdit_ShangStdx->setGeometry(QRect(120, 30, 81, 31));
        textEdit_ShangStdy = new QTextEdit(groupBox);
        textEdit_ShangStdy->setObjectName(QStringLiteral("textEdit_ShangStdy"));
        textEdit_ShangStdy->setGeometry(QRect(210, 30, 81, 31));
        pushButton_ShangStd = new QPushButton(groupBox);
        pushButton_ShangStd->setObjectName(QStringLiteral("pushButton_ShangStd"));
        pushButton_ShangStd->setGeometry(QRect(30, 30, 80, 30));
        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(800, 90, 181, 151));
        pushButton1_stdw = new QPushButton(groupBox_2);
        pushButton1_stdw->setObjectName(QStringLiteral("pushButton1_stdw"));
        pushButton1_stdw->setGeometry(QRect(20, 30, 71, 31));
        textEdit1_wx = new QTextEdit(groupBox_2);
        textEdit1_wx->setObjectName(QStringLiteral("textEdit1_wx"));
        textEdit1_wx->setGeometry(QRect(20, 70, 71, 31));
        textEdit1_wy = new QTextEdit(groupBox_2);
        textEdit1_wy->setObjectName(QStringLiteral("textEdit1_wy"));
        textEdit1_wy->setGeometry(QRect(20, 110, 71, 31));
        pushButton1_stdp = new QPushButton(groupBox_2);
        pushButton1_stdp->setObjectName(QStringLiteral("pushButton1_stdp"));
        pushButton1_stdp->setGeometry(QRect(100, 30, 71, 31));
        textEdit1_px = new QTextEdit(groupBox_2);
        textEdit1_px->setObjectName(QStringLiteral("textEdit1_px"));
        textEdit1_px->setGeometry(QRect(100, 70, 71, 31));
        textEdit1_py = new QTextEdit(groupBox_2);
        textEdit1_py->setObjectName(QStringLiteral("textEdit1_py"));
        textEdit1_py->setGeometry(QRect(100, 110, 71, 31));
        groupBox_3 = new QGroupBox(Dialog);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(1000, 90, 181, 151));
        pushButton2_stdw = new QPushButton(groupBox_3);
        pushButton2_stdw->setObjectName(QStringLiteral("pushButton2_stdw"));
        pushButton2_stdw->setGeometry(QRect(20, 30, 71, 31));
        textEdit2_wx = new QTextEdit(groupBox_3);
        textEdit2_wx->setObjectName(QStringLiteral("textEdit2_wx"));
        textEdit2_wx->setGeometry(QRect(20, 70, 71, 31));
        textEdit2_wy = new QTextEdit(groupBox_3);
        textEdit2_wy->setObjectName(QStringLiteral("textEdit2_wy"));
        textEdit2_wy->setGeometry(QRect(20, 110, 71, 31));
        pushButton2_stdp = new QPushButton(groupBox_3);
        pushButton2_stdp->setObjectName(QStringLiteral("pushButton2_stdp"));
        pushButton2_stdp->setGeometry(QRect(100, 30, 71, 31));
        textEdit2_px = new QTextEdit(groupBox_3);
        textEdit2_px->setObjectName(QStringLiteral("textEdit2_px"));
        textEdit2_px->setGeometry(QRect(100, 70, 71, 31));
        textEdit2_py = new QTextEdit(groupBox_3);
        textEdit2_py->setObjectName(QStringLiteral("textEdit2_py"));
        textEdit2_py->setGeometry(QRect(100, 110, 71, 31));
        groupBox_4 = new QGroupBox(Dialog);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(800, 270, 181, 151));
        pushButton3_stdw = new QPushButton(groupBox_4);
        pushButton3_stdw->setObjectName(QStringLiteral("pushButton3_stdw"));
        pushButton3_stdw->setGeometry(QRect(20, 30, 71, 31));
        textEdit3_wx = new QTextEdit(groupBox_4);
        textEdit3_wx->setObjectName(QStringLiteral("textEdit3_wx"));
        textEdit3_wx->setGeometry(QRect(20, 70, 71, 31));
        textEdit3_wy = new QTextEdit(groupBox_4);
        textEdit3_wy->setObjectName(QStringLiteral("textEdit3_wy"));
        textEdit3_wy->setGeometry(QRect(20, 110, 71, 31));
        pushButton3_stdp = new QPushButton(groupBox_4);
        pushButton3_stdp->setObjectName(QStringLiteral("pushButton3_stdp"));
        pushButton3_stdp->setGeometry(QRect(100, 30, 71, 31));
        textEdit3_px = new QTextEdit(groupBox_4);
        textEdit3_px->setObjectName(QStringLiteral("textEdit3_px"));
        textEdit3_px->setGeometry(QRect(100, 70, 71, 31));
        textEdit3_py = new QTextEdit(groupBox_4);
        textEdit3_py->setObjectName(QStringLiteral("textEdit3_py"));
        textEdit3_py->setGeometry(QRect(100, 110, 71, 31));
        groupBox_5 = new QGroupBox(Dialog);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(1000, 270, 181, 151));
        pushButton4_stdw = new QPushButton(groupBox_5);
        pushButton4_stdw->setObjectName(QStringLiteral("pushButton4_stdw"));
        pushButton4_stdw->setGeometry(QRect(20, 30, 71, 31));
        textEdit4_wx = new QTextEdit(groupBox_5);
        textEdit4_wx->setObjectName(QStringLiteral("textEdit4_wx"));
        textEdit4_wx->setGeometry(QRect(20, 70, 71, 31));
        textEdit4_wy = new QTextEdit(groupBox_5);
        textEdit4_wy->setObjectName(QStringLiteral("textEdit4_wy"));
        textEdit4_wy->setGeometry(QRect(20, 110, 71, 31));
        pushButton4_stdp = new QPushButton(groupBox_5);
        pushButton4_stdp->setObjectName(QStringLiteral("pushButton4_stdp"));
        pushButton4_stdp->setGeometry(QRect(100, 30, 71, 31));
        textEdit4_px = new QTextEdit(groupBox_5);
        textEdit4_px->setObjectName(QStringLiteral("textEdit4_px"));
        textEdit4_px->setGeometry(QRect(100, 70, 71, 31));
        textEdit4_py = new QTextEdit(groupBox_5);
        textEdit4_py->setObjectName(QStringLiteral("textEdit4_py"));
        textEdit4_py->setGeometry(QRect(100, 110, 71, 31));
        textEdit_Data = new QTextEdit(Dialog);
        textEdit_Data->setObjectName(QStringLiteral("textEdit_Data"));
        textEdit_Data->setGeometry(QRect(800, 440, 381, 101));
        pushButton_Test = new QPushButton(Dialog);
        pushButton_Test->setObjectName(QStringLiteral("pushButton_Test"));
        pushButton_Test->setGeometry(QRect(900, 570, 111, 61));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
        pushButtonSnapOne->setText(QApplication::translate("Dialog", "\346\213\215\347\205\247", Q_NULLPTR));
        pushButtonPicOne->setText(QApplication::translate("Dialog", "\345\212\240\350\275\275\345\233\276\347\211\207", Q_NULLPTR));
        pushButtonCalibra->setText(QApplication::translate("Dialog", "\346\240\207\345\256\232", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Dialog", "\345\237\272\345\207\206\347\202\271", Q_NULLPTR));
        pushButton_StdW->setText(QApplication::translate("Dialog", "\347\211\251\347\220\206\344\275\215\347\275\256", Q_NULLPTR));
        pushButton_Stdpix->setText(QApplication::translate("Dialog", "\345\233\276\345\203\217\344\275\215\347\275\256", Q_NULLPTR));
        pushButton_ShangStd->setText(QApplication::translate("Dialog", "\350\236\272\344\270\235\344\275\215\347\275\256", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Dialog", "\347\202\2711", Q_NULLPTR));
        pushButton1_stdw->setText(QApplication::translate("Dialog", "\350\216\267\345\217\226\347\211\251\347\220\206\344\275\215\347\275\256", Q_NULLPTR));
        pushButton1_stdp->setText(QApplication::translate("Dialog", "\350\216\267\345\217\226\345\233\276\345\203\217\344\275\215\347\275\256", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("Dialog", "\347\202\2712", Q_NULLPTR));
        pushButton2_stdw->setText(QApplication::translate("Dialog", "\350\216\267\345\217\226\347\211\251\347\220\206\344\275\215\347\275\256", Q_NULLPTR));
        pushButton2_stdp->setText(QApplication::translate("Dialog", "\350\216\267\345\217\226\345\233\276\345\203\217\344\275\215\347\275\256", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("Dialog", "\347\202\2713", Q_NULLPTR));
        pushButton3_stdw->setText(QApplication::translate("Dialog", "\350\216\267\345\217\226\347\211\251\347\220\206\344\275\215\347\275\256", Q_NULLPTR));
        pushButton3_stdp->setText(QApplication::translate("Dialog", "\350\216\267\345\217\226\345\233\276\345\203\217\344\275\215\347\275\256", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("Dialog", "\347\202\2714", Q_NULLPTR));
        pushButton4_stdw->setText(QApplication::translate("Dialog", "\350\216\267\345\217\226\347\211\251\347\220\206\344\275\215\347\275\256", Q_NULLPTR));
        pushButton4_stdp->setText(QApplication::translate("Dialog", "\350\216\267\345\217\226\345\233\276\345\203\217\344\275\215\347\275\256", Q_NULLPTR));
        pushButton_Test->setText(QApplication::translate("Dialog", "test", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
