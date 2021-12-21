#include <stdlib.h>
#include <stdio.h>

/* -------------------------------------------------------------------------- */
/*                       OPERACIONES PARA EL EJERCICIO 2                      */
/* -------------------------------------------------------------------------- */
#define NUM_OPERADORES 2
#define abatir 1
#define desplazar 2


int main(){


return 0;
}

/*  EJERCICIO 1 
Completa	el	siguiente	 fragmento	de	código	correspondiente	a	la función	Expandir,	dadas	
las	especificaciones	de	las	funciones	para	la	formulación	del	problema	del	Puzle.	(C)

Esto se corresponde a la funcion expandir que esta en busqueda.c
Lista expandir(tElemento *nodo){
    unsigned op;
    Lista sucesores=CrearLista(MAXI);
    for (op=1;op<=NUM_OPERADORES;op++) {
            if (esValido(op,nodo->estado)){
                        
         ---------------------------- BLOQUE INSERTADO ---------------------------- 
                s=aplicaOperador(op,nodo->estado); //Creo un tEstado nuevo donde almaceno tras operar
                nuevo->estado=s;//Igualo el estado del nodo
                nuevo->padre=nodo;//El padre del nodo sera el insertado
                nuevo->operador=op;//Guardo el operador aplicado en el nodo
                nuevo->costeCamino=nodo->costeCamino + coste(op,nodo->estado);//Lo mismo con los costes
                nuevo->profundidad=nodo->profundidad+1; // Actualizo la profundidad

                //PRACTICA 2
                nuevo->valHeuristica= mal_colocadas_heuristica(nuevo->estado,estadoObjetivo());
                //PRACTICA 2


            InsertarUltimo(nuevo,sucesores);
        } //bloque 1
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
typedef struct {
        char posicion; //Abatido , Desplazado y Normal
        char ocupado; // Niño, Adulto, Maleta, vacio(#)
}asiento;
    

typedef struct{

    asiento f1[2];//Piloto y copiloto
    asiento f2[3];//Fila 2
    asiento f3[2];//fila 3
    
}tEstado;

//Crea el estado inicial
tEstado* inicial(){
    
    tEstado *estado = (tEstado *) malloc(sizeof(tEstado));
    //Los asientos de la fila 1 desplazados
    estado->f1[0].posicion = 'D';
    estado->f1[1].posicion = 'D';

    estado->f1[0].ocupado ='#';
    estado->f1[1].ocupado ='#';

    //Asientos fila 2 ==> normal
    estado->f2[0].posicion = 'N';
    estado->f2[1].posicion = 'N';
    estado->f2[2].posicion = 'N';
    
    estado->f2[0].ocupado = '#';
    estado->f2[1].ocupado = '#';
    estado->f2[2].ocupado = '#';


    //Asientos f3 abatidos
    estado->f3[0].posicion = 'A';
    estado->f3[1].posicion = 'A';

    estado->f3[0].ocupado = '#';
    estado->f3[1].ocupado = '#';

return estado;//Devuelve el estado inicial
}

/*
Devuelve el estado final del coche
        Adultos ==> 2 f1 piloto y copiloto
        Niños ==> 2 f3 
        Fila 2 ==> abatidos maletas
*/
tEstado* final(){
    
    tEstado *estado = (tEstado *) malloc(sizeof(tEstado));
    
    estado->f1[0].ocupado = 'A';
    estado->f1[1].ocupado = 'A';

    //Con las maletas y abatidas
    estado->f2[0].ocupado = 'M';
    estado->f2[1].ocupado = 'M';
    estado->f2[2].ocupado = 'M';
    
    estado->f2[0].posicion = 'A';
    estado->f2[1].posicion = 'A';
    estado->f2[2].posicion = 'A';

    //Fila 3 con los niños
    estado->f3[0].ocupado = 'N';
    estado->f3[1].ocupado = 'N';
    
    
return estado;//Devuelve el estado final
    
}



