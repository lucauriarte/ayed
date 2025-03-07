#include "lib/stack_dynamic.h"
#include <stdlib.h>
#include <stdio.h>

#define bool int
#define true 1
#define false 0

typedef struct _btn
{
    int value;
    struct _btn *left;
    struct _btn *right;
}btn;


bool encontrar_camino(btn* root, int objetivo, stack* camino) {
    if (root == NULL) return false;

    push(camino, root->value);

    if (root->value == objetivo) return true;

    if (encontrar_camino(root->left, objetivo, camino) || 
        encontrar_camino(root->right, objetivo, camino)) {
        return true;
    }

    pop(camino);
    return false;
}

int _max(int a, int b) { return (a > b) ? a : b; }

int btn_height(btn *node) {

    if(node == NULL)
    {
        return -1;
    }

    return _max(btn_height(node->right), btn_height(node->left)) + 1;
}


stack* binary_path(btn* root, int key)
{
    stack* path = stack_new(btn_height(root) + 1);
    if(encontrar_camino(root, key, path)){
        return path;
    }
    else {
        stack_free(path);
        return NULL;
    }
}

/* Desde acá para abajo el código fue generado con chatgpt */

// Función para crear un nuevo nodo del árbol binario
btn* btn_new(int value) {
    btn* node = (btn*)malloc(sizeof(btn));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Función para imprimir la pila (ruta encontrada)
void print_stack(stack* s) {
    stack* temp = stack_new(stack_getmaxsize(s));

    printf("Camino encontrado: ");
    while (!stack_isempty(s)) {
        int val = pop(s);
        printf("%d ", val);
        push(temp, val);
    }
    printf("\n");

    // Restaurar la pila original
    while (!stack_isempty(temp)) {
        push(s, pop(temp));
    }
    stack_free(temp);
}

int main() {
    // Crear árbol de prueba
    btn* root = btn_new(10);
    root->left = btn_new(5);
    root->right = btn_new(20);
    root->left->left = btn_new(3);
    root->left->right = btn_new(7);
    root->right->left = btn_new(15);
    root->right->right = btn_new(25);

    int key = 7;
    stack* path = binary_path(root, key);

    if (path != NULL) {
        print_stack(path);
        stack_free(path);
    } else {
        printf("El valor %d no se encuentra en el árbol.\n", key);
    }

    // Liberar memoria del árbol
    free(root->left->left);
    free(root->left->right);
    free(root->right->left);
    free(root->right->right);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}