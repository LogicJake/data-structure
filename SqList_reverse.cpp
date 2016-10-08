#include "SqList.h"
void reverse(SqList &L)
{
	int i,j;
	int temp;
	for (int i = 0,j = L.length - 1; i < j; i++,j--)
	{
		temp = L.elem[i];
		L.elem[i] = L.elem[j];
		L.elem[j] = temp;
	}
}
int main()
{
	SqList L;
	createList(L);
	reverse(L);
	ListTraverse(L);
	return 0;
}
