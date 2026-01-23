#ifndef casamentoCadeias_H
#define casamentoCadeias_H

#define MAXTAMTEXTO 1000
#define MAXTAMPADRAO 10 
#define MAXCHAR 256
#define NUMMAXERROS 10

typedef char TipoTexto[MAXTAMTEXTO];
typedef char TipoPadrao[MAXTAMPADRAO];

void forcaBruta(TipoTexto T, long int n, TipoPadrao P, long int m);

#endif
