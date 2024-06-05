#include "btree_base.c"
#include <stdio.h>
#include "../tda/vector/vector.h"

void print_int(int value)
{
    printf("%i ", value);
}

/*
 * toStr devuelve el contenido de un nodo como string
 * asume que t_elem_tree es un número entero
 */
void btn_intToStr(btn* node, char* str) {
    if (!node) return;    
    sprintf(str, "(%03d)", node->value);    
}

// compara 2 elementos del árbol cuando son enteros
int btn_cmp_int(t_elem_btree a, t_elem_btree b) {
    return a - b;
}

void btn_sum_value(btn* node, void* ctx)
{
    int* sum = (int*)ctx;
    *sum += node->value;
}

void btn_equals_sum_of_childs(btn* node, void* ctx)
{
    int sum = 0;
    int* equals = (int*)ctx;
    if(!btn_isLeaf(node))
    {
        btn_inorder(node, btn_sum_value, &sum);
        if((sum - node->value) != node->value)
        {
            *equals = 0;
        }
    }
}

btn** btn_find_parent(btn** root, btn* node)
{
    if (root == NULL || *root == NULL || *root == node)
    {
        return NULL;
    }

    if ((*root)->left == node || (*root)->right == node)
    {
        return root;
    }

    btn** found_parent = btn_find_parent(&(*root)->left, node);
    if (found_parent == NULL)
    {
        found_parent = btn_find_parent(&(*root)->right, node);
    }
    return found_parent;
}


btn* btn_get_and_ascend(btn** root, t_elem_btree value, int cmp(t_elem_btree, t_elem_btree)) 
{
    btn** found_node = root;
    btn** parent = root;
    t_elem_btree temp = 0;

    found_node = btn_find(root, value, cmp);
    if (found_node != NULL)
    {        
        parent = btn_find_parent(root, *found_node);

        if(found_node != NULL && parent != NULL)
        {
            temp = (*found_node)->value;
            (*found_node)->value = (*parent)->value;
            (*parent)->value = temp;
        }
    }

    return *parent;
}

btn* btn_get_mirror(btn* root)
{
    btn* mirror = NULL;
    if (root == NULL)
    {
        return NULL;
    }

    mirror = btn_new(root->value);
    mirror->left = btn_get_mirror(root->right);
    mirror->right = btn_get_mirror(root->left);

    return mirror;
}

void btn_fill_vector(btn* node, void* ctx)
{
    vector* v = (vector*)ctx;
    vector_add(v, node->value);
}

vector* btn_fill_vector_inorder(btn* root)
{
    vector * v = vector_new(10);
    btn_inorder(root, btn_fill_vector, v);
    return v;
}

vector* btn_fill_vector_preorder(btn* root)
{
    vector * v = vector_new(10);
    btn_preorder(root, btn_fill_vector, v);
    return v;
}

vector* btn_fill_vector_postorder(btn* root)
{
    vector * v = vector_new(10);
    btn_postorder(root, btn_fill_vector, v);
    return v;
}

int main()
{
    btn* root = NULL;
    btn* root2 = NULL;
    btn_insert_value(&root, 20);
    btn_insert_value(&root, 10);
    btn_insert_value(&root, 30);
    btn_insert_value(&root, 15);
    btn_insert_value(&root, 25);
    btn_insert_value(&root, 35);
    btn_insert_value(&root, 22);
    
    btn_insert_value(&root2, 3);
    btn_insert_value(&root2, 1);
    btn_insert_value(&root2, 2);

    printf("\n%10s: \n", "Árbol 1");
    btn_print(root, btn_intToStr);
    printf("\n%10s: \n", "Árbol 2");
    btn_print(root2, btn_intToStr);

    //Dado un árbol binario con valores enteros, devolver la suma de todos los nodos.
    int sum = 0;
    btn_inorder(root, btn_sum_value, &sum);
    printf("\nSuma de todos los nodos del arbol 1: %i\n", sum);
    //Dado un árbol binario con valores enteros, devuelve 1 si todos los nodos tiene un valor igual a la suma de los hijos (exceptuando los nodos hoja), 0 en otro caso.
    int equals = 1;
    btn_inorder(root, btn_equals_sum_of_childs, &equals);
    equals ? printf("\nEl arbol cumple la condicion\n") : printf("\nEl arbol no cumple la condicion\n");
    
    equals = 1;
    btn_inorder(root2, btn_equals_sum_of_childs, &equals);
    equals ? printf("\nEl arbol 2 cumple la condicion\n") : printf("\nEl arbol 2 no cumple la condicion\n");

    /* Armar una función que dado un Árbol binario y un valor devuelva el nodo (si está) y además cada vez que un nodo es solicitado intercambia 
     * el lugar con su padre (a menos que sea la raíz). El objetivo de esta técnica es que los nodos que se llaman con más frecuencia se encuentren 
     * cada vez más accesibles.
     */

    btn* ascended = NULL;
    ascended = btn_get_and_ascend(&root, 12, btn_cmp_int);
    printf("\nValer del nodo ascendido: %i", ascended->value);
    printf("\n%10s: \n", "Árbol 1 Luego de ascender el nodo");
    btn_print(root, btn_intToStr);

    //Armar una función que dado un árbol binario, cree otro exactamente igual pero en espejo. 
    printf("\n%10s: \n", "Árbol 3 (Espejo del arbol 1)");
    btn_print(btn_get_mirror(root), btn_intToStr);

    //Armar 3 funciones que devuelvan el contenido de un árbol en un vector: en inorder, preorder y post order.
    vector* v = btn_fill_vector_inorder(root);
    printf("\nVector con los valores del arbol 1 en inorder:\n");
    vector_print(v, print_int);
    printf("\n");

    vector* v2 = btn_fill_vector_preorder(root);
    printf("\nVector con los valores del arbol 1 en preorder:\n");
    vector_print(v2, print_int);
    printf("\n");

    vector* v3 = btn_fill_vector_postorder(root);
    printf("\nVector con los valores del arbol 1 en postorder:\n");
    vector_print(v3, print_int);
    printf("\n");
}