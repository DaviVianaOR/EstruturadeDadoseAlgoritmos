#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

#define MAX_PALAVRAS 1000

void isolar_simbolos(char *dest, const char *src) {
    int j = 0;
    for (int i = 0; src[i] != '\0' && j < 9990; i++) {
        if (src[i] == ',' || src[i] == '.') {
            dest[j++] = ' '; dest[j++] = src[i]; dest[j++] = ' ';
        } else { dest[j++] = src[i]; }
    }
    dest[j] = '\0';
}

int main() {
    char texto_bruto[5000], texto_proc[10000];
    Token vocab[MAX_PALAVRAS];
    int total = 0;

    printf("TESTE DE MESA - CODIFICACAO DE HUFFMAN\n");
    printf("Texto: ");
    if (!fgets(texto_bruto, sizeof(texto_bruto), stdin)) return 1;
    texto_bruto[strcspn(texto_bruto, "\n")] = 0;

    isolar_simbolos(texto_proc, texto_bruto);
    char *ptr = strtok(texto_proc, " \t\r\n");

    while (ptr != NULL && total < MAX_PALAVRAS) {
        char temp[100];
        int j = 0;
        for(; ptr[j] && j < 99; j++) temp[j] = (char)tolower((unsigned char)ptr[j]);
        temp[j] = '\0';

        int encontrado = -1;
        for (int i = 0; i < total; i++) {
            if (strcmp(vocab[i].palavra, temp) == 0) { encontrado = i; break; }
        }
        if (encontrado != -1) vocab[encontrado].freq++;
        else {
            strcpy(vocab[total].palavra, temp);
            vocab[total].freq = 1; total++;
        }
        ptr = strtok(NULL, " \t\r\n");
    }

    if (total < 2) {
        printf("Erro: Necessario ao menos 2 termos distintos.\n");
        return 1;
    }

    // Ordenação Decrescente obrigatória para bater com o modelo da foto
    qsort(vocab, total, sizeof(Token), compararTokens);

    int *A = (int*)malloc((total + 1) * sizeof(int));
    for (int i = 0; i < total; i++) A[i+1] = vocab[i].freq;

    // Execução dos rastreamentos detalhados
    PrimeiraFase(A, total);
    SegundaFase(A, total);
    TerceiraFase(A, total);

    // Tabela Final de Resultados
    printf("\n+----------------------+----------+----------+\n");
    printf("| TOKEN                | FREQ     | BITS     |\n");
    printf("+----------------------+----------+----------+\n");
    for (int i = 0; i < total; i++) {
        printf("| %-20s | %8d | %8d |\n", vocab[i].palavra, vocab[i].freq, A[i+1]);
    }
    printf("+----------------------+----------+----------+\n");

    free(A);
    return 0;
}