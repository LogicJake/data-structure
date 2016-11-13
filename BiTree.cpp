#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 12500
#define MAXRC 150
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef char ElemType;
typedef int Status;
typedef struct BiTNode
{
	ElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;
typedef BiTree SElemType;
typedef struct 
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;
Status InitStack(SqStack &S)
{
	S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base)
		exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}
Status StackEmpty(SqStack S)
{
	if (S.base&&S.top == S.base)
		return TRUE;
	else
		return FALSE;
}
Status Push(SqStack &S, SElemType e)
{
	if (S.top - S.base >= S.stacksize)
	{
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT)*sizeof(SElemType));
		if (!S.base)
			exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top = e;
	S.top++;
	return OK;
}
Status Pop(SqStack &S, SElemType &e)
{
	if (S.top == S.base)
		return ERROR;
	else
	{
		S.top--;
		e = *(S.top);
		return OK;
	}
}
Status CreateBiTree(BiTree &T)
{
	char ch;
	scanf("%c",&ch);
	if(ch == ' ')
		T = NULL;
	else
	{
		if(!(T = (BiTNode *)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;
}
void PreOrderTraverse(BiTree T)
{
	SqStack s;
	InitStack(s);
	BiTree p;
	p = T;
	while(p != NULL||!StackEmpty(s))
	{
		while(p != NULL)
		{
			printf("%c ", p->data);
			Push(s,p);
			p = p->lchild;
		}
		if(!StackEmpty(s))
		{
			Pop(s,p);
			p = p->rchild;
		}
	}
}
void InOrderTraverse(BiTree T)
{
	SqStack s;
	InitStack(s);
	BiTree p;
	p = T;
	while(p != NULL||!StackEmpty(s))
	{
		while(p != NULL)
		{
			Push(s,p);
			p = p->lchild;
		}
		if(!StackEmpty(s))
		{
			Pop(s,p);
			printf("%c ", p->data);
			p = p->rchild;
		}
	}
}
Status LevelOrderTraverse(BiTree T)
{
	
}
int main()
{
	BiTree T;
	CreateBiTree(T);
	PreOrderTraverse(T);
	printf("\n");
	InOrderTraverse(T);
	return 0;
}
//ABC  DE G  F   
