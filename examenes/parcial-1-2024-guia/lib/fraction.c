#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fraction.h"

typedef struct _fraction {
    int num;
    int den;
} fraction;


// crear una fracción
fraction* fraction_new (int num, int den){
    fraction* f = (fraction*) malloc(sizeof(fraction));
    if (f != NULL) {
        f->num = num;
        f->den = den;
    }
    return f;
}

//destruir una fracción
void fraction_destroy (fraction* f){
    free(f);
}

//obtener numerador
int fraction_get_num (fraction* f){
    return f->num;
}

//obtener denominador
int fraction_get_den (fraction* f){
    return f->den;
}

//sumar 2 fracciones
fraction* fraction_add (fraction* f1, fraction* f2){
    return fraction_new(f1->num * f2->den + f2->num * f1->den,f1->den * f2->den);
}

//restar 2 fracciones
fraction* fraction_sub (fraction* f1, fraction* f2){
    return fraction_new(f1->num * f2->den - f2->num * f1->den,f1->den * f2->den);
}

//multiplicar 2 fracciones
fraction* fraction_mul (fraction* f1, fraction* f2){
    return fraction_new(f1->num * f2->num,f1->den * f2->den);
}

//dividir 2 fracciones
fraction* fraction_div (fraction* f1, fraction* f2){
    return fraction_new(f1->num * f2->den,f1->den * f2->num);
}

//máximo común divisor
int _mcd(int a, int b){
    if (b == 0) {
        return a;
    }
    return _mcd(b, a % b);
}

//simplificar una fracción
void fraction_simplify (fraction* f){
    int mcd = _mcd(f->num, f->den);
    f->num /= mcd;
    f->den /= mcd;
}

//comparar 2 fracciones
int fraction_cmp (fraction* f1, fraction* f2){
    return f1->num * f2->den - f2->num * f1->den;
}
//imprimir una fracción
void fraction_print (fraction* f){
    printf("%d/%d", f->num, f->den);
}