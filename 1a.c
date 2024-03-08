#include <stdio.h>
#include <string.h>
#include "charset_lib2.c"

#define MAX_ASCII_CHARS 256

charset* charset_intersection (charset* cs_1, charset* cs_2);

charset* charset_intersection (charset* cs_1, charset* cs_2)
{
    struct charset resultado = {0};
    int caracteres[MAX_ASCII_CHARS] = {0};
    int i = 0;
    int cant_caracteres_comunes = 0;

    resultado = charset_init();

    for (i = 0; cs_1->v[i] != '\0'; i++) 
    {
        caracteres[str1[i]] |= 0b00000001;
    }

    for (i = 0; cs_2->v[i] != '\0'; i++) 
    {
        caracteres[str2[i]] |= 0b00000010;
    }

    for (i = 0; i < MAX_ASCII_CHARS; i++) 
    {
        if (caracteres[i] == 0b00000011) 
        {
            resultado.v[cant_caracteres_comunes] = i;
            cant_caracteres_comunes++; 
        }
    }
    resultado.v[cant_caracteres_comunes] = '\0';

    return &resultado;
}