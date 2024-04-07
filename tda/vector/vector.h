#ifndef _VECTOR
#define _VECTOR

#define VECTOR_ELEMENT int

typedef struct _vector vector;

vector* vector_new(int ini_size);
// Crea el vector vacío reservando el espacio en memoria. Tamaño = 0, Tamaño
// Máximo = ini_size.

void vector_free(vector* v);
// Eliminar el vector

int vector_size(vector* v);
// Permite obtener el tamaño actual del vector

int vector_isfull(vector* v);
// Devuelve 0 si no está lleno y 1 si está lleno.

int vector_isempty(vector* v);
// Devuelve 0 si no está vacío y 1 si está vacío.

VECTOR_ELEMENT vector_get(vector* v, int index);
// Permite obtener el valor de una posición del vector

VECTOR_ELEMENT vector_set(vector* v, int index, VECTOR_ELEMENT value);
// Permite reemplazar el valor de una posición del vector

int vector_add(vector* v, VECTOR_ELEMENT value);
// Permite agregar un elemento al final

int vector_insert(vector* v, int index, VECTOR_ELEMENT value);
// Permite agregar un elemento en una posición determinada.

VECTOR_ELEMENT vector_remove(vector* v, int index);
// Permite eliminar un elemento del vector

void vector_print(vector* v, void (*print)(VECTOR_ELEMENT));
// Permite imprimir un vector por consola

void vector_sort(vector* v, int cmp(VECTOR_ELEMENT, VECTOR_ELEMENT));
// Ordena el vector de forma ascendente

int vector_search_seq(vector* v,VECTOR_ELEMENT e, int cmp(VECTOR_ELEMENT, VECTOR_ELEMENT));
// Realiza una busqueda secuencial en el vector

#endif