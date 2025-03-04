#include "lib/graph.h"
#include <stdlib.h>
#include <stdio.h>

/**
    Archivos a compilar:
    examenes/final-marzo-2023/ejercicio2.c
    examenes/final-marzo-2023/lib/graph.c
    examenes/final-marzo-2023/lib/list.c
    examenes/final-marzo-2023/lib/queue_dynamic.c
    examenes/final-marzo-2023/lib/stack_dynamic.c
*/

#define t_tlist_elem ntn*
#define t_elem_ntree int

//#define t_graph_elem t_elem_ntree

typedef struct _ntlist ntlist;

typedef struct _ntn
{
    t_elem_ntree value;
    ntlist *sons;
}ntn;

typedef struct _ntlist
{
    ntn* node;
    ntlist *next;
}ntlist;

typedef struct _list_tree
{
    t_tlist_elem node;
    struct _list_tree *next; 
}list_tree;

int cmp_int(int a, int b)
{
    return a - b; 
}

void check_and_add_node(graph* g, ntn* node)
{
    int index = graph_vertex_index(g,node->value, cmp_int);
    if(index < 0)
    {
        index = graph_add_vertex(g, node->value);
    }

    ntlist* sons = node->sons;
    int son_index = 0;
    while(sons != NULL)
    {
        son_index = graph_vertex_index(g, sons->node->value, cmp_int);
        if(son_index < 0)
        {
            son_index = graph_add_vertex(g, sons->node->value);
        }
        graph_add_edge(g, index, son_index, 1);
        sons = sons->next;
    }
}

void add_tree_to_graph(graph* g, ntn* root)
{
    if(g == NULL || root == NULL) return;

    ntlist* sons = root->sons;

    check_and_add_node(g, root);

    while(sons != NULL)
    {
        add_tree_to_graph(g, sons->node);
        sons = sons->next;
    }
}

graph* create_graph(list_tree* l)
{
    if (l == NULL) return NULL;
    graph* g = graph_new();

    while (l != NULL)
    {
        add_tree_to_graph(g, l->node);
        l = l->next;
    }

    return g;
}

/* Desde acá para abajo el codigo fue generado con chatgpt */

ntn* create_node(int value)
{
    ntn* node = (ntn*)malloc(sizeof(ntn));
    node->value = value;
    node->sons = NULL;
    return node;
}

void add_child(ntn* parent, ntn* child)
{
    ntlist* new_son = (ntlist*)malloc(sizeof(ntlist));
    new_son->node = child;
    new_son->next = parent->sons;
    parent->sons = new_son;
}

list_tree* add_tree_to_list(list_tree* list, ntn* root)
{
    list_tree* new_tree = (list_tree*)malloc(sizeof(list_tree));
    new_tree->node = root;
    new_tree->next = list;
    return new_tree;
}

int main()
{
    // ---- CONSTRUCCIÓN DEL ÁRBOL 1 ----
    ntn* n1_a = create_node(1);
    ntn* n2_a = create_node(2);
    ntn* n3_a = create_node(3);
    ntn* n4_a = create_node(4);
    ntn* n0_a = create_node(0);

    add_child(n1_a, n2_a);
    add_child(n1_a, n3_a);
    add_child(n3_a, n4_a);
    add_child(n3_a, n0_a);

    // ---- CONSTRUCCIÓN DEL ÁRBOL 2 ----
    ntn* n0_b = create_node(0);
    ntn* n2_b = create_node(2);
    ntn* n4_b = create_node(4);
    ntn* n1_b = create_node(1);

    add_child(n0_b, n2_b);
    add_child(n0_b, n4_b);
    add_child(n2_b, n1_b);

    // ---- CONSTRUCCIÓN DEL ÁRBOL 3 ----
    ntn* n2_c = create_node(2);
    ntn* n3_c = create_node(3);
    ntn* n4_c = create_node(4);
    ntn* n0_c = create_node(0);
    ntn* n1_c = create_node(1);

    add_child(n2_c, n3_c);
    add_child(n2_c, n4_c);
    add_child(n2_c, n0_c);
    add_child(n3_c, n1_c);

    // ---- CREACIÓN DE LA LISTA DE ÁRBOLES ----
    list_tree* list = NULL;
    list = add_tree_to_list(list, n1_a);   // Árbol 1 (raíz 1)
    list = add_tree_to_list(list, n0_b);   // Árbol 2 (raíz 0)
    list = add_tree_to_list(list, n2_c);   // Árbol 3 (raíz 2)

    // ---- CONSTRUCCIÓN DEL GRAFO ----
    graph* g = create_graph(list);

    // ---- IMPRESIÓN DE RESULTADOS ----
    printf("Cantidad de vértices en el grafo: %d\n", graph_vertex_count(g));

    // ---- LIBERACIÓN DE MEMORIA ----
    graph_destroy(g);

    return 0;
}