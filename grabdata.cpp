#include "grabdata.h"

//Singleton is used for ease of access by other programs
GrabData * GrabData::manager = nullptr;

GrabData::GrabData(QObject * parent) : QThread (parent){
    restart = false;
    abort = false;
    //QTextStream(stdout) << "**"; //Signal to the board to send back all data
}

//This is used to access the class, if the class hasnt been initialized it initializes it and return the manager
//static function
GrabData * GrabData::getManager(){
    //qDebug() << "Accessing grab data";
    if(manager == nullptr){
        manager = new GrabData();
    }
    return manager;
}

//Starts/restarts the thread getting data
void GrabData::getData(){
    if(!isRunning()){
        start(LowPriority);
    }else{
        restart = true;
        condition->wakeOne();
    }
}

//Delays the tread for 1 sec
void GrabData::delay(){
    QTime dieTime = QTime::currentTime().addSecs(1);
    while(QTime::currentTime() < dieTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

//1 sec between every iteration so it takes longer based on every function added
void GrabData::run(){
    //int cInd = 0;
    //Forever is a loop that doesnt end
    forever{
        //qDebug() << "running";
        //emit updateDView();
        //StatsAverageForm::getForm()->updateAvg();
        //qDebug() << "Running " << cInd++;
        DateTimeForm::getForm()->addSec();//Work around for threads being unable to change ui elements
        delay();
    }
}

//Working on
//It might be worth having this function read in the line every time and send the resulting string to where it needs to go
//Would remove the potential issue of either function reading the wrong data in and either hitting an error or losing the line
//CalForm, AnalogForm, DateTimeForm, ModForm, AverageForm, ModBusForm, NetworkForm
//This fucntion reads in the output from the console and parses it.  It then starts the function designated by the pcb
void GrabData::checkForSignal(){
    //QString * line = nullptr;
    int c = getchar();
    //During testing getchar would return first 13 and then 10 which caused it to repeat more times than necessary
    //or in this case skip the line entirely
    //Need to find offset values
    //'\n' == 10
    if(c == 13){
        c = getchar();
    }
    if(c == 10){
        c = getchar();
    }
    //printf("%c \n", c, c);
    if(c == '*'){ //'*' signals that this line contains a function
        c = getchar(); //The char following '*' designates what is required
        //printf("Got command: %c \n", c);
        string r;
        QTextStream out(stdout);
        switch(c){
            case 'c': //send NO calibration to 2BTouch
                printf("*c%f\n",  CalForm::getForm()->getNOSlope());
                break;
            case 'C': //get NO calibration data from 2BTouch
                getline(cin, r);
                CalForm::getForm()->setNOSlope(atoi(r.c_str()));
                break;
            case 'o':
                printf("*o%i\n", CalForm::getForm()->getNO2Offset());
                break;
            case 'O':
                getline(cin, r);
                CalForm::getForm()->setNOSlope(atoi(r.c_str()));
                break;
            case 'l': //get calibration for 2BTouch, NO2
                printf("%01.3f\n",CalForm::getForm()->getNO2Slope());
                break;
            case 'L': //get calibration data from 2BTouch, NO
                getline(cin, r);
                CalForm::getForm()->setNOSlope(atof(r.c_str()));
                break;
            case 'k':
                printf("*k%i\n",CalForm::getForm()->getNOOffset());
                break;
            case 'K':
                getline(cin, r);
                CalForm::getForm()->setNO2Offset(atoi(r.c_str()));
                break;
            case 'a': //get analog data for 2BTouch //Im not sure that this is implimented

                printf("%i\n",AnalogForm::getForm()->getScale());
                break;
            case 'A': //get analog data from 2BTouch
                getline(cin, r);
                AnalogForm::getForm()->setScale(atoi(r.c_str()));
                break;
            case 'd':
                DateTimeForm::getForm()->on_save_clicked();
                break;
            case 'D':
                getline(cin, r);
                readInDateTime(r);
                break;
            case '*':
                out << CalForm::getForm()->getNO2Slope() << CalForm::getForm()->getNO2Offset() << CalForm::getForm()->getNOSlope() << CalForm::getForm()->getNOOffset() << AnalogForm::getForm()->getScale() << DateTimeForm::getForm()->returnCurrent() << "\n";
                break;
            case '!': //This case will be used to read in all data
                //readInAllValues(readLine());
                break;
            default://Nothing to do if it hits the default case
                break;
        }
    } else {//Must skip through entire line so that getchar() starts at the next line
        //printf("Line is misssing signal char \n");
        //Skip through the rest of the line
        do{
        //Nothing
        }while(getchar() != '\n' && getchar() != '\0'); //Stop when the character is either new line or null
    }
}

//Format should be hhmmssddmmyy
void GrabData::readInDateTime(string s){
    if(s.size() != 12)
        qDebug() << "Bad Date/Time grabData(readInDateTime)";
    QList<string>* partials = new QList<string>();
    for(uint i = 0 ; i < 12; i+=2){
        string r("  ");
        r[0] = s[i];
        r[1] = s[i+1];
        partials->append(r);
    }
    DateTimeForm::getForm()->getCurrent(atoi(partials->at(0).c_str()), atoi(partials->at(1).c_str()), atoi(partials->at(2).c_str()), atoi(partials->at(3).c_str()), atoi(partials->at(4).c_str()), atoi(partials->at(5).c_str()));
}

//Reads in the line from the console and returns it as a string
//Should probably just use the other one
QString GrabData::readLine(){
    int current = getchar();
    QString line;
    do{
        line += current;
        current = getchar();

    }while(current != '\0' && current != '\n');
    return line;
}

//Takes a line that contains all variables seperated by a ','
//If change seperator to '\n' then running getline would seperate it without much additional effort
void readInAllValues(string s){
    QList<string> *divided = new QList<string>();
    string t = "";
    for(uint i = 0; i < s.length(); i++){
        if(s.at(i) == ','){
            divided->append(t);
            t = "";
        }else{
            t += s.at(i);
        }
    }
}

GrabData::~GrabData()
{
    abort = true;
    condition->wakeOne();
}
