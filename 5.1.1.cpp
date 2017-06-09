// ��Ŀһ.cpp : �������̨Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"string.h"
#include<malloc.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define INFEASIBLE -2
#define Max_Tree_SIZE 20
#define Init_STACT_SIZE 20
#define MAXQSIZE 100
typedef int  Status;
typedef char  TElemType;
typedef struct BiTNode {
	TElemType data;
	struct BiTNode * lchild, *rchild;
}BiTNode, * BiTree;
//����ջ�Ľṹ��
typedef struct {
	int  top;//ջ��ָ��
	BiTree base[Init_STACT_SIZE];//ջ����ָ��
}Sqstack;
//������еĽṹ��
typedef struct {
	BiTree * base;
	int front;
	int rear;
}SqQueue;


//----------------------������ջ�Ĳ���
//��ʼ��ջ
Status InitStatck(Sqstack * sq) {
	sq->top = -1;
	return OK;
}
//��ջ
Status PushStatck(Sqstack * sq,BiTree * e) {
	if (sq->top == (Init_STACT_SIZE - 1)) {
		exit(OVERFLOW);
	}
	else
		  sq->base[++sq->top] = * e;
}
//��ջ
Status PopStack(Sqstack * sq, BiTree * e) {
	if (sq->top == -1)
		exit(-3);
	* e=  sq->base[sq->top--] ;
}
//�ж�ջ�Ƿ�Ϊ��
Status StackEmpty(Sqstack * sq) {
	if (sq->top == -1)
		return 1;
	else
		return 0;
}
//-----------------------------�����Ƕ��в���
//��ʼ������
Status InitQueue(SqQueue * Q) {
	Q->base = (BiTree *)malloc(MAXQSIZE * sizeof(BiTree));
	if (!Q->base) exit(OVERFLOW);
	Q->front = Q->rear = 0;
	return OK;
}
//������
Status EnQueue(SqQueue * Q, BiTree e) {
	if ((Q->rear + 1) % MAXQSIZE == Q->front)  return ERROR;
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
	return OK;
}
//������
Status DeQueue(SqQueue * Q, BiTree * e) {
	if (Q->rear == Q->front)  return ERROR;
	*e = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXQSIZE;
	return OK;
}
//�ж϶����Ƿ�Ϊ��
Status QueueEmpty(SqQueue * Q) {
	if (Q->front == Q->rear)
		return 1;
	else
		return 0;
}
//�����Ƕ�������ز���
//����ն�����
Status InitBiTree(BiTree * BT) {
	*BT = NULL;
	return OK;
}
//����ݹ齨��������
BiTree  Pre_Create_BT()
{
	BiTree  BT;
	char ch;
	 ch=getch();
	 if (ch =='#') return NULL;   //�������
	else {
		BT = (BiTree )malloc(sizeof(BiTNode));//�����½��
		BT->data = ch;
		BT->lchild = Pre_Create_BT();     //����������
		BT->rchild = Pre_Create_BT();     //����������
		return  BT;
	}
}
/************PreOrder*****************/
Status PreOrder(BiTree BT) {
	if (BT) {
		if (!(BT->data))
			return ERROR;
			printf("%c ",BT->data);
			PreOrder(BT->lchild);
			PreOrder(BT->rchild);
			return OK;
	}
}/*PreOrder*/
/********************************InOrder******************************/
Status InOrder(BiTree BT) {
	if (BT) {
		InOrder(BT->lchild);
		if (!(BT->data))
			return ERROR;
		printf("%c ", BT->data);
		InOrder(BT->rchild);
		return OK;
	}
}/*InOrder*/

 /********************************PostOrder******************************/
Status PostOrder(BiTree BT) {
	if (BT) {
		PostOrder(BT->lchild);
		PostOrder(BT->rchild);
		if (!(BT->data))
			return ERROR;
		printf("%c ", BT->data);
		return OK;
	}
}/*PostOrder*/

/*********************************LevelOrder***************************************/
void LevelOrder(BiTree BT)
{
	BiTree  p;
	SqQueue  Q;
	InitQueue(&Q);
	if (BT==NULL)  exit;
	  p =  BT;   // ��ʼ��
	printf("%c",p->data); 
	EnQueue(&Q, p);  //���ʸ���㣬������������ 
	while (!QueueEmpty(&Q)) {   //���ӷǿ�ʱ�ظ�ִ�����в���
		DeQueue(&Q, &p);      // ����
		if (p->lchild)
		{
			printf("%c", p->lchild->data);EnQueue(&Q, p->lchild);
		}  //��������
		if (p->rchild)
		{
			printf("%c", p->rchild->data);EnQueue(&Q, p->rchild);
		} //�����Һ���
	}
}
/*********************************NROreOrder***************************************/
Status NRPreOrder(BiTree BT) {
	BiTree p;
	 Sqstack sq;
	InitStatck(&sq);
	if (BT == NULL) return 0;
	p = BT;
	while (p || !StackEmpty(&sq))
	{
		while (p)
		{
		printf("%c",p->data);               /*���ʽ���������*/
			PushStatck(&sq, &p);                         /*����ǰָ��pѹջ*/
			p = p->lchild;              /*ָ��ָ��p������*/
		}
		if (!StackEmpty(&sq))
		{
			PopStack(&sq, &p);                         /*��ջ�е���ջ��Ԫ��*/
			p = p->rchild;                     /*ָ��ָ��p���Һ��ӽ��*/
		}
	}
	return OK;
}

//
Status max(int x,int y) {
	return x > y ? x : y;
}
/*-----------------TreeDepth---------------------------*/
Status High(BiTree BT) {
	if (BT == NULL) return 0;
	else
		return max(High(BT->lchild),High(BT->rchild)) + 1;
}
/*------------------leafNumber------------------------*/
Status LeafNUmber(BiTree BT) {
	if (!BT) return 0;
	else
		if (BT->lchild==NULL && BT->rchild==NULL) return 1;
		else
			return LeafNUmber(BT->lchild)+LeafNUmber(BT->rchild);
}
int main() {
	BiTree BT;
	TElemType ch;
	int flag = 1, select;
	printf("\n");
	printf("To Creat Binary Tree,Please Input PreOrder with'#':");
	BT=Pre_Create_BT();/*������������������У���#����ս��*/
	while (flag) {
		printf("Please select:            \n");
		printf("1.PreOrder Traversal      \n");
		printf("2.InOrder Traversal       \n");
		printf("3.PostOrder Traversal     \n");
		printf("4.LevelOrder Traversal    \n");
		printf("5.NRPreOrder Traversal    \n");
		printf("6.TreeDepth               \n");
		printf("7.LeafNumber              \n");
		printf("8.Exit                    \n");

		scanf("%d", &select);

		switch (select) {
		case 1:printf("\n The  PreOrder Traversal of Binary Tree is��");/*����ݹ����*/
			PreOrder(BT);
			break;

		case 2:printf("\n The  InOrder Traversal of Binary Tree is��");/*����ݹ����*/
			InOrder(BT);
			break;

		case 3:printf("\n The  InOrder Traversal of Binary Tree is ��");/*�������*/
			PostOrder(BT);
			break;

		case 4:printf("\n The  LevelOrder Traversal of Binary Tree is��");/*����ηǵݹ����*/
			LevelOrder(BT);
			break;

		case 5:printf("\n The  NRPreOrder Traversal of Binary Tree is��");/*����ǵݹ����*/
			NRPreOrder(BT);
			break;

		case 6:printf("\n The  Depth of Binary Tree is��%d", High(BT));/*�ݹ���������߶�*/
			break;

		case 7:printf("\n The number of leaf is��%d", LeafNUmber(BT));/*�ݹ���Ҷ�ڵ���*/
			break;
		
		default:flag = 0;
			printf("Press ant Key to exit!\n");
			getch();
		}/*switch*/
		printf("\n");
	}/*while*/
}/*main*/
/*
 BiTree BT;
	InitBiTree(&BT);
	BT=Pre_Create_BT();
	printf("����ݹ�������������\n");
	PreOrder(BT);
	printf("\n");
	printf("����ݹ�������������\n");
	InOrder(BT);
	printf("\n");
	printf("����ݹ�������������\n");
	PostOrder(BT);
	printf("����ǵݹ�������������\n");
	NROrder(BT);
    return 0;
 */


