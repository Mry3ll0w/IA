#include <stdlib.h>
#include <stdio.h>

#define N 8
#define NUM_OPERADORES 
#define robar_der 1
#define robar_izq 2



typedef struct {
    
    int cinta[N];
    int robado; // Se guarda la cantidad robada por los ladrones
    int recuperado; //Se guarda la cantidad que el banco recupera
    int it_izq;
    int it_der;

}tEstado;

tEstado* inicial();
int esValido(unsigned op,tEstado *e);
tEstado* aplicaOperador(unsigned op, tEstado *e);
int testObjetivo(tEstado *e);