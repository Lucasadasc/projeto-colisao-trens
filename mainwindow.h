#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void updateInterface(int,int,int);



private slots:
    void on_sliderVelTrem1_valueChanged(int value);

    void on_sliderVelTrem2_valueChanged(int value);

    void on_sliderVelTrem3_valueChanged(int value);

    void on_sliderVelTrem4_valueChanged(int value);

    void on_sliderVelTrem5_valueChanged(int value);

    void on_sliderVelTrem6_valueChanged(int value);

    void on_checkBox_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    RegioesCriticas malha;

    //Cria os objetos TREM's
    Trem *trem1;
    Trem *trem2;
    Trem *trem3;
    Trem *trem4;
    Trem *trem5;
    Trem *trem6;
};

#endif // MAINWINDOW_H
