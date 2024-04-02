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

int main()
{
    vector* v = NULL;

    v = vector_new(100);
    fill_100_random_int(v);
    vector_print(v, print_int);

    return 0;
}