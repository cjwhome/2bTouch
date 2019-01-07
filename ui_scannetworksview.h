/********************************************************************************
** Form generated from reading UI file 'scannetworksview.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCANNETWORKSVIEW_H
#define UI_SCANNETWORKSVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScanNetworksView
{
public:

    void setupUi(QWidget *ScanNetworksView)
    {
        if (ScanNetworksView->objectName().isEmpty())
            ScanNetworksView->setObjectName(QStringLiteral("ScanNetworksView"));
        ScanNetworksView->resize(480, 277);

        retranslateUi(ScanNetworksView);

        QMetaObject::connectSlotsByName(ScanNetworksView);
    } // setupUi

    void retranslateUi(QWidget *ScanNetworksView)
    {
        ScanNetworksView->setWindowTitle(QApplication::translate("ScanNetworksView", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class ScanNetworksView: public Ui_ScanNetworksView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANNETWORKSVIEW_H
