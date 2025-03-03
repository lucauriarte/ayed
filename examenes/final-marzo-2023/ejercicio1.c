#include <stdlib.h>
#include <stdio.h>
#define t_graph_elem int

typedef struct _edge{
    int to_vertex;
    struct _edge* next;
} edge;

typedef struct _graph{
    t_graph_elem* vertex;
    edge** adj_list;
    int vertex_count;
    int vertex_max_count;
} graph;

void count_paths(graph* g, int source, int target, int* paths)
{
    edge* aux = NULL;
    if(source == target)
    {
        (*paths)++;
        return;
    }

    aux = g->adj_list[source];
    while(aux != NULL)
    {
        count_paths(g, aux->to_vertex, target, paths);
        aux = aux->next;
    }
}

int graph_count_paths(graph* g, int source, int target)
{
    int paths = 0;
    count_paths(g, source, target, &paths);
    return paths;
}

/* Desde acá para abajo fue todo generado con chatgpt */

// Función que inicializa un grafo con un número máximo de vértices
graph* create_graph(int max_vertices)
{
    graph* g = (graph*)malloc(sizeof(graph));
    if (!g) return NULL;

    g->vertex = (t_graph_elem*)malloc(max_vertices * sizeof(t_graph_elem));
    g->adj_list = (edge**)malloc(max_vertices * sizeof(edge*));
    g->vertex_count = 0;
    g->vertex_max_count = max_vertices;

    if (!g->vertex || !g->adj_list) {
        free(g->vertex);
        free(g->adj_list);
        free(g);
        return NULL;
    }

    for (int i = 0; i < max_vertices; i++) {
        g->adj_list[i] = NULL;
    }

    return g;
}

// Agrega un vértice al grafo (devuelve el índice del vértice agregado)
int add_vertex(graph* g, t_graph_elem value)
{
    if (g->vertex_count >= g->vertex_max_count) return -1;

    int index = g->vertex_count;
    g->vertex[index] = value;
    g->vertex_count++;
    return index;
}

// Agrega una arista dirigida entre dos vértices
void add_edge(graph* g, int from, int to)
{
    if (from < 0 || from >= g->vertex_count || to < 0 || to >= g->vertex_count) return;

    edge* new_edge = (edge*)malloc(sizeof(edge));
    if (!new_edge) return;

    new_edge->to_vertex = to;
    new_edge->next = g->adj_list[from];
    g->adj_list[from] = new_edge;
}

// Libera la memoria del grafo
void free_graph(graph* g)
{
    if (!g) return;

    for (int i = 0; i < g->vertex_count; i++) {
        edge* current = g->adj_list[i];
        while (current) {
            edge* temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(g->adj_list);
    free(g->vertex);
    free(g);
}

int main()
{
    // Crear un grafo con capacidad para 6 vértices
    graph* g = create_graph(6);
    if (!g) {
        printf("Error al crear el grafo.\n");
        return 1;
    }

    // Agregar vértices (0, 1, 2, 3, 4, 5)
    for (int i = 0; i < 6; i++) {
        add_vertex(g, i);
    }

    // Agregar aristas según la imagen corregida
    add_edge(g, 0, 1);
    add_edge(g, 0, 4);
    add_edge(g, 1, 4);
    add_edge(g, 1, 2);
    add_edge(g, 1, 5);
    add_edge(g, 2, 3);
    add_edge(g, 2, 5);
    add_edge(g, 4, 5);
    add_edge(g, 5, 3);

    // Probar la función contando caminos entre diferentes pares de nodos
    printf("Caminos de 1 a 3: %d\n", graph_count_paths(g, 1, 3)); // Debe ser 4 (1→2→3, 1→5→3, 1→4→5→3, 1→2→5→3)

    // Liberar memoria
    free_graph(g);
    
    return 0;
}