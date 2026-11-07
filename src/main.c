#include <stdio.h>
#include "funcoes.h"

int main(void) {
    Pergunta perguntas[MAX_PERGUNTAS];  
    Jogador jogadores[MAX_JOGADORES];
    int totalPerguntas = 0;
    int totalJogadores = 0;
    char opcao = ' ';

    carregarPerguntas(perguntas, &totalPerguntas);
    carregarHistorico(jogadores, &totalJogadores);

    while (opcao != '0') {
        exibirMenu();
        printf("Escolha: ");
        scanf(" %c", &opcao);

        if (opcao == '1') {
            jogar(perguntas, totalPerguntas, jogadores, &totalJogadores);
        } else if (opcao == '2') {
            cadastrarPergunta(perguntas, &totalPerguntas);
            salvarPerguntas(perguntas, totalPerguntas);
        } else if (opcao == '3') {
            exibirRanking(jogadores, totalJogadores);
        } else if (opcao == '0') {
            printf("Ate mais!\n");
        } else {
            printf("Opcao invalida.\n");
        }
    }

    return 0;
}
