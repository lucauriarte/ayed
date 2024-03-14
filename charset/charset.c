#include <stdio.h>
#include <stdint.h>
#include "charset.h"
#include "charset_lib2.h"

charset* charset_intersection(charset* cs_1, charset* cs_2)
{
    pcharset p_resultado = NULL;

    p_resultado = charset_init();

    for (int i = 0; i < MAX_CHARS ; i++) 
    {
        if(charset_in(cs_1, i) && charset_in(cs_2, i))
        {
            charset_add(p_resultado, i);
        }
    }

    return p_resultado;
}

char* charset_tostring(charset* ch)
{
    static char string[MAX_CHARS] = {0};
    uint8_t cant_caracteres = 0;

    for (int i = 0; i < MAX_CHARS ; i++) 
    {
        if(charset_in(ch, i))
        {
            string[cant_caracteres] = i;
            cant_caracteres++;
        }
    }
    
    string[cant_caracteres] = '\0';

    return string;
}

void charset_test()
{
    pcharset p_res = NULL;
    pcharset p_ch_1 = NULL;
    pcharset p_ch_2 = NULL;
    char* string;

    p_ch_1 = charset_init();
    p_ch_2 = charset_init();

    charset_add_str(p_ch_1, "hola");
    charset_add_str(p_ch_2, "auto");

    /* Interseccion de caracteres */

    p_res = charset_intersection(p_ch_1, p_ch_2);

    printf("Charset 1: ");
    charset_print(p_ch_1);
    printf("Charset 2: ");
    charset_print(p_ch_2);
    printf("Interseccion: ");
    charset_print(p_res);

    /* Charset a string */

    string = charset_tostring(p_ch_1);

    printf("Charset 1 convertido a string: %s\n", string);

    /* Libero memoria */

    charset_free(p_ch_1);
    charset_free(p_ch_2);
    charset_free(p_res);
}