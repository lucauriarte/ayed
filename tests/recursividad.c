#include <stdio.h>

void array_print_1(int a[], int n);
void array_print_2 (int a[], int n);
long espar (long n);
long esimpar (long n);

int exists(int a[], int n, int x) {
    return n > 0 && (a[n-1]==x || exists(a, n-1, x));
}

void array_print_1(int a[], int n) {
    if (n > 0) {
        array_print_2(a, n - 1);
        printf("%d ", a[n-1]);
    }
}

void array_print_2 (int a[], int n) {
    if (n > 0) {
        printf("%d ", a[n-1]);
        array_print_1(a, n - 1);        
    }
}

void print_mat_trans_3x4 (int mat[3][4], int i, int j){
    if (i >= 3){
        printf("\n");        
        print_mat_trans_3x4(mat,0,j+1);
    } else if (j < 4){
        printf("%3d  ",mat[i][j]);        
        print_mat_trans_3x4(mat,i+1,j);
    }
}

long espar (long n){
    long result = 1;
    if (n > 0){        
        result = esimpar(n-1);
    }
    return result;
}

long esimpar (long n){
    int result = 0;
    if (n > 0){
        return (espar(n-1));
    }
    return result;
}

long factorial_tail(long n, long acum){
    if (n == 0){
        return acum;
    } else {
        return factorial_tail(n-1, n*acum);
    }
}

int min(int a, int b)
{
    a > b ? return a : return b;
}

int array_min(int a[], int n)
{
    int res = 0;

    if(n == 1)
    {
        res = a[0];
    }
    else
    {
        res = min(array_min(a, n-1), a[n-1]);
    }

}

int array_min_2(int a[], int n) {
    int min = 0;
    if(n == 1)
    {
        return a[0];
    }

    min = array_min_2(a, n-1);
    if(a[n-1] < min)
    {
        min = a[n-1];
    }
    return min;
}

int main()
{
    int test[5] = {2,4,5,8,10};
    int matriz[3][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}};
    int vector[5] =  {10,4,8,20,30};

    int ex = 0;
    long test_l = 0;

    //ex = exists(test, 5, 2);

    //array_print_1(test, 5);
    //printf("\n");
    
    //array_print_2(test, 5);
    //printf("\n");

    //print_mat_trans_3x4(matriz, 0, 0);

    //stest_l = factorial_tail(3, 1);

    return 1;
}