/*gcc -Wl,--no-as-needed,-lrt Fibonacci.c*/
#include <stdio.h>
#include <time.h>
/*exponential time, bad*/
unsigned long long fib1(int n)
{
    if (n==0) return 0;
    if (n==1) return 1;
    return fib1(n-2)+fib1(n-1);
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
struct matrix2x2 {
    unsigned long long d[2][2];
};
static struct matrix2x2 matrix2x2mul(struct matrix2x2 m, struct matrix2x2 n)
{
    struct matrix2x2 r;
    r.d[0][0] = m.d[0][0] * n.d[0][0] + m.d[0][1] * n.d[1][0];
    r.d[0][1] = m.d[0][0] * n.d[0][1] + m.d[0][1] * n.d[1][1];
    r.d[1][0] = m.d[1][0] * n.d[0][0] + m.d[1][1] * n.d[1][0];
    r.d[1][1] = m.d[1][0] * n.d[0][1] + m.d[1][1] * n.d[1][1];
    return r;
}
static struct matrix2x2 fibpow(int n)
{
    
    static struct matrix2x2 u = {.d[0][0]=1, .d[0][1]=1, .d[1][0]=1, .d[1][1]=0};
    struct matrix2x2 r;
    if (1==n) return u;
    if (n%2==0) {
        r = fibpow(n/2);
        r = matrix2x2mul(r, r);
    } else {
        r = fibpow((n-1)/2);
        r = matrix2x2mul(r, r);
        r = matrix2x2mul(r, u);
    }
    return r;
}
/*O(lgn) time, O(1) space, best*/
unsigned long long fib4(int n)
{
    struct matrix2x2 r;
    unsigned long long f[2] = {0, 1};
    if (n<2) return f[n];
    r = fibpow(n-1);
    return r.d[0][0];
}
int main(void)
{
    int n;
    struct timespec t1, t2;
    unsigned long long r;
    printf("Fibonacci? ");
    while (scanf("%d", &n)==1) {
        printf("\n");
        clock_gettime(CLOCK_MONOTONIC, &t1);
        r = fib4(n);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        printf("fib4(%d)=%llu t=%lus %luns\n", n, r, (t2.tv_sec-t1.tv_sec), (t2.tv_nsec-t1.tv_nsec));
        clock_gettime(CLOCK_MONOTONIC, &t1);
        r = fib3(n);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        printf("fib3(%d)=%llu t=%lus %luns\n", n, r, (t2.tv_sec-t1.tv_sec), (t2.tv_nsec-t1.tv_nsec));
        clock_gettime(CLOCK_MONOTONIC, &t1);
        r = fib2(n);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        printf("fib2(%d)=%llu t=%lus %luns\n", n, r, (t2.tv_sec-t1.tv_sec), (t2.tv_nsec-t1.tv_nsec));
        /*clock_gettime(CLOCK_MONOTONIC, &t1);
        r = fib1(n);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        printf("fib1(%d)=%llu t=%lus %luns\n", n, r, (t2.tv_sec-t1.tv_sec), (t2.tv_nsec-t1.tv_nsec));*/
        printf("\nFibonacci? ");
    }
    return 0;
}
