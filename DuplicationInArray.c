/*Question 5:
An array contains n numbers ranging from 0 to n-2. There is exactly one number duplicated in
the array. How do you find the duplicated number? For example, if an array with length 5 contains numbers {0, 2,
1, 3, 2}, the duplicated number is 2.
*/
#include <stdio.h>
#include <stdlib.h>
int duplicate(int *arr, int n)
{
    int i, sum=0, ref = ((n-2)*(n-1)/2);
    for (i=0;i<n;i++) {
        int v = arr[i];
        if (v<0 || v>=n-1) {
            printf("invalid %d\n", v);
            return (-1)*i;
        }
        sum+=v;
    }
    return sum-ref;
}
int main(int argc, char **argv)
{
    int i, n, *arr, ret;
    if (argc == 1) return 0; else n = argc-1;
    arr = malloc(sizeof(int)*n);
    for (i=0;i<n;i++) arr[i]=atoi(argv[i+1]);
    for (i=0;i<n;i++) printf("%d ", arr[i]);
    ret = duplicate(arr, n);
    if (ret>=0) printf("\nduplicate=%d\n", ret);
    else printf("\nerror in %d\n", arr[ret*(-1)]);
    free(arr);
    return 0;
}