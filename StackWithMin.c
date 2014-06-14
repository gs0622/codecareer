/*Problem: http://codercareer.blogspot.tw/2011/09/no-02-stack-with-function-min.html
Define a stack, in which we can get its minimum number with a function min.
In this stack, the time complexity of min(), push() and pop() are all O(1).
*/
#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *next;
};
struct node *top = NULL;
int min;
void push(int v)
{
    struct node *cur = malloc(sizeof(struct node));
    if (!cur) return; else cur->next=NULL;
    if (!top) min=v;
    else if (min>v) {
        int w = 2*v-min; /*less than v*/
        min = v; /*new min by v*/
        v = w; /*push w on stack top*/
    }
    cur->data=v, cur->next=top, top=cur;
}
int pop(void)
{
    int v;
    struct node *cur = top;
    if (!top) return -1; /*TBD*/
    v = cur->data, top = top->next, free(cur);
    if (min>v) { int w=min; min=2*min-v, v=w; }
    return v;
}
void show(void)
{
    struct node *cur = top;
    if (!cur) return;
    printf("stack: ");
    while (cur) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf(" min: %d\n", min);
}
int main(void)
{
    int i, j;
    while (1) {
        printf("0. push 1.pop\n");
        if (scanf("%d", &i)!=1) break;
        if (0==i) printf("push? "), scanf("%d", &j), push(j);
        if (1==i) printf("pop %d\n", pop());
        show();
    }
    return 0;
}
