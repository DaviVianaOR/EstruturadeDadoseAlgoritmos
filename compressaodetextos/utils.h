#ifndef utils_h
#define utils_h
#include <stdio.h>

typedef struct {
    char termo[100];       // A palavra propriamente dita
    int freq;              // Frequência (usada na Fase 1)
    int bits;              // Comprimento do código (resultado da Fase 3)
} ItemVocabulario;

typedef struct {
    char palavra[100];
    int freq;
    int bits;
} Token;



void PrimeiraFase(int A[], int n);
void SegundaFase(int A[], int n);
void TerceiraFase(int A[], int n);
void CalculaCompCodigo(int A[], int n);
int compararTokens(const void *a, const void *b);
void imprimirVetorBonito(const char *etapa, int A[], int n, int mostrarVazio);

#endif