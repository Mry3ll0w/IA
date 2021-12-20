#include <stdlib.h>
#include <stdio.h>

//Defines para el ejercicio 1
#define NUM_OPERADORES 4
#define sup_izq 1
#define sup_dch 2
#define inf_izq 3
#define inf_dch 4

#define N 6
#define pos_invalida -124

typedef struct tEstado{
    int tablero[N][N];// representa el tablero de entrada
    int pos_rob[2]; //p[0]= ejex y p[1]=eje y      

    int pos_victoria[2];//                 
}tEstado;

//cabeceras de funciones
int esValido(unsigned int, tEstado *estado);
void aplicaOperador(unsigned op, tEstado *a);
int testObjetivo(tEstado *estado);
tEstado* crearEstado(tEstado*);
int funcion_heuristica(tEstado* estado);


int main(int arg){

    return 0;
}

/*
    Robot realiza movimientos en diagonal hacia adelante o hacia atras.
    En celdas contiguas.
    Las celdas no validas se marcan con n.
    Los movimientos son Superior izq, Superior Derecha, Inferior Izquierda, Inferior Derecha.

    r   1   2   3

    0   1   2   3

    0   1   2   3
    
    0   1   2   3
    

*/


//apartado b
int esValido(unsigned int op, tEstado* e){
    
    int valido = 0;
    switch(op){
        //Solo se pide el de superior Derecha
        case sup_dch: //case sup_dcha
            
            if ((e->pos_rob[0] - 1 >0 && e->pos_rob[1]+1 < N)&&//Posiciones Limite
                (e->tablero[e->pos_rob[0] - 1][e->pos_rob[1] + 1]!= pos_invalida)//Comprobamos que no coincida con una celda bloqueada
            )
                valido = 1;

        break;

        default: printf("El operador introducido no existe\n"); break;

    }
return valido;
}

//apartado c

void aplicaOperador(unsigned op, tEstado *estado){
    
   tEstado *nuevo= (tEstado *) malloc(sizeof(tEstado));
   memcpy(nuevo, estado,sizeof(tEstado));  // Hace una copia del estado

   switch(op){

       case sup_dch://Solo se nos pide este
            nuevo->pos_rob[0]-=1;
            nuevo->pos_rob[1]+=1;
            //Desplazamiento diagonal
       break;

   }

    return nuevo;
}

inline int testObjetivo(tEstado *estado)
{
    return estado->pos_rob[0]==estado->pos_victoria[0]&&estado->pos_victoria[1]==estado->pos_rob[1];
}



//Cuanto mayor sea la diferencia mas lejos de la solucion
inline int funcion_heuristica(tEstado* estado)
{
    return abs( estado->pos_rob[0]-estado->pos_victoria[0]+estado->pos_victoria[1]-estado->pos_rob[1]);
}

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 2                                */
/* -------------------------------------------------------------------------- */
//EN un pdf adjunto


