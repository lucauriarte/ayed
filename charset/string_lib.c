#include <stdio.h>
#include "string_lib.h"

#define MAX_STRINGS 32

char* string_get_common_chars(char string_array[][MAX_CHARS], uint8_t num_strings)
{
    charset strings[MAX_STRINGS];
    pcharset p_strings[MAX_STRINGS];
    pcharset p_res = NULL;
    char* res;

    p_res = charset_init();

    for (int i=0 ; i < num_strings ; i++) 
    {
        p_strings[i] = charset_init();
        charset_add_str(p_strings[i], string_array[i]);
    }

    for (int i=0 ; i < (num_strings -1) ; i++) 
    {
        p_res = charset_intersection(p_strings[i], p_strings[i+1]);
    }

    res = charset_tostring(p_res);

    for(int i=0 ; i < num_strings ; i++)
    {
        charset_free(p_strings[i]);
    }
    charset_free(p_res);

    return res;
}

void string_test()
{
    char strings[MAX_STRINGS][MAX_CHARS] = {"hola", "chau", "asado", "casa", "auto"};
    char* res = NULL;

    res = string_get_common_chars(strings, 5);

    printf("Caracteres comunes en el arreglo de strings: %s\n", res);
}