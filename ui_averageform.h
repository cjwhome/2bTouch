/********************************************************************************
** Form generated from reading UI file 'averageform.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AVERAGEFORM_H
#define UI_AVERAGEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AverageForm
{
public:
    QPushButton *pushButton;
    QTextBrowser *title;
    QTextBrowser *five;
    QTextBrowser *one;
    QTextBrowser *hour;
    QTextBrowser *eight;
    QListView *listView;
    QPushButton *mPrevious;
    QPushButton *mNext;

    void setupUi(QWidget *AverageForm)
    {
        if (AverageForm->objectName().isEmpty())
            AverageForm->setObjectName(QStringLiteral("AverageForm"));
        AverageForm->resize(480, 277);
        AverageForm->setMinimumSize(QSize(480, 277));
        AverageForm->setMaximumSize(QSize(480, 277));
        pushButton = new QPushButton(AverageForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(420, 10, 50, 50));
        title = new QTextBrowser(AverageForm);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(180, 10, 131, 51));
        five = new QTextBrowser(AverageForm);
        five->setObjectName(QStringLiteral("five"));
        five->setGeometry(QRect(230, 120, 161, 51));
        one = new QTextBrowser(AverageForm);
        one->setObjectName(QStringLiteral("one"));
        one->setGeometry(QRect(230, 70, 161, 51));
        hour = new QTextBrowser(AverageForm);
        hour->setObjectName(QStringLiteral("hour"));
        hour->setGeometry(QRect(230, 170, 161, 51));
        eight = new QTextBrowser(AverageForm);
        eight->setObjectName(QStringLiteral("eight"));
        eight->setGeometry(QRect(230, 220, 161, 51));
        eight->setStyleSheet(QStringLiteral("font-size: 10px"));
        listView = new QListView(AverageForm);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(70, 70, 161, 201));
        mPrevious = new QPushButton(AverageForm);
        mPrevious->setObjectName(QStringLiteral("mPrevious"));
        mPrevious->setGeometry(QRect(10, 80, 50, 181));
        mNext = new QPushButton(AverageForm);
        mNext->setObjectName(QStringLiteral("mNext"));
        mNext->setGeometry(QRect(420, 80, 50, 181));

        retranslateUi(AverageForm);

        QMetaObject::connectSlotsByName(AverageForm);
    } // setupUi

    void retranslateUi(QWidget *AverageForm)
    {
        AverageForm->setWindowTitle(QApplication::translate("AverageForm", "Form", 0));
        pushButton->setText(QApplication::translate("AverageForm", "Home", 0));
        title->setHtml(QApplication::translate("AverageForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt;\">Averages</span></p></body></html>", 0));
        five->setHtml(QApplication::translate("AverageForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt;\">5m: 0.0 ppb</span></p></body></html>", 0));
        one->setHtml(QApplication::translate("AverageForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt;\">1m: 0.0 ppb</span></p></body></html>", 0));
        hour->setHtml(QApplication::translate("AverageForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt;\">1h: 0.0 ppb</span></p></body></html>", 0));
        eight->setHtml(QApplication::translate("AverageForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10px; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt;\">8h: 0.0 ppb</span></p></body></html>", 0));
        mPrevious->setText(QApplication::translate("AverageForm", "<=", 0));
        mNext->setText(QApplication::translate("AverageForm", "=>", 0));
    } // retranslateUi

};

namespace Ui {
    class AverageForm: public Ui_AverageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AVERAGEFORM_H
