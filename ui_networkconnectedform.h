/********************************************************************************
** Form generated from reading UI file 'networkconnectedform.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORKCONNECTEDFORM_H
#define UI_NETWORKCONNECTEDFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NetworkConnectedForm
{
public:
    QPushButton *Home;
    QPushButton *mPrev;
    QPushButton *mNext;
    QLabel *Title;
    QLabel *NetworkName;
    QLabel *IP;
    QPushButton *Disconnect;
    QLabel *NetworkNameActual;
    QLabel *IPActual;

    void setupUi(QWidget *NetworkConnectedForm)
    {
        if (NetworkConnectedForm->objectName().isEmpty())
            NetworkConnectedForm->setObjectName(QStringLiteral("NetworkConnectedForm"));
        NetworkConnectedForm->resize(480, 277);
        NetworkConnectedForm->setMinimumSize(QSize(480, 277));
        NetworkConnectedForm->setMaximumSize(QSize(480, 277));
        Home = new QPushButton(NetworkConnectedForm);
        Home->setObjectName(QStringLiteral("Home"));
        Home->setGeometry(QRect(420, 10, 50, 50));
        mPrev = new QPushButton(NetworkConnectedForm);
        mPrev->setObjectName(QStringLiteral("mPrev"));
        mPrev->setGeometry(QRect(10, 80, 50, 181));
        mNext = new QPushButton(NetworkConnectedForm);
        mNext->setObjectName(QStringLiteral("mNext"));
        mNext->setGeometry(QRect(420, 80, 50, 181));
        Title = new QLabel(NetworkConnectedForm);
        Title->setObjectName(QStringLiteral("Title"));
        Title->setGeometry(QRect(135, 0, 190, 80));
        QFont font;
        font.setPointSize(30);
        Title->setFont(font);
        NetworkName = new QLabel(NetworkConnectedForm);
        NetworkName->setObjectName(QStringLiteral("NetworkName"));
        NetworkName->setGeometry(QRect(70, 100, 101, 61));
        QFont font1;
        font1.setPointSize(20);
        NetworkName->setFont(font1);
        IP = new QLabel(NetworkConnectedForm);
        IP->setObjectName(QStringLiteral("IP"));
        IP->setGeometry(QRect(70, 150, 171, 61));
        IP->setFont(font1);
        Disconnect = new QPushButton(NetworkConnectedForm);
        Disconnect->setObjectName(QStringLiteral("Disconnect"));
        Disconnect->setGeometry(QRect(175, 226, 130, 31));
        QFont font2;
        font2.setPointSize(15);
        Disconnect->setFont(font2);
        NetworkNameActual = new QLabel(NetworkConnectedForm);
        NetworkNameActual->setObjectName(QStringLiteral("NetworkNameActual"));
        NetworkNameActual->setGeometry(QRect(190, 120, 221, 31));
        NetworkNameActual->setFont(font2);
        IPActual = new QLabel(NetworkConnectedForm);
        IPActual->setObjectName(QStringLiteral("IPActual"));
        IPActual->setGeometry(QRect(250, 160, 161, 41));
        IPActual->setFont(font2);

        retranslateUi(NetworkConnectedForm);

        QMetaObject::connectSlotsByName(NetworkConnectedForm);
    } // setupUi

    void retranslateUi(QWidget *NetworkConnectedForm)
    {
        NetworkConnectedForm->setWindowTitle(QApplication::translate("NetworkConnectedForm", "Form", 0));
        Home->setText(QApplication::translate("NetworkConnectedForm", "Home", 0));
        mPrev->setText(QApplication::translate("NetworkConnectedForm", "<=", 0));
        mNext->setText(QApplication::translate("NetworkConnectedForm", "=>", 0));
        Title->setText(QApplication::translate("NetworkConnectedForm", "Network", 0));
        NetworkName->setText(QApplication::translate("NetworkConnectedForm", "Name:", 0));
        IP->setText(QApplication::translate("NetworkConnectedForm", "IP Address:", 0));
        Disconnect->setText(QApplication::translate("NetworkConnectedForm", "Disconnect", 0));
        NetworkNameActual->setText(QApplication::translate("NetworkConnectedForm", "Network Name", 0));
        IPActual->setText(QApplication::translate("NetworkConnectedForm", "192.168.56.1", 0));
    } // retranslateUi

};

namespace Ui {
    class NetworkConnectedForm: public Ui_NetworkConnectedForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORKCONNECTEDFORM_H
