// 题目一.cpp : 定义控制台应用程序的入口点。
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
//定义栈的结构体
typedef struct {
	int  top;//栈顶指针
	BiTree base[Init_STACT_SIZE];//栈顶底指针
}Sqstack;
//定义队列的结构体
typedef struct {
	BiTree * base;
	int front;
	int rear;
}SqQueue;


//----------------------以下是栈的操作
//初始化栈
Status InitStatck(Sqstack * sq) {
	sq->top = -1;
	return OK;
}
//入栈
Status PushStatck(Sqstack * sq,BiTree * e) {
	if (sq->top == (Init_STACT_SIZE - 1)) {
		exit(OVERFLOW);
	}
	else
		  sq->base[++sq->top] = * e;
}
//出栈
Status PopStack(Sqstack * sq, BiTree * e) {
	if (sq->top == -1)
		exit(-3);
	* e=  sq->base[sq->top--] ;
}
//判断栈是否为空
Status StackEmpty(Sqstack * sq) {
	if (sq->top == -1)
		return 1;
	else
		return 0;
}
//-----------------------------以下是队列操作
//初始化队列
Status InitQueue(SqQueue * Q) {
	Q->base = (BiTree *)malloc(MAXQSIZE * sizeof(BiTree));
	if (!Q->base) exit(OVERFLOW);
	Q->front = Q->rear = 0;
	return OK;
}
//进队列
Status EnQueue(SqQueue * Q, BiTree e) {
	if ((Q->rear + 1) % MAXQSIZE == Q->front)  return ERROR;
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
	return OK;
}
//出队列
Status DeQueue(SqQueue * Q, BiTree * e) {
	if (Q->rear == Q->front)  return ERROR;
	*e = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXQSIZE;
	return OK;
}
//判断队列是否为空
Status QueueEmpty(SqQueue * Q) {
	if (Q->front == Q->rear)
		return 1;
	else
		return 0;
}
//以下是二叉树相关操作
//构造空二叉树
Status InitBiTree(BiTree * BT) {
	*BT = NULL;
	return OK;
}
//先序递归建立二叉树
BiTree  Pre_Create_BT()
{
	BiTree  BT;
	char ch;
	 ch=getch();
	 if (ch =='#') return NULL;   //构造空树
	else {
		BT = (BiTree )malloc(sizeof(BiTNode));//构造新结点
		BT->data = ch;
		BT->lchild = Pre_Create_BT();     //构造左子树
		BT->rchild = Pre_Create_BT();     //构造右子树
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
	  p =  BT;   // 初始化
	printf("%c",p->data); 
	EnQueue(&Q, p);  //访问根结点，并将根结点入队 
	while (!QueueEmpty(&Q)) {   //当队非空时重复执行下列操作
		DeQueue(&Q, &p);      // 出队
		if (p->lchild)
		{
			printf("%c", p->lchild->data);EnQueue(&Q, p->lchild);
		}  //处理左孩子
		if (p->rchild)
		{
			printf("%c", p->rchild->data);EnQueue(&Q, p->rchild);
		} //处理右孩子
	}
}
/*********************************NRPreOrder***************************************/
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
		printf("%c",p->data);               /*访问结点的数据域*/
			PushStatck(&sq, &p);                         /*将当前指针p压栈*/
			p = p->lchild;              /*指针指向p的左孩子*/
		}
		if (!StackEmpty(&sq))
		{
			PopStack(&sq, &p);                         /*从栈中弹出栈顶元素*/
			p = p->rchild;                     /*指针指向p的右孩子结点*/
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
	BT=Pre_Create_BT();/*输入二叉树的先序序列，用#代表空结点*/
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
		case 1:printf("\n The  PreOrder Traversal of Binary Tree is：");/*先序递归遍历*/
			PreOrder(BT);
			break;

		case 2:printf("\n The  InOrder Traversal of Binary Tree is：");/*中序递归遍历*/
			InOrder(BT);
			break;

		case 3:printf("\n The  InOrder Traversal of Binary Tree is ：");/*后序遍历*/
			PostOrder(BT);
			break;

		case 4:printf("\n The  LevelOrder Traversal of Binary Tree is：");/*按层次非递归遍历*/
			LevelOrder(BT);
			break;

		case 5:printf("\n The  NRPreOrder Traversal of Binary Tree is：");/*先序非递归遍历*/
			NRPreOrder(BT);
			break;

		case 6:printf("\n The  Depth of Binary Tree is：%d", High(BT));/*递归求二叉树高度*/
			break;

		case 7:printf("\n The number of leaf is：%d", LeafNUmber(BT));/*递归求叶节点数*/
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
	printf("先序递归遍历输出二叉树\n");
	PreOrder(BT);
	printf("\n");
	printf("中序递归遍历输出二叉树\n");
	InOrder(BT);
	printf("\n");
	printf("后序递归遍历输出二叉树\n");
	PostOrder(BT);
	printf("先序非递归遍历输出二叉树\n");
	NROrder(BT);
    return 0;
 */


