/********************************************************************************
** Form generated from reading UI file 'analogform.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALOGFORM_H
#define UI_ANALOGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnalogForm
{
public:
    QPushButton *mPrevious;
    QLabel *name;
    QLabel *voltage;
    QLabel *value;
    QLabel *units;
    QPushButton *increase;
    QPushButton *decrease;
    QPushButton *save;
    QPushButton *mNext;
    QPushButton *home;

    void setupUi(QWidget *AnalogForm)
    {
        if (AnalogForm->objectName().isEmpty())
            AnalogForm->setObjectName(QStringLiteral("AnalogForm"));
        AnalogForm->resize(480, 277);
        AnalogForm->setMinimumSize(QSize(480, 277));
        AnalogForm->setMaximumSize(QSize(480, 277));
        QFont font;
        font.setPointSize(8);
        AnalogForm->setFont(font);
        AnalogForm->setStyleSheet(QStringLiteral("background-image: url(:./Touch-Keyboard2-Line.png)"));
        mPrevious = new QPushButton(AnalogForm);
        mPrevious->setObjectName(QStringLiteral("mPrevious"));
        mPrevious->setGeometry(QRect(10, 80, 50, 181));
        name = new QLabel(AnalogForm);
        name->setObjectName(QStringLiteral("name"));
        name->setGeometry(QRect(150, 10, 201, 50));
        QFont font1;
        font1.setPointSize(18);
        name->setFont(font1);
        voltage = new QLabel(AnalogForm);
        voltage->setObjectName(QStringLiteral("voltage"));
        voltage->setGeometry(QRect(90, 110, 91, 50));
        voltage->setFont(font1);
        value = new QLabel(AnalogForm);
        value->setObjectName(QStringLiteral("value"));
        value->setGeometry(QRect(210, 110, 51, 50));
        value->setFont(font1);
        units = new QLabel(AnalogForm);
        units->setObjectName(QStringLiteral("units"));
        units->setGeometry(QRect(270, 110, 61, 50));
        units->setFont(font1);
        increase = new QPushButton(AnalogForm);
        increase->setObjectName(QStringLiteral("increase"));
        increase->setGeometry(QRect(340, 100, 25, 25));
        decrease = new QPushButton(AnalogForm);
        decrease->setObjectName(QStringLiteral("decrease"));
        decrease->setGeometry(QRect(340, 140, 25, 25));
        save = new QPushButton(AnalogForm);
        save->setObjectName(QStringLiteral("save"));
        save->setGeometry(QRect(180, 177, 111, 61));
        QFont font2;
        font2.setPointSize(15);
        save->setFont(font2);
        mNext = new QPushButton(AnalogForm);
        mNext->setObjectName(QStringLiteral("mNext"));
        mNext->setGeometry(QRect(420, 80, 50, 181));
        home = new QPushButton(AnalogForm);
        home->setObjectName(QStringLiteral("home"));
        home->setGeometry(QRect(420, 10, 50, 50));

        retranslateUi(AnalogForm);

        QMetaObject::connectSlotsByName(AnalogForm);
    } // setupUi

    void retranslateUi(QWidget *AnalogForm)
    {
        AnalogForm->setWindowTitle(QApplication::translate("AnalogForm", "Form", 0));
        mPrevious->setText(QApplication::translate("AnalogForm", "<=", 0));
        name->setText(QApplication::translate("AnalogForm", "Analog Output", 0));
        voltage->setText(QApplication::translate("AnalogForm", "2.5V =", 0));
        value->setText(QApplication::translate("AnalogForm", "250", 0));
        units->setText(QApplication::translate("AnalogForm", "ppb", 0));
        increase->setText(QApplication::translate("AnalogForm", "+", 0));
        decrease->setText(QApplication::translate("AnalogForm", "-", 0));
        save->setText(QApplication::translate("AnalogForm", "Save", 0));
        mNext->setText(QApplication::translate("AnalogForm", "=>", 0));
        home->setText(QApplication::translate("AnalogForm", "Home", 0));
    } // retranslateUi

};

namespace Ui {
    class AnalogForm: public Ui_AnalogForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALOGFORM_H
