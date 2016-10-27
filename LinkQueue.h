#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
# define INFEASIBLE -1
# define OVERFLOW -2
typedef int ElemType;
typedef int Status;
typedef struct QNode
{
	ElemType data;
	struct QNode *next;
}QNode,* QueuePtr;
typedef struct
{
	QueuePtr front;	//队头指针
	QueuePtr rear;	//队尾指针
}LinkQueue;
Status InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front)
		exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}
Status DestroyQueue(LinkQueue &Q)
{
	while(Q.front)
	{
		Q.rear = Q.front->next;
		free (Q.front); 
		Q.front = Q.rear;
	}
	return OK;
}
Status ClearQueue(LinkQueue &Q)
{
	QueuePtr p,q;
	p = Q.front->next;
	while(p)
	{
		q = p->next;
		free (p);
		p = q;
	}
	Q.rear = Q.front;
}
Status QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}
int QueueLength(LinkQueue Q)
{
	QueuePtr p;
	int i = 0;
	p = Q.front->next;
	while(p)
	{
		i++;
		p = p->next;
	}
	return i;
}
Status GetHead(LinkQueue Q, ElemType &e)
{
	if (!QueueEmpty(Q))
	{
		Q.front = Q.front->next;
		e = Q.front->data;
		return OK;
	}
	else
		return ERROR;
}
Status EnQueue(LinkQueue &Q, ElemType e)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}
Status DeQueue(LinkQueue &Q, ElemType &e)
{
	QueuePtr p;
	if (Q.front == Q.rear)
		return ERROR;
	else
	{
		p = Q.front->next;
		e = p->data;
		Q.front->next = p->next;
		if (Q.rear == p)	//出队结点为队尾结点
			Q.rear = Q.front;
		free (p);
		return OK;
	}
}
Status QueueTraverse(LinkQueue Q)
{
	QueuePtr p;
	p = Q.front->next;
	while(p)
	{
		printf("%d ",p->data);
		p = p->next;
	}
}
