//循环队列
# include<stdio.h>
# include<stdlib.h>
# define TRUE 1
# define FALSE 0
# define OK 1
# define ERROR 0
# define INFEASIBLE -1
# define OVERFLOW -2
# define MAXSIZE 100 
typedef int ElemType;
typedef struct{
    int *base;
    int front;
    int rear;
}SqQueue;
void InitQueue(SqQueue &Q)
{
    Q.base = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));
    if(!Q.base)
        exit(OVERFLOW);
    Q.front = Q.rear = 0;
}
int QueueLength(SqQueue Q)
{
    return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}
int EnQueue(SqQueue &Q, ElemType e)
{
    if ((Q.rear + 1) % MAXSIZE == Q.front)//队列头的指针在队列尾指针的下一个位置视为队列满
        return ERROR;
    else
    {
        Q.base[Q.rear] = e;
        Q.rear = (Q.rear + 1) % MAXSIZE;
        return OK; 
    }   
}
int DeQueue(SqQueue &Q, ElemType &e)
{
    if (Q.rear == Q.front)
        return ERROR;
    else
    {
        e = Q.base[Q.front];
        Q.front = (Q.front + 1) % MAXSIZE;
        return OK;   
    } 
}
