#include <stdio.h>
#include <string.h>

#define MAX_ASCII_CHARS 256

char* intersectar_strings(const char* str1, const char* str2, const char* str3);

int main()
{
    const char* string_1 = "Hola";
    const char* string_2 = "olas";
    const char* string_3 = "casa";
    char* res_string;

    res_string = intersectar_strings(string_1, string_2, string_3);

    printf("Caracteres comunes: %s\n", res_string);

    return 0;
}

char* intersectar_strings(const char* str1, const char* str2, const char* str3)
{
    static char res[MAX_ASCII_CHARS];
    int caracteres[MAX_ASCII_CHARS] = {0};
    int i = 0;
    int cant_caracteres_comunes = 0;

    for (i = 0; str1[i] != '\0'; i++) 
    {
        caracteres[str1[i]] |= 0b00000001;
    }

    for (i = 0; str2[i] != '\0'; i++) 
    {
        caracteres[str2[i]] |= 0b00000010;
    }

    for (i = 0; str3[i] != '\0'; i++) 
    {
        caracteres[str3[i]] |= 0b00000100;
    }

    for (i = 0; i < MAX_ASCII_CHARS; i++) 
    {
        if (caracteres[i] == 0b00000111) 
        {
            res[cant_caracteres_comunes] = i;
            cant_caracteres_comunes++; 
        }
    }
    res[cant_caracteres_comunes] = '\0';

    return res;
}