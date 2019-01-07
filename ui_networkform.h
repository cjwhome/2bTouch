/********************************************************************************
** Form generated from reading UI file 'networkform.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORKFORM_H
#define UI_NETWORKFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NetworkForm
{
public:
    QLabel *title;
    QLabel *passwordLabel;
    QPushButton *mNext;
    QPushButton *mPrev;
    QPushButton *home;
    QPushButton *connect;
    QWidget *placeHolder;
    QWidget *mainPlace;

    void setupUi(QWidget *NetworkForm)
    {
        if (NetworkForm->objectName().isEmpty())
            NetworkForm->setObjectName(QStringLiteral("NetworkForm"));
        NetworkForm->resize(480, 277);
        NetworkForm->setMinimumSize(QSize(480, 277));
        NetworkForm->setMaximumSize(QSize(480, 277));
        title = new QLabel(NetworkForm);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(105, 20, 270, 60));
        QFont font;
        font.setPointSize(35);
        title->setFont(font);
        passwordLabel = new QLabel(NetworkForm);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));
        passwordLabel->setGeometry(QRect(70, 200, 151, 31));
        QFont font1;
        font1.setPointSize(20);
        passwordLabel->setFont(font1);
        mNext = new QPushButton(NetworkForm);
        mNext->setObjectName(QStringLiteral("mNext"));
        mNext->setGeometry(QRect(420, 80, 50, 181));
        mPrev = new QPushButton(NetworkForm);
        mPrev->setObjectName(QStringLiteral("mPrev"));
        mPrev->setGeometry(QRect(10, 80, 50, 181));
        home = new QPushButton(NetworkForm);
        home->setObjectName(QStringLiteral("home"));
        home->setGeometry(QRect(420, 10, 50, 50));
        connect = new QPushButton(NetworkForm);
        connect->setObjectName(QStringLiteral("connect"));
        connect->setGeometry(QRect(195, 240, 90, 30));
        placeHolder = new QWidget(NetworkForm);
        placeHolder->setObjectName(QStringLiteral("placeHolder"));
        placeHolder->setGeometry(QRect(229, 210, 181, 21));
        mainPlace = new QWidget(NetworkForm);
        mainPlace->setObjectName(QStringLiteral("mainPlace"));
        mainPlace->setGeometry(QRect(69, 100, 341, 91));

        retranslateUi(NetworkForm);

        QMetaObject::connectSlotsByName(NetworkForm);
    } // setupUi

    void retranslateUi(QWidget *NetworkForm)
    {
        NetworkForm->setWindowTitle(QApplication::translate("NetworkForm", "Form", 0));
        title->setText(QApplication::translate("NetworkForm", "NETWORK", 0));
        passwordLabel->setText(QApplication::translate("NetworkForm", "Password:", 0));
        mNext->setText(QApplication::translate("NetworkForm", "=>", 0));
        mPrev->setText(QApplication::translate("NetworkForm", "<=", 0));
        home->setText(QApplication::translate("NetworkForm", "Home", 0));
        connect->setText(QApplication::translate("NetworkForm", "Connect", 0));
    } // retranslateUi

};

namespace Ui {
    class NetworkForm: public Ui_NetworkForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORKFORM_H
