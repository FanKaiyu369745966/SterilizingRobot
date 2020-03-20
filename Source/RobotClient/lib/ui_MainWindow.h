/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QPushButton *pushButtonUp;
    QPushButton *pushButtonDown;
    QPushButton *pushButtonLeft;
    QPushButton *pushButtonRight;
    QPushButton *pushButtonSetPoint;
    QPushButton *pushButtonGoPoint;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 781, 421));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonUp = new QPushButton(centralwidget);
        pushButtonUp->setObjectName(QString::fromUtf8("pushButtonUp"));
        pushButtonUp->setGeometry(QRect(360, 450, 61, 31));
        pushButtonDown = new QPushButton(centralwidget);
        pushButtonDown->setObjectName(QString::fromUtf8("pushButtonDown"));
        pushButtonDown->setGeometry(QRect(360, 500, 61, 31));
        pushButtonLeft = new QPushButton(centralwidget);
        pushButtonLeft->setObjectName(QString::fromUtf8("pushButtonLeft"));
        pushButtonLeft->setGeometry(QRect(290, 470, 61, 31));
        pushButtonRight = new QPushButton(centralwidget);
        pushButtonRight->setObjectName(QString::fromUtf8("pushButtonRight"));
        pushButtonRight->setGeometry(QRect(430, 470, 61, 31));
        pushButtonSetPoint = new QPushButton(centralwidget);
        pushButtonSetPoint->setObjectName(QString::fromUtf8("pushButtonSetPoint"));
        pushButtonSetPoint->setGeometry(QRect(110, 480, 89, 25));
        pushButtonGoPoint = new QPushButton(centralwidget);
        pushButtonGoPoint->setObjectName(QString::fromUtf8("pushButtonGoPoint"));
        pushButtonGoPoint->setGeometry(QRect(110, 510, 89, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 28));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonUp->setText(QApplication::translate("MainWindow", "\344\270\212", nullptr));
        pushButtonDown->setText(QApplication::translate("MainWindow", "\344\270\213", nullptr));
        pushButtonLeft->setText(QApplication::translate("MainWindow", "\345\267\246", nullptr));
        pushButtonRight->setText(QApplication::translate("MainWindow", "\345\217\263", nullptr));
        pushButtonSetPoint->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\351\242\204\350\256\276\347\202\271", nullptr));
        pushButtonGoPoint->setText(QApplication::translate("MainWindow", "\345\216\273\351\242\204\350\256\276\347\202\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
