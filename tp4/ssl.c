#include <stdlib.h>
#include <stdio.h>
#define t_elem int

typedef struct _sll_node 
{
    t_elem data;
    struct _sll_node* next;
} sll_node;

void print_int(int value)
{
    printf("%i ", value);
}

int int_cmp(int a, int b)
{
    return (a-b);
}

sll_node* sll_new_node(t_elem element) 
{
    sll_node* new_node = (sll_node*)malloc(sizeof(sll_node));
    if (new_node != NULL) 
    {
        new_node->data = element;
        new_node->next = NULL;
    }
    return new_node;
}

int sll_add_node(sll_node** head, sll_node* new_node)
{
    if (new_node == NULL) return 0;
    while (*head != NULL) 
    {
        head = &(*head)->next;
    }
    *head = new_node;
    return 1;
}

t_elem sll_node_free(sll_node** a_node)
{
    sll_node* aux = *a_node;
    t_elem data = 0;
    if (aux != NULL)
    {
        data = (aux)->data;
        *a_node = aux->next;
        free(aux);
    }    
    return data;
}

sll_node** sll_node_find(sll_node** a_node, t_elem e, int cmp(t_elem, t_elem)) 
{
    while (*a_node != NULL && cmp((*a_node)->data, e) != 0) 
    {
        a_node = &(*a_node)->next;
    }
    return a_node;
}


sll_node* sll_remove_element(sll_node** a_list, t_elem e, int cmp(t_elem, t_elem))
{
    sll_node** a_node = sll_node_find(a_list, e, cmp);
    sll_node* aux = *a_node;
    if (aux != NULL)
    {
        *a_node = aux->next;
        aux->next = NULL;
    }
    return aux;
}

void sll_print(sll_node* a_node, void pnt(t_elem))
{
    while (a_node != NULL)
    {
        pnt(a_node->data);
        a_node = a_node->next;
    }
}

int sll_remove_all(sll_node** head, t_elem element, int cmp(t_elem, t_elem)) 
{
    int result = 0;
    while (sll_remove_element(head, element, cmp) != NULL) 
    {
        result += 1;
    }
    return result;
}

void sll_remove_duplicated_elements(sll_node** a_node, int cmp(t_elem, t_elem))
{
    while (*a_node != NULL)
    {
        sll_remove_all(&(*a_node)->next, (*a_node)->data, cmp);
        a_node = &(*a_node)->next;
    }
}

sll_node* sll_merge_sorted(sll_node* head1, sll_node* head2, int cmp(t_elem, t_elem))
{
    sll_node* result = NULL;

    if (head2 == NULL) 
    {
        result = head1;
    } 
    else if (head1 == NULL) 
    {
        result = head2;
    } 
    else 
    {
        if (cmp(head1->data, head2->data) < 0) 
        {            
            result = head1;
            result->next = sll_merge_sorted(head1->next, head2, cmp);
        } 
        else
        {
            result = head2;
            result->next = sll_merge_sorted(head1, head2->next, cmp);
        }
    }
    return result;
}

int is_sorted(sll_node** node,  int cmp(t_elem, t_elem))
{
    int sorted = 1;
    while((*node)->next != NULL)
    {
        if(cmp((*node)->data, (*node)->next->data) > 0)
        {
            sorted = 0;
        }
        node = &(*node)->next;
    }
    return sorted;
}

sll_node* sll_add_node_front(sll_node** a_list, sll_node* new_node)
{
    if (new_node != NULL)
    {
        new_node->next = *a_list;
        *a_list = new_node;
    }
    return new_node;
}

sll_node* sll_new_inverted(sll_node* node)
{
    sll_node* inverted = NULL;
    if(node != NULL)
    {
        while (node != NULL)
        {
            sll_add_node_front(&inverted, sll_new_node(node->data));
            node = node->next;
        }
    }
    return inverted;
}

void sll_invert(sll_node** p_head)
{
    sll_node* prev = NULL;
    sll_node* curr = *p_head;
    sll_node* next = NULL;
    while(curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *p_head = prev;
}

int sll_get_min(sll_node* n)
{
    int min = 0;
    int a = 0;
    int b = 0;

    if(n->next == NULL)
    {
        min = n->data;
    }
    else
    {
        a = n->data;
        b = sll_get_min(n->next);
        min = a < b ? a : b;
    }
    return min;
}

int main()
{
    sll_node* head = NULL;
    sll_node* head2 = NULL;
    
    sll_add_node(&head, sll_new_node(1));
    sll_add_node(&head, sll_new_node(3));
    sll_add_node(&head, sll_new_node(1));
    sll_add_node(&head, sll_new_node(8));
    sll_add_node(&head, sll_new_node(8));

    sll_add_node(&head2, sll_new_node(2));
    sll_add_node(&head2, sll_new_node(5));
    sll_add_node(&head2, sll_new_node(7));


    //Eliminar todos los elementos repetidos de una lista dinámica simplemente enlazada (SSL).
    printf("Lista antes de eliminar los elementos repetidos:\n");
    sll_print(head, print_int);
    printf("\n");
    sll_remove_duplicated_elements(&head, int_cmp);
    printf("Lista despues de eliminar los elementos repetidos:\n");
    sll_print(head, print_int);
    printf("\n");

    printf("Lista 1:\n");
    sll_print(head, print_int);
    printf("\n");
    printf("Lista 2:\n");
    sll_print(head2, print_int);
    printf("\n");
    printf("Listas fusionadas:\n");
    sll_merge_sorted(head, head2, int_cmp);
    sll_print(head, print_int);
    printf("\n");

    if(is_sorted(&head, int_cmp))
    {
        printf("La lista 1 esta ordenada\n");
    }
    else
    {
        printf("La lista 1 esta desordenada\n");
    }

    printf("Copia de la lista 1 invertida:\n");
    sll_print(sll_new_inverted(head), print_int);
    printf("\n");

    sll_invert(&head);
    printf("Lista 1 invertida:\n");
    sll_print(head, print_int);
    printf("\n");

    printf("Minimo de la lista 1: %i\n", sll_get_min(head));
}