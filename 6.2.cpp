#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define MAX_VERTEX_NUM 20
#define infotype char
#define vertexType char
bool visited[MAX_VERTEX_NUM];
#define MAXQSIZE 20
typedef struct ArcNode {
	int adjvex;
	struct ArcNode * nextarc;
	infotype * info;
}ArcNode;
typedef struct VNode {
	vertexType data;
	ArcNode * firstarc;
}VNoed,AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
	int kind;
}ALGraph;
int Locate(ALGraph *G,char v) {
	int i;
	for (i = 0;i < G->vexnum;i++)
		if (G->vertices[i].data == v)
			break;
	return i;
}
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
//ͼ�Ĵ���
void create(ALGraph *G) {
	int i;
	char v;
	int location;
	ArcNode * p;
	printf("�����뻡�Ķ�����Ŀ�ͻ�����Ŀ:\n");
	scanf("%d %d",&G->vexnum,&G->arcnum);
	printf("�����붥�㣺\n");
	for (i = 0;i < G->vexnum;i++) {
		scanf("%c", &G->vertices[i].data);
			while (G->vertices[i].data == '\n' || G->vertices[i].data == ' ')
			scanf("%c", &G->vertices[i].data);
	}
	printf("������ÿ����������ڽӵ�,������#�Ž���:\n");
	for (i = 0;i < G->vexnum;i++) {
		G->vertices[i].firstarc = (ArcNode *)malloc(sizeof(ArcNode));
		G->vertices[i].firstarc->adjvex = NULL;
		scanf("%c", &v);
		while (v == '\n' || v == ' ')
			scanf("%c", &v);
		if (v == '#') G->vertices[i].firstarc = NULL;
		else {
			location = Locate(G, v);
			G->vertices[i].firstarc->adjvex = location;
			p = G->vertices[i].firstarc;
		}
		while (v != '#') {
			p->nextarc = (ArcNode *)malloc(sizeof(ArcNode));
			scanf("%c", &v);
			while (v == '\n' || v == ' ')
				scanf("%c", &v);
			if (v == '#') {
				p->nextarc = NULL;
				break;
			}
			    location = Locate(G, v); 
				p->nextarc->adjvex = location;
				p = p->nextarc;
		}
	}	
}

int FirstAdjVex(ALGraph G, int v) {
	if (!G.vertices[v].firstarc) {
		return -1;
	}
	else
	return G.vertices[v].firstarc->adjvex;
}
int nextAdjVex(ALGraph G, int v,int w){
	ArcNode * p;
	p = G.vertices[v].firstarc->nextarc;
	if (p == NULL)
		return -1;
	else
	while (p->nextarc != NULL && w != p->adjvex)
		p = p->nextarc;
	if (p->nextarc == NULL) return -1;
return p->adjvex;
}
//ͼ����ȱ���
void DFS(ALGraph G,int v) {
	int w;
	visited[v] = true;
	printf("%c ",G.vertices[v].data);
	for (w = FirstAdjVex(G,v);w>=0;w=nextAdjVex(G,v,w))
		if(!visited[w])
		DFS(G,w);
}
void DFSTraverse(ALGraph G) {
	int i;
	for (i = 0;i < G.vexnum;i++)
		visited[i] = false;
	for (i = 0;i < G.vexnum;i++) {
		if (!visited[i])
			DFS(G,i);
	}
}
//ͼ�Ĺ�ȱ���
void BFSTraverse(ALGraph G) {
	int v ,u,w;
	SqQueue Q;
	for (v = 0;v < G.vexnum;v++) visited[v] = false;
	InitQueue(&Q);
	for (v = 0;v < G.vexnum;v++)
		if (!visited[v]) {
			visited[v] = true;printf("%c",G.vertices[v].data);
			EnQueue(&Q,v);
			while (!QueueEmpty(&Q)) {
				DeQueue(&Q, &u);
				for (w = FirstAdjVex(G, u);w >= 0;w = nextAdjVex(G, u, w)) {
					if (!visited[w]) visited[w] = true;
					printf("%c  ",G.vertices[w].data);
					EnQueue(&Q,w);
				}
			}
		}
}
int main()
{
	ALGraph G, G2;
	printf("������ͼһ������ͼ����\n");
	create(&G);
	printf("\n������ͼ��������ͼ����\n");
	create(&G2);
	printf("\n����ͼ�����������������\n");
	DFSTraverse(G);
	printf("\n����ͼ��ȱ�����\n");
	BFSTraverse(G2);
    return 0;
}

