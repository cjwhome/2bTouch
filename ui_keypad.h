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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Keypad
{
public:
    QPushButton *obutton;
    QPushButton *tbutton;
    QPushButton *fstop;
    QPushButton *fbutton;
    QPushButton *wbutton;
    QPushButton *donebutton;
    QPushButton *bpbutton;
    QPushButton *numbutton_2;
    QPushButton *numbutton;
    QPushButton *nbutton;
    QPushButton *ubutton;
    QPushButton *lbutton;
    QPushButton *cbutton;
    QPushButton *rbutton;
    QPushButton *donebutton_2;
    QPushButton *dbutton;
    QPushButton *mbutton;
    QPushButton *comma;
    QPushButton *apostrophe;
    QPushButton *bbutton;
    QPushButton *ibutton;
    QPushButton *numbutton_4;
    QPushButton *ybutton;
    QLineEdit *lineEdit;
    QPushButton *jbutton;
    QPushButton *kbutton;
    QPushButton *vbutton;
    QLabel *label;
    QPushButton *hbutton;
    QPushButton *question;
    QPushButton *numbutton_3;
    QPushButton *xbutton;
    QPushButton *spacebutton;
    QPushButton *zbutton;
    QPushButton *gbutton;
    QPushButton *qbutton;
    QPushButton *abutton;
    QPushButton *pbutton;
    QPushButton *sbutton;
    QPushButton *ebutton;

    void setupUi(QWidget *Keypad)
    {
        if (Keypad->objectName().isEmpty())
            Keypad->setObjectName(QStringLiteral("Keypad"));
        Keypad->resize(480, 238);
        Keypad->setStyleSheet(QStringLiteral(""));
        obutton = new QPushButton(Keypad);
        obutton->setObjectName(QStringLiteral("obutton"));
        obutton->setGeometry(QRect(320, 40, 35, 43));
        QFont font;
        font.setPointSize(1);
        font.setBold(true);
        font.setWeight(75);
        obutton->setFont(font);
        obutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"border-radius:10px;"));
        tbutton = new QPushButton(Keypad);
        tbutton->setObjectName(QStringLiteral("tbutton"));
        tbutton->setGeometry(QRect(160, 40, 35, 43));
        tbutton->setFont(font);
        tbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        fstop = new QPushButton(Keypad);
        fstop->setObjectName(QStringLiteral("fstop"));
        fstop->setGeometry(QRect(360, 140, 35, 39));
        fstop->setFont(font);
        fstop->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        fbutton = new QPushButton(Keypad);
        fbutton->setObjectName(QStringLiteral("fbutton"));
        fbutton->setGeometry(QRect(130, 92, 35, 42));
        fbutton->setFont(font);
        fbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        wbutton = new QPushButton(Keypad);
        wbutton->setObjectName(QStringLiteral("wbutton"));
        wbutton->setGeometry(QRect(40, 40, 35, 43));
        wbutton->setFont(font);
        wbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        donebutton = new QPushButton(Keypad);
        donebutton->setObjectName(QStringLiteral("donebutton"));
        donebutton->setGeometry(QRect(410, 93, 66, 43));
        donebutton->setFont(font);
        donebutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"border-radius:10px;"));
        bpbutton = new QPushButton(Keypad);
        bpbutton->setObjectName(QStringLiteral("bpbutton"));
        bpbutton->setGeometry(QRect(400, 40, 76, 43));
        bpbutton->setFont(font);
        bpbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"border-radius:10px;"));
        numbutton_2 = new QPushButton(Keypad);
        numbutton_2->setObjectName(QStringLiteral("numbutton_2"));
        numbutton_2->setGeometry(QRect(440, 140, 35, 39));
        numbutton_2->setFont(font);
        numbutton_2->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        numbutton = new QPushButton(Keypad);
        numbutton->setObjectName(QStringLiteral("numbutton"));
        numbutton->setGeometry(QRect(0, 140, 35, 39));
        numbutton->setFont(font);
        numbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        nbutton = new QPushButton(Keypad);
        nbutton->setObjectName(QStringLiteral("nbutton"));
        nbutton->setGeometry(QRect(240, 140, 35, 39));
        nbutton->setFont(font);
        nbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        ubutton = new QPushButton(Keypad);
        ubutton->setObjectName(QStringLiteral("ubutton"));
        ubutton->setGeometry(QRect(240, 40, 35, 43));
        ubutton->setFont(font);
        ubutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        lbutton = new QPushButton(Keypad);
        lbutton->setObjectName(QStringLiteral("lbutton"));
        lbutton->setGeometry(QRect(330, 92, 35, 43));
        lbutton->setFont(font);
        lbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        cbutton = new QPushButton(Keypad);
        cbutton->setObjectName(QStringLiteral("cbutton"));
        cbutton->setGeometry(QRect(120, 140, 35, 39));
        cbutton->setFont(font);
        cbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        rbutton = new QPushButton(Keypad);
        rbutton->setObjectName(QStringLiteral("rbutton"));
        rbutton->setGeometry(QRect(120, 40, 35, 43));
        rbutton->setFont(font);
        rbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        donebutton_2 = new QPushButton(Keypad);
        donebutton_2->setObjectName(QStringLiteral("donebutton_2"));
        donebutton_2->setGeometry(QRect(436, 190, 35, 41));
        donebutton_2->setFont(font);
        donebutton_2->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"border-radius:10px;"));
        dbutton = new QPushButton(Keypad);
        dbutton->setObjectName(QStringLiteral("dbutton"));
        dbutton->setGeometry(QRect(90, 92, 35, 43));
        dbutton->setFont(font);
        dbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        mbutton = new QPushButton(Keypad);
        mbutton->setObjectName(QStringLiteral("mbutton"));
        mbutton->setGeometry(QRect(280, 140, 35, 39));
        mbutton->setFont(font);
        mbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        comma = new QPushButton(Keypad);
        comma->setObjectName(QStringLiteral("comma"));
        comma->setGeometry(QRect(320, 140, 35, 39));
        comma->setFont(font);
        comma->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        apostrophe = new QPushButton(Keypad);
        apostrophe->setObjectName(QStringLiteral("apostrophe"));
        apostrophe->setGeometry(QRect(370, 92, 35, 43));
        apostrophe->setFont(font);
        apostrophe->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        bbutton = new QPushButton(Keypad);
        bbutton->setObjectName(QStringLiteral("bbutton"));
        bbutton->setGeometry(QRect(200, 140, 35, 39));
        bbutton->setFont(font);
        bbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        ibutton = new QPushButton(Keypad);
        ibutton->setObjectName(QStringLiteral("ibutton"));
        ibutton->setGeometry(QRect(280, 40, 35, 43));
        ibutton->setFont(font);
        ibutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        numbutton_4 = new QPushButton(Keypad);
        numbutton_4->setObjectName(QStringLiteral("numbutton_4"));
        numbutton_4->setGeometry(QRect(398, 190, 35, 41));
        numbutton_4->setFont(font);
        numbutton_4->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        ybutton = new QPushButton(Keypad);
        ybutton->setObjectName(QStringLiteral("ybutton"));
        ybutton->setGeometry(QRect(200, 40, 35, 43));
        ybutton->setFont(font);
        ybutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        lineEdit = new QLineEdit(Keypad);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(18, 10, 161, 23));
        jbutton = new QPushButton(Keypad);
        jbutton->setObjectName(QStringLiteral("jbutton"));
        jbutton->setGeometry(QRect(250, 92, 35, 43));
        jbutton->setFont(font);
        jbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        kbutton = new QPushButton(Keypad);
        kbutton->setObjectName(QStringLiteral("kbutton"));
        kbutton->setGeometry(QRect(290, 92, 35, 43));
        kbutton->setFont(font);
        kbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        vbutton = new QPushButton(Keypad);
        vbutton->setObjectName(QStringLiteral("vbutton"));
        vbutton->setGeometry(QRect(160, 140, 35, 39));
        vbutton->setFont(font);
        vbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        label = new QLabel(Keypad);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(198, 10, 261, 21));
        hbutton = new QPushButton(Keypad);
        hbutton->setObjectName(QStringLiteral("hbutton"));
        hbutton->setGeometry(QRect(210, 92, 35, 43));
        hbutton->setFont(font);
        hbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        question = new QPushButton(Keypad);
        question->setObjectName(QStringLiteral("question"));
        question->setGeometry(QRect(400, 140, 35, 39));
        question->setFont(font);
        question->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        numbutton_3 = new QPushButton(Keypad);
        numbutton_3->setObjectName(QStringLiteral("numbutton_3"));
        numbutton_3->setGeometry(QRect(0, 190, 35, 40));
        numbutton_3->setFont(font);
        numbutton_3->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        xbutton = new QPushButton(Keypad);
        xbutton->setObjectName(QStringLiteral("xbutton"));
        xbutton->setGeometry(QRect(75, 140, 35, 39));
        xbutton->setFont(font);
        xbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        spacebutton = new QPushButton(Keypad);
        spacebutton->setObjectName(QStringLiteral("spacebutton"));
        spacebutton->setGeometry(QRect(120, 190, 233, 41));
        spacebutton->setFont(font);
        spacebutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"\n"
"border-radius:10px;"));
        zbutton = new QPushButton(Keypad);
        zbutton->setObjectName(QStringLiteral("zbutton"));
        zbutton->setGeometry(QRect(40, 140, 35, 39));
        zbutton->setFont(font);
        zbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        gbutton = new QPushButton(Keypad);
        gbutton->setObjectName(QStringLiteral("gbutton"));
        gbutton->setGeometry(QRect(170, 92, 35, 43));
        gbutton->setFont(font);
        gbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        qbutton = new QPushButton(Keypad);
        qbutton->setObjectName(QStringLiteral("qbutton"));
        qbutton->setGeometry(QRect(0, 40, 35, 43));
        qbutton->setFont(font);
        qbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        abutton = new QPushButton(Keypad);
        abutton->setObjectName(QStringLiteral("abutton"));
        abutton->setGeometry(QRect(11, 92, 35, 43));
        abutton->setFont(font);
        abutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        pbutton = new QPushButton(Keypad);
        pbutton->setObjectName(QStringLiteral("pbutton"));
        pbutton->setGeometry(QRect(360, 40, 35, 43));
        pbutton->setFont(font);
        pbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        sbutton = new QPushButton(Keypad);
        sbutton->setObjectName(QStringLiteral("sbutton"));
        sbutton->setGeometry(QRect(50, 92, 35, 43));
        sbutton->setFont(font);
        sbutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));
        ebutton = new QPushButton(Keypad);
        ebutton->setObjectName(QStringLiteral("ebutton"));
        ebutton->setGeometry(QRect(80, 40, 35, 43));
        ebutton->setFont(font);
        ebutton->setStyleSheet(QLatin1String("background-image: url(:/images/empty.png);\n"
"color: rgb(255, 255, 0);\n"
"border-radius:10px;"));

        retranslateUi(Keypad);

        QMetaObject::connectSlotsByName(Keypad);
    } // setupUi

    void retranslateUi(QWidget *Keypad)
    {
        Keypad->setWindowTitle(QApplication::translate("Keypad", "Form", 0));
        obutton->setText(QApplication::translate("Keypad", "A", 0));
        tbutton->setText(QApplication::translate("Keypad", "A", 0));
        fstop->setText(QApplication::translate("Keypad", "A", 0));
        fbutton->setText(QApplication::translate("Keypad", "A", 0));
        wbutton->setText(QApplication::translate("Keypad", "A", 0));
        donebutton->setText(QApplication::translate("Keypad", "A", 0));
        bpbutton->setText(QApplication::translate("Keypad", "A", 0));
        numbutton_2->setText(QApplication::translate("Keypad", "A", 0));
        numbutton->setText(QApplication::translate("Keypad", "A", 0));
        nbutton->setText(QApplication::translate("Keypad", "A", 0));
        ubutton->setText(QApplication::translate("Keypad", "A", 0));
        lbutton->setText(QApplication::translate("Keypad", "A", 0));
        cbutton->setText(QApplication::translate("Keypad", "A", 0));
        rbutton->setText(QApplication::translate("Keypad", "A", 0));
        donebutton_2->setText(QApplication::translate("Keypad", "A", 0));
        dbutton->setText(QApplication::translate("Keypad", "A", 0));
        mbutton->setText(QApplication::translate("Keypad", "A", 0));
        comma->setText(QApplication::translate("Keypad", "A", 0));
        apostrophe->setText(QApplication::translate("Keypad", "A", 0));
        bbutton->setText(QApplication::translate("Keypad", "A", 0));
        ibutton->setText(QApplication::translate("Keypad", "A", 0));
        numbutton_4->setText(QApplication::translate("Keypad", "A", 0));
        ybutton->setText(QApplication::translate("Keypad", "A", 0));
        jbutton->setText(QApplication::translate("Keypad", "A", 0));
        kbutton->setText(QApplication::translate("Keypad", "A", 0));
        vbutton->setText(QApplication::translate("Keypad", "A", 0));
        label->setText(QApplication::translate("Keypad", "Use Keypad to enter new value", 0));
        hbutton->setText(QApplication::translate("Keypad", "A", 0));
        question->setText(QApplication::translate("Keypad", "A", 0));
        numbutton_3->setText(QApplication::translate("Keypad", "A", 0));
        xbutton->setText(QApplication::translate("Keypad", "A", 0));
        spacebutton->setText(QApplication::translate("Keypad", "A", 0));
        zbutton->setText(QApplication::translate("Keypad", "A", 0));
        gbutton->setText(QApplication::translate("Keypad", "A", 0));
        qbutton->setText(QApplication::translate("Keypad", "A", 0));
        abutton->setText(QApplication::translate("Keypad", "A", 0));
        pbutton->setText(QApplication::translate("Keypad", "A", 0));
        sbutton->setText(QApplication::translate("Keypad", "A", 0));
        ebutton->setText(QApplication::translate("Keypad", "A", 0));
    } // retranslateUi

};

namespace Ui {
    class Keypad: public Ui_Keypad {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYPAD_H
