/********************************************************************************
** Form generated from reading UI file 'menutreeform.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUTREEFORM_H
#define UI_MENUTREEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuTreeForm
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QTextEdit *textEdit;
    QPushButton *pushButton_6;

    void setupUi(QWidget *MenuTreeForm)
    {
        if (MenuTreeForm->objectName().isEmpty())
            MenuTreeForm->setObjectName(QStringLiteral("MenuTreeForm"));
        MenuTreeForm->resize(480, 277);
        MenuTreeForm->setMinimumSize(QSize(480, 277));
        MenuTreeForm->setMaximumSize(QSize(480, 277));
        pushButton = new QPushButton(MenuTreeForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(420, 10, 50, 50));
        pushButton->setMinimumSize(QSize(50, 50));
        pushButton->setMaximumSize(QSize(50, 50));
        pushButton_2 = new QPushButton(MenuTreeForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(60, 200, 50, 50));
        pushButton_3 = new QPushButton(MenuTreeForm);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(160, 200, 50, 50));
        pushButton_4 = new QPushButton(MenuTreeForm);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(260, 200, 50, 50));
        pushButton_5 = new QPushButton(MenuTreeForm);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(360, 200, 50, 50));
        textEdit = new QTextEdit(MenuTreeForm);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(89, 30, 311, 85));
        QFont font;
        font.setPointSize(20);
        textEdit->setFont(font);
        pushButton_6 = new QPushButton(MenuTreeForm);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(10, 10, 50, 50));
        pushButton_6->setMinimumSize(QSize(50, 50));
        pushButton_6->setMaximumSize(QSize(50, 50));

        retranslateUi(MenuTreeForm);

        QMetaObject::connectSlotsByName(MenuTreeForm);
    } // setupUi

    void retranslateUi(QWidget *MenuTreeForm)
    {
        MenuTreeForm->setWindowTitle(QApplication::translate("MenuTreeForm", "Form", 0));
        pushButton->setText(QApplication::translate("MenuTreeForm", "Back", 0));
        pushButton_2->setText(QApplication::translate("MenuTreeForm", "Mod", 0));
        pushButton_3->setText(QApplication::translate("MenuTreeForm", "Avg", 0));
        pushButton_4->setText(QApplication::translate("MenuTreeForm", "Cnf", 0));
        pushButton_5->setText(QApplication::translate("MenuTreeForm", "PushButton", 0));
        textEdit->setHtml(QApplication::translate("MenuTreeForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:20pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:36pt;\">Model 405</span></p></body></html>", 0));
        pushButton_6->setText(QApplication::translate("MenuTreeForm", "Home", 0));
    } // retranslateUi

};

namespace Ui {
    class MenuTreeForm: public Ui_MenuTreeForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUTREEFORM_H
