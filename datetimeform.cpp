#include "datetimeform.h"
#include "ui_datetimeform.h"

DateTimeForm * DateTimeForm::form = nullptr;

//Returns a singlton to this form, Makes it easy to update/change
DateTimeForm * DateTimeForm::getForm(){
    //qDebug() << "Accessing DateTimeForm";
    if(form == nullptr)//If the static reference is null create a new instance and set to static reference
        form = new DateTimeForm();
    return form;//Returns the static reference(singleton)
}

DateTimeForm::DateTimeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateTimeForm){
    ui->setupUi(this);
    QWidget::setWindowFlags(Qt::CustomizeWindowHint);
    form = this;

    connect(this, SIGNAL(addSecond()), this, SLOT(updateDis()));//This is used to allow the thread in grab data to update the ui element
}

DateTimeForm::~DateTimeForm(){
    delete ui;
}

//Updates the date and time with new values
void DateTimeForm::getCurrent(int h, int mi, int s, int m, int d, int y){
    hour = h;
    min = mi;
    sec = s;
    month = m;
    day = d;
    year = y%100;//Only 2 digits so this removes anymore
    updateDisplay(); //Adds a second, but this should not cause any issues because this is updated slightly slower than every second
}

//This is called by the grab data class in the loop that runs roughly every second
void DateTimeForm::updateDisplay(){
    sec += 1; //Add one second to keep the time current
    if(sec == 60){ //Only 60 seconds in a minute so set sec to 0 and add a minute
        sec = 00;
        min += 1;
        if(min == 60){ //Only 60 mins in an hour to set min to 0 and add an hour
            min = 0;
            hour += 1;
            if(hour == 24){ //Only 24 hours in a day so set hout to 0 and add a day
                hour = 0;
                day += 1;
                if(day == daysInMonth()){ //Days in month returns the days in the month based on the current month
                    day = 1;
                    month += 1;
                    if(month == 13){ //Reset month to 1 when it hits 13 and add a year
                        month = 1;
                        year += 1;
                    }
                }
            }
        }
    }
    updateDate(); //Updates the date text field
    updateTime(); //Updates the time text field
}

//This is called by the grab data class in the loop that runs roughly every second
void DateTimeForm::updateDis(){
    sec += 1; //Add one second to keep the time current
    if(sec == 60){ //Only 60 seconds in a minute so set sec to 0 and add a minute
        sec = 00;
        min += 1;
        if(min == 60){ //Only 60 mins in an hour to set min to 0 and add an hour
            min = 00;
            hour += 1;
            if(hour == 24){ //Only 24 hours in a day so set hout to 0 and add a day
                hour = 00;
                day += 1;
                if(day == daysInMonth()){ //Days in month returns the days in the month based on the current month
                    day = 01;
                    month += 1;
                    if(month == 13){ //Reset month to 1 when it hits 13 and add a year
                        month = 01;
                        year += 1;
                    }
                }
            }
        }
    }
    updateDate(); //Updates the date text field
    updateTime(); //Updates the time text field
}

//This updates the time text field and makes sure that it is formated correctly
void DateTimeForm::updateTime(){
    QString * s;
    QString * s4;
    QString * s5;

    //makes sure that hour has 2 digits
    if(hour >= 10)
        s = new QString(QString::number(hour));
    else
        s = new QString("0" + QString::number(hour));

    //Makes sure that min has 2 digits
    if(min >= 10)
        s4 = new QString(QString::number(min));
    else
        s4 = new QString("0" + QString::number(min));

    //makes sure that sec has 2 digits
    if(sec >= 10)
        s5 = new QString(QString::number(sec));
    else
        s5 = new QString("0" + QString::number(sec));

    //The currentTIndex is used to show which value the used is updating and highlight that portion blue
    //Less memory intensive than flashing
    //If change to flashing just have the grab data form call this as well and change the index portion to 2 spaces and back
    if(currentTIndex == 0)
        ui->time->setText("<font color='blue'>" + QString(*s) +"</font>:"+ *s4 +":" + *s5);
    else if(currentTIndex == 1)
        ui->time->setText(*s+":<font color='blue'>"+*s4+"</font>:"+ * s5);
    else
        ui->time->setText(*s+":"+*s4+":<font color='blue'>"+ *s5 + "</font>");
}

//This updates the date text field and makes sure that it is formated correctly
void DateTimeForm::updateDate(){
    QString * s;
    QString * s2;
    QString * s3;

    //Makes sure that day has 2 digits
    if(day >= 10)
        s = new QString(QString::number(day));
    else
        s = new QString("0" + QString::number(day));

    //Makes sure that month has 2 digits
    if(month >= 10)
        s2 = new QString(QString::number(month));
    else
        s2 = new QString("0" + QString::number(month));

    //Makes sure that year has 2 digits
    if(year >= 10)
        s3 = new QString(QString::number(year));
    else
        s3 = new QString("0" + QString::number(year));

    //The currentCIndex is used to show which value the used is updating and highlight that portion blue
    //Less memory intensive than flashing
    //If change to flashing just have the grab data form call this as well and change the index portion to 2 spaces and back
    switch (currentCIndex){
    case 0:
        ui->Date->setText("<font color='blue'>" + *s2+"</font>/"+*s+"/"+*s3);
        break;
    case 1:
        ui->Date->setText(*s2+"/<font color='blue'>"+*s+"</font>/"+*s3);
        break;
    case 2:
        ui->Date->setText(*s2+"/"+*s+"/<font color='blue'>"+*s3 + "</font>");
        break;
    }
}

void DateTimeForm::on_home_clicked(){
    hide();
}

//Used to change the currently shown form
void DateTimeForm::on_gonext_clicked(){
    UiManager * ui = UiManager::getManager();
    if(ui->currentSIndex + 1 == ui->settingWidgets->count())
        ui->currentSIndex = 0;
    else
        ui->currentSIndex += 1;

    ui->cWidget->hide();
    ui->cWidget = ui->settingWidgets->at(ui->currentSIndex);
    ui->cWidget->show();
}

//Used to change the currently shown form
void DateTimeForm::on_goPrev_clicked(){
    UiManager * ui = UiManager::getManager();
    if(ui->currentSIndex - 1 == -1)
        ui->currentSIndex = ui->settingWidgets->count() - 1;
    else
        ui->currentSIndex -= 1;

    ui->cWidget->hide();
    ui->cWidget = ui->settingWidgets->at(ui->currentSIndex);
    ui->cWidget->show();
}

//Move the time index to the right and color it blue
void DateTimeForm::on_mRightT_clicked(){
    if(currentTIndex != 2)
        currentTIndex++;
    else
        currentTIndex = 0;
    updateTime();
}

//Move the time index to the left and color it blue
void DateTimeForm::on_mLeftT_clicked(){
    if(currentTIndex != 0)
        currentTIndex--;
    else
        currentTIndex = 2;
    updateTime();
}

//This handles updating the value of the current index when the increase button is tapped
void DateTimeForm::on_increaseT_clicked(){
    switch (currentTIndex){
    case 0:
        if(hour >= 23)
            hour = 0;
        else
            hour++;
        break;
    case 1:
        if(min >= 59)
            min = 0;
        else
            min++;
        break;
    case 2:
        if(sec >= 59)
            sec = 0;
        else
            sec++;
        break;
    }
    updateTime();
}

//This handles updating the value of the current index when the decrease button is tapped
void DateTimeForm::on_decreaseT_clicked(){
    switch (currentTIndex){
    case 0:
        if(hour <= 0)
            hour = 23;
        else
            hour--;
        break;
    case 1:
        if(min <= 0)
            min = 59;
        else
            min--;
        break;
    case 2:
        if(sec <= 0)
            sec = 59;
        else
            sec--;
        break;
    }
    updateTime();
}

//This handles changing the values for the selected index when the increase button is clicked
void DateTimeForm::on_increaseC_clicked(){
    switch (currentCIndex){
    case 0:
        if(month < 12){
            month++;
            if(day > daysInMonth()){
                day = daysInMonth();
            }
        }else{
            month = 1;
            if(day > daysInMonth()){
                day = daysInMonth();
            }
        }
        break;
    case 1:
        if(day < daysInMonth())
            day++;
        else
            day = 1;
        break;
    case 2:
        if(year < 99)
            year++;
        else
            year = 0;
        break;
    }
    updateDate();
}

//This handles changing the values for the selected index when the decrease button is clicked
void DateTimeForm::on_decreaseC_clicked()
{
    switch (currentCIndex){
    case 0:
        if(month > 1){
            month--;
            if(day > daysInMonth())
            {
                day = daysInMonth();
            }
        }else{
            month = 12;
            if(day > daysInMonth()){
                day = daysInMonth();
            }
        }
        break;
    case 1:
        if(day > 1)
            day--;
        else
            day = daysInMonth();
        break;
    case 2:
        if(year > 0)
            year--;
        else
            year = 99;
        break;
    }
    updateDate();
}

//Moves the calendar index to the right and updates the selection
void DateTimeForm::on_mRightC_clicked(){
    if(currentCIndex < 2)
        currentCIndex++;
    else
        currentCIndex = 0;
    updateDate();
}

//Moves the calendar index to the left and updates the selection
void DateTimeForm::on_mLeftC_clicked(){
    if(currentCIndex > 0)
        currentCIndex--;
    else
        currentCIndex = 2;
    updateDate();
}

//This returns the number of days in each month
//There is no check for leap year
int DateTimeForm::daysInMonth(){
    switch (month){
    case 1:
        return 31;
    case 2:
        return 28;
    case 3:
        return 31;
    case 4:
        return 30;
    case 5:
        return 31;
    case 6:
        return 30;
    case 7:
        return 31;
    case 8:
        return 31;
    case 9:
        return 30;
    case 10:
        return 31;
    case 11:
        return 30;
    case 12:
        return 31;
    default:
        return -1;
    }
}

//Use this to get the proper format for the output string
QString DateTimeForm::stripString(QString s){
    QStringList list;
    list = s.split(QRegExp("\\s+")); //This will split the string based on spacing

    QString n;

    //Remove the spaces and " added by the QString::Number function, if present
    for(int i = 0; i < list.size(); i++){
        QString t;
        for(int j = 0; j < list.at(i).size(); j++){
            if(list.at(i).at(j) != ' ' && list.at(i).at(j) != '"'){
                t += list.at(i).at(j);
            }
        }
        if(t.size() == 1)
            t = "0" + t;
        n += t;
        //list.replace(i, n);
    }
    //qDebug() << list;
    return n;
}

//The pcb reads it in as hhmmssddmmyy
//Need to add check for single character numbers ie 1 instead of 01
void DateTimeForm::on_save_clicked(){
    //qDebug() << "Would send: " + (QString::number(day) + "," + QString::number(month) + "," + QString::number(year) + "," + QString::number(sec) + "," + QString::number(min) + "," + QString::number(hour));
    //QTextStream(stdout) << "*D" << stripString(QString::number(hour) + " " + QString::number(min) + " " + QString::number(sec) + " " + QString::number(day) + " " + QString::number(month) + " " + QString::number(year));

    QThread * thread = new QThread();
    SerialHandler::getHandler(thread, this)->writeLine("*D" + stripString(QString::number(hour) + " " + QString::number(min) + " " + QString::number(sec) + " " + QString::number(day) + " " + QString::number(month) + " " + QString::number(year)));
}

QString DateTimeForm::returnCurrent(){
    return QString::number(hour) + "," + QString::number(min) + "," + QString::number(sec) + "," + QString::number(day) + "," + QString::number(month) + "," + QString::number(year);
}

void DateTimeForm::addSec(){
    //emit signal to update display since grab data runs a thread which means that it is not allowed to change ui elements because it is a thread
    emit addSecond();
}
