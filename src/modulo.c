#include <stdio.h>
#include "modulo.h"

char lerResposta(void) {
    char letra;

    scanf(" %c", &letra);
    while (letra < 'A' || letra > 'D') {
        printf("Resposta invalida. Digite A, B, C ou D: ");
        scanf(" %c", &letra);
    }

    return letra;
}
