/********************************************************************************
** Form generated from reading UI file 'networkview.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORKVIEW_H
#define UI_NETWORKVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NetworkView
{
public:

    void setupUi(QWidget *NetworkView)
    {
        if (NetworkView->objectName().isEmpty())
            NetworkView->setObjectName(QStringLiteral("NetworkView"));
        NetworkView->resize(480, 277);

        retranslateUi(NetworkView);

        QMetaObject::connectSlotsByName(NetworkView);
    } // setupUi

    void retranslateUi(QWidget *NetworkView)
    {
        NetworkView->setWindowTitle(QApplication::translate("NetworkView", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class NetworkView: public Ui_NetworkView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORKVIEW_H
