#include <stdlib.h>
#include <stdio.h>

#define N 9

/* -------------------------------------------------------------------------- */
/*                                 APARTADO A                                 */
/* -------------------------------------------------------------------------- */
typedef struct {
  
  char tablero[N];
  
  int colocadas_max;//Para MAX
  
  int colocadas_min;//Para MIN
  
  

}tNodo;

//Definir tablero inicial
char inicial[N]={' ',' ',' ',' ',' ',' ',' ',' ',' '};

//Crea Un estado basandose en un tablero de entrada
tNodo *crearNodo(char celdas[N]);

//Crea el estado inicial
tNodo *NodoInicial();

/* -------------------------------------------------------------------------- */
/*                                 APARTADO B                                 */
/* -------------------------------------------------------------------------- */
#define NUM_OPERADORES 9
#define coloca_1 1
#define coloca_2 2
#define coloca_3 3
#define coloca_4 4
#define coloca_5 5
#define coloca_6 6
#define coloca_7 7
#define coloca_8 8
#define coloca_9 9


//Comrpueba si una jugada es valida
int esValida(tNodo *actual, int jugada);

/* -------------------------------------------------------------------------- */
/*                                 APARTADO C                                 */
/* -------------------------------------------------------------------------- */
//Aplica la jugada a un nodo dado
tNodo *aplicaJugada(tNodo *actual, int jugador, int jugada);

/* -------------------------------------------------------------------------- */
/*                                 APARTADO D                                 */
/* -------------------------------------------------------------------------- */

//Comrpueba si un estado es terminal
int terminal(tNodo *actual);

/* -------------------------------------------------------------------------- */
/*                                 APARTADO E                                 */
/* -------------------------------------------------------------------------- */
int funcion_heuristica(tNodo *actual,int jugador);