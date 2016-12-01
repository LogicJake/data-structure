//有向表 邻接表 
#include <iostream>
#include <stack> 
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
	int i,j,k;
	VertexType v1,v2;
	ArcNode *s;
	cin>>G.vexnum>>G.arcnum;
	for(i = 0; i < G.vexnum; i++)
	{
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}
	for(k = 0; k < G.arcnum; k++)
	{
		cin>>v1>>v2;
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		s = new ArcNode;
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
int main()
{
	ALGraph G;
	CreateGraph(G);
	PRINT(G);
	TopologicalSort(G);
 } 
 /*
4 4
1 2 3 4
1 2
1 3
3 4
4 1
 */
