/********************************************************************************
** Form generated from reading UI file 'usertypeview.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERTYPEVIEW_H
#define UI_USERTYPEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserTypeView
{
public:
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QWidget *UserTypeView)
    {
        if (UserTypeView->objectName().isEmpty())
            UserTypeView->setObjectName(QStringLiteral("UserTypeView"));
        UserTypeView->resize(480, 277);
        lineEdit = new QLineEdit(UserTypeView);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(200, 30, 251, 27));
        label = new QLabel(UserTypeView);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 171, 20));

        retranslateUi(UserTypeView);

        QMetaObject::connectSlotsByName(UserTypeView);
    } // setupUi

    void retranslateUi(QWidget *UserTypeView)
    {
        UserTypeView->setWindowTitle(QApplication::translate("UserTypeView", "Form", 0));
        label->setText(QApplication::translate("UserTypeView", "default text", 0));
    } // retranslateUi

};

namespace Ui {
    class UserTypeView: public Ui_UserTypeView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERTYPEVIEW_H
