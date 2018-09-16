/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionParam;
    QAction *actionShapeModel;
    QAction *actionCam0;
    QWidget *centralWidget;
    QWidget *widget;
    QLabel *label_2;
    QTextBrowser *textBrowser;
    QGroupBox *groupBox;
    QPushButton *pushButton_Start;
    QPushButton *pushButton_Stop;
    QPushButton *pushButton_Connect;
    QPushButton *pushButton_TestItem;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_SaveRaw;
    QPushButton *pushButton_SaveCoordinate;
    QPushButton *pushButton_SaveResult;
    QPushButton *pushButton_ChangeLink;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 600);
        QFont font;
        font.setPointSize(12);
        MainWindow->setFont(font);
        actionParam = new QAction(MainWindow);
        actionParam->setObjectName(QStringLiteral("actionParam"));
        QFont font1;
        actionParam->setFont(font1);
        actionShapeModel = new QAction(MainWindow);
        actionShapeModel->setObjectName(QStringLiteral("actionShapeModel"));
        actionCam0 = new QAction(MainWindow);
        actionCam0->setObjectName(QStringLiteral("actionCam0"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 0, 700, 525));
        widget->setMinimumSize(QSize(0, 0));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setEnabled(true);
        label_2->setGeometry(QRect(730, 20, 286, 79));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(5);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFocusPolicy(Qt::NoFocus);
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAutoFillBackground(false);
        label_2->setTextFormat(Qt::PlainText);
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/AqLogo.PNG")));
        label_2->setScaledContents(true);
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(760, 390, 221, 131));
        textBrowser->setStyleSheet(QStringLiteral("font: 9pt \"Agency FB\";"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(760, 150, 211, 101));
        pushButton_Start = new QPushButton(groupBox);
        pushButton_Start->setObjectName(QStringLiteral("pushButton_Start"));
        pushButton_Start->setGeometry(QRect(10, 20, 81, 31));
        QFont font2;
        font2.setFamily(QStringLiteral("Agency FB"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        pushButton_Start->setFont(font2);
        pushButton_Start->setStyleSheet(QStringLiteral(""));
        pushButton_Stop = new QPushButton(groupBox);
        pushButton_Stop->setObjectName(QStringLiteral("pushButton_Stop"));
        pushButton_Stop->setEnabled(false);
        pushButton_Stop->setGeometry(QRect(120, 20, 81, 31));
        pushButton_Stop->setFont(font2);
        pushButton_Connect = new QPushButton(groupBox);
        pushButton_Connect->setObjectName(QStringLiteral("pushButton_Connect"));
        pushButton_Connect->setGeometry(QRect(120, 60, 81, 31));
        QFont font3;
        font3.setFamily(QStringLiteral("Aharoni"));
        font3.setBold(true);
        font3.setWeight(75);
        pushButton_Connect->setFont(font3);
        pushButton_TestItem = new QPushButton(groupBox);
        pushButton_TestItem->setObjectName(QStringLiteral("pushButton_TestItem"));
        pushButton_TestItem->setGeometry(QRect(10, 60, 81, 31));
        pushButton_TestItem->setFont(font3);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(760, 270, 211, 101));
        pushButton_SaveRaw = new QPushButton(groupBox_2);
        pushButton_SaveRaw->setObjectName(QStringLiteral("pushButton_SaveRaw"));
        pushButton_SaveRaw->setGeometry(QRect(10, 20, 81, 31));
        pushButton_SaveRaw->setFont(font3);
        pushButton_SaveCoordinate = new QPushButton(groupBox_2);
        pushButton_SaveCoordinate->setObjectName(QStringLiteral("pushButton_SaveCoordinate"));
        pushButton_SaveCoordinate->setGeometry(QRect(10, 60, 81, 31));
        pushButton_SaveCoordinate->setFont(font3);
        pushButton_SaveResult = new QPushButton(groupBox_2);
        pushButton_SaveResult->setObjectName(QStringLiteral("pushButton_SaveResult"));
        pushButton_SaveResult->setGeometry(QRect(120, 20, 81, 31));
        pushButton_SaveResult->setFont(font3);
        pushButton_ChangeLink = new QPushButton(groupBox_2);
        pushButton_ChangeLink->setObjectName(QStringLiteral("pushButton_ChangeLink"));
        pushButton_ChangeLink->setGeometry(QRect(120, 60, 81, 31));
        pushButton_ChangeLink->setFont(font3);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 27));
        menuBar->setFont(font);
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu->setGeometry(QRect(339, 123, 156, 106));
        menu->setFont(font);
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy1);
        QFont font4;
        font4.setPointSize(20);
        mainToolBar->setFont(font4);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionParam);
        menu->addAction(actionShapeModel);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionParam->setText(QApplication::translate("MainWindow", "Calibration", Q_NULLPTR));
        actionShapeModel->setText(QApplication::translate("MainWindow", "ShapeModel", Q_NULLPTR));
        actionCam0->setText(QApplication::translate("MainWindow", "Cam0", Q_NULLPTR));
        label_2->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "\346\216\247\345\210\266\351\200\211\351\241\271", Q_NULLPTR));
        pushButton_Start->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", Q_NULLPTR));
        pushButton_Stop->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242", Q_NULLPTR));
        pushButton_Connect->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245", Q_NULLPTR));
        pushButton_TestItem->setText(QApplication::translate("MainWindow", "\346\265\213\350\257\225", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\345\212\237\350\203\275\351\200\211\351\241\271", Q_NULLPTR));
        pushButton_SaveRaw->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\216\237\345\233\276", Q_NULLPTR));
        pushButton_SaveCoordinate->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\235\220\346\240\207", Q_NULLPTR));
        pushButton_SaveResult->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\347\273\223\346\236\234", Q_NULLPTR));
        pushButton_ChangeLink->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245\351\200\211\351\241\271", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\350\256\276\347\275\256\347\225\214\351\235\242", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
