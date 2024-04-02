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

int main()
{
    vector* v = NULL;
    int sum = 0;

    v = vector_new(100);
    fill_100_random_int(v);
    vector_print(v, print_int);

    sum = vector_operate(v, add_int);
    printf("Suma de todos los elementos del vector: %i\n", sum);

    return 0;
}