/*ÉèÓĞÒ»¸öË«ÏòÑ­»·Á´±í£¬Ã¿¸ö½áµãÖĞ³ıÓĞpre£¬dataºÍnextÈı¸öÓòÍâ£¬»¹ÔöÉèÁËÒ»¸ö·ÃÎÊÆµ¶ÈÓòfreq¡£
ÔÚÁ´±í±»Æğ×÷ÓÃÇ°£¬Æµ¶ÈÓòfreqµÄÖµ¾ù³õÊ¼»¯ÎªÁã£¬
¶øµ±¶ÔÁ´±í½øĞĞÒ»´ÎLOCATE(L,x)µÄ²Ù×÷Ö®ºó£¬
±»·ÃÎÊµÄ½áµã£¨¼´ÔªËØÖµµÈÓÚxµÄ½Úµã£©ÖĞµÄÆµ¶ÈÓòfreqµÄÖµ±ãÔö1£¬
Í¬Ê±µ÷ÕûÁ´±íÖĞ½áµãÖ®¼äµÄ´ÎĞò£¬Ê¹Æä°´·ÃÎÊÆµ¶È·ÇµİÔöµÄË³ĞòÅÅÁĞ£¬
ÒÔ±ãÊ¼ÖÕ±£³Ö±»Æµ·±·ÃÎÊµÄ½áµã×ÜÊÇ¿¿½ü±íÍ·½áµã¡£*/ 
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
# define N 10
typedef int ElemType;
typedef int Status;
typedef struct Node
{
    ElemType data;
    struct Node *next;
    struct Node *pre;
    int freq;
}Node;
typedef struct Node *LinkList; 
Status InitList(LinkList &L) 
{ 
    L=(LinkList)malloc(sizeof(Node)); /* äº§ç”Ÿå¤´ç»“ç‚¹,å¹¶ä½¿LæŒ‡å‘æ­¤å¤´ç»“ç‚¹ */
    if(L==NULL) /* å­˜å‚¨åˆ†é…å¤±è´¥ */
            return ERROR;
    L->next=L->pre=L; 
    L->freq = 0;
    return OK;
}
void creatList(LinkList &L)
{
	int i;
	InitList(L);
	LinkList p;
	for (i = N-1; i>=0; i--)
	{
		p = (LinkList)malloc(sizeof(Node));
		p->data = i;
		p->freq = 0;
		p->next = L->next;
		L->next->pre = p;
		p->pre = L;
		L->next = p;
	}
}
void ListTraverse(LinkList L)
{
	LinkList p=L->next;  
    while(p!=L)  
    {  
        printf("%d ",p->data); 
        p=p->next; 
    }    
}
Status LOCATE(LinkList &L,int x)
{
	LinkList p,q;
	p = L->next;
	q = L->next;
	while(p->data!=x&&p!=L)
		p = p->next;
	if(p == L)
		return ERROR;
	else
	{
		p->freq++;
		while(q!=L&&q->freq>=p->freq)
			q = q->next;
		if(q!=p->next)
		{
			p->pre->next = p->next;
			p->next->pre = p->pre;
			p->pre = q->pre;
			q->pre->next = p;
			q->pre = p;
			p->next = q;	
		} 	
	} 
	return OK; 
}
int main()
{
	LinkList L;
	creatList(L);
	LOCATE(L,3);
	ListTraverse(L);
}
