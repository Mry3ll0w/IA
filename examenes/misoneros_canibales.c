#include <stdlib.h>
#include <stdio.h>


int main(){

    return 0;
}

/* -------------------------------------------------------------------------- */
/*           CONSTANTES, LISTAS DE OPERADORES Y ESTRUCTURA DE DATOS           */
/* -------------------------------------------------------------------------- */
#define N 2

typedef struct {
    
    int orilla_izq[N],orilla_der[N];//Canibal c , Misionero m, vacio #
    
    int barca[2];//maximo 2 personas

}tEstado;
//Canibal lador izq y misionero lado der
int inicial[]={3,3};
int vacio[]={0,0};
int barca[]={0,0};


tEstado * crea_estado(int orilla_izq[], int orilla_der[],int barca[]){

    tEstado *e = malloc(sizeof(tEstado));
    memcpy(e->barca,barca,sizeof(barca));
    memcpy(e->orilla_izq,orilla_izq,sizeof(orilla_izq));
    memcpy(e->orilla_der,orilla_der,sizeof(orilla_der));

return e;
}


tEstado* estado_inicial(){
    return crea_estado(vacio,inicial,barca);
}

/* -------------------------------------------------------------------------- */
/*                              FUNCION ES VALIDO                             */
/* -------------------------------------------------------------------------- */
#define NUM_OPERADORES 8

#define mover_misionero_barco_o_der 1
#define mover_misionero_barco_o_izq 2

#define mover_canibal_barco_o_der 3
#define mover_canibal_barco_o_izq 4
//desde la barca
#define mover_misionero_orilla_der 5
#define mover_misionero_orilla_izq 6

#define mover_canibal_orilla_der 7
#define mover_canibal_orilla_izq 8


int esValido(unsigned op,tEstado *e){
    
    int token = 0;

    switch (op){

        case mover_canibal_barco_o_der:
            //tiene que haber hueco 
            if((e->barca[1]==0)&& (e->orilla_der[1] <= 1) ){
                token = 1;
            }

        break;

        case mover_canibal_barco_o_izq:
            //hay hueco en la bara y ademas existe un canibal en el lado a mover
            if(( e->barca[1]==0)&& (e->orilla_izq[1] <= 1) ){
                token = 1;
            }
        
        break;

        case mover_misionero_barco_o_der:
            //hay hueco en la bara y ademas existe un canibal en el lado a mover
            if((e->barca[0]==0 )&& (e->orilla_der[0] <= 1) ){
                token = 1;
            }

        break;

        case mover_misionero_barco_o_izq:
            //hay hueco en la bara y ademas existe un canibal en el lado a mover
            if((e->barca[0]==0 )&& (e->orilla_izq[0] <= 1) ){
                token = 1;
            }

        break;

        case mover_misionero_orilla_der:
            //Hay que comprobar que exista un misionero en la barca para mover de orilla
            //tambien hay que comprobar que no se haya superado el total de misioneros
            //Comprobar que el n misioneros < n_canibales
            if(e->barca[0] == 1 && e->orilla_der[0] < 3 && e->orilla_der[0] > e->orilla_der[1]) { 
                token = 1;
            }

        break;

        case mover_misionero_orilla_izq:
            //Hay que comprobar que exista un misionero en la barca para mover de orilla
            //tambien hay que comprobar que no se haya superado el total de misioneros
            //Comprobar que el n misioneros < n_canibales
            if(e->barca[0] == 1 && e->orilla_izq[0] < 3 && e->orilla_izq[0] > e->orilla_izq[1]) { 
                token = 1;
            }

        break;

        case mover_canibal_orilla_der:
            //Hay que comprobar que exista un misionero en la barca para mover de orilla
            //tambien hay que comprobar que no se haya superado el total de misioneros
            //Comprobar que el n misioneros < n_canibales
            if(e->barca[1] == 1 && e->orilla_der[1] < 3 && e->orilla_der[0] > e->orilla_der[1]) { 
                token = 1;
            }
        break;

        case mover_canibal_orilla_izq:
            //Hay que comprobar que exista un misionero en la barca para mover de orilla
            //tambien hay que comprobar que no se haya superado el total de misioneros
            //Comprobar que el n misioneros < n_canibales
            if(e->barca[1] == 1 && e->orilla_izq[1] < 3 && e->orilla_der[0] > e->orilla_der[1]) { 
                token = 1;
            }
        break;

        default:break;
    }


return token;
}

tEstado* aplicaOperador(unsigned op, tEstado *e){

    tEstado *r = malloc(sizeof(tEstado));
    memcpy(r,e,sizeof(tEstado));

    switch (op){

        case mover_canibal_barco_o_der:
            //tiene que haber hueco 
                r->barca[1]++;
                r->orilla_der[1]--;
        break;

        case mover_canibal_barco_o_izq:
                r->barca[1]++;
                r->orilla_der[1]--;
        
        break;

        case mover_misionero_barco_o_der:

            r->barca[0]++;
            r->orilla_der[0]--;

        break;

        case mover_misionero_barco_o_izq:
            r->barca[0]++;
            r->orilla_izq[0]--;

        break;

        case mover_misionero_orilla_der:
            
            r->barca[0]--;
            r->orilla_der[0]++;

        break;

        case mover_misionero_orilla_izq:
           
           r->barca[0]--;
           r->orilla_izq[0]++;

        break;

        case mover_canibal_orilla_der:
            r->barca[1]--;
            r->orilla_der[1]++;
        break;

        case mover_canibal_orilla_izq:
            r->barca[1]--;
            r->orilla_izq[1]++;
        break;

        default:break;
    }

return r;   
}

int testObjetivo(tEstado *e){
    return e->orilla_izq[0]==3 && e->orilla_der[0]==3;
}

int funcion_costen(tEstado *e){return 1;}//todos los movimentos son de coste 1

//Funcion heuristica => Cuanto mas cerca este la orilla izquierda 
int funcion_heuristica(tEstado *e){

    return abs(3-e->orilla_izq[0])+abs(3-e->orilla_izq[1]);

}