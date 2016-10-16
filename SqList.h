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
# define LIST_INIT_SIZE 100
# define LISTINCREMENT 10
typedef int ElemType;
typedef int Status;
typedef struct 
{
	ElemType *elem;
	int length;
	int listsize;
}SqList;
void InitList(SqList &L)
{
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	memset(L.elem,0,sizeof(ElemType)*LIST_INIT_SIZE);	//初始化为0
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
}
void DestroyList(SqList &L)
{
	free (L.elem);
}
void ClearList(SqList &L)
{
	L.length = 0;
}
Status ListEmpty(SqList L)
{
	if (L.length == 0)
		return TRUE;
	else
		return FALSE;
}
int ListLength(SqList L)
{
	return L.length;
}
Status GetElem(SqList L,int i,ElemType &e)
{
	//判断元素位置是否合法
    if(i > L.length-1 || i < 0){
        printf("查找的位置不正确 \n");
        return ERROR; 
    }
    //判断线性表是否为空
    if(ListEmpty(L)){
        return ERROR;
    } 
	e = L.elem[i];
	return OK;
}
Status LocateElem(SqList L,ElemType e)
{
	int i = 0;
	ElemType *p = L.elem;
	while(i<L.length)
	{
		if (*p != e)
		{
			p++;
			i++;
		}
		else 
			break;
	}
	if (i<L.length)
		return i;
	else 
		return -1;
}
Status PriorElem(SqList L,ElemType cur_e,ElemType &pre_e)
{
	if (LocateElem(L,cur_e)!=-1&&LocateElem(L,cur_e)!=0)
	{
		pre_e = L.elem[LocateElem(L,cur_e)-1];
		return OK;
	}
	else 
		return ERROR;
}
Status NextElem(SqList L,ElemType cur_e,ElemType &next_e)
{
	if (LocateElem(L,cur_e)!=-1&&LocateElem(L,cur_e)!=L.length-1)
	{
		next_e = L.elem[LocateElem(L,cur_e)+1];
		return OK;
	}
	else 
		return ERROR;
}
Status ListInsert(SqList &L,int i,ElemType e)
{

	if (i>0&&i<L.length+1)
	{

		if (L.length == L.listsize)
		{
			ElemType *newbase = (ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof (ElemType));
    		if (!newbase) exit(OVERFLOW);  // 存储分配失败           
    		L.elem = newbase;                // 新基址
   			L.listsize += LISTINCREMENT; // 增加存储容量
		}
		ElemType *q = &(L.elem[i]);
		for (ElemType *p = &(L.elem[L.length-1]);p>=q;p--)
		{
			*(p+1)=*p;
		}
		*q=e;
		L.length++;
		return OK;
	}
	else 
		return ERROR;
}
Status ListInsert(SqList &L,ElemType e)
{
	int i,j;
	for (j = 0; j < L.length; ++j)
	{
		if(L.elem[j]>=e)
		{
			i=j;
			break;
		}
	}
		if (L.length == L.listsize)
		{
			ElemType *newbase = (ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof (ElemType));
    		if (!newbase) exit(OVERFLOW);  // 存储分配失败           
    		L.elem = newbase;                // 新基址
   			L.listsize += LISTINCREMENT; // 增加存储容量
		}
		ElemType *q = &(L.elem[i]);
		for (ElemType *p = &(L.elem[L.length-1]);p>=q;p--)
		{
			*(p+1)=*p;
		}
		*q=e;
		L.length++;
		return OK;	
}
Status ListDelete(SqList &L,int i,ElemType &e)
{

	if (i>0&&i<L.length)
	{
		ElemType *q = &(L.elem[i]);
		e = *q;
		ElemType *p = &(L.elem[L.length-1]); 
		for(;q<p;q++)
		{
			*q=*(q+1);
		}
		L.length--;
		return OK;
	}
	else 
		return ERROR;
}
void ListTraverse(SqList L)
{
	for (int i = 0; i <L.length;i++)
		printf("%d ",L.elem[i]);
}
Status createList(SqList &L)
{
    int i;
  	InitList(L);
    for(i = 0; i < 10; i++){
        L.elem[i] = i;
    } 
    L.length = 10;
    return OK;
} 
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
Status DeleteK(SqList &a,int i,int k)
{
	if(i<1||k<0||i+k-1>a.length)
		return INFEASIBLE;
	int count;
	for ( count= 0; count < a.length-k; ++count)
	{
		a.elem[i-1+count] = a.elem[i-1+k+count];
	}
	a.length-=k;
}
