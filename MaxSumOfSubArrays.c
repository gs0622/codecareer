#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int i, j, k, sum=0, max=0, n = argc-1, data[100];
    if (!n) return 0;
    for (i=1;i<argc;i++) data[i-1]=atoi(argv[i]);
    for (i=0;i<n;i++) printf("%d ", data[i]);
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
    return 0;
}