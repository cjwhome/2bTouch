#include "keypad.h"
#include "ui_keypad.h"

Keypad::Keypad(QLineEdit *line,bool tgl,QWidget *parent) :
        QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::Keypad)
{

    ui->setupUi(this);

    //this->setAttribute(Qt::WA_DeleteOnClose,true);

    toggle = false;     //change this to true if want to set all first characters to uppercase

    t1= false;

    pad_edit=line;
    //ui->lineEdit = pad_edit;

    if(toggle)

        setsymbol();

    else

        setalphabet();

    //connect(pad_edit, SIGNAL(cursorPositionChanged(int,int)), this, SLOT(show()));
    //connect(pad_edit, SIGNAL(cursorPositionChanged(int,int)), this, SLOT(setalphabet()));
    //connect(this, SIGNAL(accepted()), this, SLOT(seta));


    connect ( ui->abutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->bbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->cbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->dbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->ebutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->fbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->gbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->hbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->ibutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->jbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );


    connect ( ui->kbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->lbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->mbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->nbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->obutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->pbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->qbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->rbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->sbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->tbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->ubutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->vbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->wbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->xbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->ybutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->zbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    //connect ( ui->clrbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->bpbutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    ui->bpbutton->setText("BACK");

    connect ( ui->numbutton, SIGNAL( clicked() ), this, SLOT(symbolChange()) );

    connect ( ui->numbutton_2, SIGNAL( clicked() ), this, SLOT(symbolChange()) );

    connect ( ui->spacebutton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );

    connect ( ui->donebutton, SIGNAL( clicked() ), this, SLOT(keyclose()) );

    connect ( ui->donebutton_2, SIGNAL( clicked() ), this, SLOT(keyclose()) );

    connect ( ui->apostrophe, SIGNAL( clicked() ), this, SLOT(keypadHandler()) );

    connect ( ui->comma, SIGNAL( clicked() ), this, SLOT(keypadHandler()) );

    connect ( ui->fstop, SIGNAL( clicked() ), this, SLOT(keypadHandler()) );

    connect ( ui->question, SIGNAL( clicked() ), this, SLOT(keypadHandler()) );

    connect( ui->numbutton_3,SIGNAL(clicked()),this,SLOT(boardchange()));

    connect( ui->numbutton_4,SIGNAL(clicked()),this,SLOT(boardchange()));

    setStyleSheet("background-image: url(:/keyboard/keyboard/Touch-Keyboard-white-Line.png);");
    //setStyleSheet(":/keyboard/keyboard/Touch-Keyboard-white.png");


}

void Keypad::boardchange()

{

    if(t1)

    {

        setalphabet();

        t1=false;
    }

    else

    {
        setnumeric();
        t1=true;
    }

}

void Keypad::setnumeric()

{

    //setStyleSheet("background-image: url(480x200/Touch-Keyboard2.png);");
    setStyleSheet(" background-image: url(:/keyboard/keyboard/Touch-Keyboard2-Line.png);");

    ui->abutton->setText("-");

    ui->bbutton->setText("'");

    ui->cbutton->setText("?");

    ui->dbutton->setText(":");

    ui->ebutton->setText("3");

    ui->fbutton->setText(";");

    ui->gbutton->setText("(");

    ui->hbutton->setText(")");

    ui->ibutton->setText("8");

    ui->jbutton->setText("$");

    ui->kbutton->setText("&");

    ui->lbutton->setText("@");

    ui->mbutton->setText("#");

    ui->nbutton->setText("\"");

    ui->obutton->setText("9");

    ui->pbutton->setText("0");

    ui->qbutton->setText("1");

    ui->rbutton->setText("4");

    ui->sbutton->setText("/");

    ui->tbutton->setText("5");

    ui->ubutton->setText("7");

    ui->vbutton->setText("!");

    ui->wbutton->setText("2");

    ui->xbutton->setText(",");

    ui->ybutton->setText("6");

    ui->zbutton->setText(".");

    ui->numbutton->setText("CAPS");

    ui->comma->setText("_");



    ui->apostrophe->setEnabled(0);

    ui->fstop->setEnabled(0);

    ui->question->setEnabled(0);

    ui->numbutton->setEnabled(0);

    ui->numbutton_2->setEnabled(0);



}

Keypad::~Keypad()

{

    delete ui;

}

void Keypad::keypadHandler()

{

    QPushButton *button = (QPushButton *)sender();

    QString inputText = button->text();

    if(pad_edit != NULL){

        if (inputText == "SPACE")

        {

            ui->lineEdit->insert(" ");

            //setsymbol();

        }

        else if(inputText == "BACK")

        {

            ui->lineEdit->backspace();

        }

        else if(inputText == "CLR")

        {

            ui->lineEdit->clear();

        }

        else

        {

            if(ui->lineEdit->text().isEmpty()){

                //pad_edit->insert(inputText.toUpper());
                ui->lineEdit->insert(inputText);
                if(t1)

                    setnumeric();
                //else

                    //setalphabet();

            }

            else if(!pad_edit->text().isEmpty()){

                int currentPos = ui->lineEdit->cursorPosition();

                QString currentText = ui->lineEdit->text();

                QChar currentChar;

                if(currentPos >= 1){

                    currentChar = currentText.at(currentPos-1);

                    if(currentChar == ' ' || currentChar == ',')

                    {

                        ui->lineEdit->insert(inputText.toUpper());


                        if(t1)

                            setnumeric();
                        //else

                            //setalphabet();

                    }

                    else

                    {
                        ui->lineEdit->insert(inputText);

                        if(t1)

                            setnumeric();
                        //else

                            //setalphabet();
                    }
                } else {

                    //pad_edit->insert(inputText.toUpper());
                    ui->lineEdit->insert(inputText);

                    if(t1)

                        setnumeric();
                    //else

                        //setalphabet();



                }


            }

        }

    }
    pad_edit->setText(ui->lineEdit->text());
    //ui->lineEdit->setText(pad_edit->text());

}

void Keypad::setalphabet()

{

    //setStyleSheet("background-image: url(480x200/Touch-Keyboard.png);");
    this->setStyleSheet(" background-image: url(:/keyboard/keyboard/Touch-Keyboard-Line.png);");

    ui->abutton->setText("a");

    ui->bbutton->setText("b");

    ui->cbutton->setText("c");

    ui->dbutton->setText("d");

    ui->ebutton->setText("e");

    ui->fbutton->setText("f");

    ui->gbutton->setText("g");

    ui->hbutton->setText("h");

    ui->ibutton->setText("i");

    ui->jbutton->setText("j");

    ui->kbutton->setText("k");

    ui->lbutton->setText("l");

    ui->mbutton->setText("m");

    ui->nbutton->setText("n");

    ui->obutton->setText("o");

    ui->pbutton->setText("p");

    ui->qbutton->setText("q");

    ui->rbutton->setText("r");

    ui->sbutton->setText("s");

    ui->tbutton->setText("t");

    ui->ubutton->setText("u");


    ui->vbutton->setText("v");

    ui->wbutton->setText("w");

    ui->xbutton->setText("x");

    ui->ybutton->setText("y");

    ui->zbutton->setText("z");

    ui->numbutton->setText("CAPS");

    ui->comma->setText(",");

    ui->apostrophe->setText("'");

    ui->fstop->setText(".");

    ui->question->setText("?");

    ui->spacebutton->setText("SPACE");

    ui->apostrophe->setEnabled(1);

    ui->fstop->setEnabled(1);

    ui->question->setEnabled(1);

    ui->numbutton->setEnabled(1);

    ui->numbutton_2->setEnabled(1);

}

void Keypad::setsymbol()

{

   // setStyleSheet("background-image: url(480x200/Touch-Keyboard1.png);");
    setStyleSheet("background-image: url(:/keyboard/keyboard/Touch-Keyboard1-Line.png);");

    ui->abutton->setText("A");

    ui->bbutton->setText("B");

    ui->cbutton->setText("C");



    ui->dbutton->setText("D");

    ui->ebutton->setText("E");

    ui->fbutton->setText("F");



    ui->gbutton->setText("G");

    ui->hbutton->setText("H");

    ui->ibutton->setText("I");



    ui->jbutton->setText("J");

    ui->kbutton->setText("K");

    ui->lbutton->setText("L");



    ui->mbutton->setText("M");

    ui->nbutton->setText("N");

    ui->obutton->setText("O");



    ui->pbutton->setText("P");

    ui->qbutton->setText("Q");

    ui->rbutton->setText("R");



    ui->sbutton->setText("S");

    ui->tbutton->setText("T");

    ui->ubutton->setText("U");



    ui->vbutton->setText("V");

    ui->wbutton->setText("W");

    ui->xbutton->setText("X");

    ui->ybutton->setText("Y");

    ui->zbutton->setText("Z");

    ui->fstop->setText(".");


    ui->numbutton->setText("CAPS");

    ui->comma->setText(",");

    ui->apostrophe->setText(QString('"'));

    ui->apostrophe->setEnabled(1);

    ui->fstop->setEnabled(1);

    ui->question->setEnabled(1);

    ui->numbutton->setEnabled(1);

    ui->numbutton_2->setEnabled(1);

}

void Keypad::symbolChange()

{

    if(toggle){

        setsymbol();

        toggle = false;

    }

    else{

        setalphabet();

        toggle = true;

    }

}

void Keypad::keyclose()

{
    pad_edit->setText(ui->lineEdit->text());

    this->done(QDialog::Accepted);

}
