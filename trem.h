#ifndef TREM_H
#define TREM_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QString>
#include <queue>

class RegiaoCritica {
    private:
        QMutex mutex;
        QWaitCondition condicao;
        std::queue<int> fila; // Guarda os IDs na ordem de chegada
        bool ocupado;
        int dono;

    public:
        RegiaoCritica() : ocupado(false), dono(-1) {}
        void entrar(int idTrem);
        void sair();
        int getDono();
        bool estaOcupado();
};

struct RegioesCriticas {
    RegiaoCritica regiaoCriticaA;
    RegiaoCritica regiaoCriticaB;
    RegiaoCritica regiaoCriticaC;
    RegiaoCritica regiaoCriticaD;
    RegiaoCritica regiaoCriticaE;
    RegiaoCritica regiaoCriticaF;
    RegiaoCritica regiaoCriticaG;
    RegiaoCritica regiaoCriticaH;
    RegiaoCritica regiaoCriticaI;

    RegiaoCritica controleTransitoArea1;
    RegiaoCritica controleTransitoArea2;
    RegiaoCritica controleTransitoArea3;
    RegiaoCritica controleTransitoArea4;
    RegiaoCritica exclusaoMutuaB2H5;

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
};

#endif // TREM_H
