#ifndef TREM_H
#define TREM_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QString>
#include <queue>

class FilaFIFO {
private:
    QMutex mutex;
    QWaitCondition condicao;
    std::queue<int> fila; // Guarda os IDs na ordem de chegada
    bool ocupado;
    int dono;

public:
    FilaFIFO() : ocupado(false), dono(-1) {}
    void entrar(int idTrem);
    void sair();
    int getDono();
    bool estaOcupado();
};

struct RegioesCriticas {
    FilaFIFO regiaoCriticaA;
    FilaFIFO regiaoCriticaB;
    FilaFIFO regiaoCriticaC;
    FilaFIFO regiaoCriticaD;
    FilaFIFO regiaoCriticaE;
    FilaFIFO regiaoCriticaF;
    FilaFIFO regiaoCriticaG;
    FilaFIFO regiaoCriticaH;
    FilaFIFO regiaoCriticaI;

    FilaFIFO controleTransitoArea1;
    FilaFIFO controleTransitoArea2;
    FilaFIFO controleTransitoArea3;
    FilaFIFO controleTransitoArea4;
    FilaFIFO exclusaoMutuaB2H5;

    RegioesCriticas() {}
};

/*
 * Classe Trem herda QThread
 * Classe Trem passa a ser uma thread.
 * A função START inicializa a thread. Após inicializada, a thread irá executar a função RUN.
 * Para parar a execução da função RUN da thread, basta executar a função TERMINATE.
 *
 */
class Trem: public QThread{
 Q_OBJECT
public:
    Trem(int,int,int, RegioesCriticas*);  //construtor
    void run();         //função a ser executada pela thread
    void alterarVelocidade(int);

//Cria um sinal
signals:
    void updateGUI(int,int,int);

private:
   int x;           //posição X do trem na tela
   int y;           //posição Y do trem na tela
   int ID;          //ID do trem
   int velocidade;  //Velocidade. É o tempo de dormir em milisegundos entre a mudança de posição do trem
   bool estaParado;
   RegioesCriticas *malha;

   // Flags de rastreamento para exclusão mútua
   bool lockedA;
   bool lockedB;
   bool lockedC;
   bool lockedD;
   bool lockedE;
   bool lockedF;
   bool lockedG;
   bool lockedH;
   bool lockedI;

   // Métodos auxiliares de detecção por caractere (Opção 2 simplificada)
   bool estaEntrandoEmRegiaoCriticao(char regiao) const;
   bool estaSaindoRegiaoCritica(char regiao) const;
   QString obterDescricaoPosicao(char regiao) const;
};

#endif // TREM_H
