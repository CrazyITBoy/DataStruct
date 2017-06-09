// 题目二.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
// 题目一.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"string.h"
#include<malloc.h>
char snode1[100];
char snode2[100];
char snode3[100];
char snode4[100];
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define INFEASIBLE -2
#define FULL -3
#define Max_Tree_SIZE 20
#define Init_STACT_SIZE 20
#define MAXQSIZE 100
typedef int  Status;
typedef char  TElemType;
typedef struct BiTNode {
	TElemType data;
	struct BiTNode * lchild, *rchild;
}BiTNode, *BiTree;
//定义栈的结构体
typedef struct {
	int  top;//栈顶指针
	BiTree base[Init_STACT_SIZE];//栈顶底指针
}Sqstack;
//----------------------以下是栈的操作
//初始化栈
Status InitStatck(Sqstack * sq) {
	sq->top = -1;
	return OK;
}
//入栈
Status PushStatck(Sqstack * sq, BiTree * e) {
	if (sq->top == (Init_STACT_SIZE - 1)) {
		exit(FULL);
	}
	else
		sq->base[++sq->top] = *e;
}
//出栈
Status PopStack(Sqstack * sq, BiTree * e) {
	if (sq->top == -1)
		exit(-3);
	*e = sq->base[sq->top--];
}
//判断栈是否为空
Status StackEmpty(Sqstack * sq) {
	if (sq->top == -1)
		return 1;
	else
		return 0;
}
//获得栈顶元素
Status GetTop(Sqstack * sq ,BiTree * p) {
	if (sq->top == -1)
		exit(-3);
		else
			*p = sq->base[sq->top];
	return OK;
}
//以下是二叉树相关操作
//构造空二叉树
Status InitBiTree(BiTree * BT) {
	*BT = NULL;
	return OK;
}
//中序建立二叉树
BiTree  In_Create_BT()
{
	BiTree  BT;
	char ch;
	ch = getch();
	if (ch == '#') return NULL;   //构造空树
	else {
		BT = (BiTree)malloc(sizeof(BiTNode));//构造新结点
		BT->lchild = In_Create_BT();     //构造左子树
		BT->data = ch;
		BT->rchild = In_Create_BT();     //构造右子树
		return  BT;
	}
}
/*-------------------------------visit---------------------------------------*/
Status Visit(TElemType * e,TElemType * snode) {
	strcat(snode, e);
		return OK;
}
/*********************************NRPreOrder***************************************/
Status NRPreOrder(BiTree BT,char * snode) {
	BiTree p;
	Sqstack sq;
	InitStatck(&sq);
	if (BT == NULL) return 0;
	p = BT;
	while (p || !StackEmpty(&sq))
	{
		while (p)
		{
			Visit(&p->data, snode);            /*访问结点的数据域*/
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
/*----------------------NRInOrder----------------------------*/
Status NRInOrder(BiTree T,char * snode)
{
	Sqstack S;
	BiTree p;
	InitStatck(&S);
	PushStatck(&S, &T);
	while (!StackEmpty(&S))
	{
		while (GetTop(&S, &p) && p)
			PushStatck(&S, &p->lchild);
		PopStack(&S, &p);
		if (!StackEmpty(&S))
		{
			PopStack(&S, &p);
			if (!Visit(& p->data, snode))
				return ERROR;
			PushStatck(&S,& p->rchild);
		}
	}
	return OK;
}

int main()
{
	BiTree BT1, BT2;
	InitBiTree(&BT1);
	InitBiTree(&BT2);

	printf("请输入第一个树的先序序列:\n");
	BT1=In_Create_BT();
	printf("请输入第二个树的先序序列:\n");
	BT2=In_Create_BT();

	NRPreOrder(BT1,snode1);
	NRInOrder(BT1, snode2);

	NRPreOrder(BT2,snode3);
	NRInOrder(BT2, snode4);

	if ((strcmp(snode1, snode3) == 0) && (strcmp(snode2, snode4) == 0))
		printf("两颗二叉树相等\n");
	else
		printf("两颗二叉树不相等\n");
    return 0;
}

