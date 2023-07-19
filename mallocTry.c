#include<stdio.h>
#include<stdlib.h>
int** fn()
{
    int ** a = (int **)malloc(sizeof(int *)*20);

    int c = 30, d = 20, e = 30;
    *a = &c;
    *(a+1) = &d;
    *(a+2) = &e;

    int *x = (int *)malloc(sizeof(int));
    *x = 33;
    *(a+3) = x;


    // *(*a+10) = 30;

    return a;

}

void fn2()
{
    int a = 999;
    int ab = 999;
    int c = 999;
    int d = 999;
    int f = 999;

    int g = 999;
    int h = 999;
    int j = 999;
    int k = 999;
    int l = 999;
    int q = 999;
    int w = 999;
    int e = 999;
    int r = 999;
    int t = 999;
    int y = 999;
    int u = 999;
    int i = 999;
    int o = 999;
    int p = 999;
    int z = 999;
    int x = 999;
    
}

int main()
{
    int **b = fn();
    // fn2();
    printf("%d", **b);
    printf("%d", **(b+1));
    printf("%d", **(b+2));
    printf("%d", **(b+3));
    return 0;
}