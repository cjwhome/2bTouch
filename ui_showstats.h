/********************************************************************************
** Form generated from reading UI file 'showstats.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWSTATS_H
#define UI_SHOWSTATS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowStats
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ShowStats)
    {
        if (ShowStats->objectName().isEmpty())
            ShowStats->setObjectName(QStringLiteral("ShowStats"));
        ShowStats->resize(480, 277);
        centralwidget = new QWidget(ShowStats);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        ShowStats->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ShowStats);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 480, 25));
        ShowStats->setMenuBar(menubar);
        statusbar = new QStatusBar(ShowStats);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ShowStats->setStatusBar(statusbar);

        retranslateUi(ShowStats);

        QMetaObject::connectSlotsByName(ShowStats);
    } // setupUi

    void retranslateUi(QMainWindow *ShowStats)
    {
        ShowStats->setWindowTitle(QApplication::translate("ShowStats", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class ShowStats: public Ui_ShowStats {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWSTATS_H
