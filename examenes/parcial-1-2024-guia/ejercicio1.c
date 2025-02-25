#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/stack.h"

// Definir estructura de nodo de lista
typedef struct _node {
    int value;
    struct _node *next;
} node;

// Crear un nodo de lista
node* node_new(int value) {
    /**COMPLETAR**/
    return NULL; //reemplazar el resultado por el nodo creado
}

// Agregar un nodo primero a la lista
// y devolver el nodo agregado
void list_add_first(node** head, int value) {
    /**COMPLETAR**/
}

// Imprimir una lista, con un nombre. 
// ejemplo: "Lista: 1 -> 2 -> 3 -> NULL"
void list_print(node* n, char* list_name) {
    printf("%s: ", list_name);
    while (n != NULL) {
        printf("%d -> ", n->value);
        n = n->next;
    }
    printf("NULL\n");
}

// Calcular la suma de los elementos de la lista
// en forma iterativa, utilizando una variable auxiliar sum inicializada en cero
int list_sum(node* n) {
    /**COMPLETAR**/
}

// Calcular el promedio de los elementos de la lista
// en forma iterativa, utilizando dos variables auxiliares: sum y count
// (basado en la función list_sum)
float list_avg(node* n) {
    /**COMPLETAR**/
}

// Insertar en la lista un nodo en orden asendente (según el valor)
void list_insert_sorted(node** head, node* n) {    
    /**COMPLETAR**/
}

// Definir un nodo de SLL con un campo "prom" float y un puntero a una lista de enteros
// es un nodo de lista de listas con promedios
typedef struct _node_p {
    float prom;
    node* list;
    struct _node_p *next;
} node_p;

// Crear un node_p recibiendo como parámentro de entrada una lista de enteros
// Utilizar la funcion list_avg para completar el campo "prom"
node_p* node_p_new(node* list) {
    /**COMPLETAR**/
    return NULL; //reemplazar el resultado por el nodo creado
}

// Insertar en la lista de promedios en orden descendente (según el promedio)
// tener en cuenta que el campo "prom" ya está calculado, y se recibe un nodo_p
// tomar como base la función list_insert_sorted
void list_insert_sorted_prom(node_p** head, node_p* n) {
    /**COMPLETAR**/
}

// Imprimir una lista de promedios, con un nombre.
// ejemplo: 
// Lista de promedios: 
// 1: 2 -> 3 -> 1 -> NULL  
// (prom = 2.0)
// 2: 5 -> 4 -> 3 -> NULL  
// (prom = 4.0)
// utilizar list_print para imprimir la lista de enteros
void list_print_prom(node_p* n, char* list_name) {
    printf("%s: \n", list_name);
    int i = 1;
    while (n != NULL) {
        printf("%d", i);
        list_print(n->list, "");
        printf(" (prom = %.2f)\n", n->prom);
        n = n->next;
        i++;
    }
}

// Extraer la primer lista de una lista de listas con promedios y destruir el nodo
// la lista debe quedar formada a partir del siguiente nodo
// tener en cuenta que se debe liberar la memoria del nodo extraído 
// y devolver la lista que contiene
node* list_extract_first(node_p** head) {
    /**Completar**/
    return NULL; //reemplazar el resultado por la lista extraída
}

// Hacer una función que imprima una pila (stack) de listas de enteros
// utilizar list_print para imprimir cada lista
// sacar todo los elementos de la pila imprimirlos (utilizando list_print) y enviarlos a una pila auxiliar
// luego volver a ponerlos en la pila original
// tener en cuenta que se debe liberar la memoria de la pila auxiliar
void stack_print(stack* s) {
    /**COMPLETAR**/
}

// Recibir una pila (stack) de listas de enteros
// vaciar la pila y agregar cada elemento a una lista de promedios (utilizando la función list_insert_sorted_prom)
// vaciar la lista de promedios agregando cada lista a la pila (utilizando list_extract_first)
void stack_sort_avg (stack* s) {
    /**COMPLETAR**/
}

int main (int argc, char *argv[]) {
    
    // crear una lista vacía
    node* head = NULL;

    // agregar nodos a la lista por delante en este orden: 1, 3, 2
    list_add_first(&head, 1);
    list_add_first(&head, 3);
    list_add_first(&head, 2);

    // imprimir la lista
    printf("\nSe prueba que la lista 1 sea correcta:\n");
    list_print(head, "Lista");

    // imprimir la suma de los elementos de la lista
    printf("\nSuma de los elementos de la lista: %d\n", list_sum(head));

    // imprimir el promedio de los elementos de la lista
    printf("\nPromedio de los elementos de la lista: %.2f\n", list_avg(head));

    // Crear una lista 2 insertando en forma ordenada
    node* head2 = NULL;
    list_insert_sorted(&head2, node_new(5));
    list_insert_sorted(&head2, node_new(3));
    list_insert_sorted(&head2, node_new(-2));
    list_insert_sorted(&head2, node_new(4));
    list_insert_sorted(&head2, node_new(-5));
    
    printf("\nSe prueba que la lista 2 sea correcta:\n");
    list_print(head2, "Lista 2");    

    // Crear una lista de promedios
    node_p* head_p = NULL;
    list_insert_sorted_prom(&head_p, node_p_new(head));
    list_insert_sorted_prom(&head_p, node_p_new(head2));
    printf("\nSe prueba lista de listas con promedio:\n");
    list_print_prom(head_p, "Lista de promedios");

    // Crear una pila e incluir ambas listas y una más con los elementos -2 y 8
    node* head3 = NULL;
    list_add_first(&head3, 8);
    list_add_first(&head3, -2);
    

    stack* s = stack_new(3);
    push(s, head3);
    push(s, head2);
    push(s, head);

    // Imprimir la pila
    printf("\nPila original:\n");    
    stack_print(s);

    stack_sort_avg (s);

    printf("\nPila ordenanda:\n");
    stack_print(s);

    return 0;
}


// Si todo sale bien debería imprimir: 
/*

Se prueba que la lista 1 sea correcta:
Lista: 2 -> 3 -> 1 -> NULL

Suma de los elementos de la lista: 6

Promedio de los elementos de la lista: 2.00

Se prueba que la lista 2 sea correcta:
Lista 2: -5 -> -2 -> 3 -> 4 -> 5 -> NULL

Se prueba lista de listas con promedio:
Lista de promedios:
1: 2 -> 3 -> 1 -> NULL
 (prom = 2.00)
2: -5 -> -2 -> 3 -> 4 -> 5 -> NULL
 (prom = 1.00)

Pila original:
: 2 -> 3 -> 1 -> NULL
: -5 -> -2 -> 3 -> 4 -> 5 -> NULL
: -2 -> 8 -> NULL

Pila ordenanda:
: -5 -> -2 -> 3 -> 4 -> 5 -> NULL
: 2 -> 3 -> 1 -> NULL
: -2 -> 8 -> NULL

*/