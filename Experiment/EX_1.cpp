#include <iostream>

using namespace std;

typedef struct node
{
    int c;
    int e;
    struct node *next;
} linklist;
typedef struct node *plink;

plink addnode(plink end, int c, int e)
{
    plink t = new linklist;
    t->c = c;
    t->e = e;
    t->next = NULL;
    end->next = t;
    return t;
}
void printnode(plink head)
{
    plink p = head->next;
    if (p)
    {
        printf("%d %d", p->c, p->e);
        p = p->next;
        while (p)
        {
            printf(" %d %d", p->c, p->e);
            p = p->next;
        }
    }
    else
    {
        printf("0 0");
    }
}

int main()
{
    int c, e;
    plink head = new linklist;
    plink end = head;
    head->next = NULL;
    while (cin >> c >> e)
    {
        int tc, te;
        if (e != 0)
        {
            te = e - 1;
            tc = e * c;
            if (tc != 0)
            {
                end = addnode(end, tc, te);
            }
        }
    }
    printnode(head);
    return 0;
}
