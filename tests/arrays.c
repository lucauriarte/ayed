#include <stdlib.h>
#include <stdio.h>

void print_int_array (int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("A[%d] = %d\n", i, a[i]);
    }
}

void print_int_array_inverted (int a[], int n) {
    for (int i = n - 1 ; i >= 0 ; i--) {
        printf("A[%d] = %d\n", i, a[i]);
    }
}

int sequential_search(int key, int a[], int n) {
    int i = 0;
    while ((i < n) && (a[i] != key)) {
        i++;
    }    
    return (i >= n)? -1 : i;
}

int sequential_search_inv (int key, int a[], int n) {    
    while ((--n >= 0) && (a[n] != key))
        ;
    return n;
}

void array_insert(int a[], int* n, int value, int pos) {
    for (int i = *n; i > pos; i--) {
        a[i] = a[i-1];
    }
    a[pos] = value;
    (*n)++;
}

int array_remove(int a[], int* n, int pos){
    int value = a[pos];
    (*n)--;
    for (int i = pos; i < *n; i++) {
        a[i] = a[i+1];
    }    
    return value;
}

void array_add(int a[], int* n, int value) {
    a[*n] = value;
    (*n)++;
}

int array_remove_data(int key, int a[], int* n)
{
    int pos = 0;

    pos = sequential_search(key, a, *n);

    if(pos >= 0)
    {
        array_remove(a, n, pos);
    }

    return pos;
}

int main()
{
    int numeros[10] = {1, 2, 3, 4, 5};
    //char caracteres[10] = {'a', 'b', 'c', 'd', 'e'};
    int pos = 0;
    int cant_el = 5;

    print_int_array(numeros, cant_el);
    printf("\n");

    pos = sequential_search(3, numeros, cant_el);
    printf("Posicion: %u\n", pos);

    pos = sequential_search_inv(3, numeros, cant_el);
    printf("Posicion: %u\n", pos);

    //print_int_array_inverted(numeros, 5);

    array_insert(numeros, &cant_el, 8, 3);
    print_int_array(numeros, cant_el);
    printf("\n");

    array_remove(numeros, &cant_el, 3);
    print_int_array(numeros, cant_el);
    printf("\n");

    array_add(numeros, &cant_el, array_remove(numeros, &cant_el, 1));
    print_int_array(numeros, cant_el);
    printf("\n");

    array_remove_data(4, numeros, &cant_el);
    print_int_array(numeros, cant_el);
    printf("\n");
}