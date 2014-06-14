/*Question 5:
An array contains n numbers ranging from 0 to n-2. There is exactly one number duplicated in
the array. How do you find the duplicated number? For example, if an array with length 5 contains numbers {0, 2,
1, 3, 2}, the duplicated number is 2.
*/
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int i, n, v, *arr;
    if (argc == 1) return 0; else n = argc-1;
    arr = malloc(sizeof(int)*n);
    for (i=0;i<n;i++) arr[i]=-1;
    for (i=0;i<n;i++) {
        v = atoi(argv[i+1]);
        if (v<0||v>n-2) {
            printf("%d invalid\n", v);
            break;
        }
        if (arr[v]==-1) arr[v]=v;
        else printf("%d duplicated\n", v);
    }
    free(arr);
    return 0;
}