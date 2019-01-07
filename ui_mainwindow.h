/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QListView *listView;
    QFrame *line;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *homeButton;
    QPushButton *settingsButton;
    QPushButton *graphButton;
    QPushButton *statsButton;
    QLabel *mainLabel;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(480, 277);
        MainWindow->setMinimumSize(QSize(480, 277));
        MainWindow->setMaximumSize(QSize(480, 277));
        listView = new QListView(MainWindow);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(10, 10, 161, 171));
        line = new QFrame(MainWindow);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 190, 461, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        horizontalLayoutWidget = new QWidget(MainWindow);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 200, 481, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        homeButton = new QPushButton(horizontalLayoutWidget);
        homeButton->setObjectName(QStringLiteral("homeButton"));
        homeButton->setMinimumSize(QSize(50, 50));
        homeButton->setMaximumSize(QSize(50, 50));
        homeButton->setIconSize(QSize(50, 50));

        horizontalLayout->addWidget(homeButton);

        settingsButton = new QPushButton(horizontalLayoutWidget);
        settingsButton->setObjectName(QStringLiteral("settingsButton"));
        settingsButton->setMinimumSize(QSize(50, 50));
        settingsButton->setMaximumSize(QSize(50, 50));

        horizontalLayout->addWidget(settingsButton);

        graphButton = new QPushButton(horizontalLayoutWidget);
        graphButton->setObjectName(QStringLiteral("graphButton"));
        graphButton->setMinimumSize(QSize(50, 50));
        graphButton->setMaximumSize(QSize(50, 50));

        horizontalLayout->addWidget(graphButton);

        statsButton = new QPushButton(horizontalLayoutWidget);
        statsButton->setObjectName(QStringLiteral("statsButton"));
        statsButton->setMinimumSize(QSize(50, 50));
        statsButton->setMaximumSize(QSize(50, 50));

        horizontalLayout->addWidget(statsButton);

        mainLabel = new QLabel(MainWindow);
        mainLabel->setObjectName(QStringLiteral("mainLabel"));
        mainLabel->setGeometry(QRect(180, 70, 251, 71));
        QFont font;
        font.setPointSize(20);
        mainLabel->setFont(font);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Form", 0));
        homeButton->setText(QString());
        settingsButton->setText(QString());
        graphButton->setText(QString());
        statsButton->setText(QString());
        mainLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
