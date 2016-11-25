//无向带权网的基本操作
#include <iostream>
#include <queue> 
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
typedef struct AreCell
{
	VRType adj;
}AreCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{
	VertexType vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum,arcnum;
}MGraph;
int LocateVex(MGraph G, VertexType v1)
{
	for(int i = 0; i < G.vexnum; i++)
	{
		if(G.vexs[i] == v1)
			return i;
	}
}
Status CreateGraph(MGraph &G)
{
	int i,j,k;
	VertexType v1,v2;
	VRType value;
	cin>>G.vexnum>>G.arcnum;
	for(i = 0; i < G.vexnum; i++)
		cin>>G.vexs[i];
	for(i = 0; i < G.vexnum; i++)
	{
		for(j = 0; j < G.vexnum; j++)
			G.arcs[i][j].adj = INFINITY;
	}
	for(k = 0; k < G.arcnum; k++)
	{
		cin>>v1>>v2>>value;
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		G.arcs[i][j].adj = value;
		G.arcs[j][i].adj = G.arcs[i][j].adj;
	}
	return OK;
}
VertexType GetVex(MGraph G, int v)
{
	if(v >= G.vexnum)
		exit(0);
	return G.vexs[v];
}
Status PutVex(MGraph &G, int v, VertexType value)
{
	if(v < G.vexnum)
	{
		G.vexs[v] = value;
		return OK;
	}
	else
		return ERROR;
}
int FirstAdjvex(MGraph G, int v)
{
	int j;	
	for(j = 0; j < G.vexnum; j++) 
	{
		if(G.arcs[v][j].adj < INFINITY)
			return j;
	}
	return -1;
}
int NextAdjvex(MGraph G, int v, int w)
{
	int j;
	for(j = 0; j < G.vexnum; j++) 
	{
		if(G.arcs[v][j].adj < INFINITY && j > w)
			return j;
	}
	return -1;
}
Status InsertVex(MGraph &G, VertexType v)
{
	int i;
	G.vexs[G.vexnum] = v;
	G.vexnum++;
	for(i = 0; i < G.vexnum; i++)
	{
		G.arcs[G.vexnum-1][i].adj = INT_MAX;
		G.arcs[i][G.vexnum-1].adj = INT_MAX;
	}
	return OK;
}
Status DeleteVex(MGraph &G, VertexType v)
{
	int i,j;
	int Location = LocateVex(G,v);
	for (i = Location; i < G.vexnum - 1; ++i)
		G.vexs[i] = G.vexs[i+1];
	for(i = Location; i < G.vexnum - 1; i++)
	{
		for(j = 0; j < G.vexnum; j++)
			G.arcs[i][j].adj = G.arcs[i+1][j].adj;
	}
	for(i = 0; i < G.vexnum; i++)
	{
		for(j = Location; j < G.vexnum - 1; j++)
			G.arcs[i][j].adj = G.arcs[i][j+1].adj;
	}
	G.vexnum--;
}
Status InsertArc(MGraph &G, VertexType v, VertexType w, VRType value)
{
	int i = LocateVex(G,v);
	int j = LocateVex(G,w);
	G.arcs[i][j].adj = value;
	G.arcs[j][i].adj = G.arcs[i][j].adj;
	return OK;
}
Status DeleteArc(MGraph &G, VertexType v, VertexType w)
{
	int i = LocateVex(G,v);
	int j = LocateVex(G,w);
	G.arcs[i][j].adj = INT_MAX;
	G.arcs[j][i].adj = G.arcs[i][j].adj;
	return OK;
}
bool visited[MAX_VERTEX_NUM];
void DFS(MGraph G, int v)
{
	int w;
	VertexType v_vex = G.vexs[v];
	visited[v] = TRUE;
	cout<<G.vexs[v]<<" ";
	w = FirstAdjvex(G,v);
	for(w ; w > -1; w = NextAdjvex(G,v,w))
	{
		if(!visited[w])
			DFS(G,w);
	}
}
void DFSTraverse(MGraph G)
{
	int v;
	for(v = 0; v < G.vexnum; v++)
		visited[v] = FALSE;
	for(v = 0; v < G.vexnum; v++)
	if(!visited[v])
		DFS(G,v);
}
void BFSTraverse(MGraph G)
{
	int v;
	VertexType u,w;
	queue<VertexType> q;
	for(v = 0; v < G.vexnum; v++)
		visited[v] = FALSE;
	for(v = 0; v < G.vexnum; v++)
	{
		if (!visited[v])
		{
			visited[v] = TRUE;
			cout<<G.vexs[v]<<" ";
			q.push(v);
		}
		while(!q.empty())
		{
			u = q.front();
			q.pop();
			w = FirstAdjvex(G,u);
			for(w = FirstAdjvex(G,u); w > -1; w = NextAdjvex(G,u,w))
			{
				if(!visited[w])
				{
					visited[w] = TRUE;
					cout<<G.vexs[w]<<" ";
					q.push(w);
				}
			}
		}
	}
}
void PRINT(MGraph G)
{
 	int i,j;
 	for(i=0;i < G.vexnum;i++)
 	{
  		for(j=0;j< G.vexnum;j++)
  	 		printf("%15d",G.arcs[i][j]);
  		printf("\n");
 	}
}
int main()
{
	MGraph G;
	CreateGraph(G);
	PRINT(G);
//	DFSTraverse(G);
//	cout<<endl;
//	BFSTraverse(G);
//	printf("\n"); 
//	InsertVex(G,7);
//	InsertArc(G,1,3,2); 
//	printf("\n"); 
//	PRINT(G);
//	DeleteArc(G,1,3); 
//	printf("\n"); 
//	PRINT(G);
//	for(int i = 0; i < G.vexnum; i++)
//		cout<<G.vexs[i]<<" ";
//	DeleteVex(G,3);
//	printf("\n");
//	PRINT(G);
//	for(int i = 0; i < G.vexnum; i++)
//		cout<<G.vexs[i]<<" ";	
//	return 0;
 } 
/*测试数据 
6 5
1 2 3 4 5 6 
1 2 1
2 3 1
2 4 1
4 5 1
4 6 1
*/
