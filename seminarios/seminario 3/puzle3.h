#include<stdio.h>
#include<stdlib.h>

#define ARRIBA_A 1
#define ABAJO_A 2
#define IZQDA_A 3
#define DCHA_A 4

#define ARRIBA_B 5
#define ABAJO_B 6
#define IZQDA_B 7
#define DCHA_B 8

#define ARRIBA_C 9
#define ABAJO_C 10
#define IZQDA_C 11
#define DCHA_C 12
#define N 6
#define NUM_OPERADORES 12
#define nf 3
//sabemos la forma que tiene los tipo A por tanto vale el representante
//cada pieza tiene un representante el cual guardamos la posicion
#ifndef _tEstado_
#define _tEstado_ 
typedef struct tEstado {
    int tablero [N][N]; //obstaculo -1 , A = 1 ,B = 2 , C=3 
    int filas [nf+1]; // gasto peruano de memoria por comodidad 
    int col[nf+1]; // nada 1 2 3 

}tEstado;
#endif //para controlar problemas de Redefinicion

tEstado* crearEstado(int celdas[N][N]);
int testObjetivo(tEstado * e,tEstado * obj);
int esValido(unsigned op, tEstado *e);
tEstado * aplicaOperador(unsigned op, tEstado * e);