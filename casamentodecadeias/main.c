#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "casamentoCadeias.h"

int main() {
    FILE *arq;
    TipoTexto texto;
    TipoPadrao padrao;
    long n, m;
    int metodo;

    /* Leitura do padrao */
    printf("Digite o padrao a ser buscado: ");
    fgets(padrao, MAXTAMPADRAO, stdin);
    padrao[strcspn(padrao, "\n")] = '\0';
    m = strlen(padrao);

    if (m == 0) {
        printf("Padrao vazio.\n");
        return 1;
    }

    /* Abertura do arquivo */
    arq = fopen("arquivo.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo.txt\n");
        return 1;
    }

    /* Leitura do texto */
    n = fread(texto, sizeof(char), MAXTAMTEXTO - 1, arq);
    texto[n] = '\0';
    fclose(arq);

    /* Escolha do metodo */
    printf("Escolha o metodo de busca:\n");
    printf("1 - Forca Bruta\n");
    printf("2 - Boyer-Moore-Horspool (BMH)\n");
    printf("3 - Boyer-Moore-Horspool (BMH DEBUG)\n");
    printf("Opcao: ");
    scanf("%d", &metodo);

    printf("\n");

    switch (metodo) {

        case 1:
            forcaBruta(texto, n, padrao, m);
            break;

        case 2:
            BMH(texto, n, padrao, m);
            break;

        case 3:
            BMH_debug(texto, n, padrao, m);
            break;

        default:
            printf("Metodo invalido.\n");
    }

    return 0;
}
