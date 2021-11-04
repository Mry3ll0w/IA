/*******************************************/
/* 		    BUSQUEDA.C                     */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/


#include "puzle.h"
#include "listaia.h"
#include "busqueda.h"

void solucionFin(int res){
   printf("\nFin de la busqueda\n");
    if (res)
      printf("Se ha llegado al objetivo\n");
   else
      printf("No se ha llegado al objetivo\n");
}

void dispNodo(tNodo *nodo){
    dispEstado(nodo->estado);
    printf("\n");
}

void dispCamino(tNodo *nodo){
    if (nodo->padre==NULL){
        printf("\n Desde el inicio\n");
        dispEstado(nodo->estado);
    }
    else {
        dispCamino(nodo->padre);
         dispOperador(nodo->operador);
        dispEstado(nodo->estado);
    }
}

void dispSolucion(tNodo *nodo){
   printf("Profundidad=%d\n",nodo->profundidad);
   printf("Coste=%d\n",nodo->costeCamino);
   dispCamino(nodo);
}


/* Crea el nodo ra�z. */
tNodo *nodoInicial(){
   tNodo *inicial=(tNodo *) malloc(sizeof(tNodo));
   inicial->estado=estadoInicial();
   inicial->padre=NULL;
   inicial->costeCamino=0;
   inicial->profundidad=0;
   return inicial;
}

LISTA expandir(tNodo *nodo){
    unsigned op;
    LISTA sucesores=VACIA;
    tNodo *nuevo=calloc(1,sizeof(tNodo));
    tEstado *s;
    for (op=1; op<=NUM_OPERADORES;op++){
      if (esValido(op,nodo->estado)){
                        //s=(tEstado *)calloc(1,sizeof(tEstado));
          s=aplicaOperador(op,nodo->estado);
          nuevo->estado=s;
          nuevo->padre=nodo;
          nuevo->operador=op;
          nuevo->costeCamino=nodo->costeCamino + coste(op,nodo->estado);
          nuevo->profundidad=nodo->profundidad+1;

          //PRACTICA 2
          nuevo->valHeuristica= mal_colocadas_heuristica(nuevo->estado,estadoObjetivo());
          //PRACTICA 2

          InsertarUltimo(&sucesores,  (tNodo *) nuevo, (sizeof (tNodo)));
      }
  }
return sucesores;
}


int busqueda(){
    int objetivo=0, visitados=0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;

    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        
        objetivo=testObjetivo(Actual->estado);
        visitados++;
        //dispOperador(Actual->operador);
        //dispEstado(Actual->estado);
        if (!objetivo){
            Sucesores = expandir(Actual);
            Abiertos=Concatenar(Abiertos,Sucesores);
        }
   }//while

    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}





/* -------------------- IMPLEMENTACIONES DEL EJERCICIO 3 -------------------- */

int estado_repetido(LISTA cerrados, tNodo* nodo)
{
    int res=0;
    tNodo * aux= (tNodo*) calloc (1,sizeof(tNodo));
    LISTA actual = cerrados;
    
    while(!esVacia(actual) && !res)
    {
        ExtraerPrimero(actual,aux,sizeof(tNodo));
        if(iguales(aux->estado, nodo->estado))
        {
            res=1;
        }
        else
        {
            //siguiente(&actual, &actual);
            actual = actual->next;
        }
    }
    return res;
}

/* ---------------------------- BUSQUEDA EN ANCHURA CON CONTROL DE REPETIDOS ------------------------ */
int busqueda_anchura_rep(){
    int objetivo=0, visitados=0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;
    //implementado a parte
    LISTA Cerrados = VACIA;

    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        
        objetivo=testObjetivo(Actual->estado);

        //dispOperador(Actual->operador);
        //dispEstado(Actual->estado);
        
        if(!objetivo&&estado_repetido(Cerrados,Actual)==0){
        //si no esta repetido entonces expande
            Sucesores = expandir(Actual);
            visitados++;
            InsertarUltimo(&Cerrados,Actual,sizeof(tNodo));
            Abiertos=Concatenar(Abiertos,Sucesores);

        }
      
   }//while

    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

/* ---------------- BUSQUEDA EN PROFUNDIDAD EN VEZ DE ANCHURA CON ESTADOS REPETIDOS --------------- */
//CUIDADO CON EL LA MATRIZ RESULTADO QUE NO ACABA PRONTO
int busqueda_profundidad(){
    int objetivo=0, visitados=0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;
    LISTA Cerrados= VACIA;
    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        
        objetivo=testObjetivo(Actual->estado);

        //dispOperador(Actual->operador);
        //dispEstado(Actual->estado);
        if(!objetivo&&estado_repetido(Cerrados,Actual)==0){
            //si no esta repetido entonces expande
            Sucesores = expandir(Actual);
            InsertarUltimo(&Cerrados,Actual,sizeof(tNodo));
            visitados++;
            Abiertos = Concatenar(Sucesores,Abiertos);//profundidad
        }
   }//while

    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

/* ---------------- BUSQUEDA EN PROFUNDIDAD LIMITADA --------------- */
//CUIDADO CON EL LA MATRIZ RESULTADO QUE NO ACABA PRONTO
int busqueda_profundidad_limitada(int limite){
    int objetivo=0, visitados=0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;
    LISTA Cerrados = VACIA;

    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo && (limite >0)){
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        
        objetivo=testObjetivo(Actual->estado);

        dispOperador(Actual->operador);
        dispEstado(Actual->estado);
        if(!objetivo&&estado_repetido(Cerrados,Actual)==0){
            //si no esta repetido entonces expande
            Sucesores = expandir(Actual);
            InsertarUltimo(&Cerrados,Actual,sizeof(tNodo));
            Abiertos = Concatenar(Sucesores,Abiertos);//profundidad
            limite--;
            visitados++;
        }
   }//while

    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

/* ---------------- BUSQUEDA EN PROFUNDIDAD LIMITADA ITERATIVA--------------- */
//CUIDADO CON EL LA MATRIZ RESULTADO QUE NO ACABA PRONTO
int busqueda_profundidad_limitada_iterativa(const int limite_maximo,const int tasa_crecimiento){
    int it = 1; int obj=0;
    while(obj == 0&& limite_maximo < it){
        obj= busqueda_profundidad_limitada(it);
        it+=tasa_crecimiento;
    }
    return obj;
}
/////////////////////////////////////////////////////////////////////////////////////
//PRACTICA 2 HEURISTICAS
////////////////////////////////////////////////////////////////////////////////////
/* ---------------- FUNCION ORDENACION VORAZ --------------- Apuntes de clase */
LISTA Ordenacion_voraz(LISTA L,tNodo *nuevo){

    LISTA aux = NULL;
    tNodo *nodo=calloc(1,sizeof(tNodo));

    if(esVacia(L)){

        InsertarPrimero(&L,nuevo,sizeof(tNodo));
    }
    else{
        ExtraerPrimero(L,(tNodo *)nodo,sizeof(tNodo));
        while(!(esVacia(L)) && nodo->valHeuristica < nuevo->valHeuristica ){

            InsertarUltimo(&aux,(tNodo *)nodo,sizeof(tNodo));
            L = L->next;
            if(!(esVacia(L))){

                ExtraerPrimero(L,(tNodo *)nodo,sizeof(tNodo));
            }
        }
        InsertarUltimo(&aux,(tNodo *)nuevo,sizeof(tNodo));
        aux= Concatenar(aux,L);
    }
    return aux;
}

//FUNCION ORDENAR A ESTRELLA
LISTA Ordenacion_A_estrella(LISTA L,tNodo *nuevo){

    LISTA aux = NULL;
    tNodo *nodo=calloc(1,sizeof(tNodo));
    if(esVacia(L)){
        InsertarPrimero(&L,nuevo,sizeof(tNodo));
    }
    else{
        ExtraerPrimero(L,(tNodo *)nodo,sizeof(tNodo));
        while(!(esVacia(L)) && ((nodo->valHeuristica + nodo->costeCamino) < ( nuevo->valHeuristica + nuevo->costeCamino ))){
            InsertarUltimo(&aux,(tNodo *)nodo,sizeof(tNodo));
            L = L->next;
            if(!(esVacia(L))){

                ExtraerPrimero(L,(tNodo *)nodo,sizeof(tNodo));
            }
        }
        InsertarUltimo(&aux,(tNodo *)nuevo,sizeof(tNodo));
        aux= Concatenar(aux,L);
    }
return aux;
}




/* ---------------- FUNCION ORDENAR LISTA VORAZ --------------- */

LISTA Ordenar_lista_voraz(LISTA A, LISTA B){
    tNodo *nodo=calloc(1,sizeof(tNodo));
    while(B != NULL){
        ExtraerPrimero(B,nodo, sizeof(tNodo));
        A = Ordenacion_voraz(B,nodo);
        B = B->next;
    }
    return A;
}

/* ---------------- FUNCION ORDENAR ABIERTOS A* --------------- */

LISTA Ordenar_lista_A_estrella(LISTA A, LISTA S){

    tNodo *nodo=calloc(1,sizeof(tNodo));

    while(S != NULL){

        ExtraerPrimero(S,nodo, sizeof(tNodo));
        A = Ordenacion_A_estrella(S,nodo);
        S = S->next;
    }
    return A;
}





/* ---------------- FUNCION BUSQUEDA VORAZ --------------- */

int busqueda_voraz(){


    int objetivo=0, visitados=0;

    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;
    LISTA Cerrados= VACIA;
    InsertarPrimero(&Abiertos, Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo && estado_repetido(Cerrados,Actual)==0){

        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));

        EliminarPrimero(&Abiertos);

        objetivo=testObjetivo(Actual->estado);

        //dispOperador(Actual->operador);
        //dispEstado(Actual->estado);
        if (!objetivo){
            Sucesores = expandir(Actual);
            Abiertos=Ordenar_lista_voraz(Abiertos,Sucesores);
            visitados++;
        }
    }

    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

/* ---------------- FUNCION BUSQUEDA A* --------------- */

int busqueda_A_estrella(){
    int objetivo=0, visitados=0;

    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;
    LISTA Cerrados= VACIA;

    InsertarPrimero(&Abiertos, Inicial,sizeof(tNodo));

    while (!esVacia(Abiertos) && !objetivo && estado_repetido(Cerrados,Actual)==0){

        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));

        EliminarPrimero(&Abiertos);

        objetivo=testObjetivo(Actual->estado);

        //dispOperador(Actual->operador);
        //dispEstado(Actual->estado);
        if (!objetivo){
            Sucesores = expandir(Actual);
            Abiertos=Ordenar_lista_A_estrella(Abiertos,Sucesores);
            visitados++;
        }
    }//while

    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

int cuenta_nodo(LISTA a) {
    int cont=0;
    while(a->next != NULL){
        cont++;
        a = a->next;
    }
    return cont;
}

int distancia_manhattan(const tEstado * e, const tEstado* obj){
    int dist=0;
    int v_pieza=0;

    while(v_pieza < N*N){
        dist += abs(e->fila[v_pieza]-obj->fila[v_pieza]+ e->col[v_pieza] - obj->col[v_pieza]);
        v_pieza++;
    }

    //obtenemos ahora la distancia con respecto a
    return dist;
}





