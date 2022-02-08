#include <stdlib.h>
#include <stdio.h>

int main(){

return 0;
}

#define N 3
typedef struct{
    
    int tablero[N][N];
    
    int n1[2];
    int n2[2];
    
    int b1[2];
    int b2[2];

}tNodo;

int t[N][N]= {
    {1,0,0},
    {1,0,0},
    {0,-1,-1}
};
int b1[2]={0,0};
int b2[2]={0,1};

int n1[2]={1,2};
int n2[2]={2,2};

tNodo *crea_nodo(int t[N][N], int n1[2], int n2[2], int b1[2], int b2[2]){

    tNodo *n = malloc(sizeof(tNodo));
    
    memcpy(n->tablero,t, sizeof(t));
    
    memcpy(n->b1,b1,sizeof(b1));
    memcpy(n->b2,b2,sizeof(b2));

    memcpy(n->n1,n1,sizeof(n1));
    memcpy(n->n2,n2,sizeof(n2));


return n;
}

tNodo* inicial(){
    return crea_nodo(t,n1,n2,b1,b2);
}

#define NUM_OPERADORES 12

#define arr_n1 1
#define arr_n2 2

#define der_n1 3
#define der_n2 4

#define ab_n1 5
#define ab_n2 6

#define arr_b1 7
#define arr_b2 8

#define izq_b1 9
#define izq_b2 10

#define der_b1 11
#define der_b2 12

int esValida(tNodo *actual, int jugada){

    int valido = 0;

    switch (jugada){
        
        case arr_n1:
            if (
                actual->n1[1]+1 < N && //No se sale
                actual->tablero[actual->n1[0]+1][actual->n1[1]] == 0 //La posicion superior esta vacia
            ){
                valido = 1;
            }
        break;

        case arr_n2:
            if (
                actual->n2[1]+1 < N && //No se sale
                actual->tablero[actual->n2[0]+1][actual->n2[1]] == 0 //La posicion superior esta vacia
            ){
                valido = 1;
            }
        break;

        case der_n1:
            if (
                actual->n1[0]+1 < N && //No se sale
                actual->tablero[actual->n1[0]][actual->n1[1]+1] == 0 //La posicion superior esta vacia
            ){
                valido = 1;
            }
        break;

        case der_n2:
            if (
                actual->n2[0]+1 < N && //No se sale
                actual->tablero[actual->n2[0]][actual->n2[1]+1] == 0 //La posicion superior esta vacia
            ){
                valido = 1;
            }
        break;

        case ab_n1:
            if (
                actual->n1[0]-1 > 0 && //No se sale
                actual->tablero[actual->n1[0]-1][actual->n1[1]] == 0 //La posicion superior esta vacia
            ){
                valido = 1;
            }
        break;

        case ab_n2:
            if (
                actual->n2[0]-1 > 0 && //No se sale
                actual->tablero[actual->n2[0]-1][actual->n2[1]] == 0 //La posicion superior esta vacia
            ){
                valido = 1;
            }
        break;

        case arr_b1:
            if (
                actual->b1[1]+1 < N && //No se sale
                actual->tablero[actual->b1[0]+1][actual->b1[1]] == 0 //La posicion superior esta vacia
            ){
                valido = 1;
            }
        break;

        case arr_b2:
            if (
                actual->b2[1]+1 < N && //No se sale
                actual->tablero[actual->b2[0]+1][actual->b2[1]] == 0 //La posicion superior esta vacia
            ){
                valido = 1;
            }
        break;

        case izq_b1:
            if (
                actual->b1[1]-1 < 0 && //No se sale
                actual->tablero[actual->b1[0]][actual->b1[1]-1] == 0 //La posicion superior esta vacia
            ){
                valido = 1;
            }
        break;

        case izq_b2:
            if (
                actual->b2[1]-1 < 0 && //No se sale
                actual->tablero[actual->b2[0]][actual->b2[1]-1] == 0 //La posicion superior esta vacia
            ){
                valido = 1;
            }
        break;

        case der_b1:
            if (
                actual->b1[0]+1 < N && //No se sale
                actual->tablero[actual->b1[0]][actual->b1[1]+1] == 0 //La posicion superior esta vacia
            ){
                valido = 1;
            }
        break;

        case der_b2:
            if (
                actual->b2[0]+1 < N && //No se sale
                actual->tablero[actual->b2[0]][actual->b2[1]+1] == 0 //La posicion superior esta vacia
            ){
                valido = 1;
            }
        break;

    }

return valido;
}


tNodo *aplicaJugada(tNodo *actual, int jugador, int jugada);//muchisima pereza


//Comrpueba si un estado es terminal
int terminal(tNodo *actual){
    
    if( 
        (actual->n1[0] == 0 && actual->n1[1] == 2 ||
        actual->n1[0] == 1 && actual->n1[1] == 2 ||
        actual->n1[0] == 2 && actual->n1[1] == 2
        )
        &&
        (
            actual->n2[0] == 0 && actual->n2[1] == 2 ||
            actual->n2[0] == 1 && actual->n2[1] == 2 ||
            actual->n2[0] == 2 && actual->n2[1] == 2
        ) 
    )
        return 100;
    
    if( 
        (actual->b1[0] == 0 && actual->b1[1] == 0 ||
        actual->b1[0] == 0 && actual->b1[1] ==  1||
        actual->b1[0] == 0 && actual->b1[1] == 2
        )
        &&
        (
            actual->b1[0] == 0 && actual->b1[1] == 0 ||
            actual->b1[0] == 0 && actual->b1[1] ==  1||
            actual->b1[0] == 0 && actual->b1[1] == 2
        ) 
    )
        return -100;
    
    
}


int funcion_heuristica(tNodo *a,int jugador){

    return (abs( (a->n1[1] - 2) + (a->n2[1] - 2)  ) + abs((0 - a->b1[1])+(0 - a->b2[1] )))*jugador;

}