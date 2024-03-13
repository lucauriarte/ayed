#include <stdio.h>
#include "charset.h"
#include "charset_lib2.h"

charset* charset_intersection(charset* cs_1, charset* cs_2)
{
    charset resultado = {0};
    pcharset p_resultado = NULL;
    
    p_resultado = &resultado;

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