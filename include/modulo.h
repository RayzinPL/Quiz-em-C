#ifndef MODULO_H
#define MODULO_H

typedef struct {
    char enunciado[200];
    char alternativas[4][100];
    char respostaCorreta;
} Pergunta;

typedef struct {
    char nome[50];
    int acertos;
    int totalPerguntas;
    float percentual;
} Jogador;

char lerResposta(void);

#endif
