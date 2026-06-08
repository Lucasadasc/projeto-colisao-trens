#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Cria o trem com seu (ID, posição X, posição Y, &malha)
    trem1 = new Trem(1,30,20,&malha); // &malha passa o endereço de memória da variável global malha
    trem2 = new Trem(2,230,20,&malha);
    trem3 = new Trem(3,430,20,&malha);
    trem4 = new Trem(4,30,220,&malha);
    trem5 = new Trem(5,230,320,&malha);
    trem6 = new Trem(6,430,220,&malha);

    // Força a exibição dos trens em suas posições iniciais no startup da janela
    // Isso faz com que o trem apareça na posição inicial mesmo se o semáforo estiver fechado
    updateInterface(1, 30, 20);
    updateInterface(2, 230, 20);
    updateInterface(3, 430, 20);
    updateInterface(4, 30, 220);
    updateInterface(5, 230, 320);
    updateInterface(6, 430, 220);

    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem6,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

    // Conecta os Sliders aos LCDs usando a sintaxe clássica (via interface deu problema)
    connect(ui->sliderVelTrem1, SIGNAL(valueChanged(int)), ui->lcdNumber, SLOT(display(int)));
    connect(ui->sliderVelTrem2, SIGNAL(valueChanged(int)), ui->lcdNumber_2, SLOT(display(int)));
    connect(ui->sliderVelTrem3, SIGNAL(valueChanged(int)), ui->lcdNumber_3, SLOT(display(int)));
    connect(ui->sliderVelTrem4, SIGNAL(valueChanged(int)), ui->lcdNumber_4, SLOT(display(int)));
    connect(ui->sliderVelTrem5, SIGNAL(valueChanged(int)), ui->lcdNumber_5, SLOT(display(int)));
    connect(ui->sliderVelTrem6, SIGNAL(valueChanged(int)), ui->lcdNumber_6, SLOT(display(int)));

    // Inicia os trens em movimento
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
    trem6->start();
}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
    case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
        ui->labelTrem1->setGeometry(x,y,21,17);
        break;
    case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->labelTrem2->setGeometry(x,y,21,17);
        break;
    case 3: //Atualiza a posição do objeto da tela (quadrado) que representa o trem3
        ui->labelTrem3->setGeometry(x,y,21,17);
        break;
    case 4: //Atualiza a posição do objeto da tela (quadrado) que representa o trem4
        ui->labelTrem4->setGeometry(x,y,21,17);
        break;
    case 5: //Atualiza a posição do objeto da tela (quadrado) que representa o trem5
        ui->labelTrem5->setGeometry(x,y,21,17);
        break;
    case 6: //Atualiza a posição do objeto da tela (quadrado) que representa o trem6
        ui->labelTrem6->setGeometry(x,y,21,17);
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_sliderVelTrem1_valueChanged(int value)
{
    trem1->alterarVelocidade(value);

}

void MainWindow::on_sliderVelTrem2_valueChanged(int value)
{
    trem2->alterarVelocidade(value);
}

void MainWindow::on_sliderVelTrem3_valueChanged(int value)
{
    trem3->alterarVelocidade(value);
}

void MainWindow::on_sliderVelTrem4_valueChanged(int value)
{
    trem4->alterarVelocidade(value);
}

void MainWindow::on_sliderVelTrem5_valueChanged(int value)
{
    trem5->alterarVelocidade(value);
}

void MainWindow::on_sliderVelTrem6_valueChanged(int value)
{
    trem6->alterarVelocidade(value);
}

