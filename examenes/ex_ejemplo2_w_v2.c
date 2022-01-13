#include <stdlib.h>
#include <stdio.h>
#include "ex_ejemplo2_w_v2.h"


int main(){


  return 0;
}


tNodo *crearNodo(char celdas[N]){

    tNodo *n = malloc(sizeof(tNodo));

    memcpy(n->tablero,celdas,sizeof(celdas));//Copio el tablero

    n->colocadas_max = n->colocadas_min = 0;
    

return n;
}

//Crea el estado inicial
tNodo *NodoInicial(){
    return crearNodo(inicial);
}

int esValida(tNodo *actual, int jugada){

return actual->tablero[jugada-1] != ' ' && actual->colocadas_max + actual->colocadas_min < N;

}


tNodo *aplicaJugada(tNodo *actual, int jogador, int jugada){

    tNodo *nuevo = malloc(sizeof(tNodo));

    memcpy(nuevo,actual,sizeof(tNodo));

    char ficha = ' ';
    if(jogador == 1){
        nuevo->colocadas_max+=1;
       
        ficha = 'X';
    }
    else{//min
        nuevo->colocadas_min+=1;
        
        ficha  = 'O';
    }

    nuevo->tablero[jugada-1]= ficha;

return nuevo;
}

int terminal(tNodo *actual){

    int puntos_max=0;
    int puntos_min=0;

    for (int i = 0; i < N && puntos_max != 15 && puntos_min != 15; i++)
    {
        if(actual->tablero[i]== 'X'){
            puntos_max+=i+1;
        }
        else if(actual->tablero[i]== 'O'){
            puntos_min+=i+1;
        }
    }

    if(actual->colocadas_max >= 3 && puntos_max == 15)
        return 100;
    else if (actual->colocadas_min >= 3 && puntos_min == 15){
        return -100;
    }

    if(actual->colocadas_max + actual->colocadas_min == N)
        return 0;
    else{
        return 0;
    }

}

//Funcion Heuristica ==> 
int funcion_heuristica(tNodo *actual,int jugador){

    int puntos = 0;
    
    for (int i = 0; i < N ; i++)
    {
        if(actual->tablero[i]== 'X' && jugador== 1){
            puntos+=i+1;
        }
        else if(actual->tablero[i]== 'O' && jugador == -1){
            puntos+=i+1;
        }
    }


return abs(15-puntos) * jugador;
}