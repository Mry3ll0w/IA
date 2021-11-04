#include "3puzzle.h"

int esValido(unsigned int op, tEstado *estado){
    int valido=0;//token bool 
    switch(op){
        case ARRIBA://Necesitamos comprobar donde esta el hueco
            valido = (estado->filas[0]>vacio);//Si hay un hueco esta en la filas superior
        break;
        case ABAJO:
            valido = (estado->filas[0]<N-1);
        break;
        case IZQUIERDA:
            valido = (estado->cols[0]>vacio);//Igual que la primera solo que al ser izquierda tiene que ser cols
        break;
        case DERECHA:
            valido = (estado->cols[0]<N-1);
        break; // CUANDO Mueves de derecha izquierda cambias de columna y arriba/abajo cambias de fila
        default: 
        break;
    }
    return valido;
}

//redo operador
tEstado *aplicaOperador(unsigned op, tEstado *s)
{
    tEstado *nuevo = (tEstado *)malloc(sizeof(tEstado));
    memcpy(nuevo, s, sizeof(tEstado));
    int ficha;
    switch(op)
    {
        case ARRIBA: 
        //1 metemos en ficha el anterior para hacerle swap con el siguiente
            ficha = s->tablero[s->filas[0]-1][s->cols[0]]; 
            nuevo->filas[0]--;//decrementamos el valor de filas pq se ha cambiado 
            nuevo->filas[ficha]++; //actulizar valor de ficha
        break;

        case ABAJO: //RECIPROCO de Arriba (Arriba inverso y ya)
            ficha = s->tablero[s->filas[0]+1][s->cols[0]]; 
            nuevo->filas[0]++; 
            nuevo->filas[ficha]--; 
        break;

        case IZQUIERDA: 
            //Realizamos lo mismo que en arriba pero en caso de desp izq/dch se modifican las cols no fila
            ficha = s->tablero[s->filas[0]][s->cols[0]-1]; 
            nuevo->cols[0]--; 
            nuevo->cols[ficha]++;
        break;
        case DERECHA:  
            ficha = s->tablero[s->filas[0]][s->cols[0]+1]; 
            nuevo->cols[0]++; 
            nuevo->cols[ficha]--;
        break;
    }
    //cambio se hace siempre para no tener 2 en el mismo sitio (swap dentro de la matriz)
    //valor de hueco es cte
    nuevo->tablero[nuevo->filas[0]][nuevo->cols[0]] = 0;
    nuevo->tablero[nuevo->filas[ficha]][nuevo->cols[ficha]] = ficha;

    return nuevo;
}

int testObjetivo(tEstado *estado){
    /* Es decir la matriz esta en orden segun el problema del 3_puzzle
                tablero
                 1   2 
                 Ø   3
    */
   //asumo que el estado final nos lo dan ya que aparece en el enunciado, si no add manualmente
   int token=1;
   for ( int i=0; i<N && token!=0 ;i++ ){
       for ( int j=0; j<N && token!=0 ; j++){
           if (estado->tablero[i][j] != estado->tablero_final[i][j])
           {
               token=0;
           }
       }
   }
   return token;
}