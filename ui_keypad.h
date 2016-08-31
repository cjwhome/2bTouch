/********************************************************************************
** Form generated from reading UI file 'keypad.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYPAD_H
#define UI_KEYPAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Keypad
{
public:
    QPushButton *vbutton;
    QPushButton *zbutton;
    QPushButton *cbutton;
    QPushButton *pbutton;
    QPushButton *ibutton;
    QPushButton *jbutton;
    QPushButton *spacebutton;
    QPushButton *fbutton;
    QPushButton *sbutton;
    QPushButton *dbutton;
    QPushButton *obutton;
    QPushButton *kbutton;
    QPushButton *nbutton;
    QPushButton *wbutton;
    QPushButton *gbutton;
    QPushButton *ebutton;
    QPushButton *rbutton;
    QPushButton *hbutton;
    QPushButton *ybutton;
    QPushButton *tbutton;
    QPushButton *xbutton;
    QPushButton *donebutton;
    QPushButton *bbutton;
    QPushButton *mbutton;
    QPushButton *ubutton;
    QPushButton *bpbutton;
    QPushButton *lbutton;
    QPushButton *abutton;
    QPushButton *numbutton;
    QPushButton *qbutton;
    QPushButton *numbutton_2;
    QPushButton *donebutton_2;
    QPushButton *apostrophe;
    QPushButton *comma;
    QPushButton *fstop;
    QPushButton *question;
    QPushButton *numbutton_3;
    QPushButton *numbutton_4;
    QLineEdit *lineEdit;

    void setupUi(QDialog *Keypad)
    {
        if (Keypad->objectName().isEmpty())
            Keypad->setObjectName(QStringLiteral("Keypad"));
        Keypad->resize(480, 238);
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        Keypad->setFont(font);
        Keypad->setStyleSheet(QStringLiteral("background-image: url(480x200/Touch-Keyboard.png);"));
        vbutton = new QPushButton(Keypad);
        vbutton->setObjectName(QStringLiteral("vbutton"));
        vbutton->setGeometry(QRect(162, 140, 35, 39));
        QFont font1;
        font1.setPointSize(1);
        font1.setBold(true);
        font1.setWeight(75);
        vbutton->setFont(font1);
        vbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        zbutton = new QPushButton(Keypad);
        zbutton->setObjectName(QStringLiteral("zbutton"));
        zbutton->setGeometry(QRect(42, 140, 35, 39));
        zbutton->setFont(font1);
        zbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        cbutton = new QPushButton(Keypad);
        cbutton->setObjectName(QStringLiteral("cbutton"));
        cbutton->setGeometry(QRect(122, 140, 35, 39));
        cbutton->setFont(font1);
        cbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        pbutton = new QPushButton(Keypad);
        pbutton->setObjectName(QStringLiteral("pbutton"));
        pbutton->setGeometry(QRect(362, 40, 35, 43));
        pbutton->setFont(font1);
        pbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        ibutton = new QPushButton(Keypad);
        ibutton->setObjectName(QStringLiteral("ibutton"));
        ibutton->setGeometry(QRect(282, 40, 35, 43));
        ibutton->setFont(font1);
        ibutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        jbutton = new QPushButton(Keypad);
        jbutton->setObjectName(QStringLiteral("jbutton"));
        jbutton->setGeometry(QRect(252, 92, 35, 43));
        jbutton->setFont(font1);
        jbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        spacebutton = new QPushButton(Keypad);
        spacebutton->setObjectName(QStringLiteral("spacebutton"));
        spacebutton->setGeometry(QRect(122, 190, 233, 41));
        spacebutton->setFont(font1);
        spacebutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"\n"
"border-radius:10px;"));
        fbutton = new QPushButton(Keypad);
        fbutton->setObjectName(QStringLiteral("fbutton"));
        fbutton->setGeometry(QRect(132, 92, 35, 42));
        fbutton->setFont(font1);
        fbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        sbutton = new QPushButton(Keypad);
        sbutton->setObjectName(QStringLiteral("sbutton"));
        sbutton->setGeometry(QRect(52, 92, 35, 43));
        sbutton->setFont(font1);
        sbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        dbutton = new QPushButton(Keypad);
        dbutton->setObjectName(QStringLiteral("dbutton"));
        dbutton->setGeometry(QRect(92, 92, 35, 43));
        dbutton->setFont(font1);
        dbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        obutton = new QPushButton(Keypad);
        obutton->setObjectName(QStringLiteral("obutton"));
        obutton->setGeometry(QRect(322, 40, 35, 43));
        obutton->setFont(font1);
        obutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"border-radius:10px;"));
        kbutton = new QPushButton(Keypad);
        kbutton->setObjectName(QStringLiteral("kbutton"));
        kbutton->setGeometry(QRect(292, 92, 35, 43));
        kbutton->setFont(font1);
        kbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        nbutton = new QPushButton(Keypad);
        nbutton->setObjectName(QStringLiteral("nbutton"));
        nbutton->setGeometry(QRect(242, 140, 35, 39));
        nbutton->setFont(font1);
        nbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        wbutton = new QPushButton(Keypad);
        wbutton->setObjectName(QStringLiteral("wbutton"));
        wbutton->setGeometry(QRect(42, 40, 35, 43));
        wbutton->setFont(font1);
        wbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        gbutton = new QPushButton(Keypad);
        gbutton->setObjectName(QStringLiteral("gbutton"));
        gbutton->setGeometry(QRect(172, 92, 35, 43));
        gbutton->setFont(font1);
        gbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        ebutton = new QPushButton(Keypad);
        ebutton->setObjectName(QStringLiteral("ebutton"));
        ebutton->setGeometry(QRect(82, 40, 35, 43));
        ebutton->setFont(font1);
        ebutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        rbutton = new QPushButton(Keypad);
        rbutton->setObjectName(QStringLiteral("rbutton"));
        rbutton->setGeometry(QRect(122, 40, 35, 43));
        rbutton->setFont(font1);
        rbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        hbutton = new QPushButton(Keypad);
        hbutton->setObjectName(QStringLiteral("hbutton"));
        hbutton->setGeometry(QRect(212, 92, 35, 43));
        hbutton->setFont(font1);
        hbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        ybutton = new QPushButton(Keypad);
        ybutton->setObjectName(QStringLiteral("ybutton"));
        ybutton->setGeometry(QRect(202, 40, 35, 43));
        ybutton->setFont(font1);
        ybutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        tbutton = new QPushButton(Keypad);
        tbutton->setObjectName(QStringLiteral("tbutton"));
        tbutton->setGeometry(QRect(162, 40, 35, 43));
        tbutton->setFont(font1);
        tbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        xbutton = new QPushButton(Keypad);
        xbutton->setObjectName(QStringLiteral("xbutton"));
        xbutton->setGeometry(QRect(182, 140, 35, 39));
        xbutton->setFont(font1);
        xbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        donebutton = new QPushButton(Keypad);
        donebutton->setObjectName(QStringLiteral("donebutton"));
        donebutton->setGeometry(QRect(412, 93, 66, 43));
        donebutton->setFont(font1);
        donebutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"border-radius:10px;"));
        bbutton = new QPushButton(Keypad);
        bbutton->setObjectName(QStringLiteral("bbutton"));
        bbutton->setGeometry(QRect(202, 140, 35, 39));
        bbutton->setFont(font1);
        bbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        mbutton = new QPushButton(Keypad);
        mbutton->setObjectName(QStringLiteral("mbutton"));
        mbutton->setGeometry(QRect(282, 140, 35, 39));
        mbutton->setFont(font1);
        mbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        ubutton = new QPushButton(Keypad);
        ubutton->setObjectName(QStringLiteral("ubutton"));
        ubutton->setGeometry(QRect(242, 40, 35, 43));
        ubutton->setFont(font1);
        ubutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        bpbutton = new QPushButton(Keypad);
        bpbutton->setObjectName(QStringLiteral("bpbutton"));
        bpbutton->setGeometry(QRect(402, 40, 76, 43));
        bpbutton->setFont(font1);
        bpbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"border-radius:10px;"));
        lbutton = new QPushButton(Keypad);
        lbutton->setObjectName(QStringLiteral("lbutton"));
        lbutton->setGeometry(QRect(332, 92, 35, 43));
        lbutton->setFont(font1);
        lbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        abutton = new QPushButton(Keypad);
        abutton->setObjectName(QStringLiteral("abutton"));
        abutton->setGeometry(QRect(13, 92, 35, 43));
        abutton->setFont(font1);
        abutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        numbutton = new QPushButton(Keypad);
        numbutton->setObjectName(QStringLiteral("numbutton"));
        numbutton->setGeometry(QRect(2, 140, 35, 39));
        numbutton->setFont(font1);
        numbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        qbutton = new QPushButton(Keypad);
        qbutton->setObjectName(QStringLiteral("qbutton"));
        qbutton->setGeometry(QRect(2, 40, 35, 43));
        qbutton->setFont(font1);
        qbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        numbutton_2 = new QPushButton(Keypad);
        numbutton_2->setObjectName(QStringLiteral("numbutton_2"));
        numbutton_2->setGeometry(QRect(442, 140, 35, 39));
        numbutton_2->setFont(font1);
        numbutton_2->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        donebutton_2 = new QPushButton(Keypad);
        donebutton_2->setObjectName(QStringLiteral("donebutton_2"));
        donebutton_2->setGeometry(QRect(438, 190, 35, 41));
        donebutton_2->setFont(font1);
        donebutton_2->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"border-radius:10px;"));
        apostrophe = new QPushButton(Keypad);
        apostrophe->setObjectName(QStringLiteral("apostrophe"));
        apostrophe->setGeometry(QRect(372, 92, 35, 43));
        apostrophe->setFont(font1);
        apostrophe->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        comma = new QPushButton(Keypad);
        comma->setObjectName(QStringLiteral("comma"));
        comma->setGeometry(QRect(322, 140, 35, 39));
        comma->setFont(font1);
        comma->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        fstop = new QPushButton(Keypad);
        fstop->setObjectName(QStringLiteral("fstop"));
        fstop->setGeometry(QRect(362, 140, 35, 39));
        fstop->setFont(font1);
        fstop->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        question = new QPushButton(Keypad);
        question->setObjectName(QStringLiteral("question"));
        question->setGeometry(QRect(402, 140, 35, 39));
        question->setFont(font1);
        question->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        numbutton_3 = new QPushButton(Keypad);
        numbutton_3->setObjectName(QStringLiteral("numbutton_3"));
        numbutton_3->setGeometry(QRect(2, 190, 35, 40));
        numbutton_3->setFont(font1);
        numbutton_3->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        numbutton_4 = new QPushButton(Keypad);
        numbutton_4->setObjectName(QStringLiteral("numbutton_4"));
        numbutton_4->setGeometry(QRect(400, 190, 35, 41));
        numbutton_4->setFont(font1);
        numbutton_4->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        lineEdit = new QLineEdit(Keypad);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 10, 451, 23));
        vbutton->raise();
        zbutton->raise();
        cbutton->raise();
        pbutton->raise();
        ibutton->raise();
        jbutton->raise();
        spacebutton->raise();
        fbutton->raise();
        sbutton->raise();
        dbutton->raise();
        obutton->raise();
        kbutton->raise();
        nbutton->raise();
        wbutton->raise();
        gbutton->raise();
        ebutton->raise();
        rbutton->raise();
        hbutton->raise();
        ybutton->raise();
        tbutton->raise();
        xbutton->raise();
        donebutton->raise();
        bbutton->raise();
        mbutton->raise();
        ubutton->raise();
        bpbutton->raise();
        lbutton->raise();
        abutton->raise();
        numbutton->raise();
        numbutton_2->raise();
        donebutton_2->raise();
        apostrophe->raise();
        comma->raise();
        fstop->raise();
        question->raise();
        numbutton_3->raise();
        numbutton_4->raise();
        qbutton->raise();
        lineEdit->raise();

        retranslateUi(Keypad);

        QMetaObject::connectSlotsByName(Keypad);
    } // setupUi

    void retranslateUi(QDialog *Keypad)
    {
        Keypad->setWindowTitle(QApplication::translate("Keypad", "Dialog", 0));
        vbutton->setText(QApplication::translate("Keypad", "A", 0));
        zbutton->setText(QApplication::translate("Keypad", "A", 0));
        cbutton->setText(QApplication::translate("Keypad", "A", 0));
        pbutton->setText(QApplication::translate("Keypad", "A", 0));
        ibutton->setText(QApplication::translate("Keypad", "A", 0));
        jbutton->setText(QApplication::translate("Keypad", "A", 0));
        spacebutton->setText(QApplication::translate("Keypad", "A", 0));
        fbutton->setText(QApplication::translate("Keypad", "A", 0));
        sbutton->setText(QApplication::translate("Keypad", "A", 0));
        dbutton->setText(QApplication::translate("Keypad", "A", 0));
        obutton->setText(QApplication::translate("Keypad", "A", 0));
        kbutton->setText(QApplication::translate("Keypad", "A", 0));
        nbutton->setText(QApplication::translate("Keypad", "A", 0));
        wbutton->setText(QApplication::translate("Keypad", "A", 0));
        gbutton->setText(QApplication::translate("Keypad", "A", 0));
        ebutton->setText(QApplication::translate("Keypad", "A", 0));
        rbutton->setText(QApplication::translate("Keypad", "A", 0));
        hbutton->setText(QApplication::translate("Keypad", "A", 0));
        ybutton->setText(QApplication::translate("Keypad", "A", 0));
        tbutton->setText(QApplication::translate("Keypad", "A", 0));
        xbutton->setText(QApplication::translate("Keypad", "A", 0));
        donebutton->setText(QApplication::translate("Keypad", "A", 0));
        bbutton->setText(QApplication::translate("Keypad", "A", 0));
        mbutton->setText(QApplication::translate("Keypad", "A", 0));
        ubutton->setText(QApplication::translate("Keypad", "A", 0));
        bpbutton->setText(QApplication::translate("Keypad", "A", 0));
        lbutton->setText(QApplication::translate("Keypad", "A", 0));
        abutton->setText(QApplication::translate("Keypad", "A", 0));
        numbutton->setText(QApplication::translate("Keypad", "A", 0));
        qbutton->setText(QApplication::translate("Keypad", "A", 0));
        numbutton_2->setText(QApplication::translate("Keypad", "A", 0));
        donebutton_2->setText(QApplication::translate("Keypad", "A", 0));
        apostrophe->setText(QApplication::translate("Keypad", "A", 0));
        comma->setText(QApplication::translate("Keypad", "A", 0));
        fstop->setText(QApplication::translate("Keypad", "A", 0));
        question->setText(QApplication::translate("Keypad", "A", 0));
        numbutton_3->setText(QApplication::translate("Keypad", "A", 0));
        numbutton_4->setText(QApplication::translate("Keypad", "A", 0));
    } // retranslateUi

};

namespace Ui {
    class Keypad: public Ui_Keypad {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYPAD_H
