#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
    Archivos a compilar:
    examenes/parcial-2-2024/ejercicio3.c
*/

#define t_elem_ntree int

typedef struct _ntn ntn;

typedef struct _ntlist {
    ntn *value;
    struct _ntlist* next;
} ntlist;

typedef struct _ntn {
    t_elem_ntree data;
    ntlist *child;
} ntn;


ntn* ntn_new(t_elem_ntree data)
{
    ntn* new_node = (ntn*)malloc(sizeof(ntn));
    new_node->data = data;
    new_node->child = NULL;
    return new_node;
}

ntlist* ntl_new(ntn* node)
{
    ntlist* new_list = (ntlist*)malloc(sizeof(ntlist));
    new_list->value = node;
    new_list->next = NULL;
    return new_list;
}

void ntn_add_child(ntn* parent, ntn* child)
{
    ntlist* l = ntl_new(child);
    if(l != NULL)
    {
        l->next = parent->child;
        parent->child = l;
    }
}

ntn* ntn_create_mirror(ntn* root)
{
    ntn* r = NULL;
    if(root != NULL)
    {
        r = ntn_new(root->data);
        ntlist* l = root->child;
        while(l != NULL)
        {
            ntn_add_child(r, ntn_create_mirror(l->value));
            l = l->next;
        }
    }
    return r;
}

void ntn_print(ntn* root, int level) {
    if (root == NULL) return;
    
    for (int i = 0; i < level; i++) printf("   |");
    printf("--%d\n", root->data);
    
    ntlist* l = root->child;
    while (l != NULL) {
        ntn_print(l->value, level + 1);
        l = l->next;
    }
}

int main() {
    // Crear árbol de prueba
    ntn* root = ntn_new(1);
    ntn* child1 = ntn_new(2);
    ntn* child2 = ntn_new(3);
    ntn* child3 = ntn_new(4);
    
    ntn_add_child(root, child1);
    ntn_add_child(root, child2);
    ntn_add_child(root, child3);
    
    ntn_add_child(child1, ntn_new(5));
    ntn_add_child(child1, ntn_new(6));
    ntn_add_child(child2, ntn_new(7));
    ntn_add_child(child3, ntn_new(8));
    ntn_add_child(child3, ntn_new(9));
    
    printf("Arbol original:\n");
    ntn_print(root, 0);
    
    // Crear árbol espejo
    ntn* mirrored = ntn_create_mirror(root);
    
    printf("\nArbol espejado:\n");
    ntn_print(mirrored, 0);
    
    return 0;
}