/********************************************************************************
** Form generated from reading UI file 'filesform.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILESFORM_H
#define UI_FILESFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FilesForm
{
public:
    QPushButton *pushButton;
    QPushButton *mPrev;
    QPushButton *mNext;
    QLabel *label;
    QWidget *widget;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *FilesForm)
    {
        if (FilesForm->objectName().isEmpty())
            FilesForm->setObjectName(QStringLiteral("FilesForm"));
        FilesForm->resize(480, 277);
        FilesForm->setMinimumSize(QSize(480, 277));
        FilesForm->setMaximumSize(QSize(480, 277));
        pushButton = new QPushButton(FilesForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(420, 10, 50, 50));
        mPrev = new QPushButton(FilesForm);
        mPrev->setObjectName(QStringLiteral("mPrev"));
        mPrev->setGeometry(QRect(10, 80, 50, 181));
        mNext = new QPushButton(FilesForm);
        mNext->setObjectName(QStringLiteral("mNext"));
        mNext->setGeometry(QRect(420, 80, 50, 181));
        label = new QLabel(FilesForm);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(190, 10, 100, 50));
        QFont font;
        font.setPointSize(30);
        label->setFont(font);
        widget = new QWidget(FilesForm);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(70, 99, 341, 111));
        label_2 = new QLabel(FilesForm);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(110, 80, 55, 16));
        label_3 = new QLabel(FilesForm);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(310, 80, 55, 16));

        retranslateUi(FilesForm);

        QMetaObject::connectSlotsByName(FilesForm);
    } // setupUi

    void retranslateUi(QWidget *FilesForm)
    {
        FilesForm->setWindowTitle(QApplication::translate("FilesForm", "Form", 0));
        pushButton->setText(QApplication::translate("FilesForm", "Home", 0));
        mPrev->setText(QApplication::translate("FilesForm", "<=", 0));
        mNext->setText(QApplication::translate("FilesForm", "=>", 0));
        label->setText(QApplication::translate("FilesForm", "Files", 0));
        label_2->setText(QApplication::translate("FilesForm", "TextLabel", 0));
        label_3->setText(QApplication::translate("FilesForm", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class FilesForm: public Ui_FilesForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILESFORM_H
