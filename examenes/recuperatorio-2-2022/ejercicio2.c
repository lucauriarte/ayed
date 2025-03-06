#include <stdio.h>
#include "lib/graph.h"
#include "lib/vector.h"
#include "lib/queue_dynamic.h"

/**
    Archivos a compilar:
    examenes/recuperatorio-2-2022/ejercicio2.c
    examenes/recuperatorio-2-2022/lib/graph.c
    examenes/recuperatorio-2-2022/lib/list.c
    examenes/recuperatorio-2-2022/lib/queue_dynamic.c
    examenes/recuperatorio-2-2022/lib/stack_dynamic.c
    examenes/recuperatorio-2-2022/lib/vector.c
 */

void vertices_por_grado(graph* g, int origen, vector *a)
{
    int v_count = graph_vertex_count(g);
    vector* visited = vector_new(v_count);
    queue* q = queue_new(v_count);
    vector_set(visited, origen, 1);
    enqueue(q, origen);

    while(!queue_isempty(q)){
        int v = dequeue(q);

        int grado = graph_vertex_degree(g, v);
        vector_set(a, grado, vector_get(a, grado) + 1);

        list *adj_list = graph_vertex_adjacent_list(g, v);
        int neighbors = list_length(adj_list);
        for(int i=0; i<neighbors; i++){
            int n = list_get(adj_list, i);
            if(vector_get(visited, n) == 0){
                enqueue(q, n);
                vector_set(visited, n, 1);
            }
        }
    }
    queue_free(q);
    vector_free(visited);
}

int main() {
    graph* g = graph_new();

    int a = graph_add_vertex(g, 'a');
    int b = graph_add_vertex(g, 'b');
    int c = graph_add_vertex(g, 'c');
    int d = graph_add_vertex(g, 'd');
    int e = graph_add_vertex(g, 'e');
    int f = graph_add_vertex(g, 'f');

    graph_add_edge(g, a, b, 1);
    graph_add_edge(g, b, a, 1);
    graph_add_edge(g, b, c, 1);
    graph_add_edge(g, c, a, 1);
    graph_add_edge(g, c, e, 1);
    graph_add_edge(g, c, d, 1);
    graph_add_edge(g, d, b, 1);
    graph_add_edge(g, d, e, 1);
    graph_add_edge(g, e, a, 1);
    graph_add_edge(g, f, a, 1);
    graph_add_edge(g, f, e, 1);

    vector* degrees = vector_new(graph_vertex_count(g));

    vertices_por_grado(g, a, degrees);

    printf("Cantidad de nodos por grado:\n");
    for (int i = 0; i < graph_vertex_count(g); i++) {
        printf("Grado %d: %d nodos\n", i, vector_get(degrees, i));
    }

    vector_free(degrees);
    graph_destroy(g);

    return 0;
}