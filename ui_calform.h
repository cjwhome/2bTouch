/********************************************************************************
** Form generated from reading UI file 'calform.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALFORM_H
#define UI_CALFORM_H

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

class Ui_CalForm
{
public:
    QLabel *name;
    QComboBox *selectGas;
    QLabel *slope;
    QLabel *offset;
    QPushButton *home;
    QPushButton *increaseS;
    QPushButton *decreaseS;
    QPushButton *increaseO;
    QPushButton *decreaseO;
    QPushButton *save;
    QPushButton *goPrev;
    QPushButton *goNext;

    void setupUi(QWidget *CalForm)
    {
        if (CalForm->objectName().isEmpty())
            CalForm->setObjectName(QStringLiteral("CalForm"));
        CalForm->resize(480, 277);
        name = new QLabel(CalForm);
        name->setObjectName(QStringLiteral("name"));
        name->setGeometry(QRect(170, 20, 151, 31));
        QFont font;
        font.setPointSize(18);
        name->setFont(font);
        selectGas = new QComboBox(CalForm);
        selectGas->setObjectName(QStringLiteral("selectGas"));
        selectGas->setGeometry(QRect(100, 70, 271, 22));
        slope = new QLabel(CalForm);
        slope->setObjectName(QStringLiteral("slope"));
        slope->setGeometry(QRect(120, 120, 131, 31));
        QFont font1;
        font1.setPointSize(15);
        slope->setFont(font1);
        offset = new QLabel(CalForm);
        offset->setObjectName(QStringLiteral("offset"));
        offset->setGeometry(QRect(120, 170, 131, 31));
        offset->setFont(font1);
        home = new QPushButton(CalForm);
        home->setObjectName(QStringLiteral("home"));
        home->setGeometry(QRect(420, 10, 50, 50));
        home->setMinimumSize(QSize(50, 50));
        home->setMaximumSize(QSize(50, 50));
        increaseS = new QPushButton(CalForm);
        increaseS->setObjectName(QStringLiteral("increaseS"));
        increaseS->setGeometry(QRect(300, 100, 25, 25));
        decreaseS = new QPushButton(CalForm);
        decreaseS->setObjectName(QStringLiteral("decreaseS"));
        decreaseS->setGeometry(QRect(300, 130, 25, 25));
        increaseO = new QPushButton(CalForm);
        increaseO->setObjectName(QStringLiteral("increaseO"));
        increaseO->setGeometry(QRect(300, 160, 25, 25));
        decreaseO = new QPushButton(CalForm);
        decreaseO->setObjectName(QStringLiteral("decreaseO"));
        decreaseO->setGeometry(QRect(300, 190, 25, 25));
        save = new QPushButton(CalForm);
        save->setObjectName(QStringLiteral("save"));
        save->setGeometry(QRect(160, 220, 121, 41));
        goPrev = new QPushButton(CalForm);
        goPrev->setObjectName(QStringLiteral("goPrev"));
        goPrev->setGeometry(QRect(10, 80, 50, 181));
        goNext = new QPushButton(CalForm);
        goNext->setObjectName(QStringLiteral("goNext"));
        goNext->setGeometry(QRect(420, 80, 50, 181));

        retranslateUi(CalForm);

        QMetaObject::connectSlotsByName(CalForm);
    } // setupUi

    void retranslateUi(QWidget *CalForm)
    {
        CalForm->setWindowTitle(QApplication::translate("CalForm", "Form", 0));
        name->setText(QApplication::translate("CalForm", "Calibration", 0));
        selectGas->clear();
        selectGas->insertItems(0, QStringList()
         << QApplication::translate("CalForm", "NO", 0)
         << QApplication::translate("CalForm", "NO2", 0)
         << QApplication::translate("CalForm", "NOx", 0)
        );
        selectGas->setCurrentText(QApplication::translate("CalForm", "NO", 0));
        slope->setText(QApplication::translate("CalForm", "Slope:  0.0", 0));
        offset->setText(QApplication::translate("CalForm", "Offset: 0", 0));
        home->setText(QApplication::translate("CalForm", "Home", 0));
        increaseS->setText(QApplication::translate("CalForm", "+", 0));
        decreaseS->setText(QApplication::translate("CalForm", "-", 0));
        increaseO->setText(QApplication::translate("CalForm", "+", 0));
        decreaseO->setText(QApplication::translate("CalForm", "-", 0));
        save->setText(QApplication::translate("CalForm", "Save", 0));
        goPrev->setText(QApplication::translate("CalForm", "<=", 0));
        goNext->setText(QApplication::translate("CalForm", "=>", 0));
    } // retranslateUi

};

namespace Ui {
    class CalForm: public Ui_CalForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALFORM_H
