#ifndef JARRA_H
#define JARRA_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LLENAR4 1
#define LLENAR3 2
#define VACIAR4 3
#define VACIAR3 4
#define LLENAR4CON3 5
#define LLENAR3CON4 6
#define VACIAR3EN4 7
#define VACIAR4EN3 8
#define NUM_OPERADORES 8

typedef struct tEstado {
    int J4, J3;
}tEstado;

tEstado *estadoInicial();
int testObjetivo(tEstado *estado);
int esValido(unsigned op, tEstado*s);
tEstado *aplicaOperador(unsigned op,tEstado *s);
tEstado *estadoInicial();
int testObjetivo(tEstado *estado);
int esValido(unsigned op, tEstado*s);
tEstado *aplicaOperador(unsigned op,tEstado *s);

#endif