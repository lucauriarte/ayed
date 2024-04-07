#include <stdlib.h>
#include <stdio.h>
#include "../tda/vector/vector.h"

void fill_100_random_int(vector* v)
{
    for(int i=0; i<100; i++)
    {
        vector_add(v, rand() % 100);
    }
}

void print_int(int value)
{
    printf("%i\n", value);
}

int add_int(int a, int b)
{
    return a + b;
}

int compare_int(int a, int b)
{
    return a - b;
}

VECTOR_ELEMENT vector_operate(vector* v, VECTOR_ELEMENT (*operation)(VECTOR_ELEMENT, VECTOR_ELEMENT))
{
    VECTOR_ELEMENT res;
    int size = 0;

    size = vector_size(v);
    res = vector_get(v, 0);
    for(int i = 0; i<size; i++)
    {
        res = operation(res,  vector_get(v, i));
    }

    return res;
}

vector* vector_sum(vector* a, vector* b)
{
    int status = 0; 
    int size = 0;
    vector* result;
    //Compruebo si los dos vectores tienen el mismo tamano
    if(vector_size(a) != vector_size(b))
    {
        status = -1;
    }

    if(status == 0)
    {
        size = vector_size(a);
        result = vector_new(size);

        for(int i=0; i< size; i++)
        {
            vector_add(result, vector_get(a, i) + vector_get(b, i));
        }
    }
    
    return result;
}

int vector_max(vector* v, int cmp(VECTOR_ELEMENT, VECTOR_ELEMENT))
{
    int size = vector_size(v);
    VECTOR_ELEMENT max;
    VECTOR_ELEMENT element;

    max = vector_get(v, 0);
    for(int i=0; i<size; i++)
    {
        element = vector_get(v, i);
        if(cmp(element, max) > 0)
        {
            max = element;
        }
    }

    return max;
}

int vector_get_ocurrencies(vector* v, VECTOR_ELEMENT e, int cmp(VECTOR_ELEMENT, VECTOR_ELEMENT))
{
    int size = vector_size(v);
    int ocurrencies = 0;

    for(int i=0; i<size; i++)
    {
        if(cmp(vector_get(v, i), e) == 0)
        {
            ocurrencies++;
        }
    }

    return ocurrencies;
}

vector* get_sorted_vector(vector*v, int cmp(VECTOR_ELEMENT, VECTOR_ELEMENT))
{
    vector* result = NULL;
    char swapped = 1;
    int size = vector_size(v);
    VECTOR_ELEMENT e1, e2;

    result = vector_new(size);
    for (int i=0; i<size; i++)
    {
        vector_add(result, vector_get(v, i));
    }

    while ((swapped != 0) && (size > 0)) 
    {
        swapped = 0;
        for (int i = 1; i < size; i++) 
        {
            e1 = vector_get(result, i - 1);
            e2 = vector_get(result, i);
            if (cmp(e1, e2) > 0) 
            {
                vector_set(result, i, e1);
                vector_set(result, i - 1, e2);
                swapped = 1;
            }
        }
        size--;
    }
    return result;
}

/* Retorna -1 en caso de no encontrar el elemento solicitado */
int vector_sort_and_find(vector* v, VECTOR_ELEMENT e, int cmp(VECTOR_ELEMENT, VECTOR_ELEMENT))
{
    VECTOR_ELEMENT e1, e2;
    char swapped = 1;
    int position = -1; 
    int index = 0;
    int size = vector_size(v);

    while ((swapped != 0) && (size > 0)) 
    {
        swapped = 0;
        for (int i = 1; i < size; i++) 
        {
            e1 = vector_get(v, i - 1);
            e2 = vector_get(v, i);
            if (cmp(e1, e2) > 0) 
            {
                vector_set(v, i, e1);
                vector_set(v, i - 1, e2);
                swapped = 1;
            }
        }
        size--;
    }

    size = vector_size(v);
    while((position == -1) && (index < size))
    {
        if(vector_get(v, index) == e)
        {
            position = index;
        }
        index++;
    }
    return position;
}

vector* vector_mix(vector* v1, vector* v2, int cmp(VECTOR_ELEMENT, VECTOR_ELEMENT))
{
    int max_size = 0;
    int min_size = 0;
    VECTOR_ELEMENT e1;
    VECTOR_ELEMENT e2;
    vector* result = vector_new(vector_size(v1) + vector_size(v2));

    if(vector_size(v1) > vector_size(v2))
    {
        min_size = vector_size(v2);
        max_size = vector_size(v1);
    }
    else
    {
        min_size = vector_size(v1);
        max_size = vector_size(v2);
    }

    for(int i=0; i<min_size; i++)
    {
        e1 = vector_get(v1, i);
        e2 = vector_get(v2, i);
        if(cmp(e1, e2) > 0)
        {
            vector_add(result, e2);
            vector_add(result, e1);
        }
        else if (cmp(e1, e2) < 0)
        {
            vector_add(result, e2);
            vector_add(result, e1);
        }
        else
        {
            vector_add(result, e1);
        }
    }

    if(vector_size(v1) > vector_size(v2))
    {
        for(int i=min_size; i<max_size; i++)
        {
            vector_add(result, vector_get(v1, i));
        }
    }
    else if(vector_size(v1) < vector_size(v2))
    {
        for(int i=min_size; i<max_size; i++)
        {
            vector_add(result, vector_get(v2, i));
        }
    }

    return result;
}

int main()
{
    vector* v = NULL;
    vector* v1 = NULL;
    vector* v2 = NULL;
    vector* v3 = NULL;
    vector* unsorted_vector = NULL;
    vector* sorted_vector = NULL;
    vector* mixed_vector = NULL;
    int position = 0;

    v1 = vector_new(3);
    v2 = vector_new(3);
    unsorted_vector = vector_new(4);
    vector_add(v1, 2);
    vector_add(v1, 2);
    vector_add(v1, 2);
    vector_add(v2, 2);
    vector_add(v2, 3);
    vector_add(v2, 6);
    vector_add(unsorted_vector, 9);
    vector_add(unsorted_vector, 1);
    vector_add(unsorted_vector, 6);
    vector_add(unsorted_vector, 3);

    int sum = 0;

    v = vector_new(100);
    fill_100_random_int(v);
    vector_print(v, print_int);

    sum = vector_operate(v, add_int);
    printf("Suma de todos los elementos del vector: %i\n", sum);

    v3 = vector_sum(v1, v2);

    vector_print(v3, print_int);

    printf("Valor maximo del vector 1: %i\n", vector_max(v1, compare_int));

    printf("Cantidad de veces que aparece el numero 2 en el vector 1: %i\n", vector_get_ocurrencies(v1, 2, compare_int));
    
    printf("Vector antes de ordenarlo:\n");
    vector_print(unsorted_vector, print_int);
    sorted_vector = get_sorted_vector(unsorted_vector, compare_int);
    printf("Vector ordenado:\n");
    vector_print(sorted_vector, print_int);

    position = vector_sort_and_find(unsorted_vector, 6, compare_int);
    printf("Posicion del elemento \"6\" en el vector ordenado: %i\n", position);

    mixed_vector =  vector_mix(v2, sorted_vector, compare_int);
    printf("Vector mezclado:\n");
    vector_print(mixed_vector, print_int);
    
    return 0;
}