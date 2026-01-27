#include <stdio.h>
#include "casamentoCadeias.h"

/*
Códigos do livro Projeto de Algoritmos: com Implementações em Pascal e C – 3ª edição revista e ampliada
Uso apenas para estudos.
*/

/* =========================================================
   Algoritmo de Força Bruta
   ========================================================= */
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
}

/* =========================================================
   Algoritmo Boyer–Moore–Horspool (BMH)
   ========================================================= */
void BMH(TipoTexto T, long n, TipoPadrao P, long m) {
    long i, j, k;
    long d[MAXCHAR + 1];

    /* -------------------------
       Pré-processamento
       ------------------------- */
    for (j = 0; j <= MAXCHAR; j++)
        d[j] = m;

    for (j = 1; j < m; j++)
        d[(unsigned char)P[j - 1]] = m - j;

    /* -------------------------
       Pesquisa
       ------------------------- */
    i = m;
    while (i <= n) {
        k = i;
        j = m;

        while (j > 0 && T[k - 1] == P[j - 1]) {
            k--;
            j--;
        }

        if (j == 0)
            printf("Casamento na posicao: %3ld\n", k + 1);

        i += d[(unsigned char)T[i - 1]];
    }
}

void imprimeTexto(TipoTexto T, long n) {
    long i;

    printf("Texto : ");
    for (i = 0; i < n; i++)
        printf("%c ", T[i]);
    printf("\n");

    printf("Indice: ");
    for (i = 0; i < n; i++)
        printf("%ld ", i % 10);
    printf("\n");
}

void imprimePadrao(TipoPadrao P, long m, long inicio) {
    long i;

    printf("Padrao: ");
    for (i = 1; i < inicio; i++)
        printf("  ");

    for (i = 0; i < m; i++)
        printf("%c ", P[i]);

    printf("\n");
}

void BMH_debug(TipoTexto T, long n, TipoPadrao P, long m) {
    long i, j, k;
    long d[MAXCHAR + 1];
    long iteracao = 1;

    /* Pre-processamento */
    for (j = 0; j <= MAXCHAR; j++)
        d[j] = m;

    for (j = 1; j < m; j++)
        d[(unsigned char)P[j - 1]] = m - j;

    printf("=== TABELA DE DESLOCAMENTOS (d) ===\n");
    for (j = 0; j < m; j++) {
        unsigned char c = (unsigned char)P[j];
        printf("d['%c'] = %ld\n", c, d[c]);
    }

    printf("\n=== EXECUCAO DO BMH ===\n");

    i = m;
    while (i <= n) {

        printf("\n---------------------------------\n");
        printf("ITERACAO %ld\n", iteracao++);
        printf("i = %ld\n", i);

        imprimeTexto(T, n);
        imprimePadrao(P, m, i - m + 1);

        k = i;
        j = m;

        printf("\nComparacoes:\n");

        while (j > 0 && T[k - 1] == P[j - 1]) {
            printf("T[%ld] == P[%ld]  (%c == %c) OK\n",
                   k, j, T[k - 1], P[j - 1]);
            k--;
            j--;
        }

        if (j == 0) {
            printf("Resultado: CASAMENTO na posicao %ld\n", k + 1);
        } else {
            printf("Falha: T[%ld] != P[%ld]  (%c != %c)\n",
                   k, j, T[k - 1], P[j - 1]);
        }

        printf("Caractere para deslocamento: '%c'\n", T[i - 1]);
        printf("d['%c'] = %ld\n", T[i - 1], d[(unsigned char)T[i - 1]]);

        i += d[(unsigned char)T[i - 1]];
        printf("Novo i = %ld\n", i);
    }
}
