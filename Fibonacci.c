#include <stdio.h>
/*exponential time, bad*/
unsigned long long fib1(int n)
{
    if (n==0) return 0;
    if (n==1) return 1;
    return fib(n-2)+fib(n-1);
}
/*O(n) time, O(1) space, good*/
unsigned long long fib2(int n)
{
    int i;
    unsigned long long f, fm1, fm2; /*f(n), f(n-1), f(n-2)*/
    if (n==0) return 0;
    if (n==1) return 1;
    for (i=2,fm1=1,fm2=0;i<=n;i++) { /*bottom-up*/
        f = fm1+fm2, fm2=fm1, fm1=f;
    }
    return f;
}
/*O(n) time, O(1) space, good*/
unsigned long long fib3(int n)
{
    int i;
    unsigned long long f[2] = {0, 1}, tmp;
    if (n<2) return f[n];
    for (i=2;i<=n;i++) { /*bottom-up*/
        tmp = f[1], f[1]=f[0]+f[1], f[0]=tmp;
    }
    return f[1];
}
int main(void)
{
    int n;
    while (scanf("%d", &n)==1) {
        printf("fib3(%d)=%llu\n", n, fib3(n));
        printf("fib2(%d)=%llu\n", n, fib2(n));
        printf("fib1(%d)=%llu\n", n, fib1(n));
    }
    return 0;
}