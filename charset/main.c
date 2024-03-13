#include <stdio.h>
#include "charset.h"
#include "charset_lib2.h"

int main ()
{
    charset ch_1;
    charset ch_2;
    pcharset p_res = NULL;
    pcharset p_ch_1 = &ch_1;
    pcharset p_ch_2 = &ch_2;
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
    
    return 0;
}