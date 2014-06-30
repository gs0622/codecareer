#include <stdio.h>
typedef struct node {
    int data;
    struct node *next;
} list;
list *HasLoopInList(list *head)
{
    list *slow, *fast;
    if (NULL==head) return NULL;
    slow = head->next;
    if (NULL==slow) return NULL;
    fast = slow->next;
    while (NULL!=fast && NULL!=slow) {
        if (fast==slow) return fast;
        slow = slow->next;
        fast = (fast->next)? fast->next->next: NULL;
    }
    return NULL;
}
list *EntryOfLoopList(list *head)
{
    list *meet = HasLoopInList(head);
    if (!meet) return NULL;
    else {
        int nodes, i;
        list *p, *q;
        for (nodes=1, p = meet; p->next != meet;) nodes++, p = p->next;
        p = q = head;
        for (i=0;i<nodes;i++) p = p->next;
        while (p != q) p = p->next, q = q->next;
        return p;
    }
}
int main(void)
{
    list c1[6], *p;
    c1[0].data= 0, c1[0].next = &c1[1];
    c1[1].data= 1, c1[1].next = &c1[2];
    c1[2].data= 2, c1[2].next = &c1[3];
    c1[3].data= 3, c1[3].next = &c1[4];
    c1[4].data= 4, c1[4].next = &c1[5];
    c1[5].data= 5, c1[5].next = &c1[2];
    //c1[5].data= 6, c1[5].next = NULL;
    printf("case 1 has loop in list? %s\n", HasLoopInList(c1)? "yes":"no");
    p = EntryOfLoopList(c1);
    if (p) printf("case 1 entry in loop? data=%d\n", p->data);
    return 0;
}
