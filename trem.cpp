#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 20 && x <230)
                x+=10;
            else if (x == 230 && y < 220)
                y+=10;
            else if (x > 30 && y == 220)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 20 && x <430)
                x+=10;
            else if (x == 430 && y < 320)
                y+=10;
            else if (x > 230 && y == 320)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 20 && x <630)
                x+=10;
            else if (x == 630 && y < 220)
                y+=10;
            else if (x > 430 && y == 220)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (y == 220 && x <230)
                x+=10;
            else if (x == 230 && y < 420)
                y+=10;
            else if (x > 30 && y == 420)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 320 && x <430)
                x+=10;
            else if (x == 430 && y < 420)
                y+=10;
            else if (x > 230 && y == 420)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 6: //Trem 6
            if (y == 220 && x <630)
                x+=10;
            else if (x == 630 && y < 420)
                y+=10;
            else if (x > 430 && y == 420)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:
            break;
        }
        msleep(velocidade);
    }
}




