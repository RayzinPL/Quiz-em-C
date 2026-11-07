#include <stdio.h>
#include "funcoes.h"

#define ARQUIVO_PERGUNTAS "data/perguntas.txt"
#define ARQUIVO_HISTORICO "data/historico.txt"

void exibirMenu(void) {
    printf("\n========== QUIZ EM C ==========\n");
    printf("1 - Jogar\n");
    printf("2 - Cadastrar pergunta\n");
    printf("3 - Ver ranking\n");
    printf("0 - Sair\n");
    printf("===============================\n");
}

void cadastrarPergunta(Pergunta perguntas[], int *totalPerguntas) {
    int i;

    if (*totalPerguntas >= MAX_PERGUNTAS) {
        printf("Limite de perguntas atingido.\n");
        return;
    }

    printf("\nDigite o enunciado: ");
    scanf(" %199[^\n]", perguntas[*totalPerguntas].enunciado);

    for (i = 0; i < 4; i++) {
        printf("Alternativa %c: ", 'A' + i);
        scanf(" %99[^\n]", perguntas[*totalPerguntas].alternativas[i]);
    }

    printf("Qual e a resposta correta (A, B, C ou D)? ");
    perguntas[*totalPerguntas].respostaCorreta = lerResposta();

    (*totalPerguntas)++;
    printf("Pergunta cadastrada!\n");
}

void jogar(Pergunta perguntas[], int totalPerguntas,
           Jogador jogadores[], int *totalJogadores) {
    int i, j;
    char resposta;

    if (totalPerguntas == 0) {
        printf("Cadastre perguntas antes de jogar.\n");
        return;
    }

    if (*totalJogadores >= MAX_JOGADORES) {
        printf("Limite de jogadores atingido.\n");
        return;
    }

    printf("\nNome do jogador: ");
    scanf(" %49[^\n]", jogadores[*totalJogadores].nome);

    jogadores[*totalJogadores].acertos = 0;
    jogadores[*totalJogadores].totalPerguntas = totalPerguntas;

    for (i = 0; i < totalPerguntas; i++) {
        printf("\n%d. %s\n", i + 1, perguntas[i].enunciado);
        for (j = 0; j < 4; j++) {
            printf("%c) %s\n", 'A' + j, perguntas[i].alternativas[j]);
        }

        printf("Sua resposta: ");
        resposta = lerResposta();

        if (resposta == perguntas[i].respostaCorreta) {
            jogadores[*totalJogadores].acertos++;
        }
    }

    jogadores[*totalJogadores].percentual =
        (float)jogadores[*totalJogadores].acertos * 100 / totalPerguntas;

    printf("\nResultado de %s: %d de %d acertos (%.2f%%).\n",
           jogadores[*totalJogadores].nome,
           jogadores[*totalJogadores].acertos,
           totalPerguntas,
           jogadores[*totalJogadores].percentual);

    (*totalJogadores)++;
    salvarHistorico(jogadores, *totalJogadores);
}


void ordenarRanking(Jogador jogadores[], int totalJogadores) {
    int i, j;
    Jogador temporario;

    for (i = 0; i < totalJogadores - 1; i++) {
        for (j = 0; j < totalJogadores - 1 - i; j++) {
            if (jogadores[j].percentual < jogadores[j + 1].percentual) {
                temporario = jogadores[j];
                jogadores[j] = jogadores[j + 1];
                jogadores[j + 1] = temporario;
            }
        }
    }
}

void exibirRanking(Jogador jogadores[], int totalJogadores) {
    int i;

    if (totalJogadores == 0) {
        printf("Ainda nao existem partidas registradas.\n");
        return;
    }

    ordenarRanking(jogadores, totalJogadores);

    printf("\n========== RANKING ==========\n");
    for (i = 0; i < totalJogadores; i++) {
        printf("%d - %s: %.2f%% (%d/%d)\n",
               i + 1,
               jogadores[i].nome,
               jogadores[i].percentual,
               jogadores[i].acertos,
               jogadores[i].totalPerguntas);
    }
}

void salvarPerguntas(Pergunta perguntas[], int totalPerguntas) {
    FILE *arquivo;
    int i;

    arquivo = fopen(ARQUIVO_PERGUNTAS, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir perguntas.txt para gravar.\n");
        return;
    }

    for (i = 0; i < totalPerguntas; i++) {
        fprintf(arquivo, "%s;%s;%s;%s;%s;%c\n",
                perguntas[i].enunciado,
                perguntas[i].alternativas[0],
                perguntas[i].alternativas[1],
                perguntas[i].alternativas[2],
                perguntas[i].alternativas[3],
                perguntas[i].respostaCorreta);
    }

    fclose(arquivo);
}

void carregarPerguntas(Pergunta perguntas[], int *totalPerguntas) {
    FILE *arquivo;

    *totalPerguntas = 0;
    arquivo = fopen(ARQUIVO_PERGUNTAS, "r");
    if (arquivo == NULL) {
        return;
    }

    while (*totalPerguntas < MAX_PERGUNTAS &&
           fscanf(arquivo, " %199[^;];%99[^;];%99[^;];%99[^;];%99[^;]; %c",
                  perguntas[*totalPerguntas].enunciado,
                  perguntas[*totalPerguntas].alternativas[0],
                  perguntas[*totalPerguntas].alternativas[1],
                  perguntas[*totalPerguntas].alternativas[2],
                  perguntas[*totalPerguntas].alternativas[3],
                  &perguntas[*totalPerguntas].respostaCorreta) == 6) {
        (*totalPerguntas)++;
    }

    fclose(arquivo);
}

void salvarHistorico(Jogador jogadores[], int totalJogadores) {
    FILE *arquivo;
    int i;

    arquivo = fopen(ARQUIVO_HISTORICO, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir historico.txt para gravar.\n");
        return;
    }

    for (i = 0; i < totalJogadores; i++) {
        fprintf(arquivo, "%s;%d;%d;%.2f\n",
                jogadores[i].nome,
                jogadores[i].acertos,
                jogadores[i].totalPerguntas,
                jogadores[i].percentual);
    }

    fclose(arquivo);
}

void carregarHistorico(Jogador jogadores[], int *totalJogadores) {
    FILE *arquivo;

    *totalJogadores = 0;
    arquivo = fopen(ARQUIVO_HISTORICO, "r");
    if (arquivo == NULL) {
        return;
    }

    while (*totalJogadores < MAX_JOGADORES &&
           fscanf(arquivo, " %49[^;];%d;%d;%f",
                  jogadores[*totalJogadores].nome,
                  &jogadores[*totalJogadores].acertos,
                  &jogadores[*totalJogadores].totalPerguntas,
                  &jogadores[*totalJogadores].percentual) == 4) {
        (*totalJogadores)++;
    }

    fclose(arquivo);
}
