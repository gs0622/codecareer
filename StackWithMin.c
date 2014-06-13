#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *next;
};
struct node *top = NULL;
void push(int v)
{
    struct node *cur = malloc(sizeof(struct node));
    cur->data=v, cur->next=top, top=cur;
}
int pop(void)
{
    int v;
    struct node *cur = top;
    if (!top) return 0; /*TBD*/
    v = cur->data, top = top->next, free(cur);
    return v;
}
void show(void)
{
    struct node *cur = top;
    printf("stack: ");
    while (cur) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}
int main(void)
{
    int i, j;
    while (1) {
        printf("0. push 1.pop\n");
        if (scanf("%d", &i)!=1) break;
        if (0==i) scanf("%d", &j), push(j);
        if (1==i) printf("%d\n", pop());
        show();
    }
    return 0;
}