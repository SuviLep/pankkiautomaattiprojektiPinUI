#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void HandleEnterDLL(QString);
    void HandleClick();

signals:
    void PinNumberSignalEXE(QString);

private:
    Ui::MainWindow *ui;
    Dialog * ptrPIN_dll;
    QString pinnumber;
    QString correctPinNumber= "1234";
    int attemptsLeft = 3;
};
#endif // MAINWINDOW_H
