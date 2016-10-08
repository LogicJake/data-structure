#include "LinkList.h"
void reverse(LinkList &L)
{
	LinkList p,q;
	p = L->next;L->next = NULL;
	while(p)
	{
		q = p->next;
		p->next = L->next;
		L->next = p;
		p = q;
	}
}
int main()
{
	LinkList L;
	creatlist(L);
	reverse(L);
	ListTraverse(L);
	return 0;
}