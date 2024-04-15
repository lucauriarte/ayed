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
    int status = 0;
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
    status = replace(m, 0, v);
    if(status == 0)
    {
        printf("\nMatriz modificada:\n");
        matrix_print(m, print_int);
    }
    else {
        printf("Error al reemplazar\n");
    }
}

matrix* add_int_matrix(matrix* m1, matrix*m2)
{
    matrix* res = NULL;
    if((matrix_columns(m1) == matrix_columns(m2)) && (matrix_rows(m1) == matrix_rows(m2)))
    {
        res = matrix_new(matrix_rows(m1), matrix_columns(m1));
        for (int i=0; i<matrix_rows(m1); i++)
        {
            for (int j=0; j<matrix_columns(m1); j++)
            {
                int* value = (int*)malloc(sizeof(int));
                *value = *(int*)matrix_get(m1, i, j) + *(int*)matrix_get(m2, i, j);
                matrix_set(res, i, j, value);
            }
        }
    }

    return res;
}

void add_two_random_int_matrix()
{
    matrix* m1;
    matrix* m2;
    matrix* m3;

    printf("\nSuma de dos matrices de enteros:\n");
    
    m1 = matrix_new(3, 3);
    fill_matrix(m1, 10);
    printf("\nMatriz 1:\n");
    matrix_print(m1, print_int);

    m2 = matrix_new(3, 3);
    fill_matrix(m2, 10);
    printf("\nMatriz 2:\n");
    matrix_print(m2, print_int);

    m3 = add_int_matrix(m1, m2);
    printf("\nMatriz 1 + Matriz 2:\n");
    matrix_print(m3, print_int);
}

int add_vector_to_matrix_rows(matrix* m, vector* v)
{
    int status = 0;
    int* value = NULL;
    if((m != NULL) && (v != NULL) && (matrix_columns(m) == vector_size(v)))
    {
        for (int i=0; i<matrix_rows(m); i++)
        {
            for (int j=0; j<matrix_columns(m); j++)
            {
                value = (int*)matrix_get(m, i, j);
                *value += vector_get(v, j);
                matrix_set(m, i, j, value);
            }
        }
    }
    else 
    {
        status = -1;
    }
    return status;
}

void add_random_vector_to_random_matrix()
{
    matrix* m = matrix_new(3, 3);
    vector* v = vector_new(3);
    int aux = 0;

    fill_matrix(m, 10);

    while(!vector_isfull(v))
    {
        aux = rand() % 10;
        vector_add(v, aux);
    }

    printf("\nSuma de un vector a cada fila de una matriz:\n");
    printf("\nMatrix original:\n");
    matrix_print(m, print_int);
    printf("\nVector:\n");
    vector_print(v, print_int_v);

    add_vector_to_matrix_rows(m, v);
    printf("\nMatriz luego de agregarle el vector:\n");
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

    add_two_random_int_matrix();

    add_random_vector_to_random_matrix();
}