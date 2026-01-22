#include <stdio.h>
#include <string.h>
#include "casamentoCadeias.h"

int main() {
    // 1. Declaração das variáveis usando os tipos do seu módulo
    TipoTexto texto = "ABRACADABRA";
    TipoPadrao padrao = "ABRA";

    // 2. Cálculo do tamanho (n para o texto, m para o padrão)
    long int n = strlen(texto);
    long int m = strlen(padrao);

    printf("Buscando '%s' em '%s'...\n", padrao, texto);
    printf("----------------------------------\n");

    // 3. Chamada da função do módulo
    forcaBruta(texto, n, padrao, m);

    printf("----------------------------------\n");
    printf("Busca finalizada.\n");

    return 0;
}
