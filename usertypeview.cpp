#include "usertypeview.h"
#include "ui_usertypeview.h"

UserTypeView::UserTypeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserTypeView)
{
    ui->setupUi(this);
    ui->lineEdit->installEventFilter(this);
}

bool UserTypeView::showKeyPad(QLineEdit *line)

{

    /*
     *  Keypad object is by default moved to 0,392
     *  was built for 800x600 resolution
     *
     * */


    line->removeEventFilter(this);

    k=new Keypad(line,this);

    k->move(0,60);

    if(k->exec() == QDialog::Accepted)

        line->installEventFilter(this);

    return true;

}
bool UserTypeView::eventFilter(QObject *obj, QEvent *e)
{
    /*
     * Event filter that gets called if the lineedit in the ui is clicked
     * you can add more line edits through an else if construct
     * */

    if(e->type() == QEvent::MouseButtonPress){

        if(obj == ui->lineEdit){


            showKeyPad(ui->lineEdit);

        }


        else

            return false;

    }


}

UserTypeView::~UserTypeView()
{
    delete ui;
}
