#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
    Archivos a compilar:
    examenes/recuperatorio-2-2022/ejercicio1.c
 */

typedef struct _sll{
    int value;
    struct _sll *next;
}sll;

typedef struct _btn
{
    int value;
    struct _btn *left;
    struct _btn *right;
}btn;

//Crear un nodo de sll
sll* sll_new_node(int value)
{
    sll* new_node = (sll*)malloc(sizeof(sll));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

//Agregar un nodo al final de la lista y devolver el ultimo nodo
sll* sll_add_back(sll** head, sll* node)
{
    if (node != NULL){
        while(*head != NULL)
        {
            head = &(*head)->next;
        }
        *head = node;
    }
    return node;
}

void crear_lista_de_sbt(sll** head, btn* root)
{
    if(root == NULL) return;
    sll* tail = NULL;
    crear_lista_de_sbt(head, root->left);
    tail = sll_add_back(head, sll_new_node(root->value));
    head = &tail;
    crear_lista_de_sbt(head, root->right);
}

/* Desde acá para abajo el codigo fue generado con chatgpt */

// Función para imprimir la lista
void imprimir_lista(sll* head) {
    while (head != NULL) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

// Crear un árbol binario de búsqueda para probar
btn* crear_nodo_btn(int value) {
    btn* new_node = (btn*)malloc(sizeof(btn));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Función principal
int main() {
    // Crear un árbol binario de búsqueda
    btn* root = crear_nodo_btn(5);
    root->left = crear_nodo_btn(3);
    root->right = crear_nodo_btn(7);
    root->left->left = crear_nodo_btn(2);
    root->left->right = crear_nodo_btn(4);
    root->right->left = crear_nodo_btn(6);
    root->right->right = crear_nodo_btn(8);

    // Crear la lista simplemente enlazada a partir del árbol
    sll* head = NULL;
    crear_lista_de_sbt(&head, root);

    // Imprimir la lista
    imprimir_lista(head);

    return 0;
}