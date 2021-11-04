#include "puzle3.h"


//No se reciben los reprensentantes como datos de entrada

tEstado* crearEstado(int celdas[N][N]){
    tEstado* e = malloc(sizeof(tEstado));
    int it_ficha=1;
    //copiamos los datos de entrada hacia tEstado
    for(int i = 0; i<N ; i++){
        for (size_t j = 0; j < N; j++)
        {
            //filas se supone que tiene que tener -1 de serie
            //caso A
            if(celdas[i][j]==it_ficha && e->filas[it_ficha]==-1){//se mira si ya se ha encontrado con anterioridad
                e->filas[it_ficha] = i+1;
                e->col[it_ficha]=j;
                //guardamos el representante que en la 1ª vez esta justo abajo
                it_ficha++;//actualizamos la ficha
            }
            /*
            //Caso ORIGINAL
            if(celdas[i][j]==2 && e->filas[2]==-1){//se mira si ya se ha encontrado con anterioridad
                e->filas[2] = i+1;
                e->col[2]=j;
                //guardamos el representante que en la 1ª vez esta justo abajo
            }
            */
        }
        
    }
    return e;
}

int testObjetivo(tEstado * e,tEstado * obj){
    //se llega al objetivo cuando los representante de la ficha estan iguales al obj
    return (e->filas[1]==obj->filas[2] && e->col[1]==obj->col[2] &&
            e->filas[2]==obj->filas[2] && e->col[2]==obj->col[2] &&
            e->filas[3]==obj->filas[3] && e->col[3]==obj->col[3]
    );
}

int esValido(unsigned op, tEstado *e){
    int valido =0;
    switch(op){//son 12 condiciones
        case ARRIBA_A:
            //si es mayor se sale por la forma de la fila (e->filas[1] > 1)
            //por la forma controlas a 2 huecos no a 1 (e->tablero[e->filas[1]-2][e->col[1]]==0 
            //(e->tablero[e->filas[1]+1][e->col[1]+1]==0) ficha der y ficha izq con -1
            valido = (e->filas[1] > 1)&&(e->tablero[e->filas[1]-2][e->col[1]]==0)&&
            (e->tablero[e->filas[1]+1][e->col[1]+1]==0)&&((e->tablero[e->filas[1]-1][e->col[1]-1]==0));
        break;
    }
    return valido;
}

tEstado * aplicaOperador(unsigned op, tEstado * e){
    tEstado * s = (tEstado *) malloc(sizeof(tEstado));
    switch(op){
        case ARRIBA_A:
            //Act tablero
            s->tablero[e->filas[1]][e->col[1]-1]=0;//filaizq
            s->tablero[e->filas[1]][e->col[1]+1]=0;//fila der
            s->tablero[e->filas[1]+1][e->col[1]]=0; //centro abajo
            s->tablero[e->filas[1]-1][e->col[1]]=0; //centro abajo
            //centro no se actualiza ya que su lugar sigue ocupado
            s->filas[1] --;//actualizamos la nueva posicion del centro
        break;

        case ARRIBA_B:
        break;

        case ARRIBA_C: 
        break;

        case ABAJO_A:
        break;

        case ABAJO_B:
        break;
        
        case ABAJO_C:
        break;

        case DCHA_A:
        break;
        
        case DCHA_B:
        break;

        case DCHA_C:
        break;

        case IZQDA_A:
        break;

        case IZQDA_B:
        break;

        case IZQDA_C:
        break;
        
        default: break;
    }
return s;
}

//Distancia MANHATTAN ==> distancia desde el centro al lugar actual