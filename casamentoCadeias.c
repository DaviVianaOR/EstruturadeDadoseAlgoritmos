#include <stdio.h>
#include "casamentoCadeias.h"

void forcaBruta(TipoTexto T, long n, TipoPadrao P, long m) {
    long i, j, k;

    for (i = 1; i <= (n - m + 1); i++) {
        k = i;
        j = 1;

        while (j <= m && T[k - 1] == P[j - 1]) {
            j++;
            k++;
        }

        if (j > m) {
            printf("Casamento na posicao %3ld\n", i);
        }
    }
};