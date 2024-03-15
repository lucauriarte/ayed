#ifndef FRACTION_H
#define FRACTION_H

/**
 * @brief Estructura para administrar fracciones
 */
typedef struct
{
    int num;
    int den;
} fraction;

/**
 * @brief Crea e inicializa una fraccion.
 * 
 * @return puntero a la fraccion.
 */
fraction* fraction_new (int num, int den);

/**
 * @brief Destruye y libera la memoria de una fraccion.
 *
 * @param f fraccion a destruir.
 */
void fraction_destroy (fraction* f);

/**
 * @brief Imprime una fraccion.
 *
 * @param f fraccion a imprimir.
 */
void fraction_print (fraction* f);

/**
 * @brief Obtiene el numerador de una fraccion.
 *
 * @param f fraccion de la cual se quiere obtener el numerador.
 * @return numerador
 */
int fraction_get_num (fraction* f);

/**
 * @brief Obtiene el denominador de una fraccion.
 *
 * @param f fraccion de la cual se quiere obtener el denominador.
 * @return denominador
 */
int fraction_get_den (fraction* f);

/**
 * @brief Suma dos fracciones.
 *
 * @param f1 fraccion a sumar.
 * @param f2 fraccion a sumar.
 * @return fraccion resultante
 */
fraction* fraction_add (fraction* f1, fraction* f2);

/**
 * @brief Resta dos fracciones.
 *
 * @param f1 fraccion a restar.
 * @param f2 fraccion a restar.
 * @return fraccion resultante
 */
fraction* fraction_sub (fraction* f1, fraction* f2);

/**
 * @brief Multiplica dos fracciones.
 *
 * @param f1 fraccion a mnultiplicar.
 * @param f2 fraccion a multiplicar.
 * @return fraccion resultante
 */
fraction* fraction_mul (fraction* f1, fraction* f2);

/**
 * @brief Divide dos fracciones.
 *
 * @param f1 fraccion a dividir.
 * @param f2 fraccion a dividir.
 * @return fraccion resultante
 */
fraction* fraction_div (fraction* f1, fraction* f2);

/**
 * @brief Reduce una fraccion a su minima expresion.
 * En caso de que ya este en su expresion minima no la modifica.
 *
 * @param f fraccion a simplificar
 */
void fraction_simplify (fraction* f);

/**
 * @brief Compara dos fracciones.
 *
 * @param f1 fraccion a comparar.
 * @param f2 fraccion a comparar.
 * @return
 *   0 si f1 = f2
 *  >0 si f1 > f2
 *  <0 si f1 < f2
 */
int fraction_cmp (fraction* f1, fraction* f2); 

/**
 * @brief Testea todas las funciones de la libreria
 */
void fraction_test(void);

#endif