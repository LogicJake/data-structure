#include <iostream>
#include <stdlib.h>
#include <stack>
#include <queue> 
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
int BiTreeDepth(BiTree &T)			//求树的深度 
{
	if(T == NULL)
		return 0;
	else
	{
		int lDepth,rDepth;
		lDepth = BiTreeDepth(T->lchild);
		rDepth = BiTreeDepth(T->rchild);
		if(lDepth > rDepth)
			return lDepth + 1;
		else
			return rDepth + 1;
	 } 
}
int BiTreeWidth(BiTree &T)
{
	if(T == NULL)
		return 0;
	int nLastLevelWidth = 0;//记录上一层的宽度  
    int nTempLastLevelWidth = 0;  
    int nCurLevelWidth = 0;//记录当前层的宽度  
    int nWidth = 1;//二叉树的宽度  
    BiTree cur;
    queue<BiTree> q;  
    q.push(T);
    nLastLevelWidth = 1;
    nWidth = 1;
    while(!q.empty())
    {
   		nTempLastLevelWidth = nLastLevelWidth;  
        while (nTempLastLevelWidth != 0)  
        {  
            cur = q.front();//取出队列头元素  
            q.pop();		//将队列头元素出对  
            if (cur->lchild != NULL)  
            {  
                q.push(cur->lchild);  
            }  
            if (cur->rchild != NULL)  
            {  
                q.push(cur->rchild);  
            }  
            nTempLastLevelWidth--;  
        }  
        nCurLevelWidth = q.size();  
        nWidth = nCurLevelWidth > nWidth ? nCurLevelWidth : nWidth;  
        nLastLevelWidth = nCurLevelWidth;  
    }  
    return nWidth;  
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
	while(p)
	{
		x.ptr = p;
		x.tag = 0;
		s.push(x);
		p = p->lchild;
	}
	while(!s.empty()){
		x = s.top();
		if(x.ptr->rchild == NULL||x.tag == 1){	//没有右子树或者右子树已经访问过 
			s.pop();
			printf("%c ",x.ptr->data);
		}
		else{
			s.top().tag = 1;
			p = x.ptr->rchild;
			while(p)
			{
				x.ptr = p;
				x.tag = 0;
				s.push(x);
				p = p->lchild;
			 } 
		}
	}
}
void LevelOrderTraverse(BiTree T)		//层次遍历 
{
	BiTree p;
    p = T;
    if (!T) {
        return;
    }
    queue<BiTree> Q; 
    Q.push(p);
    while (!Q.empty()) {
        p = Q.front();
        Q.pop();
        printf("%c ",p->data);
        if (p->lchild)
        	Q.push(p->lchild);
        if (p->rchild)
        	Q.push(p->rchild);
    }
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
int LeafNode(BiTree T)							//求叶子结点个数
{
	if(T == NULL)
		return 0;
	if(T->lchild == NULL && T->rchild == NULL) 
		return 1;
	return LeafNode(T->lchild) + LeafNode(T->rchild);
}
void exchange(BiTree T)							//交换左右子树 
{
	BiTree temp = NULL;
 	if(T->lchild == NULL && T->rchild == NULL)
        return;
 	else{
       temp = T->lchild;
       T->lchild = T->rchild;
       T->rchild = temp;
 	}
 	if(T->lchild)
      	exchange(T->lchild);
 	if(T->rchild)
      	exchange(T->rchild);
}
Status IsCompleteBinaryTree(BiTree T) 
{
	bool flag = FALSE;
	BiTree p;
    p = T;
    if (!T) {
        return FALSE;
    }
    queue<BiTree> Q; 
    Q.push(p);
    while (!Q.empty()) {
    	if(flag == TRUE)
    	{
    		if(p->lchild != NULL || p->rchild != NULL)
    			return FALSE;
		}
        p = Q.front();
        Q.pop();
        if(p->lchild == NULL && p->rchild != NULL)
        	return FALSE;
        if((p->lchild != NULL && p->rchild == NULL) || (p->lchild == NULL && p->rchild == NULL))
        	flag = TRUE;
		if (p->lchild)
        	Q.push(p->lchild);
        if (p->rchild)
        	Q.push(p->rchild);
    }
    return TRUE;
}
void CopyTree(BiTree S,BiTree &T){
    if (!S) T=NULL;
    else{
    	BiTree lptr,rptr;
        CopyTree(S->lchild,lptr);//复制左子树到lptr
        CopyTree(S->rchild,rptr);//复制右子树到rptr
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data = S->data;
        T->lchild = lptr;
		T->rchild = rptr;
    }
}
//ABC  DE G  F   
