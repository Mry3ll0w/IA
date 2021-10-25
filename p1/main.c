/*******************************************/
/*             MAIN.C                      */
/*                                         */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "puzle.h"
#include "listaia.h"
#include "busqueda.h"

int main(){
    //solucionFin(busqueda());
    //solucionFin(busqueda_anchura_rep());
    //solucionFin(busqueda_profundidad_limitada(8));
    solucionFin(busqueda_profundidad_limitada_iterativa());
    return 0;
}
