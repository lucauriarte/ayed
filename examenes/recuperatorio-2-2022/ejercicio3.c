#include <stdio.h>
#include <stdlib.h>
#include "lib/queue_dynamic_ntn.h"

/**
    Archivos a compilar:
    examenes/recuperatorio-2-2022/ejercicio3.c
    examenes/recuperatorio-2-2022/lib/queue_dynamic_ntn.c
 */

typedef struct _ntlist ntlist;

typedef struct _ntn
{
    int value;
    ntlist *sons;
}ntn;

typedef struct _ntlist
{
    ntn *node;
    ntlist* next;
}ntlist;

int even(int value)
{
    return !(value & 1);
}

int primer_nivel_par(ntn *root) {
    if (root == NULL) return -1;

    queue *q = queue_new(100);
    enqueue(q, root);

    int level = -1;
    int all_even = 0;

    while (!queue_isempty(q) && !all_even) {
        int nodes_in_level = queue_getsize(q);
        all_even = 1;
        level++;

        for (int i = 0; i < nodes_in_level; i++) {
            ntn *node = dequeue(q);
            if(!even(node->value)){
                all_even = 0;
            }

            ntlist *child = node->sons;
            while (child != NULL) {
                enqueue(q, child->node);
                child = child->next;
            }
        }

    }

    queue_free(q);
    return all_even == 1 ? level : -1;
}

/* Desde acá para abajo todo el codigo fue generado con chatgpt */
// Función para crear un nuevo nodo del árbol
ntn *new_ntn(int value) {
    ntn *node = malloc(sizeof(ntn));
    node->value = value;
    node->sons = NULL;
    return node;
}

// Función para agregar un hijo a un nodo
void add_child(ntn *parent, ntn *child) {
    ntlist *new_son = malloc(sizeof(ntlist));
    new_son->node = child;
    new_son->next = parent->sons;
    parent->sons = new_son;
}

// Función que imprime el resultado de `primer_nivel_par`
void test_tree(ntn *root, const char *name) {
    int nivel = primer_nivel_par(root);
    printf("%s -> Primer nivel con todos pares: %d\n", name, nivel);
}

// Función para liberar el árbol
void free_tree(ntn *root) {
    if (root == NULL) return;
    ntlist *child = root->sons;
    while (child != NULL) {
        ntlist *next = child->next;
        free_tree(child->node);
        free(child);
        child = next;
    }
    free(root);
}

// Main para probar los árboles de la imagen
int main() {
    // Árbol 1 (Devuelve Nivel 2)
    ntn *root1 = new_ntn(9);
    ntn *n1 = new_ntn(1);
    ntn *n3 = new_ntn(3);
    ntn *n4 = new_ntn(4);
    add_child(root1, n1);
    add_child(root1, n3);
    add_child(root1, n4);
    add_child(n3, new_ntn(6));
    add_child(n3, new_ntn(8));
    add_child(n3, new_ntn(2));
    add_child(n4, new_ntn(4));
    add_child(n4, new_ntn(2));

    // Árbol 2 (Devuelve Nivel 1)
    ntn *root2 = new_ntn(3);
    ntn *n6 = new_ntn(6);
    ntn *n4b = new_ntn(4);
    add_child(root2, new_ntn(6));
    add_child(root2, n6);
    add_child(root2, n4b);
    add_child(n6, new_ntn(8));
    add_child(n6, new_ntn(2));
    add_child(n6, new_ntn(4));
    add_child(n4b, new_ntn(2));

    // Probar ambos árboles
    test_tree(root1, "Árbol 1");
    test_tree(root2, "Árbol 2");

    // Liberar memoria
    free_tree(root1);
    free_tree(root2);

    return 0;
}