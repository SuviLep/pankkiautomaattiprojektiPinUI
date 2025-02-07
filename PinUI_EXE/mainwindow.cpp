#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ptrPIN_dll= new Dialog(this);

    //Yhteys DLL signalista Mainin HandleEnterDLL, josta lähetään takaisin mainiin
    connect(ptrPIN_dll, SIGNAL(PinNumberSignalDLL(QString)),
            this, SLOT(HandleEnterDLL(QString)));

    //Yhteys mainin pushbuttonista Slottiin handleclick, josta-->DLL show
    connect(ui->pushButton,SIGNAL(clicked(bool)),
            this,SLOT(HandleClick()));
}

MainWindow::~MainWindow()
{
    delete ui;
    ui = nullptr;
}

void MainWindow::HandleEnterDLL(QString p)
{
    pinnumber=p;
    ui->lineEdit->setText(p);

    qDebug()<<"Main handleEnterDLL";


    if(pinnumber==correctPinNumber){

        qDebug()<<"pinkoodi oikein";
    }
    else if(pinnumber != correctPinNumber){

        qDebug()<<"väärä pin, lähetään signaali takaisin DLL "
                    " ja avataan uudelleen pin-ikkuna";
        attemptsLeft--;
        ptrPIN_dll->setAttempts(QString::number(attemptsLeft)+" yritystä jäljellä");
        ptrPIN_dll->open();
    }
}

void MainWindow::HandleClick()
{
    ptrPIN_dll->show();
    qDebug()<<"handleCLICK funktiossa ollaan";
}
