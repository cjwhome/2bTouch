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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DisplayGraph
{
public:

    void setupUi(QWidget *DisplayGraph)
    {
        if (DisplayGraph->objectName().isEmpty())
            DisplayGraph->setObjectName(QStringLiteral("DisplayGraph"));
        DisplayGraph->resize(480, 277);

        retranslateUi(DisplayGraph);

        QMetaObject::connectSlotsByName(DisplayGraph);
    } // setupUi

    void retranslateUi(QWidget *DisplayGraph)
    {
        DisplayGraph->setWindowTitle(QApplication::translate("DisplayGraph", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class DisplayGraph: public Ui_DisplayGraph {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYGRAPH_H
