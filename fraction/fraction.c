#include "fraction.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Encuentra el maximo comun divisor entre dos enteros
 * 
 * @param a entero a.
 * @param b entero b.
 * @return mcd entre a y b
 */
int mcd(int a, int b) 
{
    int aux = 0;

    while (b != 0) 
    {
        aux = b;
        b = a % b;
        a = aux;
    }

    return a;
}

/**
 * @brief Encuentra el minimo comun multiplo entre dos enteros
 * 
 * @param a entero a.
 * @param b entero b.
 * @return mcm entre a y b
 */
int mcm(int a, int b) 
{
    return (a * b) / mcd(a, b);    
}

fraction* fraction_new (int num, int den)
{
    fraction* res = NULL;
    res = (fraction*)malloc(sizeof(fraction));

    if(den == 0)
    {
        den = 1;
    }

    res->num = num;
    res->den = den;

    return res;
}

void fraction_destroy (fraction* f)
{
    free(f);   
}

void fraction_print (fraction* f)
{
    printf(" %i/%i\n", f->num, f->den);
}

int fraction_get_num (fraction* f)
{
    return f->num;
}

int fraction_get_den (fraction* f)
{
    return f->den;
}

fraction* fraction_add (fraction* f1, fraction* f2)
{
    fraction* res = NULL;
    int den_comun = 0;
    int num_1 = 0;
    int num_2 = 0;

    res = fraction_new(1, 1);
    
    den_comun = mcm(f1->den, f2->den);
    
    num_1 = f1->num * (den_comun / f1->den);
    num_2 = f2->num * (den_comun / f2->den);
    
    res->num = num_1 + num_2;
    res->den = den_comun;
    
    return res;
}

fraction* fraction_sub (fraction* f1, fraction* f2)
{
    fraction* m_f2 = NULL;
    fraction* res = NULL;

    res = fraction_new(1, 1);
    m_f2 = fraction_new(-f2->num, f2->den);

    res = fraction_add(f1, m_f2);

    return res;
}

fraction* fraction_mul (fraction* f1, fraction* f2)
{
    fraction* res = NULL;

    res = fraction_new(1, 1);

    res->num = f1->num * f2->num;
    res->den = f1->den * f2->den;

    return res;
}

fraction* fraction_div (fraction* f1, fraction* f2)
{
    fraction* res = NULL;

    res = fraction_new(1, 1);

    res->num = f1->num * f2->den;
    res->den = f1->den * f2->num;

    return res;
}

void fraction_test(void)
{
    fraction* f1;
    fraction* f2;
    fraction* f3;

    f1 = fraction_new(2, 4);
    f2 = fraction_new(3, 9);

    printf("Fraccion 1: ");
    fraction_print(f1);
    printf("Fraccion 2: ");
    fraction_print(f2);

    printf("Suma de fracciones: ");
    f3 = fraction_add(f1, f2);
    fraction_print(f3);
    fraction_destroy(f3);

    printf("Resta de fracciones: ");
    f3 = fraction_sub(f1, f2);
    fraction_print(f3);
    fraction_destroy(f3);

    printf("Multiplicacion de fracciones: ");
    f3 = fraction_mul(f1, f2);
    fraction_print(f3);
    fraction_destroy(f3);

    printf("Division de fracciones: ");
    f3 = fraction_div(f1, f2);
    fraction_print(f3);
    fraction_destroy(f3);
}