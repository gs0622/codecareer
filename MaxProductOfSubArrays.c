/*test case: ./a.out -5 0 -4 1 4 3 -2*/
/*test case: ./a.out 0 0 0 0 0*/
/*test case: ./a.out 0 0 0 0 -1*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX(a,b)    ((a)>(b)?(a):(b))
#if 1 /*Brute force, time: O(n^2)*/
int main(int argc, char **argv)
{
    long i, j, max, mul, n = argc-1, data[100];
    if (!n) return 0;
    for (i=1;i<argc;i++) data[i-1]=atol(argv[i]);
    for (i=0,max=data[0];i<n;i++) {
        for (j=i,mul=1;j<n;j++) {
            if (0==data[j]) { mul=0; break; }
            mul = mul*data[j];
        }
        max = MAX(max, mul);
    }
    printf("max=%ld\n", max);
    return 0;
}
#else /*Brute force, time: O(n^3)*/
int main(int argc, char **argv)
{
    long i, j, k, mul=1, max=0, n = argc-1, data[100];
    if (!n) return 0;
    for (i=1;i<argc;i++) data[i-1]=atoi(argv[i]);
    for (i=0;i<n;i++) {
        for (j=1;j<=n;j++) {
            for (k=i,mul=1;k<i+j&&k<n;k++) {
                if (0==data[k]) {
                    mul=0;
                    break;
                }
                mul=mul*data[k];
            }
            max=(mul>max)?mul:max;
        }
    }
    printf("max=%ld\n", max);
    return 0;
}
#endif

