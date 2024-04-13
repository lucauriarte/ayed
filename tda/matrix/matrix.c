#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

/**
 * @brief Crea la matriz con el tamaño apropiado según las dimensiones establecidas.
 * 
 * @param row filas 
 * @param col columnaumns 
 * @return matrix* 
 */
matrix* matrix_new(int rows, int columns){
    matrix* mtx = NULL;

    mtx = (matrix*)malloc(sizeof(matrix));

    if(mtx != NULL)
    {
        mtx->a = (void**)malloc(sizeof(void*) * rows * columns);
        if(mtx->a != NULL)
        {
            mtx->columns = columns;
            mtx->rows = rows;
        }
        else
        {
            mtx = NULL;
        }
    }

    return mtx;
}

/**
 * @brief Elimina la matriz
 * 
 * @param m puntero a la matriz 
 */
void matrix_free(matrix* m){
    free(m->a);
    free(m);
}

/**
 * @brief Permite obtener la cantidad de filas
 * 
 * @param m puntero a la matriz 
 * @return int la cantidad de filas
 */
int matrix_rows(matrix* m){
    int rows = -1;
    if (m != NULL)
    {
        rows = m->rows;
    }
    return rows;
}

/**
 * @brief Permite obtener la cantidad de columnas
 * 
 * @param m puntero a la matriz 
 * @return int la cantidad de columnas
 */
int matrix_columns(matrix* m){
    int columns = -1;
    if (m != NULL)
    {
        columns = m->columns;
    }
    return columns;
}

/**
 * @brief Permite obtener el valor de una posición de la matriz
 * 
 * @param m puntero a la matriz 
 * @param row fila 
 * @param col columna 
 * @return void* 
 */
void* matrix_get(matrix* m, int row, int col){
    void* aux = NULL;
    if((m != NULL) && (row >= 0) && (row <= m->rows) && (col >= 0) && (col <= m->columns))
    {
        aux = m->a[(row * m->columns) + col];
    }
    return aux;
}

/**
 * @brief Permite reemplazar o asignar un elemento a la matriz
 * 
 * @param m puntero a la matriz 
 * @param row fila
 * @param col columna
 * @param value valor a asignar
 */
void matrix_set(matrix* m, int row, int col, void* value){
    if((m != NULL) && (row >= 0) && (row <= m->rows) && (col >= 0) && (col <= m->columns))
    {
        m->a[(row * m->columns) + col] = value;
    }    
}

/**
 * @brief Permite imprimir una matriz por consola
 * 
 * @param m puntero a la matriz 
 * @param prt función que permite imprimir un valor de la matriz
 */
void matrix_print(matrix* m, void prt(void*)){
    if(m != NULL)
    {
        for(int i=0; i<m->rows; i++)
        {
            for(int j=0; j<m->columns; j++)
            {
                prt(m->a[(i*m->columns) + j]);
                printf(" ");
            }
            printf("\n");
        }
    }
}