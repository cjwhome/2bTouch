#include "averageform.h"
#include "ui_averageform.h"

AverageForm::AverageForm(QWidget *parent, QList<GasDataState *> * mod, bool sts) :
    QWidget(parent),
    ui(new Ui::AverageForm)
{
    stats = sts;
    gases = mod;

    ui->setupUi(this);
    //Set the style sheets individually rather than all at once so it does not effect any other QTextBrowsers
    ui->one->setStyleSheet("QTextBrowser {font-size: 25px}");
    ui->five->setStyleSheet("QTextBrowser {font-size: 25px}");
    ui->eight->setStyleSheet("QTextBrowser {font-size: 25px}");
    ui->hour->setStyleSheet("QTextBrowser {font-size: 25px}");

    //Removes the top bar with the minimize, close and fill buttons
    QWidget::setWindowFlags(Qt::CustomizeWindowHint);
    model = new QStringListModel(this);
    QStringList List;

    for(int i = 0; i < gases->size(); i++){
        if(gases->at(i)->unit != ""){//If there is no unit then ignore that data entry
            QListWidgetItem * nItem = new QListWidgetItem();
            QString * s = new QString();
            QString * name = gases->at(i)->name;

            //It might be worth creating this part of the string when initializing the dasDataState
            for(int j = 0; j < name->length(); j++){
                //Check and see of the char is number and if so add the subscript tags
                if(name->at(j) >= 48 && name->at(j) <= 57){
                    s->append("<sub>" + QString(name->at(j)) + "</sub>");
                }else{
                    s->append(QString(name->at(j)));
                }
            }
            //Check if there is any current data for the gas, if not default to 0.0
            if(gases->at(i)->data.size() > 0){
                s->append(": <font color='blue'>" + QString::number(gases->at(i)->data.at(gases->at(i)->data.size()-1)) + "</font> " + gases->at(i)->unit);
            }else{
                s->append(": <font color='blue'>0.0</font> " + gases->at(i)->unit);
            }
            nItem->setText(*s);
            List << *s;
        }
    }
    model->setStringList(List);
    ui->listView->setModel(model);
    ui->listView->setItemDelegate(new RichTextDelegate());
    ui->listView->setWordWrap(true);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView->update();

    connect(ui->listView, SIGNAL(clicked(const QModelIndex)), this, SLOT(on_listView_pressed(const QModelIndex)));
}

AverageForm::~AverageForm(){
    delete ui;
}

//This is the home button
void AverageForm::on_pushButton_clicked(){
    hide();
}

//The average form is currently located in both ui groups in the uimanager
void AverageForm::on_mNext_clicked(){
    if(!stats){
        UiManager * ui = UiManager::getManager();
        if(ui->currentSIndex + 1 == ui->settingWidgets->count()){
            ui->currentSIndex = 0;
        }else{
            ui->currentSIndex += 1;
        }
        ui->cWidget->hide();
        ui->cWidget = ui->settingWidgets->at(ui->currentSIndex);
        ui->cWidget->show();
    }else{
        UiManager * manager = UiManager::getManager();
        if(manager->cStatIndex + 1 >= manager->statsWidgets->count()){
            manager->cStatIndex = 0;
        }else{
            manager->cStatIndex += 1;
        }
        manager->cStatWidget->hide();
        manager->cStatWidget = manager->statsWidgets->at(manager->cStatIndex);
        manager->cStatWidget->show();
    }
}

//The average form is currently located in both ui groups in the uimanager
void AverageForm::on_mPrevious_clicked(){
    //stats is true if this is in the stats ui list  in ui manager
    if(!stats){
        UiManager * ui = UiManager::getManager(); //Get the uimanager class
        if((ui->currentSIndex -= 1) < 0)//Decrease the stats index and make sure it is valid
            ui->currentSIndex = ui->settingWidgets->count() - 1; //If not valid set the index to the last form in the list
        ui->cWidget->hide();//This hides the current widget but dose not delete it
        ui->cWidget = ui->settingWidgets->at(ui->currentSIndex); //set the current widget to the one at the current index
        ui->cWidget->show();//show the current widget
    }else{
        UiManager * manager = UiManager::getManager();//Get the uimanager class
        if((manager->cStatIndex -= 1) < 0)//Decrease the index and make sure it is valid
            manager->cStatIndex = manager->statsWidgets->count() - 1;//If not valid set the index to the last form in the list
        manager->cStatWidget->hide();//This hides the current widget but dose not delete it
        manager->cStatWidget = manager->statsWidgets->at(manager->cStatIndex);//set the current widget to the one at the current index
        manager->cStatWidget->show();//show the current widget
    }
}

//This is used to choose which gase average to display
void AverageForm::on_listView_pressed(const QModelIndex &index){
    if(index.row() == -1){ //If there are no selected rows then it returns a -1 which causes an index out of range value
        currentGasIndex = 0;
    }else{
        currentGasIndex = index.row(); //Sets the current gas index to the index of the listview.
                                        //This works becaus the 3 gases are the the first 3 enteries in the gases/data list are the 3 gases
    }
    //Populate the text fields with their respective averages
    //Format "Time: value unit" ie 1m: 1.1 ppb
    //Averages are calculated in the gasDataState struct
    ui->one->setText(QString("1m: " + QString::number(gases->at(currentGasIndex)->getMinAverage(), 'g', 3) + " " + gases->at(currentGasIndex)->unit));
    ui->five->setText(QString("5m: " + QString::number(gases->at(currentGasIndex)->get5MinAverage(), 'g', 3) + " " + gases->at(currentGasIndex)->unit));
    ui->hour->setText(QString("1h: " + QString::number(gases->at(currentGasIndex)->getHourAverage(), 'g', 3) + " " + gases->at(currentGasIndex)->unit));
    ui->eight->setText(QString("8h: " + QString::number(gases->at(currentGasIndex)->getEightAverage(), 'g', 3) + " " + gases->at(currentGasIndex)->unit));
}

//This is used to update the averages every second, The grab data class has a loop that runs every seconds and calls the update function
void AverageForm::update(){
    int slIndex = 0;  //String list index
    for(int i = 0; i < gases->size(); i++){
        //Only interested in the gases/values with units
        QString * s = gases->at(i)->richTextName;
        if(gases->at(i)->unit != ""){
            if(gases->at(i)->data.size() > 0){
                if(*gases->at(i)->richTextName == "Null")
                    gases->at(i)->setRichName();
                s->append(": <font color='blue'>" + QString::number(gases->at(i)->data.at(gases->at(i)->data.size()-1), 'g', 3) + "</font> " + gases->at(i)->unit);
            }else{
                s->append(": <font color='blue'>0.0</font> " + gases->at(i)->unit);
            }
            model->setData(model->index(slIndex),*s, 0);
            slIndex++;
        }
    }
    //Updates the averages in the respective text fields, the averages are calculated in the gasDataState struct that represents the gases
    qDebug() << QString::number(gases->at(currentGasIndex)->getEightAverage(), 'g', 3);
    ui->one->setText(QString("1m: " + QString::number(gases->at(currentGasIndex)->getMinAverage(), 'g', 3) + " " + gases->at(currentGasIndex)->unit));
    ui->five->setText(QString("5m: " + QString::number(gases->at(currentGasIndex)->get5MinAverage(), 'g', 3) + " " + gases->at(currentGasIndex)->unit));
    ui->hour->setText(QString("1h: " + QString::number(gases->at(currentGasIndex)->getHourAverage(), 'g', 3) + " " + gases->at(currentGasIndex)->unit));
    ui->eight->setText(QString("8h: " + QString::number(gases->at(currentGasIndex)->getEightAverage(), 'g', 3) + " " + gases->at(currentGasIndex)->unit));
}
