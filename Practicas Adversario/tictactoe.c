/*******************************************/
/* 		    tictactoe.c                    */
/*       Estrategia MiniMax                */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tictactoe.h"

//Llama a creanodo (por algun motivo no se llama directamente)
tNodo *estadoInicial()
{
   return crearNodo(tablero_inicial);
}

//Crea un Tnodo inicial para comenzar a operar sobre el tablero
tNodo *crearNodo(int celdas[N])
{
    tNodo *Nodo = (tNodo *) malloc(sizeof(tNodo));//Reserva de memoria para el nuevo tNodo
    int i, c;
    Nodo->vacias=0;
    for (i=0;i<N;i++){
        c=celdas[i];
        Nodo->celdas[i]=c;//Metemos el valor de celdas[i](input) en el nuevo nodo->celdas[i]
        
        //Si la celda esta vacia aumentamos en uno el nº de vacias
        if (c==0)
	        Nodo->vacias=Nodo->vacias+1;
    }
    return Nodo;
}

//Aplica la jugada deseada, donde la jugada va del 1 - 9 (nº de huecos del tic tac toe 3X3)
tNodo *aplicaJugada(tNodo *actual, int jugador, int jugada){
    tNodo *nuevo = (tNodo *) malloc(sizeof(tNodo));
    memcpy(nuevo,actual,sizeof(tNodo));
    nuevo->celdas[jugada]=jugador;// marca la posicion que indica jugadas pone la marca del jugador
    nuevo->vacias--;  
    return nuevo;
}

//Comprueba la validacion de una jugada
int esValida(tNodo *actual, int jugada){
    return (jugada>=0 && jugada<9 && actual->celdas[jugada]==0);
    //si esta vacia la posicion, la jugada es valido
}

//Devuelve el opuesto al jugador 
int opuesto( int jugador){
    return (jugador * -1);//Jugador 1 y Jugador -1
}

//Si el tablero esta vacio devuelve 1, si no lo esta 0
int lleno(tNodo *tablero){
    return (tablero->vacias == 0);
}


//Preguntar en clase
int terminal(tNodo *Nodo)
{
    unsigned opciones[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i=0,res=0;
    while (res==0 && i<8) {
      if(Nodo->celdas[opciones[i][0]] != 0 &&
            Nodo->celdas[opciones[i][0]] == Nodo->celdas[opciones[i][1]] &&
            Nodo->celdas[opciones[i][0]] == Nodo->celdas[opciones[i][2]])
            res=Nodo->celdas[opciones[i][2]];  //indica que jugador ocupa las casillas ganadoras
      i++;
    }
    
    return res*100;
}

////////////////////////////////////////
//  VISUALIZACI�N DE NodoS
////////////////////////////////////////

char marca(int i) {
   switch(i) {
     case 1:
          return 'X';
     case 0:
           return ' ';
     case -1:
          return 'O';
     default: return ' ';}
}

void dispNodo(tNodo *b) {
     printf("---+---+---\n");
     printf(" %c | %c | %c\n",marca(b->celdas[0]),marca(b->celdas[1]),marca(b->celdas[2]));
     printf("---+---+---\n");
     printf(" %c | %c | %c\n",marca(b->celdas[3]),marca(b->celdas[4]),marca(b->celdas[5]));
     printf("---+---+---\n");
     printf(" %c | %c | %c\n",marca(b->celdas[6]),marca(b->celdas[7]),marca(b->celdas[8]));
     printf("---+---+---\n\n");
}

/* -------------------------------------------------------------------------- */
/*                                 PRACTICA 6                                 */
/* -------------------------------------------------------------------------- */


int funcion_heuristica(tNodo *actual,int jugador)
{
    //El valor de la heuristica viene dado por el numero de filas que puede completar
    /* Forma del tablero
        p1  p2  p3      1   0   0       1 _ 1

        p4  p5  p6

        p7  p8  p9

    */
    //Usamos la matriz curseada WINNER
    unsigned opciones[8][3] = {
        {0,1,2}, 
        {3,4,5},
        {6,7,8},
        {0,3,6},
        {1,4,7},
        {2,5,8},
        {0,4,8},
        {2,4,6}
    };
    int i=0,valHeuristica=0;
    
    //Comprobacion de todas la posibles combinaciones ganadoras (guardadas en la matriz winner)
    while (i<8) {

      if(actual->celdas[opciones[i][0]] == jugador &&
        (actual->celdas[opciones[i][1]]== 0 ||  actual->celdas[opciones[i][1]]== jugador) &&
        (actual->celdas[opciones[i][2]]== 0 ||  actual->celdas[opciones[i][2]]== jugador )&&
        (actual->celdas[opciones[i][0]]!=actual->celdas[opciones[i][1]]!=actual->celdas[opciones[i][2]])
        ){

            valHeuristica++;//Cuando se cumpla la igualdad superior entonces sabemos que la fila se puede rellenar
        
        }
        ++i;
    }

    return valHeuristica;

}







