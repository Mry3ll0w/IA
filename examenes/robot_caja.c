#include <stdlib.h>
#include <stdio.h>


int main(){

  return 0;
}

/* -------------------------------------------------------------------------- */
/*                                 APARTADO A                                 */
/* -------------------------------------------------------------------------- */
//define de n y numero de operadores y tal
#define N 4 //Matrix 4x4
//OPERADORES
#define NUM_OPERADORES 9

#define robot_der 1
#define robot_izq 2
#define robot_ar 3
#define robot_ab 4

#define recoger_caja 5
#define empujar_caja_d 6
#define empujar_caja_izq 7
#define empujar_caja_ab 8
#define empujar_caja_ar 9


typedef struct {
    
    char tablero[N][N];

    int robot[2];//x e y 
    int caja[2];
    int salida[2];

    int recogida;//controla si la caja se ha recogido o no

}tEstado;

/* -------------------------------------------------------------------------- */
/*                                 apartado b                                 */
/* -------------------------------------------------------------------------- */

char t[N][N]={//B es para las bloquedas, v para las vacias
    {'R','b','b','v'},
    {'v','v','C','v'},
    {'v','v','b','v'},
    {'b','v','v','S'},
};

char objetivo [N][N]={
    {'v','b','b','v'},
    {'v','v','v','v'},
    {'v','v','b','v'},
    {'b','v','v','R'},
};

tEstado *crearEstado(int celdas[N][N]){

  tEstado* out = malloc(sizeof(tEstado));
  memcpy(out->tablero,celdas,sizeof(celdas));

  for (size_t i=0; i<N; i++){
    for (size_t j=0; j< N; j++){

      if(out->tablero[i][j]=='R'){
        out->robot[0]=i;
        out->robot[1]=j;
      }
      else if(out->tablero[i][j]=='C'){
        out->caja[0]=i;
        out->caja[1]=j;
      }
      else if(out->tablero[i][j]=='S'){
        out->salida[0]=i;
        out->salida[1]=j;
      }

    }
  }

return out;
}

/* Genera el estado inicial a partir de crearEstado y puzle_inicial. */
tEstado *estadoInicial(){
  return crearEstado(t);
}

/* Genera el estado final a partir de crearEstado y puzle_final. */
tEstado *estadoObjetivo(){
  return crearEstado(objetivo);
}

/* -------------------------------------------------------------------------- */
/*                                 apartado c                                 */
/* -------------------------------------------------------------------------- */

/* Comprueba si es posible aplicar un operador a una configuraci�n determinada para el puzle.
  Devuelve 1 si el movimiento es v�lido y 0 en otro caso. */
int esValido(unsigned op, tEstado* e){

  int token = 0;
  switch(op){

    case robot_der:
    break;

    case robot_izq:
    break;

    case robot_ar:
    break;

    case robot_ab:
    break;

    case empujar_caja_ab:
    break;

    case empujar_caja_ar:
    break;

    case empujar_caja_d:
    break;

    case empujar_caja_izq:
    break;

    case recoger_caja:
      if(
      (e->robot[0]==e->caja[0] && e->robot[1]==e->caja[1]-1 // a la derecha
        ||
        e->robot[0]==e->caja[0] && e->robot[1]==e->caja[1]+1 //a la izquierda
        ||
        e->robot[0]==e->caja[0]-1 && e->robot[1]==e->caja[1] //arriba
        ||
        e->robot[0]==e->caja[0]+1 && e->robot[1]==e->caja[1] //abajo
      )
      && e->recogida == 0 // aun no ha sido recogida
      )
      token = 1;
    break;

  }

return token;
}


/* -------------------------------------------------------------------------- */
/*                                 APARTADO D                                 */
/* -------------------------------------------------------------------------- */

/* Aplica un operador a una configuraci�n concreta del puzle.
  Devuelve la nueva configuraci�n del tablero tras el movimiento. */
tEstado *aplicaOperador(unsigned op, tEstado *estado);

/* -------------------------------------------------------------------------- */
/*                                 APARTADO E                                 */
/* -------------------------------------------------------------------------- */

/* Devuelve 1 si un estado es igual al estado objetivo. */
int testObjetivo(tEstado *estado);

/* -------------------------------------------------------------------------- */
/*                                  APARTADO F                                 */
/* -------------------------------------------------------------------------- */
/* Devuelve el coste de aplicar el operador. */
int coste(unsigned op, tEstado *estado);



/* ------------------------------- APARTADO G ------------------------------- */

int heuristica(tEstado *estado, tEstado *objetivo);