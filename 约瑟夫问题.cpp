/*4．约瑟夫问题。设有n个人做作圆桌周围，从第s个人开始报数，报到m的人出列，然后再从下一个人开始报数，
数到m的人又出列，如此重复，直到所有的人都出列为止。要求按出列的先后顺序输出每个人的信息。(选做题)
结构体和结点可以参照下列代码：
typedef char datatype;
typedef struct node
{
datatype info;
struct node *next;
} NODE;
*/
#include <stdio.h>
#include <malloc.h>
typedef char datatype;
int n;//记录人数
typedef struct node
{
datatype info;
struct node *next;
} NODE,*Linklist;
int CreatList(Linklist &L,int n)
{
	int i;
	Linklist p,head;
	L=(Linklist)malloc(sizeof(NODE)); /* 产生头结点,并使L指向此头结点 */
	L->info = 0;
    head = L;
	if(L==NULL) /* 存储分配失败 */
            return -1;
	L->next = head;
    for (i = n; i >0; i--)
	{
		p = (Linklist)malloc(sizeof(NODE));
		p->info = i;
		p->next = L->next;
		L->next = p;
	}
	return 1;
}

void DestroyList(Linklist &L)
{
	Linklist p,q;
	p=L->next;           /*  p指向第一个结点 */
	while(p)                /*  没到表尾 */
	{
		q=p->next;
		free(p);
		p=q;
	}
	free(L);        /* 释放头节点的空间 */
}
void ListJump(Linklist &L,int s,int m)
{
	Linklist p,q;
	int i;
	p=L->next;
	while(p->info<s)
	{
		p = p->next;
	}
	while(p->next!=p)  
    {  
        if(p->info == 0)//忽略头结点
			p=p->next;
		else
		{
			for(i=1;i<m-1;i++)	//报数
			{
				p=p->next;
				if(p->info == 0)	//忽略头结点
					p=p->next;
			}
			if(p->next->info == 0)
				q = p->next->next;
			else
				q = p->next;
			p->next = q->next;			/* 将q的后继赋值给p的后继 */
			printf("%d ",q->info);
			free(q); 
			n--;
			if(n==1)
				break;
			p=p->next;
		}
    }
	printf("%d",p->info);
}
int main()
{
	int s,m;
	scanf("%d",&n);
	scanf("%d",&s);
	scanf("%d",&m);
	Linklist L;
	CreatList(L,n);
	ListJump(L,s,m);
	return 0;
}
