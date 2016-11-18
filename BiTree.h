#include <iostream>
#include <stdlib.h>
#include <stack>
using namespace std;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef char ElemType;
typedef int Status;
typedef struct BiTNode
{
	ElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;
typedef struct
{	
	BiTree ptr; 
	bool tag;		//0为左子数 1为右子树 
}stacknode;
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
	stack<BiTree> s;
	BiTree p;
	p = T;
	while(p != NULL||!s.empty())
	{
		while(p != NULL)
		{
			printf("%c ", p->data);
			s.push(p);
			p = p->lchild;
		}
		if(!s.empty())
		{
			p = s.top();
			s.pop();
			p = p->rchild;
		}
	}
}
void InOrderTraverse(BiTree T)
{
	stack<BiTree> s;
	BiTree p;
	p = T;
	while(p != NULL||!s.empty())
	{
		while(p != NULL)
		{
			s.push(p);
			p = p->lchild;
		}
		if(!s.empty())
		{
			p = s.top();
			s.pop();
			printf("%c ", p->data);
			p = p->rchild;
		}
	}
}
void PostOrderTraverse(BiTree T)
{
	stacknode x;
	stack<stacknode> s;
	BiTree p;
	p = T;
	do
	{
		while(p != NULL)
		{
			x.ptr = p;
			x.tag = 0;
			s.push(x);
			p = p->lchild;
		}
		while(!s.empty() && s.top().tag == 1)
		{
			x.ptr = s.top().ptr;
			x.tag = s.top().tag;
			s.pop();
			p = x.ptr;
			printf("%c ",p->data);
		}
		if(!s.empty())
		{
			s.top().tag = 1;
			p = s.top().ptr->rchild;
		}
	}while(!s.empty());
}
void PreOrderTraverse_recursion(BiTree T)
{
	if(T!=NULL)
    {
        printf("%c ",T->data);
        PreOrderTraverse_recursion(T->lchild);
        PreOrderTraverse_recursion(T->rchild);
    }
}
void InOrderTraverse_recursion(BiTree T)      //递归中序遍历
{
    if(T!=NULL)
    {
        InOrderTraverse_recursion(T->lchild);
        printf("%c ",T->data);
        InOrderTraverse_recursion(T->rchild);
    }
}
void PostOrderTraverse_recursion(BiTree T)    //递归后序遍历
{
    if(T!=NULL)
    {
        PostOrderTraverse_recursion(T->lchild);
        PostOrderTraverse_recursion(T->rchild);
        printf("%c ",T->data); 
    }    
} 
int main()
{
	BiTree T;
	CreateBiTree(T);
	PreOrderTraverse(T);
	printf("\n");
	PreOrderTraverse_recursion(T);
	printf("\n");
	InOrderTraverse(T);
	printf("\n");
	InOrderTraverse_recursion(T);
	printf("\n");
	PostOrderTraverse(T);
	printf("\n");
	PostOrderTraverse_recursion(T);
	return 0;
}
//ABC  DE G  F   
