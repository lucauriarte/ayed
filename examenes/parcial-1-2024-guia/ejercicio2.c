#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/fraction.h"

//Difinir un tipo de nodo de lista que contenga fracciones
typedef struct _node {
    fraction* value;
    struct _node *next;
} node;

//Crear un nodo de lista
node* node_new(fraction* value) {
    /**COMPLETAR**/
    return NULL; //reemplazar el resultado por el nodo creado
}

// Agregar un nodo al final de la lista
// y devolver el nodo agregado (para poder utilizarlo como el ultimo)
node* list_add_last(node** head, node* n) {    
    /**COMPLETAR**/
    return n;
}

// Imprimir una lista de fracciones, con un nombre.
// usar fraction_print para imprimir cada fracción.
void list_print(node* n, char* list_name) {
    printf("%s: ", list_name);
    while (n != NULL) {
        fraction_print(n->value);
        printf(" -> ");
        n = n->next;
    }
    printf("NULL\n");
}

// Clonar un nodo de una lista de fracciones
// crear un nuevo nodo con una fracción clonada (utilizando fraction_new)
// utilizar node_new para crear el nuevo nodo (ya queda con NULL, en next)
// devolver el puntero al nuevo nodo
node* node_clone(node* n) {
    return NULL; // completar remplazando el NULL (una sola linea de código)
}

// Clonar una lista y su contenido.
// Recorrer la lista original, 
// para cada nodo crear un nuevo nodo (usando node_clone),
// cada nodo nuevo se agrega al final de la lista clonada (utilizar list_add_last)
// devolver el puntero al primer nodo de la lista clonada
// ¿es eficiente? no, se recorrer toda la lista clonada con cada invocación a list_add_last
node* list_clone(node* head) {
    node* clone = NULL;
    /**COMPLETAR while... **/
    return clone;
}

// Clonar la lista en forma recursiva.
// Utilizar node_clone,
// si la lista no está vacía, clonar el primer nodo de la lista
// y luego invocar recursivamente clonar el resto de la lista
// devolver el puntero al primer nodo de la lista clonada
node* list_clone_recursive(node* head) {
    node* clone = NULL;
    /**COMPLETAR if... **/
    return clone;
}


// Buscar un nodo en una lista de fracciones
// devolver el doble puntero del nodo buscado (para poder modificarlo)
// tener en cuenta que puede ser el primero de la lista o un "next" de un nodo
// resolver en forma iterativa con un ciclo while 
// preguntando por *head distinto de NULL y *head distinto de n
// si devuelve un puntero con un puntero a NULL, el nodo no está en la lista
node** list_search(node** head, node* n) {
    /**COMPLETAR while... **/
    return head; //se puede usar head como auxiliar para devolver el resultado
}

// Repetir la misma búsqueda pero en forma recursiva
// basandose en la función anterior 
// reemplazar el while por if 
// dentro del if realizar la invocación recursiva 
// se puede re-utilizar head (porque es local) 
// para recibir el resultado de la invocación recursiva
node** list_search_recursive(node** head, node* n) {
    /**COMPLETAR if... **/
    return head;
}

// Encontrar la intereseción de dos listas
// recorrer la primera lista y para cada nodo invocar a list_search 
// (para recorrer la segunda verificando si está)
// si encuentra el mismo nodo devuelve el doble puntero de la segunda lista
// si no encuentra el doble puntero de la segunda lista apuntando a NULL
// utilizando la función list_search
node** list_intersection(node** list_a, node** list_b) {
    /**COMPLETAR**/
    return NULL; //Reemplazar por el resultado de la búsqueda
}


// Hacer una segunda versión recursiva de la función anterior
// primero buscar la interesección llamando a list_search_recursive
// en la lista B con el primer nodo de A
// si A no es NULL y no se encontró, invocar recursivamente con el siguiente de A
node** list_intersection_recursive(node** list_a, node** list_b) {
    /**COMPLETAR**/
    return NULL; //Reemplazar por el resultado de la búsqueda
}

// Dividir una lista desde la intersección 
// Utilizando las funciones anteriores
// list_intersection y list_clone
int split_list (node** list_a, node** list_b){
    /**COMPLETAR**/
    return 0; //Reemplazar por el resultado
}

// probar la misma efectividad con las versiones recursivas
int split_list_recursive(node** list_a, node** list_b){
    /**COMPLETAR**/
    return 0; //Reemplazar por el resultado
}

int main (int argc, char** argv){

    node* head = node_new(fraction_new(1,2));
    node* tail = list_add_last(&head, node_new(fraction_new(1,2)));
    node* intersec = NULL; //para fortar un punto de intersección
    if (tail != NULL) {
        //me voy quedando con el último para que sea más eficiente agregar al final
        tail = list_add_last(&tail->next, node_new(fraction_new(1,3)));
        tail = list_add_last(&tail->next, node_new(fraction_new(5,2)));
        intersec = list_add_last(&tail->next, node_new(fraction_new(99,99)));
        tail = list_add_last(&intersec->next, node_new(fraction_new(2,4)));
        tail = list_add_last(&tail->next, node_new(fraction_new(2,2)));
    }
    node* head2 = node_new(fraction_new(8,2));
    node* tail2 = list_add_last(&head2, node_new(fraction_new(5,3)));
    if (tail2 != NULL){
        tail2 = list_add_last(&tail2->next, node_new(fraction_new(5,3)));
        tail2 = list_add_last(&tail2->next, node_new(fraction_new(1,4)));
        tail2 = list_add_last(&tail2->next, intersec);
    }

    printf("\nSe Imprimen las listas recien creadas:\n");
    list_print(head, "Lista 1");
    list_print(head2, "Lista 2");

    printf("\nSe modifica la intersección de las listas:\n");
    if (intersec != NULL) {
        fraction_destroy(intersec->value);
        intersec->value = fraction_new(1,5);    
        // observar que se modifica un único nodo y ambas listas se ven afectadas
        list_print(head, "Lista 1");
        list_print(head2, "Lista 2");
    }    

    printf("\nSe prueban las búsquedas:\n");
    node** busca1 = list_search(&head, intersec);
    if (*busca1 != NULL) {
        list_print(*busca1, "Lista 1 desde el nodo encontrado");
    } else {
        printf("No encontrado en la lista 1\n");
    }
    node** busca2 = list_search_recursive(&head2, intersec);
    if (*busca2 != NULL) {
        list_print(*busca1, "Lista 2 desde el nodo encontrado");
    } else {
        printf("No encontrado en la lista 2\n");
    }

    printf("\nClonar la lista 1 con la funcion iterativa:\n");
    node* clone = list_clone(head);
    list_print(clone, "Lista clonada");

    printf("\nClonar la lista 2 con la funcion recursiva:\n");
    node* clone2 = list_clone_recursive(head2);
    list_print(clone2, "Lista clonada");

    printf("\nAlteramos las listas clonadas multiplicando por una fracción negativa:\n");
    fraction* neg = fraction_new(-1,1);
    node* aux = clone;
    while (aux != NULL) {
        fraction* f = fraction_mul(aux->value, neg);
        fraction_destroy(aux->value);
        aux->value = f;
        aux = aux->next;
    }
    aux = clone2;
    while (aux != NULL) {
        fraction* f = fraction_mul(aux->value, neg);
        fraction_destroy(aux->value);
        aux->value = f;
        aux = aux->next;
    }
    fraction_destroy(neg);
    list_print(head, "Lista 1 original");
    list_print(clone, "Lista clonada negativa");
    list_print(head2, "Lista 2 original");    
    list_print(clone2, "Lista clonada negativa");

    printf("\nSe buscan las intersecciones de las listas originales (en forma iterativa):\n");
    node** intersec1 = list_intersection(&head, &head2);
    if (intersec1 != NULL && *intersec1 != NULL) {
        list_print(*intersec1, "Intersección de las listas");
    } else {
        printf("No hay intersección\n");
    }

    printf("\nSe buscan las intersecciones de las listas originales (en forma recursiva):\n");
    node** intersec2 = list_intersection_recursive(&head, &head2);
    if (intersec2 != NULL && *intersec2 != NULL) {
        list_print(*intersec2, "Intersección de las listas");
    } else {
        printf("No hay intersección\n");
    }


    printf("\nSe divide la lista 2 desde la intersección:\n");
    if (split_list(&head, &head2)) {
    //if (split_list_recursive(&head, &head2)) {
        list_print(head, "Lista 1");
        list_print(head2, "Lista 2");
        neg = fraction_new(-1,1);
        aux = head2;
        while (aux != NULL) {
            fraction* f = fraction_mul(aux->value, neg);
            fraction_destroy(aux->value);
            aux->value = f;
            aux = aux->next;
        }
        fraction_destroy(neg);
        printf("\nSe vuelve a imprimir las listas para ver que solo la 2da se alteró:\n");
        list_print(head, "Lista 1");
        list_print(head2, "Lista 2");        
    } else {
        printf("No se pudo dividir\n");
    }
    

    return 0;
}


// Si todo es correcto, el programa debería imprimir:
/* 

Se Imprimen las listas recien creadas:
Lista 1: 1/2 -> 1/2 -> 1/3 -> 5/2 -> 99/99 -> 2/4 -> 2/2 -> NULL
Lista 2: 8/2 -> 5/3 -> 5/3 -> 1/4 -> 99/99 -> 2/4 -> 2/2 -> NULL

Se modifica la intersección de las listas:
Lista 1: 1/2 -> 1/2 -> 1/3 -> 5/2 -> 1/5 -> 2/4 -> 2/2 -> NULL
Lista 2: 8/2 -> 5/3 -> 5/3 -> 1/4 -> 1/5 -> 2/4 -> 2/2 -> NULL

Se prueban las búsquedas:
Lista 1 desde el nodo encontrado: 1/5 -> 2/4 -> 2/2 -> NULL
Lista 2 desde el nodo encontrado: 1/5 -> 2/4 -> 2/2 -> NULL

Clonar la lista 1 con la funcion iterativa:
Lista clonada: 1/2 -> 1/2 -> 1/3 -> 5/2 -> 1/5 -> 2/4 -> 2/2 -> NULL

Clonar la lista 2 con la funcion recursiva:
Lista clonada: 8/2 -> 5/3 -> 5/3 -> 1/4 -> 1/5 -> 2/4 -> 2/2 -> NULL

Alteramos las listas clonadas multiplicando por una fracción negativa:
Lista 1 original: 1/2 -> 1/2 -> 1/3 -> 5/2 -> 1/5 -> 2/4 -> 2/2 -> NULL
Lista clonada negativa: -1/2 -> -1/2 -> -1/3 -> -5/2 -> -1/5 -> -2/4 -> -2/2 -> NULL
Lista 2 original: 8/2 -> 5/3 -> 5/3 -> 1/4 -> 1/5 -> 2/4 -> 2/2 -> NULL
Lista clonada negativa: -8/2 -> -5/3 -> -5/3 -> -1/4 -> -1/5 -> -2/4 -> -2/2 -> NULL

Se buscan las intersecciones de las listas originales (en forma iterativa):
Intersección de las listas: 1/5 -> 2/4 -> 2/2 -> NULL

Se buscan las intersecciones de las listas originales (en forma recursiva):
Intersección de las listas: 1/5 -> 2/4 -> 2/2 -> NULL

Se divide la lista 2 desde la intersección:
Lista 1: 1/2 -> 1/2 -> 1/3 -> 5/2 -> 1/5 -> 2/4 -> 2/2 -> NULL
Lista 2: 8/2 -> 5/3 -> 5/3 -> 1/4 -> 1/5 -> 2/4 -> 2/2 -> NULL

Se vuelve a imprimir las listas para ver que solo la 2da se alteró:
Lista 1: 1/2 -> 1/2 -> 1/3 -> 5/2 -> 1/5 -> 2/4 -> 2/2 -> NULL
Lista 2: -8/2 -> -5/3 -> -5/3 -> -1/4 -> -1/5 -> -2/4 -> -2/2 -> NULL

*/