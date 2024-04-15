#include <stdlib.h>
#include <stdio.h>


void hanoi(int n, char source, char target, char aux, int* paso)
{
    if(n>0)
    {
        hanoi(n-1, source, aux, target, paso);
        printf("%i) %c->%c\n",(*paso)++, source, target);
        hanoi(n-1, aux, target, source, paso);
    }
}

int main ()
{
    int paso = 0;
    hanoi(3, 'A', 'C', 'B', &paso);
}