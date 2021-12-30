#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define N 6
#define NUM_OPERADORES 

#define izq_a 1
#define izq_b 2 
#define izq_c 3

#define der_a 4 
#define der_b 5
#define der_c 6

#define abajo_a 7
#define abajo_b 8
#define abajo_c 9

#define arriba_a 10
#define arriba_b 11
#define arriba_c 12

/* -------------------------------------------------------------------------- */
/*                                   tEstado                                  */
/* -------------------------------------------------------------------------- */
typedef struct {
    char tablero[N][N];//Nos dan un tablero 6*6
    char final [N][N];
    int centro_a[2];
    int centro_b[2];
    int centro_c[2];

}tEstado;

//Creacion de estado inicial
tEstado *inicial(char tablero[N][N], int p_a[2],int p_b[2],int p_c[2]){

    tEstado *e = (tEstado*) malloc(sizeof(tEstado));
    memcpy(e->tablero, tablero, sizeof(tablero));//Copiamos el tablero de entrada inicial en el tEstado
    memcpy(e->centro_a, p_a, sizeof(p_a));
    memcpy(e->centro_b, p_b, sizeof(p_b));
    memcpy(e->centro_b, p_c, sizeof(p_c));

    return e;
}

//Creacion de estado final
tEstado *final(char final[N][N], int p_a[2],int p_b[2],int p_c[2]){
    tEstado *e = (tEstado*) malloc(sizeof(tEstado));
    
    memcpy(e->tablero, final, sizeof(final));//Copiamos el tablero de entrada inicial en el tEstado
    memcpy(e->centro_a, p_a, sizeof(p_a));
    memcpy(e->centro_b, p_b, sizeof(p_b));
    memcpy(e->centro_b, p_c, sizeof(p_c));

    return e;
}

//Funciones esValido

int esValido(unsigned int op, tEstado* e){
    int valido = 0;

    switch (op)
    {
    case izq_b :
        
        if(
            e->centro_b[1]-2 > 0 && //Comprobar si se sale del mapa
            e->tablero[e->centro_b[0]][e->centro_b[1]-2] == 'v' && //lat izq esta en posicion vacia tras mover
            e->tablero[e->centro_b[0]-1][e->centro_b[1]-1] == 'v'  //superior esta en posicion vacia tras mover
            
        )
            valido = 1;
        
        break;
    
    case abajo_b:
            if(
                //Comprobar que no salga del mapa
                e->centro_b[0]+1 < N &&
                e->tablero[e->centro_b[0]+1][e->centro_b[1]-1] == 'v' && //lat izq esta en posicion vacia tras mover
                e->tablero[e->centro_b[0]+1][e->centro_b[1]+1] == 'v' //Lat derecha
            )
                valido = 1;
        break;
    
    default:
        break;
    }



return valido;    
}

tEstado* aplicaOperador(unsigned op, tEstado *e){
    
    tEstado * nuevo = (tEstado*) malloc(sizeof(tEstado));
    memcpy(nuevo,e,sizeof(tEstado));

    switch(op){
        case izq_b :
        
        //Cambiamos la posicion del centro
        nuevo->centro_b[1]-=1;
        
        
        break;
    
    case abajo_b:
         nuevo->centro_b[0]+=1;  
        break;

    }

    return nuevo;

}

int testObjetivo(tEstado *e){
    tEstado *f = (tEstado *) malloc(sizeof(tEstado));
    memcpy(f,final,sizeof(tEstado));


return e -> centro_a == f->centro_a && e -> centro_b == f->centro_b && e -> centro_c == f->centro_c;    

}


//Funcion heuristica
/* 
    Sera la suma de las distancias manhattan de todas las coordenadas de las figuras con su colocacion final
*/
int funcion_heuristica(tEstado* e){

    tEstado *f = (tEstado *) malloc(sizeof(tEstado));
    memcpy(f,final,sizeof(tEstado));

    int m_a = abs(sqrt(  pow((e->centro_a[0] - f->centro_a [0]),2)    +   pow((e->centro_a[1] - f->centro_a [1]),2)  ));
    int m_b = abs(sqrt(  pow((e->centro_b[0] - f->centro_b [0]),2)    +   pow((e->centro_b[1] - f->centro_b [1]),2)  ));
    int m_c = abs(sqrt(  pow((e->centro_c[0] - f->centro_c [0]),2)    +   pow((e->centro_c[1] - f->centro_c [1]),2)  ));

    return m_a+m_b+m_c;

}


int main(){

  return 0;
}