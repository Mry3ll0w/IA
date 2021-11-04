#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 8
#define IZQ 1
#define DCHA 2
#define NUM_OPERADORES 2

typedef struct tEstado{
    int cinta[N];
    int lado_izq; //extremos cambiantes
    int lado_dcha;
    int cant_robado;//ladrones
    int recuperado; //banco
}tEstado;

tEstado* crearEstado(int cinta[N]);
int esValido(unsigned op,tEstado *e);
tEstado* aplicaOperador(unsigned op, tEstado *e);
int testObjetivo(tEstado *e);