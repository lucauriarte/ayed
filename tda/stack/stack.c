#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

stack* stack_new(int maxsize)
{
    stack* s = NULL;
    if(maxsize > 0)
    {
        s = (stack*)malloc(sizeof(stack));
        s->maxsize = maxsize;
        s->count = 0;
    }

    return s;
}

void stack_free(stack* s)
{
    free(s);
}

int stack_getsize(stack* s)
{
    return s->count;
}

int stack_getmaxsize(stack* s)
{
    return s->maxsize;
}

int stack_isempty(stack* s)
{
    if(s->count == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int stack_isfull(stack* s)
{
    if(s->count == s->maxsize)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void push(stack* s, t_elem elem)
{
    stack_node* node = NULL;
    if((s != NULL) && (s->count != s->maxsize))
    {
        node = (stack_node*)malloc(sizeof(stack_node));
        node->value = elem;
        node->next = s->head;
        s->head = node;
        s->count++;
    }
}

t_elem pop(stack* s)
{
    t_elem elem = 0;
    stack_node* aux = NULL;
    if((s != NULL))
    {
        elem = s->head->value;
        aux = s->head->next;
        free(s->head);
        s->head = aux;
    }
    return elem;
}

t_elem top(stack* s)
{
  t_elem elem = 0;
      if(s != NULL)
      {
          elem = s->head->value; 
      }
  return elem;
}

void stack_destroy(stack* s, void elem_free(t_elem))
{
    stack_node * aux = NULL;
    while(s->count > 0)
    {
        aux = s->head->next;
        elem_free(s->head->value);
        free(s->head);
        s->head = aux;
    }
}