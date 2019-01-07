/********************************************************************************
** Form generated from reading UI file 'settingsview.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSVIEW_H
#define UI_SETTINGSVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsView
{
public:

    void setupUi(QWidget *SettingsView)
    {
        if (SettingsView->objectName().isEmpty())
            SettingsView->setObjectName(QStringLiteral("SettingsView"));
        SettingsView->resize(480, 277);

        retranslateUi(SettingsView);

        QMetaObject::connectSlotsByName(SettingsView);
    } // setupUi

    void retranslateUi(QWidget *SettingsView)
    {
        SettingsView->setWindowTitle(QApplication::translate("SettingsView", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingsView: public Ui_SettingsView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSVIEW_H
