#ifndef FUNCOES_H
#define FUNCOES_H

#include "modulo.h"

#define MAX_PERGUNTAS 100
#define MAX_JOGADORES 100

void exibirMenu(void);
void cadastrarPergunta(Pergunta perguntas[], int *totalPerguntas);
void jogar(Pergunta perguntas[], int totalPerguntas,
           Jogador jogadores[], int *totalJogadores);
void ordenarRanking(Jogador jogadores[], int totalJogadores);
void exibirRanking(Jogador jogadores[], int totalJogadores);

void salvarPerguntas(Pergunta perguntas[], int totalPerguntas);
void carregarPerguntas(Pergunta perguntas[], int *totalPerguntas);
void salvarHistorico(Jogador jogadores[], int totalJogadores);
void carregarHistorico(Jogador jogadores[], int *totalJogadores);

#endif
