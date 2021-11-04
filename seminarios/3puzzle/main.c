#include <stdlib.h>
#include <stdio.h>
#include "3puzzle.h"
void show_estado(tEstado* ej);
int main(){
    tEstado* ej;
    ej->tablero[0][0]=0;
    ej->tablero[0][1]=1;
    ej->tablero[1][0]=3;
    ej->tablero[1][1]=2;
    //tablero final
    ej->tablero_final[0][0]= 1;
    ej->tablero_final[0][1]= 2;
    ej->tablero_final[1][0]= vacio;
    ej->tablero_final[1][1]= 3;
    //pruebas
    show_estado(ej);
    aplicaOperador(IZQUIERDA,ej);
    show_estado(ej);
    
}
void show_estado(tEstado* ej){
    for ( int i=0; i<N ;i++ ){
        for ( int j=0; j<N; j++){
            printf("%d  ",ej->tablero[i][j]);
        }
        printf("\n");
    }
}