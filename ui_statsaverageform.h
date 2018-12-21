/********************************************************************************
** Form generated from reading UI file 'statsaverageform.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATSAVERAGEFORM_H
#define UI_STATSAVERAGEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatsAverageForm
{
public:
    QPushButton *mPrev;
    QPushButton *mNext;
    QLabel *EightLabel;
    QLabel *title;
    QComboBox *selectGas;
    QLabel *HourLabel;
    QLabel *HourAvg_2;
    QLabel *HourAvg;
    QPushButton *home;

    void setupUi(QWidget *StatsAverageForm)
    {
        if (StatsAverageForm->objectName().isEmpty())
            StatsAverageForm->setObjectName(QStringLiteral("StatsAverageForm"));
        StatsAverageForm->resize(480, 277);
        StatsAverageForm->setMinimumSize(QSize(480, 277));
        StatsAverageForm->setMaximumSize(QSize(480, 277));
        mPrev = new QPushButton(StatsAverageForm);
        mPrev->setObjectName(QStringLiteral("mPrev"));
        mPrev->setGeometry(QRect(10, 70, 50, 191));
        mNext = new QPushButton(StatsAverageForm);
        mNext->setObjectName(QStringLiteral("mNext"));
        mNext->setGeometry(QRect(420, 70, 50, 191));
        EightLabel = new QLabel(StatsAverageForm);
        EightLabel->setObjectName(QStringLiteral("EightLabel"));
        EightLabel->setGeometry(QRect(70, 200, 170, 30));
        QFont font;
        font.setPointSize(15);
        EightLabel->setFont(font);
        title = new QLabel(StatsAverageForm);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(175, 20, 130, 40));
        QFont font1;
        font1.setPointSize(20);
        title->setFont(font1);
        selectGas = new QComboBox(StatsAverageForm);
        selectGas->setObjectName(QStringLiteral("selectGas"));
        selectGas->setGeometry(QRect(105, 70, 270, 20));
        HourLabel = new QLabel(StatsAverageForm);
        HourLabel->setObjectName(QStringLiteral("HourLabel"));
        HourLabel->setGeometry(QRect(70, 110, 170, 30));
        HourLabel->setFont(font);
        HourAvg_2 = new QLabel(StatsAverageForm);
        HourAvg_2->setObjectName(QStringLiteral("HourAvg_2"));
        HourAvg_2->setGeometry(QRect(240, 200, 131, 30));
        HourAvg_2->setFont(font);
        HourAvg = new QLabel(StatsAverageForm);
        HourAvg->setObjectName(QStringLiteral("HourAvg"));
        HourAvg->setGeometry(QRect(240, 110, 131, 30));
        HourAvg->setFont(font);
        home = new QPushButton(StatsAverageForm);
        home->setObjectName(QStringLiteral("home"));
        home->setGeometry(QRect(420, 10, 50, 50));

        retranslateUi(StatsAverageForm);

        QMetaObject::connectSlotsByName(StatsAverageForm);
    } // setupUi

    void retranslateUi(QWidget *StatsAverageForm)
    {
        StatsAverageForm->setWindowTitle(QApplication::translate("StatsAverageForm", "Form", 0));
        mPrev->setText(QApplication::translate("StatsAverageForm", "<=", 0));
        mNext->setText(QApplication::translate("StatsAverageForm", "=>", 0));
        EightLabel->setText(QApplication::translate("StatsAverageForm", "Eight Average:", 0));
        title->setText(QApplication::translate("StatsAverageForm", "Averages", 0));
        selectGas->clear();
        selectGas->insertItems(0, QStringList()
         << QApplication::translate("StatsAverageForm", "NO", 0)
         << QApplication::translate("StatsAverageForm", "NO2", 0)
         << QApplication::translate("StatsAverageForm", "NOx", 0)
        );
        selectGas->setCurrentText(QApplication::translate("StatsAverageForm", "NO", 0));
        HourLabel->setText(QApplication::translate("StatsAverageForm", "Hour Average:", 0));
        HourAvg_2->setText(QApplication::translate("StatsAverageForm", "0.0 ppb", 0));
        HourAvg->setText(QApplication::translate("StatsAverageForm", "0.0 ppb", 0));
        home->setText(QApplication::translate("StatsAverageForm", "Home", 0));
    } // retranslateUi

};

namespace Ui {
    class StatsAverageForm: public Ui_StatsAverageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATSAVERAGEFORM_H
