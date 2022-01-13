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
    tNodo *nuevo=calloc(1,sizeof(tNodo));//tNodo *nuevo =
    tEstado *s;
    for (op=1; op<=NUM_OPERADORES;op++){//Recorre todas la operaciones
      if (esValido(op,nodo->estado)){
                        //s=(tEstado *)calloc(1,sizeof(tEstado));
          s=aplicaOperador(op,nodo->estado);
          nuevo->estado=s;
          nuevo->padre=nodo;
          nuevo->operador=op;
          nuevo->costeCamino=nodo->costeCamino + coste(op,nodo->estado);
          nuevo->profundidad=nodo->profundidad+1;
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
/*
Búsqueda en Anchura con Control de Estados Repetido
    Si existe algun repetido entonces devuelve 0
*/
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
        visitados++;
        //dispOperador(Actual->operador);
        //dispEstado(Actual->estado);
        
        if(!objetivo&&estado_repetido(Cerrados,Actual)==0){
        //si no esta repetido entonces expande
            Sucesores = expandir(Actual);
            InsertarPrimero(&Cerrados,Actual,sizeof(tNodo));
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

/* ---------------- BUSQUEDA EN PROFUNDIDAD EN VEZ DE ANCHURA --------------- */
//CUIDADO CON EL LA MATRIZ RESULTADO QUE NO ACABA PRONTO
int busqueda_profundidad(){
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
            //Abiertos=Concatenar(Abiertos,Sucesores);//anchura
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

    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo && (limite >0)){
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        
        objetivo=testObjetivo(Actual->estado);
        visitados++;
        dispOperador(Actual->operador);
        dispEstado(Actual->estado);
        if (!objetivo){
            Sucesores = expandir(Actual);
            //Abiertos=Concatenar(Abiertos,Sucesores);//anchura
            Abiertos = Concatenar(Sucesores,Abiertos);//profundidad
            limite--;
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
int busqueda_profundidad_limitada_iterativa(){
    int objetivo=0, visitados=0;
    int limite = 2;
    int limite_inicial =2;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;

    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo ){
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        
        objetivo=testObjetivo(Actual->estado);
        visitados++;
        dispOperador(Actual->operador);
        dispEstado(Actual->estado);

        if (!objetivo){
            if(limite <= 0){
                limite = limite_inicial + 1;
            }
            Sucesores = expandir(Actual);
            //Abiertos=Concatenar(Abiertos,Sucesores);//anchura
            Abiertos = Concatenar(Sucesores,Abiertos);//profundidad
            limite--;
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