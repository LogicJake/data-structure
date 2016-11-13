#include<iostream>
#include<stdlib.h>
#include<stack>
using namespace std;
typedef char ElemType;
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
			cout<<p->data;
		}
		if(!s.empty())
		{
			s.top().tag = 1;
			p = s.top().ptr->rchild;
		}
	}while(!s.empty());
}
void CreateBiTree(BiTree &T)
{
	char ch;
	scanf("%c",&ch);
	if(ch == ' ')
		T = NULL;
	else
	{
		if(!(T = (BiTNode *)malloc(sizeof(BiTNode))))
			exit(0);
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}
int main()
{
	BiTree T;
	CreateBiTree(T);
	PostOrderTraverse(T);
}
