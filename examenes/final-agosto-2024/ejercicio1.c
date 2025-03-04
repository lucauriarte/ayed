#include <stdlib.h>
#include <stdio.h>

/**
    Archivos a compilar:
    examenes/final-agosto-2024/ejercicio1.c
 */

#define bool int
#define true 1
#define false 0

typedef struct _btn
{
    bool is_operator;
    union
    {
        float num;
        char op;
    }value;
    struct _btn *right;
    struct _btn* left;
}btn;

float operate(float a, float b, char op)
{
    float res = 0;
    switch (op)
    {
        case '+':
        res = a + b;
        break;
        case '-':
        res = a - b;
        break;
        case '*':
        res = a * b;
        break;
        case '/':
        if(b != 0)
        {
            res = a / b;
        }
        break;
    }
    return res;
}

float calc(btn* root)
{
    if(root == NULL) return 0;

    if(root->is_operator == false) return root->value.num;

    return operate(calc(root->left), calc(root->right),root->value.op);
}

/* De acá para abajo el codigo fue generado con chatgpt */

// Función para crear un nodo operador
btn* create_operator_node(char op, btn* left, btn* right)
{
    btn* node = (btn*)malloc(sizeof(btn));
    node->is_operator = true;
    node->value.op = op;
    node->left = left;
    node->right = right;
    return node;
}

// Función para crear un nodo número
btn* create_number_node(float num)
{
    btn* node = (btn*)malloc(sizeof(btn));
    node->is_operator = false;
    node->value.num = num;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Función para liberar la memoria del árbol
void free_tree(btn* root)
{
    if (root)
    {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main()
{
    // Construcción del árbol según la imagen
    btn* n1 = create_number_node(-2);
    btn* n2 = create_number_node(4.5);
    btn* n3 = create_number_node(5.5);
    btn* n4 = create_operator_node('+', n2, n3);
    btn* n5 = create_operator_node('*', n1, n4);

    btn* n6 = create_number_node(-15);
    btn* n7 = create_number_node(-8);
    btn* n8 = create_number_node(5);
    btn* n9 = create_operator_node('+', n7, n8);
    btn* n10 = create_operator_node('/', n6, n9);

    btn* root = create_operator_node('-', n5, n10);

    // Evaluar la expresión
    float result = calc(root);
    printf("Resultado de la expresión: %.2f\n", result);  // Debe imprimir -25.00

    // Liberar memoria
    free_tree(root);

    return 0;
}