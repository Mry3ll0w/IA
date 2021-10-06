#include "3puzzle.h"

int esValido(unsigned int op, tEstado *estado){
    int valido=0;
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


tEstado *aplicaOperador(unsigned op, tEstado *a){
    tEstado *s= (tEstado *)malloc(sizeof(tEstado));
    memcpy(s,a,sizeof(tEstado));
    //Entiendo que realmente no desplazamos nunca otra cosa que no sea el valor "vacio"
    switch(op){
        case ARRIBA:
            s->filas[0]--;
        break;
        case ABAJO:
            s->filas[0]++;
        break;
        case IZQUIERDA:
            s->cols[0]--;
        break;
        case DERECHA:
            s->cols[0]++;
        break;
        default: break;
    }
    return s;
}

int testObjetivo(tEstado *estado){
    return (estado->tablero[0][0]==vacio)&&(estado->tablero[0][1]==1)
            &&(estado->tablero[1][0]==2) && (estado->tablero[1][1]==3);
    /* Es decir la matriz esta en orden segun el problema del 3_puzzle
                tablero
                 Ø   1
                 2   3
    */
}