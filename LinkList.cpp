# include <stdio.h>
# include <stdlib.h> 
# include <malloc.h>
# include <string.h>
# define TRUE 1
# define FALSE 0
# define OK 1
# define ERROR 0
# define INFEASIBLE -1
# define OVERFLOW -2
typedef int ElemType;
typedef int Status;
typedef struct Node
{
    ElemType data;
    struct Node *next;
}Node;
typedef struct Node *LinkList; 
Status InitList(LinkList *L) 
{ 
    *L=(LinkList)malloc(sizeof(Node)); /* 产生头结点,并使L指向此头结点 */
    if(*L==NULL) /* 存储分配失败 */
            return ERROR;
    (*L)->next=NULL; /* 指针域为空 */
    return OK;
}
void DestroyList(LinkList *L)
{
	free (*L);
	*L=NULL;
}
Status ClearList(LinkList *L)
{ 
	LinkList p,q;
	p=(*L)->next;           /*  p指向第一个结点 */
	while(p)                /*  没到表尾 */
	{
		q=p->next;
		free(p);
		p=q;
	}
	(*L)->next=NULL;        /* 头结点指针域为空 */
	return OK;
}
Status ListEmpty(LinkList L)
{
	if (L->next==NULL)
		return TRUE;
	else
		return FALSE;
}
int ListLength(LinkList L)
{
	int i=0;
	LinkList p=L->next;
	while(p)
	{
		i++;
		p=p->next;
	}
	return i;
}
Status GetElem(LinkList L,int i,ElemType *e)
{
/*	if (i>0&&i<ListLength(L))
	{
		printf("查找的位置不正确\n");
	}
*/
	int j;
	LinkList p;		/* 声明一结点p */
	p = L->next;		/* 让p指向链表L的第一个结点 */
	j = 1;		/*  j为计数器 */
	while (p && j<i)  /* p不为空或者计数器j还没有等于i时，循环继续 */
	{   
		p = p->next;  /* 让p指向下一个结点 */
		++j;
	}
	if ( !p || j>i ) 
		return ERROR;  /*  第i个元素不存在 */
	*e = p->data;   /*  取第i个元素的数据 */
	return OK;
}
Status LocateElem(LinkList L,ElemType e)
{
	int i = 0;
	LinkList p=L->next;
	while(p)
	{
		i++;
		if (p->data!=e)
			p=p->next;
		else
			break;
	}
	if (i>0&&i<ListLength(L))
		return i;
	else
	{
		printf("查找失败！");
		return FALSE;
	}
}
Status PriorElem(LinkList L,ElemType cur_e,ElemType &pre_e)
{
	LinkList p=L->next;
	if (cur_e==p->data)
	{
		printf("不存在前驱！");
		return ERROR;
	}
	else
	{
		while(p)
		{
			if (p->next->data==cur_e)
			{
				pre_e=p->data;
				break;
			}
			else
				p=p->next;
		}
	}	
	if (!p)
	{
		printf("无此数据！");
		return ERROR;
	}
}
Status NextElem(LinkList L,ElemType cur_e,ElemType &next_e)
{
	LinkList p=L->next;
	while(p)
	{
		if (p->data==cur_e)
		{
 
			if (p->next!=NULL)
			{
				next_e=p->next->data;
				break;
			}
			else
			{
				printf("不存在后继！");
				return ERROR;
			}	
		}
		else
			p=p->next;
	}
	if (!p)
	{
		printf("无此数据！");
		return ERROR;
	}
}
Status ListInsert(LinkList *L,int i,ElemType e)
{
	LinkList p,s;
	p = *L;   
	int j = 0;
	while (p && j < i-1)     /* 寻找第i-1个结点 */
	{
		p = p->next;
		++j;
	} 
	if (!p || j > i-1) 
		return ERROR;   /* 第i-1个元素不存在 */
	s = (LinkList)malloc(sizeof(Node)); 
	s->data = e;  
	s->next = p->next;      /* 将p的后继结点赋值给s的后继  */
	p->next = s;          /* 将s赋值给p的后继 */
	return OK;
}
Status ListDelete(LinkList *L,int i,ElemType &e)
{
	int j;
	LinkList p,q;
	p = *L;
	j = 0;
	while (p->next && j < i-1)	/* 寻找前驱，即第i-1个元素 */
	{
        p = p->next;
        ++j;
	}
	if (!(p->next) || j > i) 
	    return ERROR;           /* 第i个元素不存在 */
	q = p->next;
	p->next = q->next;			/* 将q的后继赋值给p的后继 */
	e = q->data;               /* 将q结点中的数据给e */
	free(q);                    /* 让系统回收此结点，释放内存 */
	return OK;
}
void ListTraverse(LinkList L)
{
	LinkList p=L->next;  
    while(p)  
    {  
        printf("%d ",p->data); 
        p=p->next; 
    }    
}
int main()
{
	LinkList L;//ͷָ???
	LinkList *LL=&L; 
	InitList(LL);
	int e;
	printf("%d",ListInsert(LL,1,1));
	printf("%d",ListInsert(LL,2,2));
	printf("%d",ListInsert(LL,3,3));
	printf("%d",ListInsert(LL,4,4));
}