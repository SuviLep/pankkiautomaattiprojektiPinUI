#include "dialog.h"
#include "ui_dialog.h"
#include "QDebug"
#include "QTimer"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
        ui->setupUi(this);

        // Luodaan timer. Kun timeout->close dialog.
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Dialog::close);

        // Asetetaan aika 15 sekkaa ja startataan timer.
        timer->setInterval(15000);
        timer->start();

    // Enter ja Clear buttoneiden yhteydet Slottiin ENTER_CLEAR_ClickHandler()

    connect(ui->BtnENTER, SIGNAL(clicked(bool)),
            this, SLOT(ENTER_CLEAR_ClickHandler()));
    connect(ui->BtnCLEAR, SIGNAL(clicked(bool)),
            this, SLOT (ENTER_CLEAR_ClickHandler()));

    // Numeronappien yhteydet Slottiin numberClickedHandler()
    connect(ui->Btn1, SIGNAL(clicked(bool)),
            this, SLOT (numberClickedHandler()));
    connect(ui->Btn2, SIGNAL(clicked(bool)),
            this, SLOT (numberClickedHandler()));
    connect(ui->Btn3, SIGNAL(clicked(bool)),
            this, SLOT (numberClickedHandler()));
    connect(ui->Btn4, SIGNAL(clicked(bool)),
            this, SLOT (numberClickedHandler()));
    connect(ui->Btn5, SIGNAL(clicked(bool)),
            this, SLOT (numberClickedHandler()));
    connect(ui->Btn6, SIGNAL(clicked(bool)),
            this, SLOT (numberClickedHandler()));
    connect(ui->Btn7, SIGNAL(clicked(bool)),
            this, SLOT (numberClickedHandler()));
    connect(ui->Btn8, SIGNAL(clicked(bool)),
            this, SLOT (numberClickedHandler()));
    connect(ui->Btn9, SIGNAL(clicked(bool)),
            this, SLOT (numberClickedHandler()));
    connect(ui->Btn0, SIGNAL(clicked(bool)),
            this, SLOT (numberClickedHandler()));
}

void Dialog::restartTimer()
{
    // Asetetaan timerin uudelleen käynnistäminen aina, kun dialogi avataan
    timer->start();
}

Dialog::~Dialog()
{
    delete ui;
    delete timer;
    qDebug()<<"Deleting automatically pinUI object";
}

    void Dialog::ENTER_CLEAR_ClickHandler()
{
       qDebug() << "DLL ENTER_CLEAR_ClickHandler";

       QPushButton *button = qobject_cast<QPushButton*>(sender());
    // käytetään sender()-funktiota, joka palauttaa osoittimen objektiin, joka on lähettänyt tämän signaalin.
       QString btnname = button->objectName();
    // haetaan napin nimi(objectName()) ja tallennetaan se btnname-muuttujaan.

       qDebug() << "Button name: " << btnname;

    // Jos enter, lähetään pinkoodi mainiin.
         if (btnname == "BtnENTER") {
         ui->lineEditPINKOODI->text();
             emit PinNumberSignalDLL(num);
         ui->lineEditPINKOODI->clear();
         num="";
         close();
         }

    //Jos Clear, poistetaan yksi merkki näytöltä

         if (btnname == "BtnCLEAR") {
             if (!num.isEmpty()) {
                 num.chop(1); // Poistetaan viimeinen merkki merkkijonosta
                 ui->lineEditPINKOODI->setText(num);
             }
         }
}

void Dialog::numberClickedHandler()
{
    //Ensimmäiset neljä merkkiä otetaan pinkoodi-kentässä käyttöön..

        // Jos neljä numeroa syötetty, ei tehdä mitään.
        if (num.length() >= 4) {
            return;
        }

        QPushButton *button = qobject_cast<QPushButton*>(sender());
        QString name = button->objectName();

        // Lisää napin nimi viimeiseksi merkiksi pinkoodiin
        num += name.last(1);

        //Tarkistetaan, onko enemmän kuin neljä merkkiä. Poistetaan ylimääräiset tarvittaessa.
        if (num.length() > 4) {
            num = num.right(4);
        }

        ui->lineEditPINKOODI->setText(num);
        qDebug()<<"DLL-> numberCLicked handler";
}
void Dialog::setAttempts(const QString &newAttempts)
{
    attempts = newAttempts;
    ui->lineEditAttemptsLeft->setText(attempts);
}
void Dialog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    // Käynnistetään timer aina uudelleen alusta kun dialogi tulee näkyviin
    restartTimer();
    // Nollataan pinkoodinäyttö
    ui->lineEditPINKOODI->clear();
    num="";
}
