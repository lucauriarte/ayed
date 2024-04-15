#include "../tda/matrix/matrix.h"
#include "../tda/vector/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_int(void* value)
{
    printf("%4d", *(int*)value);
}

void print_int_v(int value)
{
    printf("%4d\n", value);
}

void fill_matrix(matrix* m, int max) 
{
    srand(time(NULL));

    for (int i=0; i<matrix_rows(m); i++)
    {
        for (int j=0; j<matrix_columns(m); j++)
        {
            int* value = (int*)malloc(sizeof(int));
            *value = rand() % max;
            matrix_set(m, i, j, value);
        }
    }
}

void fill_and_print_10x10_int_matix(matrix* m)
{
    printf("Este procedimiento llena una matriz de 10x10 con numeros aleatorios, y luego la imprime\n");

    fill_matrix(m, 20);

    matrix_print(m, print_int);
}

int replace_row(matrix* m, int row, vector* v) 
{
    int status = 0;
    int* value = NULL;
    if((m != NULL) && (v != NULL) && (matrix_columns(m) == vector_size(v)))
    {
        for (int j=0; j<matrix_columns(m); j++)
        {
            value = (int*)matrix_get(m, row, j);
            *value = vector_get(v, j);
            matrix_set(m, row, j, value);
        }
    }
    else 
    {
        status = -1;
    }
    return status;
}

int replace_col(matrix* m, int col, vector* v) 
{
    int status = 0;
    int* value = NULL;
    if((m != NULL) && (v != NULL) && (matrix_rows(m) == vector_size(v)))
    {
        for (int i=0; i<matrix_rows(m); i++)
        {
            value = (int*)matrix_get(m, i, col);
            *value = vector_get(v, i);
            matrix_set(m, i, col, value);
        }
    }
    else 
    {
        status = -1;
    }
    return status;
}

void replace_with_int_vector(matrix* m, int replace(matrix*, int, vector*))
{
    int aux = 0;
    vector* v = vector_new(10);
    while(!vector_isfull(v))
    {
        aux = rand() % 10;
        vector_add(v, aux);
    }
    printf("\nMatrix original:\n");
    matrix_print(m, print_int);
    printf("\nVector:\n");
    vector_print(v, print_int_v);
    replace(m, 0, v);
    printf("\nMatriz modificada:\n");
    matrix_print(m, print_int);
}

int main()
{
    matrix* m = NULL;

    m = matrix_new(10, 10);
    
    fill_and_print_10x10_int_matix(m);

    printf("\nReemplazo de una fila por un vector de enteros:\n");
    replace_with_int_vector(m, replace_row);

    printf("\nReemplazo de una columna por un vector de enteros:\n");
    replace_with_int_vector(m, replace_col);
}