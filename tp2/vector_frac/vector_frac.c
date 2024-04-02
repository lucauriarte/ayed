#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

void fill_100_random_frac(vector* v)
{
    fraction* fracs[100];

    for(int i=0; i<100; i++)
    {
        fracs[i] = fraction_new(rand() % 100, rand() % 100);
        vector_add(v, fracs[i]);
    }
}

int main()
{
    vector* v = NULL;

    v = vector_new(100);
    fill_100_random_frac(v);
    vector_print(v, fraction_print);

    return 0;
}