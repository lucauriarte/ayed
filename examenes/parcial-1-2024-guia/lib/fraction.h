/* Fraction data type */
typedef struct _fraction fraction;

fraction* fraction_new (int num, int den); // crear una fracción
void fraction_destroy (fraction* f); //destruir una fracción
int fraction_get_num (fraction* f); //obtener numerador
int fraction_get_den (fraction* f); //obtener denominador
fraction* fraction_add (fraction* f1, fraction* f2); //sumar 2 fracciones
fraction* fraction_sub (fraction* f1, fraction* f2); //restar 2 fracciones
fraction* fraction_mul (fraction* f1, fraction* f2); //multiplicar 2 fracciones
fraction* fraction_div (fraction* f1, fraction* f2); //dividir 2 fracciones
void fraction_simplify (fraction* f); //simplificar una fracción
int fraction_cmp (fraction* f1, fraction* f2); //comparar 2 fracciones
void fraction_print (fraction* f); //imprimir una fracción