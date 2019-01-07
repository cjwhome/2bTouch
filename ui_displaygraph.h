/********************************************************************************
** Form generated from reading UI file 'displaygraph.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYGRAPH_H
#define UI_DISPLAYGRAPH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DisplayGraph
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *homeButton;
    QPushButton *zOut;
    QPushButton *zIn;
    QPushButton *selectGas_2;
    QPushButton *settings;
    QFrame *line;
    QWidget *placeHolder;

    void setupUi(QWidget *DisplayGraph)
    {
        if (DisplayGraph->objectName().isEmpty())
            DisplayGraph->setObjectName(QStringLiteral("DisplayGraph"));
        DisplayGraph->resize(480, 277);
        DisplayGraph->setMinimumSize(QSize(480, 277));
        DisplayGraph->setMaximumSize(QSize(480, 277));
        horizontalLayoutWidget = new QWidget(DisplayGraph);
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

        zOut = new QPushButton(horizontalLayoutWidget);
        zOut->setObjectName(QStringLiteral("zOut"));
        zOut->setMinimumSize(QSize(50, 50));
        zOut->setMaximumSize(QSize(50, 50));

        horizontalLayout->addWidget(zOut);

        zIn = new QPushButton(horizontalLayoutWidget);
        zIn->setObjectName(QStringLiteral("zIn"));
        zIn->setMinimumSize(QSize(50, 50));
        zIn->setMaximumSize(QSize(50, 50));

        horizontalLayout->addWidget(zIn);

        selectGas_2 = new QPushButton(horizontalLayoutWidget);
        selectGas_2->setObjectName(QStringLiteral("selectGas_2"));
        selectGas_2->setMinimumSize(QSize(50, 50));
        selectGas_2->setMaximumSize(QSize(50, 50));

        horizontalLayout->addWidget(selectGas_2);

        settings = new QPushButton(horizontalLayoutWidget);
        settings->setObjectName(QStringLiteral("settings"));
        settings->setMinimumSize(QSize(50, 50));
        settings->setMaximumSize(QSize(50, 50));

        horizontalLayout->addWidget(settings);

        line = new QFrame(DisplayGraph);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 190, 461, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        placeHolder = new QWidget(DisplayGraph);
        placeHolder->setObjectName(QStringLiteral("placeHolder"));
        placeHolder->setGeometry(QRect(10, 10, 461, 181));

        retranslateUi(DisplayGraph);

        QMetaObject::connectSlotsByName(DisplayGraph);
    } // setupUi

    void retranslateUi(QWidget *DisplayGraph)
    {
        DisplayGraph->setWindowTitle(QApplication::translate("DisplayGraph", "Form", 0));
        homeButton->setText(QString());
        zOut->setText(QString());
        zIn->setText(QString());
        selectGas_2->setText(QString());
        settings->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DisplayGraph: public Ui_DisplayGraph {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYGRAPH_H
