#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "PinUI_DLL_global.h"

namespace Ui {
class Dialog;
}

class PINUI_DLL_EXPORT Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    //void setAttemptsLeft(const QString newAttemptsLeft);

    void setAttempts(const QString &newAttempts);

signals:
    void PinNumberSignalDLL(QString);

private slots:
    void ENTER_CLEAR_ClickHandler();
    void numberClickedHandler();
    void restartTimer();

protected:
    void showEvent(QShowEvent *event) override;


private:
    Ui::Dialog *ui;
    QString num;
    QString attempts;
    QTimer *timer;
};

#endif // DIALOG_
