#include "utils.h"
#include <stdio.h>

#include <stdio.h>
#include "utils.h"

// Função auxiliar para imprimir o vetor em uma única linha dentro da tabela
// Imprime o vetor respeitando a lacuna no índice 1 se necessário
#include <stdio.h>
#include "utils.h"

void imprimirLinhaVetor(int A[], int n, int vazioNoUm) {
    printf("[");
    for (int i = 1; i <= n; i++) {
        if (vazioNoUm && i == 1) printf(" / ");
        else printf("%2d ", A[i]);
        if (i < n) printf("|");
    }
    printf("]");
}

void PrimeiraFase(int A[], int n) {
    int Raiz = n;
    int Folha = n;
    int Prox;
    char etapa = 'a';

    printf("\n>>> FASE 1: REDUCAO (SEGUINDO LOGICA DA IMAGEM)\n");
    printf("Etapa | %-25s | Prox | Raiz | Folha\n", "Vetor A");
    printf("--------------------------------------------------------------\n");
    
    // a) Estado Inicial
    printf("  %c)  | ", etapa++);
    imprimirLinhaVetor(A, n, 0);
    printf(" | %4d | %4d | %4d\n", n, Raiz, Folha);

    for (Prox = n; Prox >= 2; Prox--) {
        // Seleção do 1º Filho
        if ((Folha < 1) || ((Raiz > Prox) && (A[Raiz] <= A[Folha]))) {
            A[Prox] = A[Raiz]; A[Raiz] = Prox; Raiz--;
        } else {
            A[Prox] = A[Folha]; Folha--;
        }
        printf("  %c)  | ", etapa++);
        imprimirLinhaVetor(A, n, 0);
        printf(" | %4d | %4d | %4d\n", Prox, Raiz, Folha);

        // Seleção do 2º Filho
        if ((Folha < 1) || ((Raiz > Prox) && (A[Raiz] <= A[Folha]))) {
            A[Prox] += A[Raiz]; A[Raiz] = Prox; Raiz--;
        } else {
            A[Prox] += A[Folha]; Folha--;
        }
        printf("  %c)  | ", etapa++);
        imprimirLinhaVetor(A, n, 0);
        printf(" | %4d | %4d | %4d\n", Prox, Raiz, Folha);
    }
    
    // k) Transição final: A[1] torna-se vazio para Fase 2
    printf("  %c)  | ", etapa);
    imprimirLinhaVetor(A, n, 1);
    printf(" | %4d | %4d | %4d\n", 1, Raiz, Folha);
}

void SegundaFase(int A[], int n) {
    printf("\n>>> FASE 2: NIVEIS (A[1] VAZIO)\n");
    A[2] = 0; 
    printf("init  | "); imprimirLinhaVetor(A, n, 1); printf("\n");

    for (int Prox = 3; Prox <= n; Prox++) {
        A[Prox] = A[A[Prox]] + 1;
        printf("P:%2d  | ", Prox);
        imprimirLinhaVetor(A, n, 1);
        printf("\n");
    }
}

void TerceiraFase(int A[], int n) {
    int Disp = 1, u = 0, h = 0, Raiz = 2, Prox = 1;
    printf("\n>>> FASE 3: COMPRIMENTOS (RASTREAMENTO COMPLETO)\n");
    printf("Disp | u | h | Raiz | Prox | Vetor A\n");
    printf("--------------------------------------------------------------\n");

    while (Disp > 0) {
        // Registra estado antes de processar o nível h
        while (Raiz <= n && A[Raiz] == h) { 
            u++; 
            Raiz++; 
        }
        
        while (Disp > u) {
            A[Prox] = h;
            printf("%4d | %d | %d | %4d | %4d | ", Disp, u, h, Raiz, Prox);
            imprimirLinhaVetor(A, n, 0);
            printf("\n");
            
            Prox++; 
            Disp--;
        }
        
        // Estado após atribuir folhas no nível h
        if (u > 0 || Disp == 0) {
            printf("%4d | %d | %d | %4d | %4d | ", Disp, u, h, Raiz, Prox);
            imprimirLinhaVetor(A, n, 0);
            printf(" (Nivel %d concluido)\n", h);
        }

        Disp = 2 * u;
        h++;
        u = 0;
    }
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