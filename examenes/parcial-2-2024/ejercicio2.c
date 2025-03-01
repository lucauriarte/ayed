#include "lib/vector.h"
#include <stdio.h>
#include <stdlib.h>

/**
    examenes/parcial-2-2024/ejercicio2.c
    examenes/parcial-2-2024/lib/vector.c

    Definir en vector.h
    typedef struct
    {
        int dni;
        char nombre[50];
        char apellido[50];
    }persona;

    #define VECTOR_ELEMENT persona*
)
 */

#define t_elem_btree persona*

typedef struct _btn {
    t_elem_btree value;
    struct _btn *left;
    struct _btn *right;
} btn;

btn* btn_new(t_elem_btree value)
{
    btn* node = NULL;

    node = (btn*)malloc(sizeof(btn));
    node->value = value;
    node->right = NULL;
    node->left = NULL;

    return node;
}

btn* _sbt_create_helper(vector* v, int start, int end) {
    if (start > end) return NULL;

    int mid = (start + end) / 2;
    btn* node = btn_new(vector_get(v, mid));
    node->left = _sbt_create_helper(v, start, mid - 1);
    node->right = _sbt_create_helper(v, mid + 1, end);

    return node;
}

btn* sbt_create_from_vector(vector* v) {
    return _sbt_create_helper(v, 0, vector_size(v) - 1);
}

// Función para imprimir el árbol en orden
void print_inorder(btn* root) {
    if (root == NULL) return;
    print_inorder(root->left);
    printf("DNI: %d, Nombre: %s, Apellido: %s\n", root->value->dni, root->value->nombre, root->value->apellido);
    print_inorder(root->right);
}

// Función para liberar la memoria del árbol
void free_tree(btn* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    // Crear vector ordenado por apellido
    vector* v = vector_new(7);

    persona personas[] = {
        {12345678, "Ana", "Alvarez"},
        {23456789, "Bruno", "Bianchi"},
        {34567890, "Carlos", "Cortez"},
        {45678901, "Diana", "Dominguez"},
        {56789012, "Elena", "Estrada"},
        {67890123, "Federico", "Fernandez"},
        {78901234, "Gustavo", "Gimenez"}
    };

    // Insertar personas en el vector
    for (int i = 0; i < 7; i++) {
        vector_add(v, &personas[i]);
    }

    // Construir el árbol balanceado
    btn* root = sbt_create_from_vector(v);

    // Imprimir árbol en orden
    printf("Árbol en orden:\n");
    print_inorder(root);
    
    // Liberar memoria
    free_tree(root);
    vector_free(v);

    return 0;
}