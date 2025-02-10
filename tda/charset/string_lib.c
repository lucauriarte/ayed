#include <stdint.h>
#include <stdio.h>
#include "charset.h"
#include "charset_lib2.h"
#include "string_lib.h"

#define MAX_STRINGS 32

char* string_get_common_chars(char string_array[][MAX_CHARS], uint8_t num_strings)
{
    pcharset p_strings[MAX_STRINGS];
    pcharset p_res = NULL;
    char* res;

    p_res = charset_init();

    for (int i=0 ; i < num_strings ; i++) 
    {
        p_strings[i] = charset_init();
        charset_add_str(p_strings[i], string_array[i]);
    }

    p_res = charset_intersection(p_strings[0], p_strings[1]);
    for (int i=2 ; i < num_strings ; i++) 
    {
        p_res = charset_intersection(p_res, p_strings[i]);
    }

    res = charset_tostring(p_res);

    for(int i=0 ; i < num_strings ; i++)
    {
        charset_free(p_strings[i]);
    }
    charset_free(p_res);

    return res;
}

uint8_t string_words_count(char* string)
{
    pcharset delimiters = NULL;
    uint8_t words_count = 0;
    uint8_t prev_char_delimiter = 1;

    delimiters = charset_init();

    charset_add_str(delimiters, "”.,:;’?()[]{}");
    charset_add(delimiters, 0x20); // Espacio
    charset_add(delimiters, 0x9); // TAB

    while (*string != '\0')
    {
        // Si el carácter actual no es un delimitador y el carácter anterior fue un delimitador, incrementar el contador de palabras
        if (!charset_in(delimiters, *string) && prev_char_delimiter)
        {
            words_count++;
        }

        prev_char_delimiter = charset_in(delimiters, *string);

        string++;
    }

    charset_free(delimiters);

    return words_count;
}

uint8_t string_valid_usernames(char usernames[][MAX_CHARS], uint8_t num_usernames)
{
    uint8_t valid_usernames = 0;
    pcharset valid_chars = NULL;
    pcharset usernames_ch[MAX_STRINGS];
    pcharset intersetion = NULL;
    char* p_username;

    valid_chars = charset_init();

    charset_add_range(valid_chars, '0', '9');
    charset_add_range(valid_chars, 'a', 'z');
    charset_add_range(valid_chars, 'A', 'Z');

    for (int i=0 ; i < num_usernames ; i++) 
    {
        p_username = usernames[i];
        while (*p_username != '\0' && charset_in(valid_chars, *p_username))
        {
            p_username++;
        }
        if(*p_username == '\0')
        {
            valid_usernames++;
        }
    }

    return valid_usernames;
}

void string_test()
{
    char strings[MAX_STRINGS][MAX_CHARS] = {"hola", "chau", "asado", "casa", "auto"};
    char usernames[MAX_STRINGS][MAX_CHARS] = {"cuca", "cuca123", "cuca!", "Cuca", "C u c a", "c.u.c.a"};
    char* res = NULL;
    char *str = "Esta/es una.cadena;de(prueba   tab";
    uint8_t words = 0;
    uint8_t valid_usernames = 0;
    /* Caracteres comunes en varios strings */
    res = string_get_common_chars(strings, 5);

    printf("Caracteres comunes en el arreglo de strings: %s\n", res);

    /* Contar palabras separadas por ciertos caracteres */
    words = string_words_count(str);
    
    printf("Cantidad de palabras: %d\n", words);

    /* Comprobar cantidad de usuarios validos */
    valid_usernames = string_valid_usernames(usernames, 6);

    printf("Cantidad de nombres de usuario validos: %u\n", valid_usernames);
}