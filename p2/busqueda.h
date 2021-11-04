/*******************************************/
/* 		    BUSQUEDA.H                     */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef _tNodo_
#define _tNodo_
typedef struct NodoBusqueda_{
    tEstado *estado;
    unsigned operador;
    int costeCamino;
    int profundidad;
    int valHeuristica;
    struct NodoBusqueda_ *padre;
} tNodo;

#endif

int busqueda(void);
void solucionFin(int res);
int busqueda_anchura_rep();
int busqueda_profundidad();
int busqueda_profundidad_limitada(int limite);
int busqueda_profundidad_limitada_iterativa(const int limite_maximo, const int tasa_crecimiento);
int mal_colocadas_heuristica (tEstado *estado, tEstado *objetivo);
int busqueda_voraz();
int busqueda_A_estrella();
int cuenta_nodo(LISTA);