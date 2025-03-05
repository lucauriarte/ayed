#include <stdio.h>
#include "lib/graph.h"
#include "lib/queue_dynamic.h"
#include "lib/vector.h"
#include "lib/list.h"

/**
    Archivos a compilar:
    examenes/final-agosto-2024/ejercicio2.c
    examenes/final-agosto-2024/lib/graph.c
    examenes/final-agosto-2024/lib/list.c
    examenes/final-agosto-2024/lib/queue_dynamic.c
    examenes/final-agosto-2024/lib/stack_dynamic.c
    examenes/final-agosto-2024/lib/vector.c

    Definir tipos de datos de TDAs:
    #define t_graph_elem char
    #define t_queue_elem t_friendship
 */

typedef struct _t_friendship
{
    char f1;
    char f2;
    int weight;
}t_friendship;

void vector_insert_sorted(vector* v, t_friendship f) {
    int size = vector_size(v);
    int i = 0;

    if(size == 0) vector_add(v, f);
    
    while (i < size && (vector_get(v, i)).weight > f.weight) {
        i++;
    }
    
    vector_insert(v, i, f);
}

void process_friendship(vector* top_friends, t_friendship f, int N) {
    if (vector_size(top_friends) < N) {
        vector_insert_sorted(top_friends, f);
    } else if (f.weight > vector_get(top_friends, N - 1).weight) {
        vector_remove(top_friends, N - 1);
        vector_insert_sorted(top_friends, f);
    }
}

void get_top_friendships(graph* social_networking, vector* top_friends, int N) {
    int users = graph_vertex_count(social_networking);

    for (int i = 0; i < users; i++) {
        char f1 = graph_vertex_get(social_networking, i);
        list* adj_list = graph_vertex_adjacent_list(social_networking, i);
        int fof1 = list_length(adj_list);

        for (int j = 0; j < fof1; j++) {
            int index_f2 = list_get(adj_list, j);
            char f2 = graph_vertex_get(social_networking, index_f2);

            if (f1 < f2) {
                int weight = graph_get_edge_weight(social_networking, i, index_f2);
                t_friendship f = {f1, f2, weight};
                process_friendship(top_friends, f, N);
            }
        }
    }
}

queue* friendship_top(graph* social_networking, int N) {
    queue* top_interactions = queue_new(N);
    vector* top_friends = vector_new(N);

    get_top_friendships(social_networking, top_friends, N);

    for (int i = 0; i < vector_size(top_friends); i++) {
        enqueue(top_interactions, vector_get(top_friends, i));
    }

    vector_free(top_friends);
    return top_interactions;
}

int main() {
    graph* social_networking = graph_new();
    
    int a = graph_add_vertex(social_networking, 'A');
    int b = graph_add_vertex(social_networking, 'B');
    int c = graph_add_vertex(social_networking, 'C');
    int d = graph_add_vertex(social_networking, 'D');
    int e = graph_add_vertex(social_networking, 'E');
    int f = graph_add_vertex(social_networking, 'F');
    int g = graph_add_vertex(social_networking, 'G');
    int h = graph_add_vertex(social_networking, 'H');
    int i = graph_add_vertex(social_networking, 'I');
    int j = graph_add_vertex(social_networking, 'J');
    
    graph_add_edge(social_networking, a, b, 10);
    graph_add_edge(social_networking, b, a, 10);
    graph_add_edge(social_networking, a, c, 3);
    graph_add_edge(social_networking, c, a, 3);
    graph_add_edge(social_networking, a, f, 5);
    graph_add_edge(social_networking, f, a, 5);
    graph_add_edge(social_networking, b, e, 17);
    graph_add_edge(social_networking, e, b, 17);
    graph_add_edge(social_networking, b, g, 15);
    graph_add_edge(social_networking, g, b, 15);
    graph_add_edge(social_networking, b, d, 5);
    graph_add_edge(social_networking, d, b, 5);
    graph_add_edge(social_networking, d, h, 3);
    graph_add_edge(social_networking, h, d, 3);
    graph_add_edge(social_networking, d, i, 5);
    graph_add_edge(social_networking, i, d, 5);
    graph_add_edge(social_networking, f, e, 10);
    graph_add_edge(social_networking, e, f, 10);
    graph_add_edge(social_networking, f, i, 5);
    graph_add_edge(social_networking, i, f, 5);
    graph_add_edge(social_networking, i, j, 12);
    graph_add_edge(social_networking, j, i, 12);
    
    queue* top_friends = friendship_top(social_networking, 5);
    
    printf("Top amistades:\n");
    while (!queue_isempty(top_friends)) {
        t_friendship f = dequeue(top_friends);
        printf("%c - %c: %d\n", f.f1, f.f2, f.weight);
    }
    
    queue_free(top_friends);
    graph_destroy(social_networking);
    
    return 0;
}