#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 8
#define IZQ 1
#define DCHA 2
#define NUM_OPERADORES 2

typedef struct tEstado{
    int cinta[N];
    int lado_izq; //extremos cambiantes
    int lado_dcha;
    int cant_robado;//ladrones
    int recuperado; //banco
}tEstado;

//crea el estado inicial
tEstado* crearEstado(int cinta[N]){
    tEstado *e = (tEstado*)malloc(sizeof(tEstado));
    for(int i = 0; i < N; ++i){
        e->cinta[i] = cinta[i];
    }
    e-> lado_izq =0;
    e-> lado_dcha =N-1;
    e->cant_robado=e->recuperado=0;

return e;
}

int esValido(unsigned op,tEstado *e){
    int valido;
    if(N%2&&(op==IZQ||op==DCHA)){
        valido = (e->lado_izq < e->lado_dcha);
    }
    else{
        valido = (e->lado_izq < e->lado_dcha-1);
    }
    
    return valido;
}

tEstado* aplicaOperador(unsigned op, tEstado *e){
    tEstado *nuevo = (tEstado*)malloc(sizeof(tEstado));
    memcpy(nuevo,e,sizeof(tEstado));
    switch(op){
        case IZQ:
            nuevo->lado_izq ++;
            nuevo->lado_dcha--;
            nuevo->cant_robado+=nuevo->cinta[e->lado_izq];//se coge e pq es cte y aun no se ha modificado el valor de lado izq
            nuevo->recuperado+=nuevo->cinta[e->lado_dcha];
            nuevo->cinta[e->lado_izq] =-1; //-1 = ha sido robado
            
        break;
        case DCHA:
            nuevo->lado_dcha -=2;
            nuevo->cant_robado +=nuevo->cinta[e->lado_dcha];
            nuevo->recuperado +=nuevo->cinta[e->lado_dcha-1];
        break;
    }
    return nuevo;
}

int testObjetivo(tEstado *e){
    int objetivo = 0;
    if(N%2 == 0){
        objetivo = (e->lado_izq > e->lado_dcha)&&(e->cant_robado > e->recuperado);
    }
    else{
        objetivo = (e->lado_izq == e->lado_dcha)&&(e->cant_robado > e->recuperado);
    }

}