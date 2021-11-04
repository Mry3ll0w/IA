#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//variables
#define N 2
#define vacio 0
//operaciones
#define ARRIBA 1
#define ABAJO 2
#define IZQUIERDA 3
#define DERECHA 4
//numero de operadores
#define NUM_OPERADORES 4


typedef struct tEstado{
    int tablero[N][N];// representar
    int filas[N*N];//Se usa para controlar las posiciones
    int cols[N*N];//igual que filas
    /* ESTADO INICIAL
        0 1                             0   1   2   3 <- Representa los numeros dados 
        3 2   elemento 0 -->   filas    0   0   1   1
                               cols     0   1   1   0
    */      
   int tablero_final[N][N];                   
}tEstado;

//cabeceras de funciones
int esValido(unsigned int, tEstado *estado);
tEstado *aplicaOperador(unsigned op, tEstado *a);
 int testObjetivo(tEstado *estado);