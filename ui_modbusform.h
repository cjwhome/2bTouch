/********************************************************************************
** Form generated from reading UI file 'modbusform.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODBUSFORM_H
#define UI_MODBUSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModbusForm
{
public:
    QPushButton *home;
    QPushButton *mPrev;
    QPushButton *mNext;
    QLabel *title;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *layout;
    QPushButton *save;

    void setupUi(QWidget *ModbusForm)
    {
        if (ModbusForm->objectName().isEmpty())
            ModbusForm->setObjectName(QStringLiteral("ModbusForm"));
        ModbusForm->resize(480, 277);
        ModbusForm->setMinimumSize(QSize(480, 277));
        ModbusForm->setMaximumSize(QSize(480, 277));
        home = new QPushButton(ModbusForm);
        home->setObjectName(QStringLiteral("home"));
        home->setGeometry(QRect(420, 10, 50, 50));
        mPrev = new QPushButton(ModbusForm);
        mPrev->setObjectName(QStringLiteral("mPrev"));
        mPrev->setGeometry(QRect(10, 80, 50, 181));
        mNext = new QPushButton(ModbusForm);
        mNext->setObjectName(QStringLiteral("mNext"));
        mNext->setGeometry(QRect(420, 80, 50, 181));
        title = new QLabel(ModbusForm);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(115, 30, 250, 100));
        QFont font;
        font.setPointSize(40);
        title->setFont(font);
        horizontalLayoutWidget = new QWidget(ModbusForm);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(80, 140, 311, 80));
        layout = new QHBoxLayout(horizontalLayoutWidget);
        layout->setObjectName(QStringLiteral("layout"));
        layout->setContentsMargins(0, 0, 0, 0);
        save = new QPushButton(ModbusForm);
        save->setObjectName(QStringLiteral("save"));
        save->setGeometry(QRect(175, 227, 130, 40));
        QFont font1;
        font1.setPointSize(15);
        save->setFont(font1);

        retranslateUi(ModbusForm);

        QMetaObject::connectSlotsByName(ModbusForm);
    } // setupUi

    void retranslateUi(QWidget *ModbusForm)
    {
        ModbusForm->setWindowTitle(QApplication::translate("ModbusForm", "Form", 0));
        home->setText(QApplication::translate("ModbusForm", "Home", 0));
        mPrev->setText(QApplication::translate("ModbusForm", "<=", 0));
        mNext->setText(QApplication::translate("ModbusForm", "=>", 0));
        title->setText(QApplication::translate("ModbusForm", "Modbus", 0));
        save->setText(QApplication::translate("ModbusForm", "Save", 0));
    } // retranslateUi

};

namespace Ui {
    class ModbusForm: public Ui_ModbusForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODBUSFORM_H
