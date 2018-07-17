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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QPushButton *pushButtonCreateShapeModel;
    QLabel *label;
    QListView *listView;
    QPushButton *pushButton_delete;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_name;
    QPushButton *pushButton_name;
    QLabel *label_2;
    QComboBox *combo_ShangStd;
    QComboBox *combo_Type;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QDialog *DialogShapeModel)
    {
        if (DialogShapeModel->objectName().isEmpty())
            DialogShapeModel->setObjectName(QStringLiteral("DialogShapeModel"));
        DialogShapeModel->resize(941, 528);
        QFont font;
        font.setPointSize(9);
        DialogShapeModel->setFont(font);
        widget = new QWidget(DialogShapeModel);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 10, 631, 441));
        pushButtonSnapOne = new QPushButton(DialogShapeModel);
        pushButtonSnapOne->setObjectName(QStringLiteral("pushButtonSnapOne"));
        pushButtonSnapOne->setGeometry(QRect(670, 10, 111, 61));
        pushButtonPicOne = new QPushButton(DialogShapeModel);
        pushButtonPicOne->setObjectName(QStringLiteral("pushButtonPicOne"));
        pushButtonPicOne->setGeometry(QRect(800, 10, 111, 61));
        pushButtonCreateShapeModel = new QPushButton(DialogShapeModel);
        pushButtonCreateShapeModel->setObjectName(QStringLiteral("pushButtonCreateShapeModel"));
        pushButtonCreateShapeModel->setGeometry(QRect(670, 90, 111, 61));
        label = new QLabel(DialogShapeModel);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(670, 250, 161, 31));
        listView = new QListView(DialogShapeModel);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setEnabled(true);
        listView->setGeometry(QRect(670, 281, 241, 171));
        pushButton_delete = new QPushButton(DialogShapeModel);
        pushButton_delete->setObjectName(QStringLiteral("pushButton_delete"));
        pushButton_delete->setEnabled(false);
        pushButton_delete->setGeometry(QRect(670, 470, 93, 28));
        pushButton_2 = new QPushButton(DialogShapeModel);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(820, 470, 93, 28));
        lineEdit_name = new QLineEdit(DialogShapeModel);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(670, 190, 241, 21));
        pushButton_name = new QPushButton(DialogShapeModel);
        pushButton_name->setObjectName(QStringLiteral("pushButton_name"));
        pushButton_name->setGeometry(QRect(820, 230, 93, 28));
        label_2 = new QLabel(DialogShapeModel);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(670, 170, 91, 16));
        combo_ShangStd = new QComboBox(DialogShapeModel);
        combo_ShangStd->setObjectName(QStringLiteral("combo_ShangStd"));
        combo_ShangStd->setGeometry(QRect(830, 90, 80, 30));
        combo_Type = new QComboBox(DialogShapeModel);
        combo_Type->setObjectName(QStringLiteral("combo_Type"));
        combo_Type->setGeometry(QRect(830, 120, 80, 30));
        label_3 = new QLabel(DialogShapeModel);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(790, 90, 41, 31));
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(DialogShapeModel);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(790, 120, 41, 31));
        label_4->setAlignment(Qt::AlignCenter);

        retranslateUi(DialogShapeModel);

        QMetaObject::connectSlotsByName(DialogShapeModel);
    } // setupUi

    void retranslateUi(QDialog *DialogShapeModel)
    {
        DialogShapeModel->setWindowTitle(QApplication::translate("DialogShapeModel", "Dialog", Q_NULLPTR));
        pushButtonSnapOne->setText(QApplication::translate("DialogShapeModel", "\351\207\207\351\233\206\345\233\276\347\211\207", Q_NULLPTR));
        pushButtonPicOne->setText(QApplication::translate("DialogShapeModel", "\345\212\240\350\275\275\345\233\276\347\211\207", Q_NULLPTR));
        pushButtonCreateShapeModel->setText(QApplication::translate("DialogShapeModel", "\345\210\233\345\273\272\346\250\241\346\235\277", Q_NULLPTR));
        label->setText(QApplication::translate("DialogShapeModel", "\345\267\262\345\255\230\345\234\250\347\232\204\346\250\241\346\235\277:", Q_NULLPTR));
        pushButton_delete->setText(QApplication::translate("DialogShapeModel", "\345\210\240\351\231\244", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("DialogShapeModel", "\346\265\213\350\257\225", Q_NULLPTR));
        pushButton_name->setText(QApplication::translate("DialogShapeModel", "\345\221\275\345\220\215", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogShapeModel", "\346\226\260\346\250\241\346\235\277\345\221\275\345\220\215:", Q_NULLPTR));
        combo_ShangStd->clear();
        combo_ShangStd->insertItems(0, QStringList()
         << QApplication::translate("DialogShapeModel", "\350\257\267\351\200\211\346\213\251", Q_NULLPTR)
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
        combo_Type->clear();
        combo_Type->insertItems(0, QStringList()
         << QApplication::translate("DialogShapeModel", "\350\257\267\351\200\211\346\213\251", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "1", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "2", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "3", Q_NULLPTR)
         << QApplication::translate("DialogShapeModel", "4", Q_NULLPTR)
        );
        label_3->setText(QApplication::translate("DialogShapeModel", "\347\274\226\345\217\267", Q_NULLPTR));
        label_4->setText(QApplication::translate("DialogShapeModel", "\347\261\273\345\236\213", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogShapeModel: public Ui_DialogShapeModel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSHAPEMODEL_H
