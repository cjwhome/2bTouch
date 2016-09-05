/********************************************************************************
** Form generated from reading UI file 'adminview.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINVIEW_H
#define UI_ADMINVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminView
{
public:

    void setupUi(QWidget *AdminView)
    {
        if (AdminView->objectName().isEmpty())
            AdminView->setObjectName(QStringLiteral("AdminView"));
        AdminView->resize(480, 277);

        retranslateUi(AdminView);

        QMetaObject::connectSlotsByName(AdminView);
    } // setupUi

    void retranslateUi(QWidget *AdminView)
    {
        AdminView->setWindowTitle(QApplication::translate("AdminView", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class AdminView: public Ui_AdminView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINVIEW_H
