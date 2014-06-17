/*Calculate 1+2+¡K+n*/
#include <stdio.h>
int sum_loop(int n)
{
    int i, sum;
    for (sum=0,i=1;i<=n;i++) sum+=i;
    return sum;
}
int sum_dfs(int n)
{
    return (n>0)? n+sum_dfs(n-1):0; 
}
int main(void)
{
    int str[128];
    while (scanf("%s", &str)==1) {
        printf("%s\n", str);
    }
}