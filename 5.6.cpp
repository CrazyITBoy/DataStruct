// 题目六.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#define  Status int
#define OK 1
#define FULL -3
#define empty -4
#define ElemType char
#define MAXSIZE 100
int SumNode=0;
//定义树结构体
typedef struct BiTNode {
	ElemType data;
	struct BiTNode * lchild, *rchild;
}BiTNode, *BiTree;
//定义栈结构体
typedef struct {
	int top;
	BiTree base[MAXSIZE];
}SqStatck;
//一下是栈的一些相关操作
Status initStatcK(SqStatck * sq) {
	sq->top = -1;
	return OK;
}
Status PushStatck(SqStatck * sq,BiTree T) {
	if (sq->top == MAXSIZE - 1)
		exit(FULL);
	else
	sq->base[++sq->top] = T;
	return OK;
}
Status PopStatck(SqStatck * sq, BiTree * T){
	if (sq->top == -1)
		exit(empty);
	else
		* T = sq->base[sq->top--];
	return OK;
}
Status GetTop(SqStatck * sq, BiTree * T) {
	if (sq->top == -1)
		exit(empty);
	else
		* T = sq->base[sq->top];
	return OK;
}
//判断栈是否为空
Status StatckEmpty(SqStatck * sq) {
	if (sq->top == -1)
		return 1;
	else
		return 0;
	return OK;
}
//以下是树的相关操作
Status InitBiTree(BiTree * BT) {
	* BT = NULL;
	return OK;
}
/*---------CreatBiTree---------------*/
Status CreatBiTree(BiTree * BT) {
	SqStatck Sq;
	BiTNode * p,*e;
	char ch;
	int flag;
	InitBiTree(BT);
	initStatcK(&Sq);
	scanf("%c",&ch);
	while (ch != '#') {
		switch (ch) {
		case '(':
			PushStatck(&Sq,p);
			flag = 1;
			break;
		case ',':
				flag = 0;
				break;
		case')':
			PopStatck(&Sq,&p);
			break;
		default:
			p = (BiTree)malloc(sizeof(BiTNode));
			 p->lchild = p->rchild = NULL;
			p->data = ch;
			if (*BT==NULL) {
				 * BT = p;
			}
			else {
				GetTop(&Sq,&e);
				if (!flag)
					e->rchild = p;
				else
					e->lchild = p;
			}		
		}
		scanf("%c", &ch);
	}
	return OK;
}
/**-------------------------------------**/
Status NRPreOrder(BiTree BT) {
	BiTree p;
	SqStatck sq;
	initStatcK(&sq);
	if (BT == NULL) return 0;
	p = BT;
	while (p || !StatckEmpty(&sq))
	{
		while (p)
		{
			SumNode++;  
			printf("%c ",p->data);
			PushStatck(&sq, p);
			p = p->lchild;              
		}
		if (!StatckEmpty(&sq))
		{
			PopStatck(&sq, &p);
			p = p->rchild;                     
		}
	}
	return OK;
}
int main()
{
	BiTree BT;
	CreatBiTree(&BT);
	printf("先序遍历出来的序列是：\n");
	NRPreOrder(BT);
	printf("总结点数目是\n");
	printf("\n%d\n",SumNode);
    return 0;
}

