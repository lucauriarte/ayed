#include "lib/vector.h"
#include <stdlib.h>
#include <stdio.h>

#define t_elem int
#define t_vector_elem void*

typedef struct _ntn
{
    t_elem data;
    vector* sons;
}ntn;

typedef struct _edge
{
    int to_vertex;
    struct _edge *next;
}edge;

typedef struct
{
    t_elem* vertex;
    vector* adj_list;
    int vertex_count;
    int max_vertex;
}digraph;


int get_vertex_index(digraph* g, t_elem v1, int cmp(t_elem, t_elem))
{
    int i = 0;
    while (i < g->vertex_count && cmp(g->vertex[i], v1) != 0)
        i++;
    return (i == g->vertex_count) ? -1 : i;
}

int is_edge(digraph *g, t_elem v1, t_elem v2, int cmp(t_elem, t_elem))
{
    edge* e = vector_get(g->adj_list,get_vertex_index(g, v1, cmp));
    int i2 = get_vertex_index(g, v2, cmp);
    while (e != NULL && e->to_vertex != i2)
        e = e->next;
    return (e != NULL) ? 1 : 0;
}

void recorrer_ntn(ntn *t, digraph *g, int cmp(t_elem, t_elem), int* inc)
{
    if (t == NULL || *inc == 0) return;

    int parent_idx = get_vertex_index(g, t->data, cmp);
    if (parent_idx == -1) {
        *inc = 0;
        return;
    }

    vector* sons = t->sons;
    int sons_qty = vector_size(sons);
    for (int i=0; i<sons_qty; i++)
    {
        ntn* s = (ntn*)vector_get(sons, i);
        //Comprobar existencia de la arista padre->hijo
        int child_idx = get_vertex_index(g, s->data, cmp);
        if (child_idx == -1 || !is_edge(g, t->data, s->data, cmp)) {
            *inc = 0;
            return;
        }
        recorrer_ntn(s, g, cmp, inc);
    }

}

int is_included(ntn *t, digraph *g, int cmp(t_elem, t_elem))
{
    int included = 1;
    recorrer_ntn(t, g, cmp, &included);
    return included;
}

/* Desde acá para abajo el codigo fue generado con chatgpt */

/** Función de comparación de elementos */
int cmp(t_elem a, t_elem b) {
    return a - b;
}

/** Función auxiliar para crear un nodo del árbol */
ntn* crear_ntn(t_elem data) {
    ntn* nodo = malloc(sizeof(ntn));
    nodo->data = data;
    nodo->sons = vector_new(1);
    return nodo;
}

/** Agregar un hijo a un nodo del árbol */
void agregar_hijo(ntn* padre, ntn* hijo) {
    vector_add(padre->sons, hijo);
}

/** Función auxiliar para crear un grafo */
digraph* crear_grafo(int max_vertices) {
    digraph* g = malloc(sizeof(digraph));
    g->vertex = malloc(max_vertices * sizeof(t_elem));
    g->adj_list = vector_new(1);
    g->vertex_count = 0;
    g->max_vertex = max_vertices;
    return g;
}

/** Agregar un nodo al grafo */
void agregar_nodo(digraph* g, t_elem data) {
    if (g->vertex_count < g->max_vertex) {
        g->vertex[g->vertex_count] = data;
        vector_add(g->adj_list, NULL);  // Inicializa su lista de adyacencia en NULL
        g->vertex_count++;
    }
}

/** Agregar una arista al grafo */
void agregar_arista(digraph* g, t_elem from, t_elem to) {
    int from_idx = get_vertex_index(g, from, cmp);
    int to_idx = get_vertex_index(g, to, cmp);
    
    if (from_idx == -1 || to_idx == -1) return;  // Si los nodos no existen, salir

    edge* new_edge = malloc(sizeof(edge));
    new_edge->to_vertex = to_idx;
    new_edge->next = vector_get(g->adj_list, from_idx);
    vector_set(g->adj_list, from_idx, new_edge);
}

/** Función para liberar el grafo */
void destruir_grafo(digraph* g) {
    for (int i = 0; i < g->vertex_count; i++) {
        edge* e = vector_get(g->adj_list, i);
        while (e != NULL) {
            edge* temp = e;
            e = e->next;
            free(temp);
        }
    }
    free(g->vertex);
    vector_free(g->adj_list);
    free(g);
}

/** Función para liberar el árbol */
void destruir_arbol(ntn* nodo) {
    if (nodo == NULL) return;
    int hijos = vector_size(nodo->sons);
    for (int i = 0; i < hijos; i++) {
        destruir_arbol(vector_get(nodo->sons, i));
    }
    vector_free(nodo->sons);
    free(nodo);
}

/** MAIN DE PRUEBA */
int main() {
    // Crear el árbol n-ario
    ntn* raiz = crear_ntn(1);
    ntn* nodo2 = crear_ntn(2);
    ntn* nodo3 = crear_ntn(3);
    ntn* nodo4 = crear_ntn(4);

    agregar_hijo(raiz, nodo2);
    agregar_hijo(raiz, nodo3);
    agregar_hijo(nodo2, nodo4);

    // Crear el grafo dirigido
    digraph* g = crear_grafo(6);
    agregar_nodo(g, 1);
    agregar_nodo(g, 2);
    agregar_nodo(g, 3);
    agregar_nodo(g, 4);
    agregar_nodo(g, 5);

    agregar_arista(g, 1, 2);
    agregar_arista(g, 1, 3);
    agregar_arista(g, 1, 5);
    agregar_arista(g, 2, 4);

    // Prueba de la función is_included
    int resultado = is_included(raiz, g, cmp);
    printf("¿El árbol está incluido en el grafo? %d\n", resultado);

    // Liberar memoria
    destruir_arbol(raiz);
    destruir_grafo(g);

    return 0;
}