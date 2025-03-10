#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

typedef struct _t_friendship
{
    char f1;
    char f2;
    int weight;
}t_friendship;

typedef struct _vector{
   VECTOR_ELEMENT* a;
   int size;
   int max_size;
} vector;

int expand(vector* v)
{
   int status = 0;
   
   v->max_size *= 2;
   v->a = (VECTOR_ELEMENT*)realloc(v->a, sizeof(VECTOR_ELEMENT) * v->max_size);
   if(v->a == NULL)
   {
      status = -1;
   }

   return status;
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
      res->a = (VECTOR_ELEMENT*)malloc(sizeof(VECTOR_ELEMENT) * ini_size);
      if(res->a != NULL)
      {
         res->size = 0;
         res->max_size = ini_size;
      }
      else
      {
         free(res);
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
   VECTOR_ELEMENT old_value = {0};
   
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
   int status = 0;
   
   if(vector_isfull(v))
   {
      status = expand(v);
   }
   if(status == 0)
   {
      v->a[v->size] = value;
      v->size++;
   }

   return status;
}

/**
 * @brief Permite agregar un elemento en una posición determinada.
 * 
 * @param v 
 * @param index 
 * @param value 
 */
int vector_insert(vector* v, int index, VECTOR_ELEMENT value){
   int status = 0;

   if(vector_isfull(v))
   {
      status = expand(v);
   }
   if(index >= v->size)
   {
      status = -1;
   }
   if(status == 0)
   {   
      for (int i = v->size; i > index; i--) 
      {
         v->a[i] = v->a[i-1];
      }
      v->a[index] = value;
      v->size++;  
   }

   return status;
}

/**
 * @brief Permite eliminar un elemento del vector
 * 
 * @param v 
 * @param index 
 */
VECTOR_ELEMENT vector_remove(vector* v, int index){
   VECTOR_ELEMENT value = v->a[index];
    v->size--;
    for (int i = index; i < v->size; i++)
    {
        v->a[i] = v->a[i+1];
    }

    return value;
}

/**
 * @brief print the vector
 * 
 */
void vector_print(vector* v, void (*print)(VECTOR_ELEMENT)){
   for (int i = 0; i < v->size; i++)
   {
      printf("V[%i] = ", i);
      print(v->a[i]);
   }
}

/**
 * @brief Ordena el vector de forma ascendente
 * 
 * @param v Vector
 * @param cmp Funcion de comparacion 
 */
void vector_sort(vector* v, int cmp(VECTOR_ELEMENT, VECTOR_ELEMENT))
{
   VECTOR_ELEMENT e1;
   VECTOR_ELEMENT e2;
   char swapped = 1;
   int size = vector_size(v);

   while ((swapped != 0) && (size > 0)) 
   {
      swapped = 0;
      for (int i = 1; i < size; i++) 
      {
         e1 = vector_get(v, i - 1);
         e2 = vector_get(v, i);
         if (cmp(e1, e2) > 0) 
         {
               vector_set(v, i, e1);
               vector_set(v, i - 1, e2);
               swapped = 1;
         }
      }
      size--;
   }
}

/**
 * @brief Realiza una busqueda secuencial en el vector
 * 
 * @param v Vector
 * @param e Elemento a buscar
 * @param cmp Funcion de comparacion
 * @return Retorna la posicion del elemento o -1 si este no esta presente en el vector
 */
int vector_search_seq(vector* v,VECTOR_ELEMENT e, int cmp(VECTOR_ELEMENT, VECTOR_ELEMENT))
{
   int position = 0;
   int size =  vector_size(v);

   while ((position < size) && (cmp(vector_get(v, position), e) != 0)) 
   {
      position++;
   }

   return (position < size)? position : -1;
}

/**
 * @brief Realiza una busqueda binaria en el vector. Requiere que el vector este ordenado
 * 
 * @param v Vector
 * @param e Elemento a buscar
 * @param cmp Funcion de comparacion
 * @return Retorna la posicion del elemento o -1 si este no esta presente en el vector
 */
int vector_search_bin(vector* v, VECTOR_ELEMENT e, int cmp(VECTOR_ELEMENT, VECTOR_ELEMENT))
{
   int size =  vector_size(v);
   int high = size - 1;
   int low = 0;
   int mid = (high - low) / 2;

   while ((low < high) && (cmp(vector_get(v, mid), e) != 0))
   {
      if (cmp(e, vector_get(v, mid)) < 0)
      {
         high = mid - 1;
      }
      else
      {
         low = mid + 1;
      }
      mid = (high + low) / 2;
   }

   return(cmp(vector_get(v, mid), e) == 0) ? mid : -1;
}