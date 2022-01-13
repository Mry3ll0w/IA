#include <stdlib.h>
#include <stdio.h>

#define N 9
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


int main(){

    return 0;
}

typedef struct {

    char tablero[N];//Sumar + 1 pq es de 0 al 8
    
    //Para controlar que se han colocado minimo 3 jugadas
    unsigned int ocupadas_min;
    unsigned int punt_min;
    unsigned int ocupadas_max;
    unsigned int punt_max;
}tNodo;

char t_inicial[N]={'#','#','#','#','#','#','#','#','#'};

tNodo* crearNodo(char tablero[N]){

    tNodo* nodo = malloc(sizeof(tNodo));
    memcpy(nodo->tablero, tablero, sizeof(tablero));
    nodo->ocupadas_min =nodo->ocupadas_min =nodo->punt_max = nodo->ocupadas_max = 0;

    return nodo;
}

//Crea el estado inicial
tNodo* inicial(){
    
    return crearNodo(t_inicial);

}

//Verifica si es valida la aplicacion de una jugada
int esValido(unsigned op,tNodo *e){
    int valida = 0;

    switch(op) {

        case coloca_1:
            if (e->tablero[coloca_1-1]=='#')
            {
                valida = 1;
            }
            
        break;

        case coloca_2:
            if (e->tablero[coloca_2-1]=='#')
            {
                valida = 1;
            }
        break;

        case coloca_3:
            if (e->tablero[coloca_3-1]=='#')
            {
                valida = 1;
            }
        break;

        case coloca_4:
            if (e->tablero[coloca_4-1]=='#')
            {
                valida = 1;
            }
        break;

        case coloca_5:
            if (e->tablero[coloca_5-1]=='#')
            {
                valida = 1;
            }
        break;

        case coloca_6:
            if (e->tablero[coloca_6-1]=='#')
            {
                valida = 1;
            }
        break;

        case coloca_7:
            if (e->tablero[coloca_7-1]=='#')
            {
                valida = 1;
            }
        break;

        case coloca_8:
            if (e->tablero[coloca_8-1]=='#')
            {
                valida = 1;
            }
        break;

        case coloca_9:
            if (e->tablero[coloca_9-1]=='#')
            {
                valida = 1;
            }
        break;

    }
return valida;
}

tNodo *aplicaJugada(tNodo *a, int jugador, int jugada){

    tNodo *nuevo = (tNodo *) malloc(sizeof(tNodo));
    memcpy(nuevo,a,sizeof(tNodo));//copiamos el nodo

   

    if (jugador == 1)
    {
        nuevo->tablero[jugada-1]='X';
        nuevo->ocupadas_max++;
        nuevo->punt_max+=jugada;//Jugada tiene la puntuacion
    }
    else{
        nuevo->tablero[jugada-1]='O';
        nuevo->ocupadas_min++;
        nuevo->punt_min+=jugada;
    }

    return nuevo;
}

int terminal(tNodo *n)
{
   
    int res=0;

    if (n->punt_max >= 15 && n->ocupadas_min >= 3)
    {
        res = 1;
    }
    else if(n->punt_min >= 15 && n->ocupadas_max >= 3){
        res = -1;
    }
    
    return res*100;
}

//La heuristica sera cuanto queda para llegar al objetivo ( 15 )
int heuristica(tNodo *n, int jugador){
    
    int res=0;

    if (jugador==1)
    {
        res = abs(15 - n->punt_max);
    }
    else{
        res = abs(15 - n->punt_min);
    }
    
return res*jugador;//Si es min sera - y si es max sera +
}

