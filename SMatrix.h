#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 12500
#define MAXRC 150
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int ElemType;
typedef int Status;
typedef struct
{
	int i,j;
	ElemType e;
}Triple;
typedef struct{
	Triple data[MAXSIZE+1];	//data[0]弃用
	int rpos[MAXRC+1];		//各行第一个非零元的位置表
	int mu,nu,tu;			//矩阵的行数，列数，非零元个数
}TSMatrix;
Status TransposeSMatrix(TSMatrix M, TSMatrix &T)
{
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	if (T.tu)
	{
		int q = 1,col,p;
		for (col = 1; col <= M.nu; ++col)
		{
			for (p = 1; p <= M.tu; ++p)
			{
				if (M.data[p].j == col)
				{
					T.data[q].i = M.data[p].j;
					T.data[q].j = M.data[p].i;
					T.data[q].e = M.data[p].e;
					q++;
				}
			}
		}
		return OK;
	}
	else 
		return FALSE;
}
Status FsatTransposeSMatrix(TSMatrix M, TSMatrix &T)
{
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	int num[T.nu];
	int cpot[T.nu];
	if (T.tu)
	{
		int p,q,t,col;
		for (col = 1; col <= M.nu; col++)
			num[col] = 0;
		for (t = 1; t <= M.tu; t++)
			num[M.data[t].j]++;
		cpot[1] = 1;
		for (col = 2; col <= M.nu; col++)
			cpot[col] = cpot[col-1] + num[col-1];
		for (p = 1; p <= M.tu; p++)
		{
			col = M.data[p].j;
			q = cpot[col];
			T.data[q].i = M.data[p].j;
			T.data[q].j = M.data[p].i;
			T.data[q].e = M.data[p].e;
			cpot[col]++;
		}
		return OK;
	}
	else
		return FALSE;
}
Status MultSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q)
{
	int arow,brow,p,q,ccol,t;
	int ctemp[N.nu];
	if(M.nu != N.nu)
		return ERROR;
	Q.mu = M.mu;
	Q.nu = N.nu;
	Q.tu = 0;
	if(M.tu * N.tu != 0)		//Q是非零矩阵
	{
		for (arow = 1; arow <= M.mu; ++arow)	//处理M的每一行
		{
			ctemp[N.nu] = 0;						//当前行各元素累积器清零
			Q.rpos[arow] = Q.tu + 1;
			for(p = M.rpos[arow]; p < M.rpos[arow+1]; p++)//对当前行的每一个非零元素
			{
				brow = M.data[p].j;						//找到对应元在N中的行号
				if(brow < N.nu)
					t = N.rpos[brow+1];
				else
					t = N.tu + 1;
			}
			for(q = N.rpos[brow]; q < t; q++)			
			{
				ccol = N.data[q].j;						//乘积在Q中的列号
				ctemp[ccol] += M.data[p].e * N.data[q].e;
			}
			for(ccol = 1; ccol < Q.nu; ccol++)
			{
				if(ctemp[ccol])
				{
					if(++Q.tu > MAXSIZE)
						return ERROR;
					Q.data[Q.tu].i = arow;
					Q.data[Q.tu].j = ccol;
					Q.data[Q.tu].e = ctemp[ccol];
				}
			}
		}
	}
}
