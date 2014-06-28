#include <stdio.h>
typedef struct node {
    int data;
    struct node *next;
} list;
int HasLoopInList(list *head)
{
    list *slow, *fast;
    if (NULL==head) return 0/*false*/;
    slow = head->next;
    if (NULL==slow) return 0;
    fast = slow->next;
    while (NULL!=fast && NULL!=slow) {
        if (fast==slow) return 1/*true*/;
        slow = slow->next;
        fast = (fast->next)? fast->next->next: NULL;
    }
    return 0;
}
int main(void)
{
    list c1[6];
    c1[0].data= 1, c1[0].next = &c1[1];
    c1[1].data= 2, c1[1].next = &c1[2];
    c1[2].data= 3, c1[2].next = &c1[3];
    c1[3].data= 4, c1[3].next = &c1[4];
    c1[4].data= 5, c1[4].next = &c1[5];
    //c1[5].data= 6, c1[5].next = &c1[3];
    c1[5].data= 6, c1[5].next = NULL;
    printf("case 1 has loop in list? %s\n", HasLoopInList(c1)? "yes":"no");
    return 0;
}
