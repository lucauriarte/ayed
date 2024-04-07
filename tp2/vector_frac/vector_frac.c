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

void remove_equivalent_fracs(vector* v)
{
    int index = 0;
    int size = vector_size(v);
    while(index < size)
    {
        fraction* e = vector_get(v, index);
        for(int i=(index+1); i<size; i++)
        {
            if(fraction_cmp(e, vector_get(v, i)) == 0)
            {
                vector_remove(v, i);
                size--;
            }
        }
        index++;
    }
}

int main()
{
    vector* v = NULL;

    v = vector_new(100);
    fill_100_random_frac(v);
    vector_print(v, fraction_print);
    remove_equivalent_fracs(v);
    vector_print(v, fraction_print);
    return 0;
}