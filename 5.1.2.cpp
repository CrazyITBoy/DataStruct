// 题目一代码.cpp : 定义控制台应用程序的入口点。
//
/*
设计并验证如下算法：在完善“12.6.4参考源程序”的前提下：按后序序列建立二叉树的二叉链表结构，求其单分支节点数目、双分支节点数目，并交换该二叉树。
*/
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
#define is_singleNode 1
#define is_doubleNOde 2
#define is_leafNode 0
int singleNodeSum = 0;
int doubleNodeSum = 0;
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
		exit(OVERFLOW);
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
//二叉树建议
Status InitBiTree(BiTree * BT) {
	*BT = NULL;
	return OK;
}
//后序递归建立二叉树
BiTree  Post_Create_BT()
{
	BiTree  BT;
	char ch;
	ch = getch();
    if (ch == '#') return NULL;   //构造空树
	else {
		BT = (BiTree)malloc(sizeof(BiTNode));//构造新结点
		BT->lchild = Post_Create_BT();     //构造左子树
		BT->rchild = Post_Create_BT();     //构造右子树
		BT->data = ch;
		return  BT;
	}
}
/*-------------------visit------------------------*/
Status Visit(BiTree BT) {
	if (BT->lchild != NULL&&BT->rchild == NULL)
		return is_singleNode;
	else if (BT->lchild == NULL&&BT->rchild != NULL)
		return is_singleNode;
	else if (BT->lchild != NULL&&BT->rchild != NULL)
		return is_doubleNOde;
	else
		return is_leafNode;
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
			if (Visit(p) == 1)
				singleNodeSum++;
			else if (Visit(p) == 2)
				doubleNodeSum++;
			printf("%c ",p->data);
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
void change_left_right(BiTree BT)
{
	BiTree p;
	if (BT) {
		change_left_right(BT->lchild);
		change_left_right(BT->rchild);
		p = BT->lchild;
		BT->lchild=BT->rchild;
		BT->rchild = p;
	}
}

int main()
{
	BiTree BT;
	InitBiTree(&BT);
	printf("请输入二叉树序列（先序）：\n");
	BT=Post_Create_BT();
	NRPreOrder(BT);
	printf("单结点总数是: %d\n双结点数是: %d\n",singleNodeSum,doubleNodeSum);
	change_left_right(BT);
	printf("交换二叉树后的遍历输出：\n");
	NRPreOrder(BT);
    return 0;
}

