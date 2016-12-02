//邻接表 
#include <iostream>
#include <stack> 
#include <string.h>
using namespace std;
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
typedef int VertexType;
typedef int VRType;
typedef int Status;
typedef struct ArcNode{
	int adjvex;
	struct ArcNode *nextarc;
	int info;		//存储弧长； 
}ArcNode;
typedef struct VNode{
	VertexType data;
	ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;	//邻接表 
	int vexnum,arcnum;
}ALGraph;
int LocateVex(ALGraph G, VertexType v1)
{
	for(int i = 0; i < G.vexnum; i++)
	{
		if(G.vertices[i].data == v1)
			return i;
	}
}
Status CreateGraph(ALGraph &G)
{
	int i,j,k,value;
	char choice;
	VertexType v1,v2;
	ArcNode *s;
	cout<<"是否有权？(y or n)";
	cin>>choice;
	cin>>G.vexnum>>G.arcnum;
	for(i = 0; i < G.vexnum; i++)
	{
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}
	for(k = 0; k < G.arcnum; k++)
	{
		if(choice == 'y')	//有权 
			cin>>v1>>v2>>value;
		else
			cin>>v1>>v2;
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		s = new ArcNode;
		s->info = value;
		s->adjvex = j;
		s->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = s;
	}
 } 
void PRINT(ALGraph G)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        printf("vertex:%d", G.vertices[i].data);
        ArcNode *p = G.vertices[i].firstarc;
        while (p)
        {
            printf("→%d", G.vertices[p->adjvex].data);
            p = p->nextarc;
        }
        printf("\n");
    }
}

/**************拓扑排序***********************/ 
void FindInDegree(ALGraph G,int *indegree)
{
	int i;
	ArcNode *p;
	for(i = 0; i < G.vexnum; i++)
		indegree[i] = 0;
	for(i = 0; i < G.vexnum; i++)
	{
		p = G.vertices[i].firstarc;
        while (p)
        {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
	}
}
Status TopologicalSort(ALGraph &G)		//如果可以拓扑排序 说明不存在环 
{
	int indegree[G.vexnum];
	int i,k;
	ArcNode *p; 
	FindInDegree(G,indegree);
 	stack<int> s;
 	for(i = 0; i < G.vexnum; i++)
 		if(!indegree[i])
 			s.push(i);
 	int count = 0;
 	while(!s.empty())
 	{
 		i = s.top();
 		s.pop();
 		cout<<G.vertices[i].data<<" ";
 		count++;
 		for(p = G.vertices[i].firstarc; p; p = p->nextarc)
 		{
 			k = p->adjvex;
			if(!(--indegree[k]))
				s.push(k);	
		 }		
	 }
	if(count < G.vexnum)
		return ERROR;
	else
		return OK;
} 

/******************改造拓扑排序求关键路径**********************************/
stack<int> T;	//T为拓扑序列顶点栈，s为0入度顶点栈 
int ve[MAX_VERTEX_NUM]; 	//全局变量，各顶点事件的最早发生时间 
Status TopologicalOrder(ALGraph &G, stack<int> &T)
{
	int indegree[G.vexnum];
	int i,k;
	ArcNode *p; 
	FindInDegree(G,indegree);
	memset(ve,0,G.vexnum*sizeof(int));
 	stack<int> s;
 	for(i = 0; i < G.vexnum; i++)
 		if(!indegree[i])
 			s.push(i);
 	int count = 0;
 	while(!s.empty())
 	{
 		i = s.top();
 		s.pop();
 		T.push(i); 
 		count++;
 		for(p = G.vertices[i].firstarc; p; p = p->nextarc)
 		{
 			k = p->adjvex;
			if(!(--indegree[k]))
				s.push(k);	
			if(ve[i]+(p->info) > ve[k])
				ve[k] = ve[i]+(p->info);
		 }		
	 }
	if(count < G.vexnum)
		return ERROR;
	else
		return OK;
}
Status CriticalPath(ALGraph G)
{
	int i,j,k,dut,ee,el;
	char tag;
	ArcNode *p;
	if(!TopologicalOrder(G,T))
		return ERROR;
	int vl[G.vexnum];
	for(i = 0; i < G.vexnum-1; i++)
		vl[i] = INT_MAX;
	vl[G.vexnum-1] = ve[G.vexnum-1];
	while(!T.empty())	//按拓扑逆排序求各顶点vl值 
	{
		for(j = T.top(),T.pop(),p = G.vertices[j].firstarc; p; p = p->nextarc) 
		{
			k = p->adjvex;
			dut = p->info;
			if(vl[k] - dut < vl[j])
				vl[j] = vl[k] - dut;
		}
	}
	cout<<"关键路径："<<endl; 
	for(j = 0; j < G.vexnum; j++)
	{
		for(p = G.vertices[j].firstarc; p; p = p->nextarc)
		{
			k = p->adjvex;
			dut = p->info;
			ee = ve[j];
			el = vl[k] - dut;
			tag = (ee == el)?'*':' ';
			if(tag == '*')
				cout<<G.vertices[j].data<<" "<<G.vertices[k].data<<" "<<dut<<" "<<ee<<" "<<el<<" "<<endl; 
		}
	}
}
int main()
{
	ALGraph G;
	CreateGraph(G);
	PRINT(G);
//	TopologicalSort(G);
	CriticalPath(G);
 } 
/*测试数据 
9 11
1 2 3 4 5 6 7 8 9
1 2 6
1 3 4
1 4 5
2 5 1
3 5 1
4 6 2
5 7 9
5 8 7
6 8 4
7 9 2
8 9 4

6 8
1 2 3 4 5 6
1 2 3
1 3 2
2 4 2
2 5 3
3 4 4
3 6 3
4 6 2
5 6 1
 */
