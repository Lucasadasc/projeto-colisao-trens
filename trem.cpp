#include "trem.h"
#include <QtCore>
#include <QString>
#include <iostream>

// Implementação da classe RegiaoCritica
void RegiaoCritica::entrar(int idTrem) {
    mutex.lock();
    fila.push(idTrem);
    // Dorme se a região estiver ocupada OU se não for a vez deste trem
    while (ocupado || fila.front() != idTrem) {
        condicao.wait(&mutex);
    }
    fila.pop();
    ocupado = true;
    dono = idTrem;
    mutex.unlock();
}

void RegiaoCritica::sair() {
    mutex.lock();
    ocupado = false;
    dono = -1;
    condicao.wakeAll();
    mutex.unlock();
}

int RegiaoCritica::getDono() {
    mutex.lock();
    int d = dono;
    mutex.unlock();
    return d;
}

bool RegiaoCritica::estaOcupado() {
    mutex.lock();
    bool o = ocupado;
    mutex.unlock();
    return o;
}

//Construtor
Trem::Trem(int ID, int x, int y, RegioesCriticas *malha){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->malha = malha;
    velocidade = 100;
    estaParado = false;

    // Inicializa as flags de travamento como false
    lockedA = false;
    lockedB = false;
    lockedC = false;
    lockedD = false;
    lockedE = false;
    lockedF = false;
    lockedG = false;
    lockedH = false;
    lockedI = false;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        if (estaParado) {
            msleep(velocidade);
            continue;
        }

        switch(ID){
        case 1: //Trem 1
            if (y == 20 && x < 230) {
                if (estaEntrandoEmRegiaoCriticao('D')) {
                    malha->regiaoCriticaD.entrar(ID);
                    lockedD = true;
                }
                x += 10;
            } else if (x == 230 && y < 220) {
                if (estaEntrandoEmRegiaoCriticao('A')) {
                    malha->regiaoCriticaA.entrar(ID);
                    lockedA = true;
                }
                y += 10;
            } else if (x > 30 && y == 220) {
                x -= 10;
                if (estaSaindoRegiaoCritica('D')) {
                    if (lockedD) {
                        malha->regiaoCriticaD.sair();
                        lockedD = false;
                    }
                }
            } else {
                y -= 10;
                if (estaSaindoRegiaoCritica('A')) {
                    if (lockedA) {
                        malha->regiaoCriticaA.sair();
                        lockedA = false;
                    }
                }
            }
            emit updateGUI(ID, x, y);
            break;
        case 2: //Trem 2
            if (y == 20 && x < 430) {
                if (estaEntrandoEmRegiaoCriticao('E')) {
                    malha->controleTransitoArea4.entrar(ID);
                    malha->regiaoCriticaE.entrar(ID);
                    lockedE = true;
                }
                x += 10;
                if (estaSaindoRegiaoCritica('D')) {
                    if (lockedD) {
                        malha->regiaoCriticaD.sair();
                        lockedD = false;
                    }
                }
            } else if (x == 430 && y < 320) {
                if (estaEntrandoEmRegiaoCriticao('G')) {
                    malha->controleTransitoArea2.entrar(ID);
                    malha->regiaoCriticaG.entrar(ID);
                    lockedG = true;
                } else if (estaEntrandoEmRegiaoCriticao('B')) {
                    malha->exclusaoMutuaT2T5.entrar(ID);
                    malha->controleTransitoArea3.entrar(ID);
                    malha->regiaoCriticaB.entrar(ID);
                    lockedB = true;
                }
                y += 10;
                if (estaSaindoRegiaoCritica('E')) {
                    if (lockedE) {
                        malha->regiaoCriticaE.sair();
                        lockedE = false;
                    }
                    malha->controleTransitoArea4.sair();
                }
            } else if (x > 230 && y == 320) {
                if (estaEntrandoEmRegiaoCriticao('F')) {
                    while (malha->regiaoCriticaA.getDono() == 1) {
                        msleep(10);
                    }
                    malha->controleTransitoArea3.sair(); // Libera o Loop 3 antes de travar o Loop 1
                    malha->controleTransitoArea1.entrar(ID);
                    malha->regiaoCriticaF.entrar(ID);
                    lockedF = true;
                }
                x -= 10;
                if (estaSaindoRegiaoCritica('G')) {
                    if (lockedG) {
                        malha->regiaoCriticaG.sair();
                        lockedG = false;
                    }
                    malha->controleTransitoArea2.sair();
                }
            } else {
                if (estaEntrandoEmRegiaoCriticao('D')) {
                    malha->regiaoCriticaD.entrar(ID);
                    lockedD = true;
                }
                y -= 10;
                if (estaSaindoRegiaoCritica('B')) {
                    if (lockedB) {
                        malha->regiaoCriticaB.sair();
                        lockedB = false;
                        malha->exclusaoMutuaT2T5.sair();
                    }
                }
                if (estaSaindoRegiaoCritica('F')) {
                    if (lockedF) {
                        malha->regiaoCriticaF.sair();
                        lockedF = false;
                    }
                    malha->controleTransitoArea1.sair();
                }
            }
            emit updateGUI(ID, x, y);
            break;
        case 3: //Trem 3
            if (y == 20 && x < 630) {
                x += 10;
                if (estaSaindoRegiaoCritica('E')) {
                    if (lockedE) {
                        malha->regiaoCriticaE.sair();
                        lockedE = false;
                    }
                    malha->controleTransitoArea4.sair();
                }
            } else if (x == 630 && y < 220) {
                if (estaEntrandoEmRegiaoCriticao('C')) {
                    malha->controleTransitoArea4.entrar(ID);
                    malha->regiaoCriticaC.entrar(ID);
                    lockedC = true;
                }
                y += 10;
            } else if (x > 430 && y == 220) {
                if (estaEntrandoEmRegiaoCriticao('E')) {
                    malha->regiaoCriticaE.entrar(ID);
                    lockedE = true;
                }
                x -= 10;
            } else {
                y -= 10;
                if (estaSaindoRegiaoCritica('C')) {
                    if (lockedC) {
                        malha->regiaoCriticaC.sair();
                        lockedC = false;
                    }
                }
            }
            emit updateGUI(ID, x, y);
            break;
        case 4: //Trem 4
            if (y == 220 && x < 230) {
                if (estaEntrandoEmRegiaoCriticao('F')) {
                    malha->controleTransitoArea3.entrar(ID);
                    malha->regiaoCriticaF.entrar(ID);
                    lockedF = true;
                }
                x += 10;
            } else if (x == 230 && y < 420) {
                if (estaEntrandoEmRegiaoCriticao('H')) {
                    malha->regiaoCriticaH.entrar(ID);
                    lockedH = true;
                }
                y += 10;
                if (estaSaindoRegiaoCritica('F')) {
                    if (lockedF) {
                        malha->regiaoCriticaF.sair();
                        lockedF = false;
                    }
                    malha->controleTransitoArea1.sair();
                }
                if (estaSaindoRegiaoCritica('A')) {
                    if (lockedA) {
                        malha->regiaoCriticaA.sair();
                        lockedA = false;
                    }
                }
            } else if (x > 30 && y == 420) {
                x -= 10;
                if (estaSaindoRegiaoCritica('H')) {
                    if (lockedH) {
                        malha->regiaoCriticaH.sair();
                        lockedH = false;
                    }
                    malha->controleTransitoArea3.sair();
                }
            } else {
                if (estaEntrandoEmRegiaoCriticao('A')) {
                    malha->controleTransitoArea1.entrar(ID);
                    malha->regiaoCriticaA.entrar(ID);
                    lockedA = true;
                }
                y -= 10;
            }
            emit updateGUI(ID, x, y);
            break;
        case 5: //Trem 5
            if (y == 320 && x < 430) {
                x += 10;
                if (estaSaindoRegiaoCritica('F')) {
                    if (lockedF) {
                        malha->regiaoCriticaF.sair();
                        lockedF = false;
                    }
                }
                if (estaSaindoRegiaoCritica('H')) {
                    if (lockedH) {
                        malha->regiaoCriticaH.sair();
                        lockedH = false;
                        malha->exclusaoMutuaT2T5.sair();
                    }
                }
            } else if (x == 430 && y < 420) {
                if (estaEntrandoEmRegiaoCriticao('I')) {
                    malha->regiaoCriticaI.entrar(ID);
                    lockedI = true;
                }
                y += 10;
                if (estaSaindoRegiaoCritica('B')) {
                    if (lockedB) {
                        malha->regiaoCriticaB.sair();
                        lockedB = false;
                    }
                    malha->controleTransitoArea3.sair();
                }
            } else if (x > 230 && y == 420) {
                if (estaEntrandoEmRegiaoCriticao('H')) {
                    while (malha->controleTransitoArea1.estaOcupado() || malha->regiaoCriticaB.estaOcupado()) {
                        msleep(10);
                    }
                    malha->controleTransitoArea2.entrar(ID);
                    malha->exclusaoMutuaT2T5.entrar(ID);
                    malha->controleTransitoArea3.entrar(ID);
                    malha->regiaoCriticaH.entrar(ID);
                    lockedH = true;
                }
                x -= 10;
                if (estaSaindoRegiaoCritica('I')) {
                    if (lockedI) {
                        malha->regiaoCriticaI.sair();
                        lockedI = false;
                    }
                    malha->controleTransitoArea2.sair();
                }
            } else {
                if (estaEntrandoEmRegiaoCriticao('B')) {
                    malha->regiaoCriticaB.entrar(ID);
                    lockedB = true;
                    malha->regiaoCriticaF.entrar(ID);
                    lockedF = true;
                }
                y -= 10;
            }
            emit updateGUI(ID, x, y);
            break;
        case 6: //Trem 6
            if (y == 220 && x < 630) {
                x += 10;
                if (estaSaindoRegiaoCritica('G')) {
                    if (lockedG) {
                        malha->regiaoCriticaG.sair();
                        lockedG = false;
                    }
                    malha->controleTransitoArea2.sair();
                }
            } else if (x == 630 && y < 420) {
                y += 10;
                if (estaSaindoRegiaoCritica('C')) {
                    if (lockedC) {
                        malha->regiaoCriticaC.sair();
                        lockedC = false;
                    }
                    malha->controleTransitoArea4.sair();
                }
            } else if (x > 430 && y == 420) {
                if (estaEntrandoEmRegiaoCriticao('I')) {
                    malha->controleTransitoArea4.entrar(ID);
                    malha->controleTransitoArea2.entrar(ID);
                    malha->regiaoCriticaI.entrar(ID);
                    lockedI = true;
                }
                x -= 10;
            } else {
                if (estaEntrandoEmRegiaoCriticao('G')) {
                    malha->regiaoCriticaG.entrar(ID);
                    lockedG = true;
                } else if (estaEntrandoEmRegiaoCriticao('C')) {
                    malha->regiaoCriticaC.entrar(ID);
                    lockedC = true;
                }
                y -= 10;
                if (estaSaindoRegiaoCritica('I')) {
                    if (lockedI) {
                        malha->regiaoCriticaI.sair();
                        lockedI = false;
                    }
                }
            }
            emit updateGUI(ID, x, y);
            break;
        default:
            break;
        }

        msleep(velocidade);
    }
}

void Trem::alterarVelocidade(int valorSlider){
    this->velocidade = 200 - valorSlider;
    this->estaParado = false;

    if (valorSlider == 200) {
        this->velocidade = 1;
    }

    if (valorSlider == 0) {
        this->estaParado = true;
    }
}

bool Trem::estaEntrandoEmRegiaoCriticao(char regiao) const {
    bool resultado = false;
    switch(regiao) {
    case 'A': // y = 220 e x entre 30 e 230 (T1 e T4)
        if (ID == 1) resultado = (x == 230 && y == 200);
        else if (ID == 4) resultado = (x == 30 && y == 240);
        break;
    case 'B': // y = 320 e x entre 230 e 430 (T2 e T5)
        if (ID == 2) resultado = (x == 430 && y == 300);
        else if (ID == 5) resultado = (x == 230 && y == 340);
        break;
    case 'C': // y = 220 e x entre 430 e 630 (T3 e T6)
        if (ID == 3) resultado = (x == 630 && y == 200);
        else if (ID == 6) resultado = (x == 430 && y == 240);
        break;
    case 'D': // x = 230 e y entre 20 e 220 (T1 e T2)
        if (ID == 1) resultado = (x == 210 && y == 20);
        else if (ID == 2) resultado = (x == 230 && y == 240);
        break;
    case 'E': // x = 430 e y entre 20 e 220 (T2 e T3)
        if (ID == 2) {
            resultado = (x == 410 && y == 20);
        } else if (ID == 3) {
            resultado = (x == 450 && y == 220);
        }
        break;
    case 'F': // x = 230 e y entre 220 e 320 (T2 e T4)
        if (ID == 2) {
            resultado = (x == 250 && y == 320);
        } else if (ID == 4) {
            resultado = (x == 210 && y == 220);
        }
        break;
    case 'G': // x = 430 e y entre 220 e 320 (T2 e T6)
        if (ID == 2) {
            resultado = (x == 430 && y == 200);
        }
        else if (ID == 6) resultado = (x == 430 && y == 340);
        break;
    case 'H': // x = 230 e y entre 320 e 420 (T4 e T5)
        if (ID == 4) resultado = (x == 230 && y == 300);
        else if (ID == 5) resultado = (x == 250 && y == 420);
        break;
    case 'I': // x = 430 e y entre 320 e 420 (T5 e T6)
        if (ID == 5) resultado = (x == 410 && y == 320);
        else if (ID == 6) resultado = (x == 450 && y == 420);
        break;
    }

    QString regioes = "F";

    if (resultado && regioes.contains(regiao)) { 
        std::cout << "ID: " << ID << " entrando na regiao " << regiao << std::endl;
    }

    return resultado;
}

bool Trem::estaSaindoRegiaoCritica(char regiao) const {
    bool resultado = false;
    switch(regiao) {
    case 'A': // y = 220 e x entre 50 e 230 (T1 e T4)
        if (ID == 1) {
            resultado = (x == 30 && y == 200);
        } else if (ID == 4) {
            resultado = (x == 230 && y == 240);
        }
        break;
    case 'B': // y = 320 e x entre 230 e 430 (T2 e T5)
        if (ID == 2) resultado = (x == 230 && y == 300);
        else if (ID == 5) resultado = (x == 430 && y == 350);
        break;
    case 'C': // y = 220 e x entre 430 e 630 (T3 e T6) continuar daqui
        if (ID == 3) resultado = (x == 430 && y == 200);
        else if (ID == 6) resultado = (x == 630 && y == 240);
        break;
    case 'D': // x = 230 e y entre 20 e 220 (T1 e T2)
        if (ID == 1) {
            resultado = (x == 210 && y == 220);
        } else if (ID == 2) {
            resultado = (x == 250 && y == 20);
        }
        break;
    case 'E': // x = 430 e y entre 20 e 220 (T2 e T3)
        if (ID == 2){
            resultado = (x == 430 && y == 240);
        } else if (ID == 3) {
            resultado = (x == 450 && y == 20);
        }
        break;
    case 'F': // x = 230 e y entre 220 e 320 (T2 e T4)
        if (ID == 2) {
            resultado = (x == 230 && y == 200);
        } 
        else if (ID == 4) {
            resultado = (x == 230 && y == 340);
        }
        else if (ID == 5) {
            resultado = (x == 250 && y == 320);
        }
        break;
    case 'G': // x = 430 e y entre 220 e 320 (T2 e T6)
        if (ID == 2) {
            resultado = (x == 410 && y == 320);
        }
        else if (ID == 6) {
            resultado = (x == 450 && y == 220);
        }
        break;
    case 'H': // x = 230 e y entre 320 e 420 (T4 e T5)
        if (ID == 4) {
            resultado = (x == 210 && y == 420);
        }
        else if (ID == 5){
            resultado = (x == 240 && y == 320);
        }
        break;
    case 'I': // x = 430 e y entre 320 e 420 (T5 e T6)
        if (ID == 5) {
            resultado = (x == 410 && y == 420);
        }
        else if (ID == 6){
            resultado = (x == 430 && y == 300);
        }
        break;
    }

    // lista de regioes para printar
    QString regioes = "F";

    if (resultado && regioes.contains(regiao)) {
        std::cout << "ID: " << ID << " saindo da regiao " << regiao << std::endl;
    }

    return resultado;
}
