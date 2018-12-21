/********************************************************************************
** Form generated from reading UI file 'configform.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGFORM_H
#define UI_CONFIGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigForm
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QLabel *label;

    void setupUi(QWidget *ConfigForm)
    {
        if (ConfigForm->objectName().isEmpty())
            ConfigForm->setObjectName(QStringLiteral("ConfigForm"));
        ConfigForm->resize(480, 277);
        ConfigForm->setMinimumSize(QSize(480, 277));
        ConfigForm->setMaximumSize(QSize(480, 277));
        pushButton = new QPushButton(ConfigForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(420, 10, 50, 50));
        pushButton->setMinimumSize(QSize(50, 50));
        pushButton->setMaximumSize(QSize(50, 50));
        pushButton_2 = new QPushButton(ConfigForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(60, 80, 75, 75));
        pushButton_3 = new QPushButton(ConfigForm);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(240, 160, 75, 75));
        pushButton_4 = new QPushButton(ConfigForm);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(130, 160, 75, 76));
        pushButton_5 = new QPushButton(ConfigForm);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(320, 80, 75, 75));
        pushButton_6 = new QPushButton(ConfigForm);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(10, 10, 50, 50));
        pushButton_6->setMinimumSize(QSize(50, 50));
        pushButton_6->setMaximumSize(QSize(50, 50));
        label = new QLabel(ConfigForm);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(150, 10, 211, 71));
        QFont font;
        font.setPointSize(18);
        label->setFont(font);

        retranslateUi(ConfigForm);

        QMetaObject::connectSlotsByName(ConfigForm);
    } // setupUi

    void retranslateUi(QWidget *ConfigForm)
    {
        ConfigForm->setWindowTitle(QApplication::translate("ConfigForm", "Form", 0));
        pushButton->setText(QApplication::translate("ConfigForm", "Back", 0));
        pushButton_2->setText(QApplication::translate("ConfigForm", "Date/Time", 0));
        pushButton_3->setText(QApplication::translate("ConfigForm", "Unt", 0));
        pushButton_4->setText(QApplication::translate("ConfigForm", "I/O", 0));
        pushButton_5->setText(QApplication::translate("ConfigForm", "Cal", 0));
        pushButton_6->setText(QApplication::translate("ConfigForm", "Home", 0));
        label->setText(QApplication::translate("ConfigForm", "Configuration", 0));
    } // retranslateUi

};

namespace Ui {
    class ConfigForm: public Ui_ConfigForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGFORM_H
