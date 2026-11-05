# Simulação de Trens — Sistemas Operacionais

Projeto acadêmico de Sistemas Operacionais da UFRN que simula seis trens em uma malha ferroviária com interface gráfica em C++ e Qt. Cada trem executa em uma thread própria e percorre um trajeto com trechos compartilhados, permitindo estudar concorrência, exclusão mútua e situações de deadlock.

## Funcionalidades

- Simulação simultânea de seis trens, identificados de T1 a T6.
- Controle individual de velocidade pela interface.
- Nove regiões críticas, identificadas de A a I.
- Opção para exibir as regiões dos controles de tráfego na malha.
- Atualização das posições por sinais e slots do Qt.

## Sincronização

A classe `Trem` herda de `QThread` e implementa o movimento de cada trem. Os trechos compartilhados são coordenados pela classe `RegiaoCritica`, que utiliza:

- `QMutex` para proteger o estado da região;
- `QWaitCondition` para bloquear os trens enquanto aguardam passagem;
- uma fila de IDs para organizar o acesso por ordem de chegada.

A estrutura `RegioesCriticas` reúne as regiões A a I e controles adicionais de tráfego, usados para coordenar a aquisição de trechos ao longo dos percursos. As decisões de sincronização e os cenários de deadlock estão descritos nas anotações e nos artefatos do projeto.

## Requisitos

- Compilador C++ (como GCC).
- Qt 5 com os módulos Core, GUI e Widgets.
- `qmake` e `make`.
- Ambiente gráfico para executar a aplicação.

O Qt Creator é opcional e permite configurar, compilar e executar o projeto pela IDE.

## Compilação e execução

### Pelo terminal

Na pasta que contém o arquivo `Trem.pro`, execute:

```bash
mkdir -p build
cd build
qmake ../Trem.pro
make
./Trem
```

Use o `qmake` da instalação do Qt 5 caso existam várias versões do Qt no sistema. A compilação em `build/` gera um Makefile para o ambiente local, sem depender do Makefile já presente no projeto.

### Pelo Qt Creator

1. Abra o arquivo `Trem.pro`.
2. Selecione um kit Desktop com Qt 5 e compilador C++ configurados.
3. Compile o projeto e execute a aplicação.

## Como usar

Os seis trens começam a se mover ao abrir a janela. Cada um possui um controle deslizante e um visor com o valor selecionado:

| Valor | Comportamento |
| --- | --- |
| `0` | Solicita a pausa do trem. |
| `1` a `199` | Quanto maior o valor, menor o intervalo entre os movimentos. |
| `200` | Define o intervalo mínimo de 1 ms entre os movimentos. |

O valor inicial dos controles é `100`. Os valores representam ajustes de velocidade da simulação, sem unidade física.

Marque **Exibir regiões dos semáforos** para visualizar as áreas destacadas dos controles de tráfego.

Ao pausar, o trem mantém as regiões que já adquiriu. Por isso, pausar um trem em um trecho compartilhado pode fazer outros aguardarem; aumente novamente seu controle de velocidade para permitir que ele prossiga e libere o trecho. Se estiver bloqueado aguardando uma região, a pausa será observada quando essa espera terminar e a execução voltar ao início do laço de movimento.

## Estrutura do projeto

| Arquivo ou pasta | Descrição |
| --- | --- |
| `Trem.pro` | Configuração do projeto para o qmake. |
| `main.cpp` | Inicialização da aplicação Qt. |
| `mainwindow.h` / `mainwindow.cpp` | Criação dos trens, conexões e controles da interface. |
| `mainwindow.ui` | Layout da janela, editável no Qt Designer. |
| `trem.h` / `trem.cpp` | Threads dos trens, trajetos e sincronização das regiões críticas. |
| `anotacoes.txt` | Notas sobre decisões de implementação e deadlocks. |
| `artefatos/` | Documentos de planejamento, dados dos alunos e referências aos vídeos. |
