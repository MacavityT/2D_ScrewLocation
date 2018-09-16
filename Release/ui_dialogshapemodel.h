/********************************************************************************
** Form generated from reading UI file 'dialogshapemodel.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSHAPEMODEL_H
#define UI_DIALOGSHAPEMODEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogShapeModel
{
public:
    QWidget *widget;
    QPushButton *pushButtonSnapOne;
    QPushButton *pushButtonPicOne;
    QLabel *label;
    QListView *listView;
    QPushButton *pushButton_delete;
    QPushButton *pushButton_Test;
    QGroupBox *groupBox;
    QComboBox *combo_Type;
    QPushButton *pushButton_confirm;
    QComboBox *combo_ShangStd;
    QPushButton *pushButtonCreateShapeModel;
    QComboBox *combo_Score;
    QPushButton *pushButtonSaveOne;
    QPushButton *pushButtonPicContinue;
    QPushButton *pushButtonShowRegion;
    QPushButton *pushButtonDetectRegion;
    QPushButton *pushButtonShowCross;
    QPushButton *pushButtonClearWindow;
    QButtonGroup *ViewControl;

    void setupUi(QDialog *DialogShapeModel)
    {
        if (DialogShapeModel->objectName().isEmpty())
            DialogShapeModel->setObjectName(QStringLiteral("DialogShapeModel"));
        DialogShapeModel->resize(1024, 600);
        QFont font;
        font.setPointSize(9);
        DialogShapeModel->setFont(font);
        widget = new QWidget(DialogShapeModel);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 10, 640, 480));
        pushButtonSnapOne = new QPushButton(DialogShapeModel);
        ViewControl = new QButtonGroup(DialogShapeModel);
        ViewControl->setObjectName(QStringLiteral("ViewControl"));
        ViewControl->addButton(pushButtonSnapOne);
        pushButtonSnapOne->setObjectName(QStringLiteral("pushButtonSnapOne"));
        pushButtonSnapOne->setGeometry(QRect(880, 40, 80, 30));
        pushButtonPicOne = new QPushButton(DialogShapeModel);
        ViewControl->addButton(pushButtonPicOne);
        pushButtonPicOne->setObjectName(QStringLiteral("pushButtonPicOne"));
        pushButtonPicOne->setGeometry(QRect(880, 190, 80, 30));
        label = new QLabel(DialogShapeModel);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(730, 250, 231, 31));
        listView = new QListView(DialogShapeModel);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setEnabled(true);
        listView->setGeometry(QRect(730, 281, 241, 171));
        pushButton_delete = new QPushButton(DialogShapeModel);
        pushButton_delete->setObjectName(QStringLiteral("pushButton_delete"));
        pushButton_delete->setEnabled(false);
        pushButton_delete->setGeometry(QRect(740, 470, 80, 30));
        pushButton_Test = new QPushButton(DialogShapeModel);
        pushButton_Test->setObjectName(QStringLiteral("pushButton_Test"));
        pushButton_Test->setEnabled(false);
        pushButton_Test->setGeometry(QRect(880, 470, 80, 30));
        groupBox = new QGroupBox(DialogShapeModel);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(60, 510, 581, 71));
        combo_Type = new QComboBox(groupBox);
        combo_Type->setObjectName(QStringLiteral("combo_Type"));
        combo_Type->setGeometry(QRect(30, 20, 80, 30));
        combo_Type->setStyleSheet(QLatin1String("background-color:rgb(225,225,225);\n"
"border-radius:10px;"));
        pushButton_confirm = new QPushButton(groupBox);
        pushButton_confirm->setObjectName(QStringLiteral("pushButton_confirm"));
        pushButton_confirm->setGeometry(QRect(370, 20, 80, 30));
        pushButton_confirm->setStyleSheet(QLatin1String("background-color:rgb(225,225,225);\n"
"border-radius:10px;"));
        combo_ShangStd = new QComboBox(groupBox);
        combo_ShangStd->setObjectName(QStringLiteral("combo_ShangStd"));
        combo_ShangStd->setGeometry(QRect(130, 20, 80, 30));
        combo_ShangStd->setLayoutDirection(Qt::LeftToRight);
        combo_ShangStd->setStyleSheet(QLatin1String("background-color:rgb(225,225,225);\n"
"border-radius:10px;"));
        pushButtonCreateShapeModel = new QPushButton(groupBox);
        pushButtonCreateShapeModel->setObjectName(QStringLiteral("pushButtonCreateShapeModel"));
        pushButtonCreateShapeModel->setGeometry(QRect(470, 20, 80, 30));
        pushButtonCreateShapeModel->setStyleSheet(QLatin1String("background-color:rgb(225,225,225);\n"
"border-radius:10px;"));
        combo_Score = new QComboBox(groupBox);
        combo_Score->setObjectName(QStringLiteral("combo_Score"));
        combo_Score->setGeometry(QRect(230, 20, 121, 30));
        combo_Score->setLayoutDirection(Qt::LeftToRight);
        combo_Score->setStyleSheet(QLatin1String("background-color:rgb(225,225,225);\n"
"border-radius:10px;"));
        pushButtonSaveOne = new QPushButton(DialogShapeModel);
        ViewControl->addButton(pushButtonSaveOne);
        pushButtonSaveOne->setObjectName(QStringLiteral("pushButtonSaveOne"));
        pushButtonSaveOne->setGeometry(QRect(740, 190, 80, 30));
        pushButtonPicContinue = new QPushButton(DialogShapeModel);
        ViewControl->addButton(pushButtonPicContinue);
        pushButtonPicContinue->setObjectName(QStringLiteral("pushButtonPicContinue"));
        pushButtonPicContinue->setGeometry(QRect(740, 40, 80, 30));
        pushButtonShowRegion = new QPushButton(DialogShapeModel);
        pushButtonShowRegion->setObjectName(QStringLiteral("pushButtonShowRegion"));
        pushButtonShowRegion->setGeometry(QRect(880, 90, 80, 30));
        pushButtonDetectRegion = new QPushButton(DialogShapeModel);
        pushButtonDetectRegion->setObjectName(QStringLiteral("pushButtonDetectRegion"));
        pushButtonDetectRegion->setGeometry(QRect(740, 90, 80, 30));
        pushButtonShowCross = new QPushButton(DialogShapeModel);
        pushButtonShowCross->setObjectName(QStringLiteral("pushButtonShowCross"));
        pushButtonShowCross->setGeometry(QRect(740, 140, 80, 30));
        pushButtonClearWindow = new QPushButton(DialogShapeModel);
        pushButtonClearWindow->setObjectName(QStringLiteral("pushButtonClearWindow"));
        pushButtonClearWindow->setGeometry(QRect(880, 140, 80, 30));

        retranslateUi(DialogShapeModel);

        QMetaObject::connectSlotsByName(DialogShapeModel);
    } // setupUi

    void retranslateUi(QDialog *DialogShapeModel)
    {
        DialogShapeModel->setWindowTitle(QApplication::translate("DialogShapeModel", "Dialog", Q_NULLPTR));
        pushButtonSnapOne->setText(QApplication::translate("DialogShapeModel", "\345\215\225\345\270\247\351\207\207\345\233\276", Q_NULLPTR));
        pushButtonPicOne->setText(QApplication::translate("DialogShapeModel", "\345\212\240\350\275\275\345\233\276\347\211\207", Q_NULLPTR));
        label->setText(QApplication::translate("DialogShapeModel", "\346\250\241\346\235\277\345\210\227\350\241\250\357\274\210\345\217\214\345\207\273\346\237\245\347\234\213\345\233\276\347\211\207\357\274\211:", Q_NULLPTR));
        pushButton_delete->setText(QApplication::translate("DialogShapeModel", "\345\210\240\351\231\244", Q_NULLPTR));
        pushButton_Test->setText(QApplication::translate("DialogShapeModel", "\346\265\213\350\257\225", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("DialogShapeModel", "\351\200\211\346\213\251\346\211\271\345\244\264\345\217\212\345\257\271\345\272\224\350\236\272\344\270\235\347\274\226\345\217\267", Q_NULLPTR));
        combo_Type->clear();
        combo_Type->insertItems(0, QStringList()
         << QApplication::translate("DialogShapeModel", "\346\211\271\345\244\264\347\274\226\345\217\267", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "1", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "2", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "3", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "4", Q_NULLPTR)
        );
        pushButton_confirm->setText(QApplication::translate("DialogShapeModel", "\345\210\233\345\273\272\346\250\241\346\235\277", Q_NULLPTR));
        combo_ShangStd->clear();
        combo_ShangStd->insertItems(0, QStringList()
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\235\347\274\226\345\217\267", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\2351", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\2352", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\2353", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\2354", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\2355", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\2356", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\2357", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\2358", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\2359", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23510", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23511", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23512", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23513", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23514", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23515", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23516", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23517", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23518", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23519", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23520", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23521", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23522", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23523", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23524", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23525", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23526", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23527", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23528", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23529", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "\350\236\272\344\270\23530", Q_NULLPTR)
        );
        pushButtonCreateShapeModel->setText(QApplication::translate("DialogShapeModel", "\344\277\235\345\255\230\346\250\241\346\235\277", Q_NULLPTR));
        combo_Score->clear();
        combo_Score->insertItems(0, QStringList()
         << QApplication::translate("DialogShapeModel", "\347\233\270\344\274\274\345\272\246(\351\273\230\350\256\2440.5)", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "0.1", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "0.2", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "0.3", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "0.4", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "0.5", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "0.6", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "0.7", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "0.8", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "0.9", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "1.0", Q_NULLPTR)
        );
        pushButtonSaveOne->setText(QApplication::translate("DialogShapeModel", "\344\277\235\345\255\230\345\233\276\347\211\207", Q_NULLPTR));
        pushButtonPicContinue->setText(QApplication::translate("DialogShapeModel", "\350\277\236\347\273\255\351\207\207\345\233\276", Q_NULLPTR));
        pushButtonShowRegion->setText(QApplication::translate("DialogShapeModel", "\346\230\276\347\244\272\345\214\272\345\237\237", Q_NULLPTR));
        pushButtonDetectRegion->setText(QApplication::translate("DialogShapeModel", "\345\210\233\345\273\272\345\214\272\345\237\237", Q_NULLPTR));
        pushButtonShowCross->setText(QApplication::translate("DialogShapeModel", "\346\230\276\347\244\272\345\207\206\345\277\203", Q_NULLPTR));
        pushButtonClearWindow->setText(QApplication::translate("DialogShapeModel", "\346\270\205\347\251\272\347\252\227\345\217\243", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogShapeModel: public Ui_DialogShapeModel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSHAPEMODEL_H
