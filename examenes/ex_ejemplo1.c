#include <stdlib.h>
#include <stdio.h>
/* EJERCICIO 1
Completa	el	siguiente	 fragmento	de	código	correspondiente	a	la función	Expandir,	dadas	
las	especificaciones	de	las	funciones	para	la	formulación	del	problema	del	Puzle.	(C)

Lista expandir(tElemento *nodo){
    unsigned op;
    tEstado* s;
    Lista sucesores=CrearLista(MAXI);
    for (op=1;op<=NUM_OPERADORES;op++) {
        if (esValido(op,nodo->estado)){
                        s=(tEstado *)calloc(1,sizeof(tEstado));
          s=aplicaOperador(op,nodo->estado);
          nuevo->estado=s;
          nuevo->padre=nodo;
          nuevo->operador=op;
          nuevo->costeCamino=nodo->costeCamino + coste(op,nodo->estado);
          nuevo->profundidad=nodo->profundidad+1;
          
          InsertarUltimo(&sucesores,  (tNodo *) nuevo, (sizeof (tNodo)));

      }
 } //for
 return sucesores;
}//expandir

*/


/* EJERCICIO 2
Monovolumen con las siguentes carcteristiscas:

    Capacidad total de 7 personas:
        2 asientos delanteros
        2 de una pieza posiciones central e izq + individual en lado der
        2	asientos	en	una	tercera	fila.
    
    Caracteristicas extras:
        -todos los asientos son abatibles excepto el delantero
        -Asiento del copiloto solo se puede abatir si el de atras esta abatido==> si copiloto abatido entonces
        asiento segunda fila abatido.
        - Los asientos != fila delantera se pueden abatir cuando quieras
        - Asientos delanteros se pueden desplazar si no estan abatidos ==> 
            si quieres abatir piloto ==> f2 (izq y central) estan en posicion normal
            si quieres abatir copiloto ==> f2 (der) posicion normal
        -Asientos abatidos no se pueden desplazar
        -Asiento desplazado no se puede abatir

    Estado inicial del coche:
        asientos f1 desplazados
        asientos f2 normal
        asientos f3 abatidos

    Costes:
        Abatir y poner normal ==>2
        Desplazar ==> 1

    Estado final
        Adultos ==> 2 f1 piloto y copiloto
        Niños ==> 2 f3 
        Fila 2 ==> abatidos maletas 
*/

int main(){

return 0;
}
#define N 7
//apartado a 
typedef struct {
    char ocupado; //Niño Adulto Maleta Vacio
    char estado; //Abatido Desplazado Normal
}asiento;

typedef struct {
    
    asiento asientos[N]; // 0 1 f1   || 2 3 4  f2 || 5 6 f3
    

}tEstado;

//crea esl estado inicial
/* -------------------------------------------------------------------------- */
/*                               ESTADO INICIAL                               */
/* -------------------------------------------------------------------------- */
//   Estado inicial del coche:
//        asientos f1 desplazados
//        asientos f2 normal
//        asientos f3 abatidos
tEstado *estadoInicial(){
    
    tEstado *e = malloc(sizeof(tEstado));

    //Todo el coche esta vacio
    for(int i =0 ; i < N; ++i){
        e->asientos[i].ocupado = 'v';

        //Primera fila
        if (i == 0 || i == 1)
        {
            e->asientos[i].estado='d';
        }
        else if(i == 2 || i== 3 || i == 4){
            e->asientos[i].estado ='n';
        }
        else if(i == 5 || i == 6){

            e->asientos[i].estado ='a';
        }
        
    }

return e;
}

/*

    Estado final
        Adultos ==> 2 f1 piloto y copiloto
        Fila 2 ==> abatidos maletas 
        Niños ==> 2 f3 
        

*/
tEstado *estadoObjetivo(){

    tEstado *e = malloc(sizeof(tEstado));
    //f1
    e-> asientos[0].ocupado = 'a';
    e-> asientos[1].ocupado = 'a';
    
    e->asientos[0].estado = 'n';
    e->asientos[1].estado = 'n';

    //f2
    e->asientos[2].ocupado = 'm';
    e->asientos[3].ocupado = 'm';
    e->asientos[4].ocupado = 'm';

    e->asientos[2].estado = e->asientos[3].estado = e->asientos[4].estado='n';
    
    //f3
    e-> asientos[5].ocupado = e->asientos[6].ocupado ='n';
    e-> asientos[5].estado = e->asientos[6].estado ='n';

return e;
}

/* -------------------------------------------------------------------------- */
/*                                 APARTADO B                                 */
/* -------------------------------------------------------------------------- */
#define NUM_OPERADORES 16
//ocupar
#define ocupar_piloto 1
#define ocupar_copiloto 2

#define ocupar_f2_1 3
#define ocupar_f2_2 4
#define ocupar_f2_3 5

#define ocupar_f3_1 6
#define ocupar_f3_2 7

//desplazar
#define desp_piloto 8
#define desp_copiloto 9

//abatir
#define abatir_piloto 10
#define abatir_copiloto 11

#define abatir_f2_1 12
#define abatir_f2_2 13
#define abatir_f2_3 14

#define abatir_f3_1 15
#define abatir_f3_2 16

/* -------------------------------------------------------------------------- */
/*                                 APARTADO C                                 */
/* -------------------------------------------------------------------------- */

//Comprobar si hemos llegado a un estado final
int testObjetivo(tEstado *e){

    tEstado * final = estadoObjetivo();
    int valido = 1;
    
    for(int i = 0; i < NUM_OPERADORES && valido ; i++){

        if(
            e->asientos[i].estado != final->asientos[i].estado || 
            e->asientos[i].ocupado != final->asientos[i].ocupado
        )
            valido = 0;
    }
return valido;
}

/*
    Caracteristicas extras:
        //-todos los asientos son abatibles excepto el delantero
        -Asiento del copiloto solo se puede abatir si el de atras esta abatido==> si copiloto abatido entonces
        asiento segunda fila abatido.
        - Los asientos != fila delantera se pueden abatir cuando quieras
        - Asientos delanteros se pueden desplazar si no estan abatidos ==> 
            si quieres abatir piloto ==> f2 (izq y central) estan en posicion normal
            si quieres abatir copiloto ==> f2 (der) posicion normal
        -Asientos abatidos no se pueden desplazar
        -Asiento desplazado no se puede abatir

*/
int esValido(unsigned op,tEstado *e){

    int valido = 0;

    switch(op){
        //de asientos piloto y copiloto mucho texto
        case ocupar_piloto:
            valido = (e->asientos[0].ocupado == 'v');
        break;
        case ocupar_copiloto:
            valido = (e->asientos[1].ocupado == 'v');
        break;

        case desp_piloto:
            //Si quiero piloto asiento 2 posicion normal
            valido = (
                e->asientos[0].estado == 'n' &&
                e->asientos[2].estado == 'n' && e->asientos[3].estado == 'n'
                
            );
        break;

        case desp_copiloto:
            //Si quiero piloto asiento  posicion normal
            valido = (
                e->asientos[1].estado == 'n' &&
                e->asientos[4].estado == 'n'
            );
        break;

        case abatir_piloto:
                valido = (
                    e->asientos[0].estado == 'n'
                );
        break;
        /*
            Asiento del copiloto solo se puede abatir si el de atras esta abatido==> si copiloto abatido entonces
        asiento segunda fila abatido.
        */
        case abatir_copiloto:
            valido = (
                    e->asientos[0].estado == 'n'&&
                    e->asientos[4].estado == 'a'
                );
        break;

        default:break;
    }
return valido;
}

//AplicaOperador
tEstado* aplicaOperador(unsigned op, tEstado *e){
    
    tEstado * n = malloc(sizeof(tEstado));
    memcpy(n, e, sizeof(tEstado));

    switch(op){
        //de asientos piloto y copiloto mucho texto
        case ocupar_piloto:
            e->asientos[0].ocupado == 'a';
        break;
        case ocupar_copiloto:
            e->asientos[1].ocupado == 'a';
        break;

        case desp_piloto:
            //Si quiero piloto asiento 2 posicion normal
           
                e->asientos[0].estado ='d';
               
        break;

        case desp_copiloto:
            //Si quiero piloto asiento  posicion normal
            e->asientos[1].estado ='d';
        break;

        case abatir_piloto:
               
            e->asientos[0].estado == 'a';
                
        break;
        /*
            Asiento del copiloto solo se puede abatir si el de atras esta abatido==> si copiloto abatido entonces
        asiento segunda fila abatido.
        */
        case abatir_copiloto:
           e->asientos[1].estado == 'a';
        break;

        default:break;
    }

return n;
}


/* -------------------------------------------------------------------------- */
/*                                 APARTADO D                                 */
/* -------------------------------------------------------------------------- */
/*
 Costes:
        Abatir y poner normal ==>2
        Desplazar ==> 1
*/
int coste(unsigned op, tEstado *e ){
    
    if (op == abatir_piloto || op == abatir_copiloto )//paso de poner el resto mucho texto FALTO PONER NORMAL EN OPERACIONES
    {
        return 2;
    }
    else if (desp_copiloto == op || desp_piloto ==op){
        return 1;
    }
    else{
        return 0;
    }
    
}

/* -------------------------------------------------------------------------- */
/*                                 APARTADO E                                 */
/* -------------------------------------------------------------------------- */
//Como de distinto esta el coche
int funcion_heuristica(tEstado* e){
    int cont =0;
    tEstado* f = estadoObjetivo();

    for(int i =0; i<N; i++){
        
        if(e->asientos[i].estado != f->asientos[i].estado)
            ++cont;
        
        if(e->asientos[i].ocupado != f->asientos[i].ocupado)
            ++cont;
    }

    return cont;
}