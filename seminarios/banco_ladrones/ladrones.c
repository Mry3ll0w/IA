#include <stdlib.h>
#include "ladrones.h"

tEstado* inicial(){
    
    tEstado *e = malloc(sizeof(tEstado));
    int v [N]= {4,3,2,5,7,1,8,6};

    memcpy(e->cinta,v,sizeof(v));
    e->robado = 0;
    e->recuperado = 0;
    e->it_der = 7;
    e->it_izq = 0;

return e;
}

int esValido(unsigned op,tEstado *e){

    int valido = 0;
    switch(op){

        case robar_izq:
            valido =  
                (e->cinta[e->it_izq] > 0 )&& (e->it_der > e->it_izq);//Se puede robar ese contenido
        break;

        case robar_der:
            valido = e->cinta[e->it_der] > 0 && (e->it_der > e->it_izq);
        break;

        default: break;
    }

return valido;
}

int testObjetivo(tEstado *e){

    int fin = 0;
    if(N%2 == 0){
        fin = (e->it_izq > e->it_der)&&(e->robado > e->recuperado);
    }
    else{
        fin = (e->it_izq == e->it_der)&&(e->robado > e->recuperado);
    }
    
    

return fin;
}

tEstado* aplicaOperador(unsigned op, tEstado *e){

    tEstado* n = malloc(sizeof(tEstado));
    memcpy(n,e,sizeof(tEstado));
    switch(op){
        
        case robar_izq:
            
            n->robado+=n->cinta[n->it_izq];
            n->cinta[n->it_izq]=0;
            n->it_izq--;
            
            n->recuperado+=n->cinta[n->it_der];
            n->cinta[n->it_der]=0;
            n->it_der--;

        break;

        case robar_der:
            n->robado+=n->cinta[n->it_der];
            n->cinta[n->it_der]=0;
            n->recuperado+=n->cinta[n->it_der-1];
            n->cinta[n->it_der-1]=0;
            n->it_der-=2;//Ya que se elimina el primer elemento de la izquierda por los ladrones y el anterior por el banco 
        break;

        default:break;
    }
return n;
}