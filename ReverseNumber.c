#include <stdio.h>
static int reverse(int v)
{
    int r=0;
    while (v>0) r=r*10+v%10, v/=10;
    return r;
}
int main(void)
{
    int n;
    while (scanf("%d", &n)==1) {
        printf("%d -> %d\n", n, reverse(n));
    }
}
