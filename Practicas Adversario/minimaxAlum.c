/*******************************************/
/* 		    minimaxAlum.c                  */
/*       Estrategia MiniMax                */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tictactoe.h"



tNodo *PSEUDOminimax(tNodo *t) {
     int mejorJugada = -1;
     int puntos = -2;
     int i, temp;
     tNodo *intento=malloc(sizeof(tNodo));
     printf("\n Mi turno: \n");

     for(i = 0; i < 9; ++i){ // 9 Es el numero de casillas donde puedes colocar una ficha
            //Va recorriendo todas las jugadas para obtener la de mejor heuristica/valor de utilidad 
            if (esValida(t,i)){
                  intento=aplicaJugada(t,1,i); //Intenta jugada
                  temp = terminal(intento); // Calcula el valor minimax
                  if(temp > puntos) {
                        puntos = temp;
                        mejorJugada = i;
                  }
            }

      }//for
      
      t=aplicaJugada(t,1,mejorJugada);
      return t;
}

tNodo *jugadaAdversario(tNodo *t) { //Seleccion de Jugada por parte del jugador (no agente inteligente)
     int jugada = 0;
     printf("\nJugada ([0..8])?: ");
     scanf("%d", &jugada);
     while (!esValida(t,jugada))
     {
        printf("\n Intenta otra posicion del tablero \n");
        printf("\n");
        printf("\nJugada ([0..8])?: ");
        scanf("%d", &jugada);
     }
     t=aplicaJugada(t,-1,jugada);
     return t;
}


