#include <stdlib.h>
#include <stdio.h>

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
}