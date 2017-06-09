/*
设计并验证如下算法：图采用邻接矩阵表示，实现无向图的深度优先搜索与有向图的广度优先搜索。
#define INFINTY INT_MAX //图的数组（邻接矩阵）存储表示
#define MAX_VERTEX_NUM 20
typedef enum {DG,DN,AG,AN}Graphkind;//{有向图，有向网，无向图，无向网}
typedef struct AreCell{
VRType adj;//VRType 是顶点关系类型。对无权图，用0或1表示相邻与否；对带权图，则为权值类型。
InfoType * info;//该弧相关信息指针
}Arecell,AdjMatrix[MAX_VERTEX_NUM][ MAX_VERTEX_NUM];
Typedef struct{
VertexType vexs[MAX_VERTEX_NUM];//顶点向量
AdjMatrix arcs;  //邻接矩阵
Int vexnum,arcnum;  //图的当前顶点数和弧数
Graphkind kind;  //图的种类标志
}Mgraph;
*/
#include "stdafx.h"
#include<stdio.h>
#include <limits.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include<conio.h>
#define MAXQSIZE 200
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
#define VRType int
#define InfoType char
#define VertexType char
bool visited[MAX_VERTEX_NUM];
typedef enum { DG, AG }Graphkind;
typedef struct AreCell {
	VRType adj;
	InfoType * info;
}AreCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct {
	VertexType  vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum, arcnum;
	Graphkind kind;
}GraphMap;
//定义队列的结构体
typedef struct {
	int * base;
	int front;
	int rear;
}SqQueue;
//初始化队列
void InitQueue(SqQueue * Q) {
	Q->base = (int *)malloc(MAXQSIZE * sizeof(int));
	if (!Q->base) exit(-1);
	Q->front = Q->rear = 0;
}
//进队列
void EnQueue(SqQueue * Q, int e) {
	if ((Q->rear + 1) % MAXQSIZE == Q->front)  return;
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
}
//出队列
void DeQueue(SqQueue * Q, int * e) {
	if (Q->rear == Q->front)  return;
	*e = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXQSIZE;
}
//判断队列是否为空
int QueueEmpty(SqQueue * Q) {
	if (Q->front == Q->rear)
		return 1;
	else
		return 0;
}
//定位操作
int Locate(GraphMap G, VertexType v) {
	int i;
	for (i = 0;i < G.vexnum;i++)
		if (G.vexs[i] == v)
			break;
	return i - 1;
}
//创建图 
void Create(GraphMap * G, int m) {
	int i, j, k;
	VRType w;
	VertexType v1, v2;
	if (m == 1)
		G->kind = AG;
	else
		G->kind = DG;
	printf("请输入图的顶点的数目和弧数目:\n");
	scanf("%d %d", &G->vexnum, &G->arcnum);
	printf("请输入顶点（按照顺序):\n");
	for (i = 0;i < G->vexnum;i++) {
		scanf("%c", &G->vexs[i]);
		if (G->vexs[i] == '\n')
			i--;
	}
	for (i = 0;i < G->vexnum;i++)
		for (j = 0;j < G->vexnum;j++) {
			G->arcs[i][j].adj = INFINITY;
			G->arcs[i][j].info = NULL;
		}
	printf("弧对应的点的联系:\n");
	for (k = 0;k < G->arcnum;k++) {
		scanf("%c",&v1);
		while (v1 == '\n'||v1 == ' ') {
			scanf("%c", &v1);
		}
		scanf("%c",&v2);
		while (v2 == '\n'||v2==' ') {
			scanf("%c", &v2);
		}
		scanf("%d",&w);
		i = Locate(*G, v1);
		j = Locate(*G, v2);
		G->arcs[i][j].adj = w;
		if (G->kind == AG)
			G->arcs[j][i].adj = G->arcs[i][j].adj;
	}
}
void DFS(GraphMap G, int v) {
	int j;
	printf("%c ", G.vexs[v]);
	visited[v] = true;
	for (j = 0;j < G.vexnum;j++)
		if (G.arcs[v][j].adj == 1 && !visited[j]) {
			v = j;
			break;
		}
	if (!visited[v])
		DFS(G, v);
}
//无向图的深度遍历
void DFSTraverse(GraphMap G) {
	VertexType V;
	for (int i = 0;i < G.vexnum;i++)
		visited[i] = false;
	for (int i = 0;i < G.vexnum;i++)
		if (!visited[i])
			DFS(G, i);
}
//有向图的广度遍历
void BFSTraverse(GraphMap G) {
	int v;
	int u;
	SqQueue Q;
	for (v = 0;v < G.vexnum;v++)
		visited[v] = false;
	InitQueue(&Q);
	for (v = 0;v < G.vexnum;v++) {
		if (!visited[v])
			visited[v] = true;
		printf("%c ", G.vexs[v]);
		EnQueue(&Q, v);
		while (!QueueEmpty(&Q)) {
			DeQueue(&Q, &u);
			for (int j = 0;j < G.vexnum;j++)
				if (G.arcs[v][j].adj == 1) {
					visited[j] = true;
					printf("%c ", G.vexs[j]);
					EnQueue(&Q, j);
				}
		}
	}
}
int main()
{
	GraphMap G1, G2;
	printf("输入无向图(每次输入一个数据都需要回车)\n");
	Create(&G1, 2);//创建无向图
	printf("无向图深度遍历：\n");
	BFSTraverse(G1);
	printf("\n输入有向图(每次输入一个数据都需要回车):\n");
	Create(&G2, 1);//创建有向图
	printf("有向图广度遍历：\n");
	DFSTraverse(G2);
	return 0;
}

