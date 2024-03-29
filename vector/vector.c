#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

typedef struct _vector{
   VECTOR_ELEMENT* a;
   int size;
   int max_size;
} vector;


void resize(vector* v)
{
   
}

/**
 * @brief Crea el vector vacío reservando el espacio en memoria. Tamaño = 0, Tamaño Máximo = ini_size.
 * 
 * @param ini_size 
 * @return vector* 
 */
vector* vector_new(int ini_size)
{
   vector* res = NULL;

   res = (vector*)malloc(sizeof(vector));
   
   if(res != NULL)
   {
      res->a = (VECTOR_ELEMENT*)malloc(sizeof(VECTOR_ELEMENT) * res->max_size);
      if(res->a != NULL)
      {
         res->size = 0;
         res->max_size = ini_size;
      }
      else
      {
         res = NULL;
      }
   }

   return res;
}

/**
 * @brief Eliminar el vector
 * 
 * @param v 
 */
void vector_free(vector* v){
   free(v->a);
   free(v);
} 

/**
 * @brief Permite obtener el tamaño actual del vector
 * 
 * @param v 
 * @return int 
 */
int vector_size(vector* v){
   return v->size;
}

/**
 * @brief Devuelve 0 si no está lleno y 1 si está lleno. 
 * 
 * @param v 
 * @return int 
 */
int vector_isfull(vector* v) {
   int isfull = 0;

   if(v->size == v->max_size)
   {
      isfull = 1;
   }

   return isfull;
}

/**
 * @brief Devuelve 0 si no está vacío y 1 si está vacío. 
 * 
 * @param v 
 * @return int 
 */
int vector_isempty(vector* v){
   int isempty = 0;

   if(v->size == 0)
   {
      isempty = 1;
   }

   return isempty;
}


/**
 * @brief Permite obtener el valor de una posición del vector
 * 
 * @param v 
 * @param index 
 * @return VECTOR_ELEMENT 
 */
VECTOR_ELEMENT vector_get(vector* v, int index){
   return v->a[index];
}  


/**
 * @brief Permite reemplazar el valor de una posición del vector
 * 
 * @param v 
 * @param index 
 * @return VECTOR_ELEMENT 
 */
VECTOR_ELEMENT vector_set(vector* v, int index, VECTOR_ELEMENT value){
   VECTOR_ELEMENT old_value = 0;
   
   old_value = v->a[index];

   v->a[index] = value;

   return old_value;
}

/**
 * @brief Permite agregar un elemento al final
 * 
 * @param v 
 * @param value 
 */
int vector_add(vector* v, VECTOR_ELEMENT value){
   if(vector_isfull(v))
   {
      expand(v);
   }
}

/**
 * @brief Permite agregar un elemento en una posición determinada.
 * 
 * @param v 
 * @param index 
 * @param value 
 */
int vector_insert(vector* v, int index, VECTOR_ELEMENT value){
   /*** COMPLETAR ***/
}


/**
 * @brief Permite eliminar un elemento del vector
 * 
 * @param v 
 * @param index 
 */
VECTOR_ELEMENT vector_remove(vector* v, int index){
   /*** COMPLETAR ***/ 
}

/**
 * @brief print the vector
 * 
 */
void vector_print(vector* v, void (*print)(VECTOR_ELEMENT)){
   /*** COMPLETAR ***/
}