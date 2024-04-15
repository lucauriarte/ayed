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
    printf("%4d", value);
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

int main()
{
    matrix* m = NULL;

    m = matrix_new(10, 10);
    
    fill_and_print_10x10_int_matix(m);
}