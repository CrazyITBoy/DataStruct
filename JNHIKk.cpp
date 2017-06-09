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
//������еĽṹ��
typedef struct {
	int * base;
	int front;
	int rear;
}SqQueue;
//��ʼ������
void InitQueue(SqQueue * Q) {
	Q->base = (int *)malloc(MAXQSIZE * sizeof(int));
	if (!Q->base) exit(-1);
	Q->front = Q->rear = 0;
}
//������
void EnQueue(SqQueue * Q, int e) {
	if ((Q->rear + 1) % MAXQSIZE == Q->front)  return;
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
}
//������
void DeQueue(SqQueue * Q, int * e) {
	if (Q->rear == Q->front)  return;
	*e = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXQSIZE;
}
//�ж϶����Ƿ�Ϊ��
int QueueEmpty(SqQueue * Q) {
	if (Q->front == Q->rear)
		return 1;
	else
		return 0;
}
//��λ����
int Locate(GraphMap G, VertexType v) {
	int i;
	for (i = 0;i < G.vexnum;i++)
		if (G.vexs[i] == v)
			break;
	return i - 1;
}
//����ͼ 
void Create(GraphMap * G, int m) {
	int i, j, k;
	VRType w;
	VertexType v1, v2;
	if (m == 1)
		G->kind = AG;
	else
		G->kind = DG;
	printf("������ͼ�Ķ������Ŀ�ͻ���Ŀ:\n");
	scanf("%d %d", &G->vexnum, &G->arcnum);
	printf("�����붥�㣨����˳��):\n");
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
	printf("����Ӧ�ĵ����ϵ:\n");
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
//����ͼ����ȱ���
void DFSTraverse(GraphMap G) {
	VertexType V;
	for (int i = 0;i < G.vexnum;i++)
		visited[i] = false;
	for (int i = 0;i < G.vexnum;i++)
		if (!visited[i])
			DFS(G, i);
}
//����ͼ�Ĺ�ȱ���
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
	printf("��������ͼ(ÿ������һ�����ݶ���Ҫ�س�)\n");
	Create(&G1, 2);//��������ͼ
	printf("����ͼ��ȱ�����\n");
	BFSTraverse(G1);
	printf("\n��������ͼ(ÿ������һ�����ݶ���Ҫ�س�):\n");
	Create(&G2, 1);//��������ͼ
	printf("����ͼ��ȱ�����\n");
	DFSTraverse(G2);
	return 0;
}

