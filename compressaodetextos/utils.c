#include "utils.h"
#include <stdio.h>

#include <stdio.h>
#include "utils.h"

// Função auxiliar para imprimir o vetor em uma única linha dentro da tabela
// Imprime o vetor respeitando a lacuna no índice 1 se necessário
void imprimirLinhaVetor(int A[], int n, int vazioNoUm) {
    printf("[");
    for (int i = 1; i <= n; i++) {
        if (vazioNoUm && i == 1) printf("  ");
        else printf("%2d", A[i]);
        if (i < n) printf(",");
    }
    printf("]");
}

void PrimeiraFase(int A[], int n) {
    int Raiz = n;
    int Folha = n;
    int Prox;
    int valor_filho;

    printf("\n>>> RASTREAMENTO DETALHADO FASE 1: REDUCAO\n");
    printf("+------+------+----------+-------+-------+----------------------+\n");
    printf("| Etapa| Prox | V. Filho | Raiz  | Folha | Vetor A              |\n");
    printf("+------+------+----------+-------+-------+----------------------+\n");
    
    // Etapa 0: Estado Inicial
    printf("|   0  |  --  |    --    | %5d | %5d | ", Raiz, Folha);
    imprimirLinhaVetor(A, n, 0);
    printf(" |\n");

    int etapa = 1;
    for (Prox = n; Prox >= 2; Prox--) {
        /* SELEÇÃO DO PRIMEIRO FILHO */
        if ((Folha < 1) || ((Raiz > Prox) && (A[Raiz] <= A[Folha]))) {
            valor_filho = A[Raiz]; // Valor do nó interno
            A[Prox] = A[Raiz];
            A[Raiz] = Prox;
            Raiz--;
        } else {
            valor_filho = A[Folha]; // Valor da folha
            A[Prox] = A[Folha];
            Folha--;
        }
        
        printf("| %4d | %4d | %8d | %5d | %5d | ", etapa++, Prox, valor_filho, Raiz, Folha);
        imprimirLinhaVetor(A, n, 0);
        printf(" |\n");

        /* SELEÇÃO E SOMA DO SEGUNDO FILHO */
        if ((Folha < 1) || ((Raiz > Prox) && (A[Raiz] <= A[Folha]))) {
            valor_filho = A[Raiz];
            A[Prox] += A[Raiz];
            A[Raiz] = Prox;
            Raiz--;
        } else {
            valor_filho = A[Folha];
            A[Prox] += A[Folha];
            Folha--;
        }

        printf("| %4d | %4d | %8d | %5d | %5d | ", etapa++, Prox, valor_filho, Raiz, Folha);
        imprimirLinhaVetor(A, n, 0);
        printf(" |\n");
    }
    printf("+------+------+----------+-------+-------+----------------------+\n");
}

void SegundaFase(int A[], int n) {
    printf("\n>>> RASTREAMENTO FASE 2: NIVEIS (A[1] VAZIO)\n");
    printf("+-------+----------------------+\n");
    printf("| Prox  | Vetor A              |\n");
    printf("+-------+----------------------+\n");

    A[2] = 0; 
    printf("|  init | "); imprimirLinhaVetor(A, n, 1); printf(" |\n");

    for (int Prox = 3; Prox <= n; Prox++) {
        A[Prox] = A[A[Prox]] + 1;
        printf("| %5d | ", Prox);
        imprimirLinhaVetor(A, n, 1);
        printf(" |\n");
    }
}

void TerceiraFase(int A[], int n) {
    int Disp = 1, u = 0, h = 0, Raiz = 2, Prox = 1;
    printf("\n>>> RASTREAMENTO FASE 3: BITS\n");
    printf("+------+---+---+------+------+----------------------+\n");
    printf("| Disp | u | h | Raiz | Prox | Vetor A              |\n");
    printf("+------+---+---+------+------+----------------------+\n");

    while (Disp > 0) {
        while (Raiz <= n && A[Raiz] == h) { u++; Raiz++; }
        while (Disp > u) {
            A[Prox] = h;
            Prox++; Disp--;
            printf("| %4d | %d | %d | %4d | %4d | ", Disp, u, h, Raiz, Prox - 1);
            imprimirLinhaVetor(A, n, 0);
            printf(" |\n");
        }
        Disp = 2 * u;
        h++; u = 0;
    }
}

void CalculaCompCodigo(int A[], int n){
    PrimeiraFase (A, n);
    SegundaFase (A, n);
    TerceiraFase (A, n);
}

int compararTokens(const void *a, const void *b) {
    Token *t1 = (Token *)a;
    Token *t2 = (Token *)b;
    
    // Ordem Decrescente: Se t2 > t1, retorna positivo (troca)
    if (t2->freq > t1->freq) return 1;
    if (t2->freq < t1->freq) return -1;
    return 0;
}

void imprimirVetorBonito(const char *etapa, int A[], int n, int mostrarVazio) {
    printf("\n>>> %s\n", etapa);
    
    // Topo da tabela
    printf("+---------");
    for (int i = 1; i <= n; i++) printf("+-----");
    printf("+\n");

    // Linha de Índices
    printf("| INDICE  ");
    for (int i = 1; i <= n; i++) printf("| %3d ", i);
    printf("|\n");

    // Divisória Central
    printf("+---------");
    for (int i = 1; i <= n; i++) printf("+-----");
    printf("+\n");

    // Linha de Valores
    printf("| VALOR   ");
    for (int i = 1; i <= n; i++) {
        if (mostrarVazio && i == 1) {
            printf("| [ ] "); // Representação da posição vazia
        } else {
            printf("| %3d ", A[i]);
        }
    }
    printf("|\n");

    // Base da tabela
    printf("+---------");
    for (int i = 1; i <= n; i++) printf("+-----");
    printf("+\n");
}