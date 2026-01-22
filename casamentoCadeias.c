#include "casamentoCadeias.h"
#include "stdio.h"

void forcaBruta(TipoTexto T, long int n, TipoPadrao P, long int m){
    long int i, j, k;
    for (i = 1; i <= (n - m + 1); i++){
        k = 1; j = 1;
        while (T[k-1] == P[j-1] && j <=m) {
            j++;
            k++;
        }
        if (j > m) printf("Casamento na posicao %3ld\n", i);
    }
}
