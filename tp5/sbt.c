#include "btree_base.c"
#include <stdio.h>
#include <limits.h>

#define t_elem int

// Estructura de contexto para determinar si un arbol es u SBT
typedef struct
{
    t_elem_btree prev_value;
    int is_sbt;
} context_t;

typedef struct _sll_node 
{
    t_elem data;
    struct _sll_node* next;
} sll_node;

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

void sll_print(sll_node* a_node, void pnt(t_elem))
{
    while (a_node != NULL)
    {
        pnt(a_node->data);
        a_node = a_node->next;
    }
}

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

btn** find (btn** node, t_elem_btree data, int cmp(t_elem_btree, t_elem_btree)) {
    while ((*node != NULL) && (cmp((*node)->value, data) != 0)) {
        if (cmp(data, (*node)->value) < 0)
            node = &(*node)->left;
        else
            node = &(*node)->right;        
    }
    return node;
}

int sbtn_insert(btn **root, btn *new_node, int cmp(t_elem_btree, t_elem_btree))
{
    int res = 0;
    if (new_node != NULL) {
        btn** found = find(root, new_node->value, cmp);
        if (*found == NULL) {
            *found = new_node;
            res = 1;
        }
    }
    return res;
}

int sbtn_insert_value(btn **node, int value)
{
    btn* new_node = NULL;
    int status = 0;

    new_node = btn_new(value);
    status = sbtn_insert(node, new_node, btn_cmp_int);

    return status;
}

btn** sbt_min(btn**root)
{
    btn** min = root;
    while(*root != NULL)
    {
        min = root;
        root = &(*root)->left;
    }
    return min;
}

btn** sbt_max(btn**root)
{
    btn** max = root;
    while(*root != NULL)
    {
        max = root;
        root = &(*root)->right;
    }
    return max;
}

btn* find_node(btn** root, int value, int cmp(t_elem_btree, t_elem_btree))
{
    btn* found = NULL;
    if(*root != NULL)
    {
        if(cmp((*root)->value, value) == 0)
        {
            found = *root;
        }
        else if(cmp((*root)->value, value) > 0)
        {
            found = find_node(&(*root)->left, value, cmp);
        }
        else if(cmp((*root)->value, value) < 0)
        {
            found = find_node(&(*root)->right, value, cmp);
        }
    }
    return found;
}

btn* find_node_it(btn** root, int value, int cmp(t_elem_btree, t_elem_btree))
{
    btn* found = *root;

    while((found != NULL) && (cmp(found->value, value) != 0))
    {
        if(cmp(found->value, value) > 0)
        {
            found = found->left;
        }
        else if(cmp(found->value, value) < 0)
        {
            found = found->right;
        }
    }
    return found;
}

btn** find_node_2(btn** root, int value, int cmp(t_elem_btree, t_elem_btree))
{
    btn** found = root;
    if(*root != NULL)
    {
        if(cmp((*root)->value, value) == 0)
        {
            found = root;
        }
        else if(cmp((*root)->value, value) > 0)
        {
            found = find_node_2(&(*root)->left, value, cmp);
        }
        else if(cmp((*root)->value, value) < 0)
        {
            found = find_node_2(&(*root)->right, value, cmp);
        }
    }
    return found;
}

btn** find_node_2_it(btn** root, int value, int cmp(t_elem_btree, t_elem_btree))
{
    btn** found = root;

    while((*found != NULL) && (cmp((*found)->value, value) != 0))
    {
        if(cmp((*found)->value, value) > 0)
        {
            found = &(*found)->left;
        }
        else if(cmp((*found)->value, value) < 0)
        {
            found = &(*found)->right;
        }
    }
    return found;
}

int sbt_exists(btn** root, int value, int cmp(t_elem_btree, t_elem_btree))
{
    btn* found = *root;

    while((found != NULL) && (cmp(found->value, value) != 0))
    {
        if(cmp(found->value, value) > 0)
        {
            found = found->left;
        }
        else if(cmp(found->value, value) < 0)
        {
            found = found->right;
        }
    }

    if(found != NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

btn* remove_and_set_right(btn** root, int value, int cmp(t_elem_btree, t_elem_btree))
{
    btn** p_node = root;
    btn* removed_node = NULL;
    p_node = find_node_2(root, value, cmp);
    if(((*p_node) != NULL) && ((*p_node)->right != NULL))
    {
        sbtn_insert(&(*p_node)->right, (*p_node)->left, cmp);
        (*p_node)->left = NULL;
        removed_node = *p_node;
        *p_node = removed_node->right;
    }
    return removed_node;
}

btn* remove_and_set_maxl_minr(btn** root, int value, int cmp(t_elem_btree, t_elem_btree))
{
    btn** p_node = root;
    btn** aux = root;
    btn* removed_node = NULL;
    p_node = find_node_2(root, value, cmp);
    aux = p_node;
    if(*aux != NULL)
    {
        aux = sbt_max(&(*p_node)->left);
        if(*aux == NULL)
        {
            aux = sbt_min(&(*p_node)->right);
        }
        removed_node = *p_node;
        *p_node = *aux;
        *aux = NULL;
    }
    return removed_node;
}

btn* remove_and_set_maxl_if_ltr(btn** root, int value, int cmp(t_elem_btree, t_elem_btree))
{
    btn** p_node = root;
    btn** aux = root;
    btn* removed_node = NULL;
    p_node = find_node_2(root, value, cmp);
    if((*p_node != NULL) && (cmp(btn_height((*p_node)->left), btn_height((*p_node)->right))>=0))
    {
        removed_node = *p_node;
        aux = sbt_max(&(*p_node)->left);
        *p_node = *aux;
        *aux = NULL;
    }
    return removed_node;
}

btn* remove_and_set_minr_if_rtl(btn** root, int value, int cmp(t_elem_btree, t_elem_btree))
{
    btn** p_node = root;
    btn** aux = root;
    btn* removed_node = NULL;
    p_node = find_node_2(root, value, cmp);
    if((*p_node != NULL) && (cmp(btn_height((*p_node)->right), btn_height((*p_node)->left))>0))
    {
        removed_node = *p_node;
        aux = sbt_min(&(*p_node)->right);
        *p_node = *aux;
        *aux = NULL;
    }
    return removed_node;
}

void btn_insert_value_on_sbtn(btn* node, void* ctx)
{
    btn** sbtn = (btn**)ctx;
    sbtn_insert_value(sbtn, node->value);
}

void sll_remove_duplicated_elements_using_sbt(sll_node* a_node)
{
    btn* sbtn = NULL;
    while(a_node != NULL)
    {
        if(!sbtn_insert_value(&sbtn, a_node->data))
        {
            sll_node_free(&a_node);
        }
        a_node = a_node->next;
    }
}

void btn_is_sbtn(btn* node, void* ctx)
{
    context_t* context = (context_t*)ctx;
    if(node->value <= context->prev_value)
    {
        context->is_sbt = 0;
    }
    context->prev_value = node->value;
}

int main() {
    btn* root = NULL;
    sbtn_insert_value(&root, 20);
    sbtn_insert_value(&root, 10);
    sbtn_insert_value(&root, 30);
    sbtn_insert_value(&root, 15);
    sbtn_insert_value(&root, 25);
    sbtn_insert_value(&root, 35);
    sbtn_insert_value(&root, 22);
    sbtn_insert_value(&root, 27);

    btn* root2 = NULL;
    btn_insert_value(&root2, 20);
    btn_insert_value(&root2, 10);
    btn_insert_value(&root2, 30);
    btn_insert_value(&root2, 15);
    btn_insert_value(&root2, 25);
    btn_insert_value(&root2, 35);
    btn_insert_value(&root2, 22);
    btn_insert_value(&root2, 27);

    printf("\n%10s: \n", "Árbol");
    btn_print(root, btn_intToStr);

    printf("\n%10s: \n", "Árbol 2");
    btn_print(root2, btn_intToStr);

    btn** min = sbt_min(&root);
    printf("\nMinimo en el arbol: %i\n", (*min)->value);

    btn** max = sbt_max(&root);
    printf("\nMáximo en el arbol: %i\n", (*max)->value);

    btn* found = find_node(&root, 15, btn_cmp_int);
    printf("\n Valor encontrado en el arbol (recursiva): %i\n", found->value);

    btn* found_it = find_node_it(&root, 15, btn_cmp_int);
    printf("\n Valor encontrado en el arbol (iterativa): %i\n", found_it->value);

    btn** found_2 = find_node_2(&root, 15, btn_cmp_int);
    printf("\n Valor encontrado en el arbol (p doble recursiva): %i\n", (*found_2)->value);

    btn** found_2_it = find_node_2_it(&root, 15, btn_cmp_int);
    printf("\n Valor encontrado en el arbol (p doble iterativa): %i\n", (*found_2_it)->value);

    sbt_exists(&root, 15, btn_cmp_int) ? printf("El nodo 15 existe\n") : printf("El nodo 15 no existe\n");
    sbt_exists(&root, 4, btn_cmp_int) ? printf("El nodo 4 existe\n") : printf("El nodo 4 no existe\n");

    //Quitar un nodo de un SBT, reemplazando el nodo por su rama Derecha y agregando la rama Izquierda a la rama derecha.
    /*
    remove_and_set_right(&root, 30, btn_cmp_int);
    printf("\n%10s: \n", "Árbol modificado");
    btn_print(root, btn_intToStr);
    */
    //Quita un nodo de un SBT, reemplazando el nodo por el máximo de su rama izquierda, o en su defecto por el mínimo de su rama derecha.
    /*
    remove_and_set_maxl_minr(&root, 35, btn_cmp_int);
    printf("\n%10s: \n", "Árbol modificado");
    btn_print(root, btn_intToStr);
    */
    //Quitar un nodo de un SBT, reemplazando el nodo por el máximo de su rama izquierda, si la rama izquierda es igual o más alta que la derecha.
    /*
    remove_and_set_maxl_if_ltr(&root, 30, btn_cmp_int);
    printf("\n%10s: \n", "Árbol modificado");
    btn_print(root, btn_intToStr);
    */
    //Quitar un nodo de un SBT, reemplazando el nodo por el mínimo de su rama derecha, si la rama derecha es más alta que la izquierda.
    /*
    remove_and_set_minr_if_rtl(&root, 20, btn_cmp_int);
    printf("\n%10s: \n", "Árbol modificado");
    btn_print(root, btn_intToStr);
    */
    //Armar una función (y las funciones auxiliares necesarias) para que dado un Árbol binario (BT) y un SBT (ABB) con los mismos valores sin destruir el árbol original.  
    btn* sbtn = NULL;
    btn_preorder(root2, btn_insert_value_on_sbtn, &sbtn);
    printf("\n%10s: \n", "\nÁrbol transfotmado en SBT\n");
    btn_print(sbtn, btn_intToStr);
    //Eliminar todos los elementos repetidos de una lista dinámica simplemente enlazada, recorriendo la lista una sola vez y utilizando como estructura auxiliar un SBT.
    sll_node* head = NULL;
    
    sll_add_node(&head, sll_new_node(1));
    sll_add_node(&head, sll_new_node(3));
    sll_add_node(&head, sll_new_node(1));
    sll_add_node(&head, sll_new_node(8));
    sll_add_node(&head, sll_new_node(8));

    printf("Lista antes de eliminar los elementos repetidos:\n");
    sll_print(head, print_int);
    printf("\n");
    sll_remove_duplicated_elements_using_sbt(head);
    printf("Lista despues de eliminar los elementos repetidos:\n");
    sll_print(head, print_int);
    printf("\n");

    //Dado un árbol binario, determinar si es un SBT. 
    context_t context = {INT_MIN, 1};
    btn_inorder(root, btn_is_sbtn, &context);
    context.is_sbt ? printf("\nEl arbol 1 es de busqueda\n") : printf("\nEl arbol 1 no es de busqueda\n");
}