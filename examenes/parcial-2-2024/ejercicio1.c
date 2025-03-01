#include "lib/graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
    Archivos fuente a compilar:
    examenes/parcial-2-2024/ejercicio1.c
    examenes/parcial-2-2024/lib/graph.c
    examenes/parcial-2-2024/lib/list.c
    examenes/parcial-2-2024/lib/queue_dynamic.c
    examenes/parcial-2-2024/lib/stack_dynamic.c

    Definir en librerias:
    #define t_graph_elem char*
    #define t_list_elem int
**/

typedef struct _fs_list{
    t_graph_elem contact;
    struct _fs_list *next;
}fs_list;

int _strcmp (t_graph_elem a, t_graph_elem b){
    return strcmp( (char*)a, (char*)b);
}

fs_list* fs_new_node(t_graph_elem contact) 
{
    fs_list* new_node = (fs_list*)malloc(sizeof(fs_list));
    if (new_node != NULL) 
    {
        new_node->contact = contact;
        new_node->next = NULL;
    }
    return new_node;
}

int fs_add_node(fs_list** head, fs_list* new_node)
{
    if (new_node == NULL) return 0;
    while (*head != NULL) 
    {
        head = &(*head)->next;
    }
    *head = new_node;
    return 1;
}

fs_list* friendship_suggestion (graph* social_networking, t_graph_elem contact, int Na, int Naa)
{
    int index = 0, f_qty = 0, fof_qty = 0, f_id = 0, fof_id = 0;
    fs_list *suggested = NULL;
    list *f_list = NULL, *fof_list = NULL;
    index = graph_vertex_index(social_networking, (void*)contact, _strcmp);
    f_list = graph_vertex_adjacent_list(social_networking, index);
    f_qty = list_length(f_list);
    for(int i=0; i<f_qty; i++)
    {
        f_id = list_get(f_list, i);
        if(graph_get_edge_weight(social_networking, index, f_id) >= Na)
        {
            fof_list = graph_vertex_adjacent_list(social_networking, f_id);
            fof_qty = list_length(fof_list);
            for(int j=0; j<fof_qty; j++)
            {
                fof_id = list_get(fof_list, j);
                if(graph_get_edge_weight(social_networking, f_id, fof_id) >= Naa && graph_get_edge_weight(social_networking, fof_id, index) == 0)
                {
                    fs_add_node(&suggested, fs_new_node(graph_vertex_get(social_networking, fof_id)));
                }
            }
        }
    }
    return suggested;
}

// Función auxiliar para imprimir la lista enlazada
void print_suggestions(fs_list* head) {
    printf("Sugerencias de amistad:\n");
    while (head) {
        printf("- %s\n", head->contact);
        head = head->next;
    }
}

int main() {
    // Crear el grafo
    graph* social_networking = graph_new();

    // Agregar nodos (perfiles de la red social)
    t_graph_elem nodes[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    int num_nodes = sizeof(nodes) / sizeof(nodes[0]);

    for (int i = 0; i < num_nodes; i++) {
        graph_add_vertex(social_networking, nodes[i]);
    }

    // Agregar aristas bidireccionales (grafo no dirigido)
    graph_add_edge_byname(social_networking, "A", "B", 10, _strcmp);
    graph_add_edge_byname(social_networking, "B", "A", 10, _strcmp);

    graph_add_edge_byname(social_networking, "A", "C", 3, _strcmp);
    graph_add_edge_byname(social_networking, "C", "A", 3, _strcmp);

    graph_add_edge_byname(social_networking, "A", "F", 5, _strcmp);
    graph_add_edge_byname(social_networking, "F", "A", 5, _strcmp);

    graph_add_edge_byname(social_networking, "B", "D", 5, _strcmp);
    graph_add_edge_byname(social_networking, "D", "B", 5, _strcmp);

    graph_add_edge_byname(social_networking, "B", "E", 17, _strcmp);
    graph_add_edge_byname(social_networking, "E", "B", 17, _strcmp);

    graph_add_edge_byname(social_networking, "B", "G", 15, _strcmp);
    graph_add_edge_byname(social_networking, "G", "B", 15, _strcmp);

    graph_add_edge_byname(social_networking, "D", "H", 3, _strcmp);
    graph_add_edge_byname(social_networking, "H", "D", 3, _strcmp);

    graph_add_edge_byname(social_networking, "D", "I", 5, _strcmp);
    graph_add_edge_byname(social_networking, "I", "D", 5, _strcmp);

    graph_add_edge_byname(social_networking, "E", "F", 10, _strcmp);
    graph_add_edge_byname(social_networking, "F", "E", 10, _strcmp);

    graph_add_edge_byname(social_networking, "F", "I", 5, _strcmp);
    graph_add_edge_byname(social_networking, "I", "F", 5, _strcmp);

    graph_add_edge_byname(social_networking, "I", "J", 12, _strcmp);
    graph_add_edge_byname(social_networking, "J", "I", 12, _strcmp);

    graph_add_edge_byname(social_networking, "G", "D", 5, _strcmp);
    graph_add_edge_byname(social_networking, "D", "G", 5, _strcmp);

    // Parámetros de la sugerencia
    int Na = 5;   // Interacciones mínimas con el amigo
    int Naa = 10;  // Interacciones mínimas con el amigo en común

    // Ejecutar la función y obtener las sugerencias
    fs_list* suggestions = friendship_suggestion(social_networking, "D", Na, Naa);

    // Imprimir las sugerencias de amistad
    print_suggestions(suggestions);

    // Liberar memoria
    graph_destroy(social_networking);
    return 0;
}