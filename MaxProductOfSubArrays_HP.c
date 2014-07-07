#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b)    ((a)>(b)?(a):(b))
int MaxProductSeq(const int arr[], int sz)
{
    int i, max, neg, cnt, mul, tmp;
    if (sz<=0) return 0;
    for (i=0,max=arr[0],mul=1,cnt=0,tmp=0;i<sz;i++) {
        if (0==arr[i]) { mul=1,cnt=0; continue; }
        neg = (arr[i]<0)? 1: 0; /*is negative*/
        cnt += neg? 1: 0; /*total neg count*/
        mul *= arr[i];
        if (1==cnt && neg) tmp = arr[i]; /*remember 1st neg*/
        max = (0==cnt%2)? MAX(max, mul): MAX(max, mul/tmp);
    }
    return max;

}
int main(int argc, char **argv)
{
    int i, n = argc-1, data[100];
    for (i=1;i<argc;i++) data[i-1]=atoi(argv[i]);
    printf("max=%d\n", MaxProductSeq(data, n));
    return 0;
}

