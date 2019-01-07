/********************************************************************************
** Form generated from reading UI file 'selectgasform.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTGASFORM_H
#define UI_SELECTGASFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectGasForm
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *apply;
    QLabel *label;

    void setupUi(QWidget *SelectGasForm)
    {
        if (SelectGasForm->objectName().isEmpty())
            SelectGasForm->setObjectName(QStringLiteral("SelectGasForm"));
        SelectGasForm->resize(300, 250);
        SelectGasForm->setMinimumSize(QSize(0, 0));
        gridLayoutWidget = new QWidget(SelectGasForm);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 40, 259, 153));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        apply = new QPushButton(SelectGasForm);
        apply->setObjectName(QStringLiteral("apply"));
        apply->setGeometry(QRect(105, 210, 90, 30));
        label = new QLabel(SelectGasForm);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(110, 10, 80, 15));

        retranslateUi(SelectGasForm);

        QMetaObject::connectSlotsByName(SelectGasForm);
    } // setupUi

    void retranslateUi(QWidget *SelectGasForm)
    {
        SelectGasForm->setWindowTitle(QApplication::translate("SelectGasForm", "Form", 0));
        apply->setText(QApplication::translate("SelectGasForm", "Apply", 0));
        label->setText(QApplication::translate("SelectGasForm", "Select Gasses", 0));
    } // retranslateUi

};

namespace Ui {
    class SelectGasForm: public Ui_SelectGasForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTGASFORM_H
