/*******************************************/
/* 		      PUZLE.C                      */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "puzle.h"



tEstado *crearEstado(int puzle[N][N])
{
   tEstado *estado = (tEstado *) malloc(sizeof(tEstado));
   int i, j, ficha;

   for (i=0;i<N;i++)
      for (j=0;j<N;j++)
      {
         ficha=puzle[i][j];
         estado->celdas[i][j]=ficha;
         estado->fila[ficha]=i;
         estado->col[ficha]=j;
      }
   return estado;
}


tEstado *estadoInicial()
{
   return crearEstado(puzle_inicial);
}


tEstado *estadoObjetivo()
{
   return crearEstado(puzle_final);
}

int coste(unsigned op, tEstado *estado)
{
   return 1;
}

/* VISUALIZACI�N DE ESTADOS Y OPERADORES*/


void dispEstado(tEstado *estado)
{
   int i,j;

   for (i=0; i<N; i++)
   {
      for (j=0; j<N; j++)
         printf("%d",estado->celdas[i][j]);
      printf("\n");
   }
   printf("\n");
}


void dispOperador(unsigned op)
{
   switch(op)
   {
      case ARRIBA:    printf("Movimiento ARRIBA:\n"); break;
      case ABAJO:     printf("Movimiento ABAJO:\n"); break;
      case IZQUIERDA: printf("Movimiento IZQUIERDA:\n"); break;
      case DERECHA:   printf("Movimiento DERECHA:\n"); break;
      default: break;
   }
}

// FUNCIONES QUE SE HAN DE IMPLEMENTAR EN LA PRACTICA 1

// Funci�n auxiliar para comprobar si dos puzles tienen las fichas colocadas en el mismo orden en el tablero
int iguales(tEstado *s, tEstado *t)  //
{
   int token = 1;
   for ( int i=0; i< N && token!=0;i++ ){
      for ( int j=0; j< N && token!=0; j++){
         if (s->celdas[i][j] != t->celdas[i][j])
         {
            token = 0;
         }
      }
   }
return token;
}


int testObjetivo(tEstado *estado) // ok
{
   int token=1;
   for ( int i=0; i<N && token!=0 ;i++ ){
       for ( int j=0; j<N && token!=0 ; j++){
           if (estado->celdas[i][j] != puzle_final[i][j])
           {
               token=0;
           }
       }
   }
return token;
}


int esValido(unsigned op, tEstado *estado)
{
   int valido=0;//token bool
    switch(op){
        case ARRIBA://Necesitamos comprobar donde esta el hueco
            valido = (estado->fila[0]>vacio);//Si hay un hueco esta en la filas superior
        break;
        case ABAJO:
            valido = (estado->fila[0]<N-1);
        break;
        case IZQUIERDA:
            valido = (estado->col[0]>vacio);//Igual que la primera solo que al ser izquierda tiene que ser cols
        break;
        case DERECHA:
            valido = (estado->col[0]<N-1);
        break; // CUANDO Mueves de derecha izquierda cambias de columna y arriba/abajo cambias de fila
        default:
        break;
    }
    return valido;
}


tEstado *aplicaOperador(unsigned op, tEstado *estado)
{
   tEstado *nuevo= (tEstado *) malloc(sizeof(tEstado));
   memcpy(nuevo, estado,sizeof(tEstado));  // Hace una copia del estado

   int ficha;
   switch(op)
   {
      case ARRIBA:
      //1 metemos en ficha el anterior para hacerle swap con el siguiente
         ficha = estado->celdas[estado->fila[0]-1][estado->col[0]];
         nuevo->fila[0]--;//decrementamos el valor de fila pq se ha cambiado
         nuevo->fila[ficha]++; //actulizar valor de ficha
      break;

      case ABAJO: //RECIPROCO de Arriba (Arriba inverso y ya)
         ficha = estado->celdas[estado->fila[0]+1][estado->col[0]];
         nuevo->fila[0]++;
         nuevo->fila[ficha]--;
      break;

      case IZQUIERDA:
         //Realizamos lo mismo que en arriba pero en caso de desp izq/dch se modifican las cols no fila
         ficha = estado->celdas[estado->fila[0]][estado->col[0]-1];
         nuevo->col[0]--;
         nuevo->col[ficha]++;
      break;
      case DERECHA:
         ficha = estado->celdas[estado->fila[0]][estado->col[0]+1];
         nuevo->col[0]++;
         nuevo->col[ficha]--;
      break;
      default:  break;
    }
    //cambio se hace siempre para no tener 2 en el mismo sitio (swap dentro de la matriz)
    //valor de hueco es cte
    nuevo->celdas[nuevo->fila[0]][nuevo->col[0]] = 0;
    nuevo->celdas[nuevo->fila[ficha]][nuevo->col[ficha]] = ficha;


return nuevo;
}

//PRACTICA 2
int mal_colocadas_heuristica(tEstado *estado, tEstado *objetivo){
    int cont_mal_colocadas = 0;
    for(int i = 0 ; i< N ; i++){
        for (int j = 0; j < N ; ++j) {
            if (estado->celdas[i][j] != objetivo->celdas[i][j]){
            cont_mal_colocadas++;
            }
        }
    }
    return cont_mal_colocadas;
}

