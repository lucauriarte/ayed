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

int main()
{
    vector* v = NULL;
    vector* v1 = NULL;
    vector* v2 = NULL;
    vector* v3 = NULL;

    v1 = vector_new(3);
    v2 = vector_new(3);
    vector_add(v1, 2);
    vector_add(v1, 3);
    vector_add(v1, 6);
    vector_add(v2, 2);
    vector_add(v2, 3);
    vector_add(v2, 6);

    int sum = 0;

    v = vector_new(100);
    fill_100_random_int(v);
    vector_print(v, print_int);

    sum = vector_operate(v, add_int);
    printf("Suma de todos los elementos del vector: %i\n", sum);

    v3 = vector_sum(v1, v2);

    vector_print(v3, print_int);

    return 0;
}