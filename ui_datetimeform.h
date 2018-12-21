/********************************************************************************
** Form generated from reading UI file 'datetimeform.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATETIMEFORM_H
#define UI_DATETIMEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DateTimeForm
{
public:
    QPushButton *home;
    QLabel *name;
    QPushButton *mLeftT;
    QPushButton *mRightT;
    QPushButton *mRightC;
    QLabel *clabel;
    QLabel *tLabel;
    QLabel *time;
    QPushButton *increaseT;
    QPushButton *decreaseT;
    QPushButton *increaseC;
    QPushButton *decreaseC;
    QPushButton *save;
    QPushButton *mLeftC;
    QLabel *Date;
    QPushButton *gonext;
    QPushButton *goPrev;

    void setupUi(QWidget *DateTimeForm)
    {
        if (DateTimeForm->objectName().isEmpty())
            DateTimeForm->setObjectName(QStringLiteral("DateTimeForm"));
        DateTimeForm->resize(480, 277);
        DateTimeForm->setMinimumSize(QSize(480, 277));
        DateTimeForm->setMaximumSize(QSize(480, 277));
        home = new QPushButton(DateTimeForm);
        home->setObjectName(QStringLiteral("home"));
        home->setGeometry(QRect(420, 10, 50, 50));
        home->setMinimumSize(QSize(50, 50));
        home->setMaximumSize(QSize(50, 50));
        name = new QLabel(DateTimeForm);
        name->setObjectName(QStringLiteral("name"));
        name->setGeometry(QRect(160, 20, 171, 31));
        QFont font;
        font.setPointSize(18);
        name->setFont(font);
        mLeftT = new QPushButton(DateTimeForm);
        mLeftT->setObjectName(QStringLiteral("mLeftT"));
        mLeftT->setEnabled(true);
        mLeftT->setGeometry(QRect(70, 170, 50, 50));
        mLeftT->setMinimumSize(QSize(50, 50));
        mLeftT->setMaximumSize(QSize(50, 50));
        mRightT = new QPushButton(DateTimeForm);
        mRightT->setObjectName(QStringLiteral("mRightT"));
        mRightT->setEnabled(true);
        mRightT->setGeometry(QRect(360, 170, 50, 50));
        mRightT->setMinimumSize(QSize(50, 50));
        mRightT->setMaximumSize(QSize(50, 50));
        mRightC = new QPushButton(DateTimeForm);
        mRightC->setObjectName(QStringLiteral("mRightC"));
        mRightC->setEnabled(true);
        mRightC->setGeometry(QRect(360, 90, 50, 50));
        mRightC->setMinimumSize(QSize(50, 50));
        mRightC->setMaximumSize(QSize(50, 50));
        clabel = new QLabel(DateTimeForm);
        clabel->setObjectName(QStringLiteral("clabel"));
        clabel->setGeometry(QRect(180, 50, 71, 41));
        tLabel = new QLabel(DateTimeForm);
        tLabel->setObjectName(QStringLiteral("tLabel"));
        tLabel->setGeometry(QRect(180, 140, 91, 41));
        time = new QLabel(DateTimeForm);
        time->setObjectName(QStringLiteral("time"));
        time->setGeometry(QRect(170, 170, 111, 51));
        QFont font1;
        font1.setPointSize(15);
        time->setFont(font1);
        increaseT = new QPushButton(DateTimeForm);
        increaseT->setObjectName(QStringLiteral("increaseT"));
        increaseT->setGeometry(QRect(300, 160, 25, 25));
        decreaseT = new QPushButton(DateTimeForm);
        decreaseT->setObjectName(QStringLiteral("decreaseT"));
        decreaseT->setGeometry(QRect(300, 200, 25, 25));
        increaseC = new QPushButton(DateTimeForm);
        increaseC->setObjectName(QStringLiteral("increaseC"));
        increaseC->setGeometry(QRect(300, 80, 25, 25));
        decreaseC = new QPushButton(DateTimeForm);
        decreaseC->setObjectName(QStringLiteral("decreaseC"));
        decreaseC->setGeometry(QRect(300, 120, 25, 25));
        save = new QPushButton(DateTimeForm);
        save->setObjectName(QStringLiteral("save"));
        save->setGeometry(QRect(190, 230, 93, 28));
        mLeftC = new QPushButton(DateTimeForm);
        mLeftC->setObjectName(QStringLiteral("mLeftC"));
        mLeftC->setGeometry(QRect(70, 90, 50, 50));
        mLeftC->setMinimumSize(QSize(50, 50));
        mLeftC->setMaximumSize(QSize(50, 50));
        Date = new QLabel(DateTimeForm);
        Date->setObjectName(QStringLiteral("Date"));
        Date->setGeometry(QRect(170, 90, 111, 51));
        Date->setFont(font1);
        gonext = new QPushButton(DateTimeForm);
        gonext->setObjectName(QStringLiteral("gonext"));
        gonext->setGeometry(QRect(420, 80, 50, 181));
        goPrev = new QPushButton(DateTimeForm);
        goPrev->setObjectName(QStringLiteral("goPrev"));
        goPrev->setGeometry(QRect(10, 80, 50, 181));

        retranslateUi(DateTimeForm);

        QMetaObject::connectSlotsByName(DateTimeForm);
    } // setupUi

    void retranslateUi(QWidget *DateTimeForm)
    {
        DateTimeForm->setWindowTitle(QApplication::translate("DateTimeForm", "Form", 0));
        home->setText(QApplication::translate("DateTimeForm", "Home", 0));
        name->setText(QApplication::translate("DateTimeForm", "Date & Time", 0));
        mLeftT->setText(QApplication::translate("DateTimeForm", "<-", 0));
        mRightT->setText(QApplication::translate("DateTimeForm", "->", 0));
        mRightC->setText(QApplication::translate("DateTimeForm", "->", 0));
        clabel->setText(QApplication::translate("DateTimeForm", "(MM/DD/YY)", 0));
        tLabel->setText(QApplication::translate("DateTimeForm", "(HH:MM:SS)", 0));
        time->setText(QApplication::translate("DateTimeForm", "10:10:10", 0));
        increaseT->setText(QApplication::translate("DateTimeForm", "+", 0));
        decreaseT->setText(QApplication::translate("DateTimeForm", "-", 0));
        increaseC->setText(QApplication::translate("DateTimeForm", "+", 0));
        decreaseC->setText(QApplication::translate("DateTimeForm", "-", 0));
        save->setText(QApplication::translate("DateTimeForm", "Save", 0));
        mLeftC->setText(QApplication::translate("DateTimeForm", "<-", 0));
        Date->setText(QApplication::translate("DateTimeForm", "10/10/10", 0));
        gonext->setText(QApplication::translate("DateTimeForm", "=>", 0));
        goPrev->setText(QApplication::translate("DateTimeForm", "<=", 0));
    } // retranslateUi

};

namespace Ui {
    class DateTimeForm: public Ui_DateTimeForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATETIMEFORM_H
