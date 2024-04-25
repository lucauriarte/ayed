#include <stdlib.h>
#include <stdio.h>
#include "vector_float/vector.h"

int add_from_zero_to(int n)
{
    if(n == 0 || n == 1)
    {
        return n;
    }
    else
    {
        return n + add_from_zero_to(n - 1);
    }
}

int multiply(int a, int b)
{
    if(b == 0)
    {
        return 0;
    }
    else if(b == 1)
    {
        return a;
    }
    else
    {
        return a + multiply(a, b - 1);
    }
}

int fibonacci(int n)
{
    int result = 1;
    if (n > 1) 
    {
        result = fibonacci(n - 1) + fibonacci(n - 2);
    }
    return result;
}

void print_fibonacci(int n) 
{
    if (n > 0)
    {
        print_fibonacci(n - 1);
        printf("%d ", fibonacci(n));
    }
}

void print_fibonacci_less_than_x(int x, int index) {
    int fib = fibonacci(index);
    if (fib < x) 
    {
        printf("%d ", fib);
        print_fibonacci_less_than_x(x, index + 1);
    }
}

float recursive_pow(int x, int n)
{
    float res = 1;
    if (n > 0)
    {
        res = x * recursive_pow(x , n-1);
    }
    else if (n < 0)
    {
        res = (1.0/x) * recursive_pow(x , n+1);
    }
    return res;
}

int digits_are_crescent(int a)
{
    int are_crescent = 1;
    int last_digit = a % 10;
    a /= 10;

    if (a > 0)
    {
        if(last_digit > a % 10)
        {
            return digits_are_crescent(a);
        }
        else 
        {
            are_crescent = 0;
        }
    }
    return are_crescent;
}

void print_inverted_count_to(int n)
{
    int aux = 0;
    if(n == 1)
    {
        printf("1\n");
    }
    else
    {
        print_inverted_count_to(n - 1);
        aux = n;
        while (aux > 0)
        {
            printf("%i ", aux);
            aux--;
        }
        printf("\n");
    }
}

float vector_float_max(vector* v, int count)
{
    float max = 0;
    float a = 0;
    float b = 0;

    if(count == 0)
    {
        max = vector_get(v, count);
    }
    else
    {
        a = vector_float_max(v, count - 1);
        b = vector_get(v, count);
        max = a > b ? a : b;
    }
    return max;
}

float vector_float_min(vector* v, int count)
{
    float min = 0;
    float a = 0;
    float b = 0;

    if(count == 0)
    {
        min = vector_get(v, count);
    }
    else
    {
        a = vector_float_min(v, count - 1);
        b = vector_get(v, count);
        min = a < b ? a : b;
    }
    return min;
}

float vector_float_add(vector* v, int index)
{
    float sum = 0;

    if(index == vector_size(v) - 1)
    {
        sum = vector_get(v, index);
    }
    else
    {
        sum = vector_get(v, index) + vector_float_add(v, index + 1);
    }
    return sum;
}

float vector_float_average(vector* v, int index)
{
    float avg = 0;

    if(index == vector_size(v) - 1)
    {
        avg = vector_get(v, index);
    }
    else
    {
        avg = (vector_get(v, index) + vector_float_add(v, index + 1)) / vector_size(v);
    }
    return avg;
}

void vector_float_print(vector* v, int size)
{
    if (size > 0) 
    {
        vector_float_print(v, size - 1);
        printf("%f ", vector_get(v, (size - 1)));
    }
}

void vector_float_print_inverted(vector* v, int size)
{
    if (size > 0) 
    {
        printf("%f ", vector_get(v, (size - 1)));
        vector_float_print(v, size - 1);
    }
}

int main()
{
    //Calcular en forma recursiva la suma de los n primeros números naturales
    printf("Suma de todos los numeros naturales desde  hasta 4: %i\n", add_from_zero_to(4));

    // Calcular en forma recursiva el producto entre dos números enteros a través de multiplicaciones sucesivas
    printf("Multiplicacion de 3 x 4: %i\n", multiply(3, 4));

    //Desarrollar funciones recursivas que muestren por pantalla la sucesión de Fibonacci para los n primeros términos
    printf("Fibonacci de 5 terminos: ");
    print_fibonacci(5);
    printf("\n");

    //Desarrollar funciones recursivas que muestren por pantalla la sucesión de Fibonacci para los términos menores a x
    printf("Fibonacci para los terminos menores a 10: ");
    print_fibonacci_less_than_x(10, 1);
    printf("\n");

    //Desarrollar una función que calcule recursivamente el valor x^n. Considerar que tanto x como n puedan ser negativos.
    printf("2 elevado a 4: %f\n", recursive_pow(2,4));
    printf("2 elevado a -4: %f\n", recursive_pow(2,-4));

    //Desarrollar una función recursiva que determine si los dígitos de un número natural están dispuestos de forma creciente
    int num = 1579;
    if(digits_are_crescent(num))
    {
        printf("Los digitos del numero %i estan ordenados de forma creciente\n", num);   
    }
    else
    {
        printf("Los digitos del numero %i no estan ordenados de forma creciente\n", num);
    }

    print_inverted_count_to(5);

    vector* v = vector_new(4);
    vector_add(v, 0.2);
    vector_add(v, 5);
    vector_add(v, 1.5);
    vector_add(v, 7.6);

    printf("Maximo en el vector de numeros reales: %f\n", vector_float_max(v, vector_size(v) - 1));
    printf("Minimo en el vector de numeros reales: %f\n", vector_float_min(v, vector_size(v) - 1));
    printf("Suma de los elementos del vector de numeros reales: %f\n", vector_float_add(v, 0));
    printf("Promedio de los elementos del vector de numeros reales: %f\n", vector_float_average(v, 0));
    printf("Vector de flotantes:\n");
    vector_float_print(v, vector_size(v));
    printf("\n");
    printf("Vector de flotantes invertido:\n");
    vector_float_print_inverted(v, vector_size(v));
    printf("\n");
}