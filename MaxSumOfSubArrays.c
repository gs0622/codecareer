/*test case: a.out -5 0 -4 1 4 3 -2*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX(a,b)    ((a)>(b)?(a):(b))
int main(int argc, char **argv)
{
#if 1 /*DP*/
    int i, max, data[100]={}, dp[100]={}, n=argc-1;
    if (0==n) return 0;
    assert(n<100);
    for (i=1;i<argc;i++) data[i-1]=atoi(argv[i]);
    //for (i=0;i<n;i++) printf("%3d ", data[i]); puts("");
    dp[0]=MAX(0, data[0]);
    for (i=1;i<n;i++) dp[i]=MAX(0, dp[i-1]+data[i]);
    //for (i=0;i<n;i++) printf("%3d ", dp[i]);
    for (i=1, max=dp[0];i<n;i++) max = MAX(dp[i], max);
    printf("max=%d\n", max);
#else /*Brute force*/
    int i, j, k, sum=0, max=0, n = argc-1, data[100];
    if (!n) return 0;
    for (i=1;i<argc;i++) data[i-1]=atoi(argv[i]);
    //for (i=0;i<n;i++) printf("%d ", data[i]); puts("");
    printf("\n");
    for (i=0;i<n;i++) {
        for (j=1;j<=n;j++) {
            for (sum=0,k=i;k<i+j&&k<n;k++) {
                sum=sum+data[k];
            }
            //printf("s=%d, %d %d %d\n", sum, i, j, k);
            max=(sum>max)?sum:max;
        }
    }
    printf("max=%d\n", max);
#endif
    return 0;
}