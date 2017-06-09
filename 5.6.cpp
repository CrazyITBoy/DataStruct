// ��Ŀ��.cpp : �������̨Ӧ�ó������ڵ㡣
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
//�������ṹ��
typedef struct BiTNode {
	ElemType data;
	struct BiTNode * lchild, *rchild;
}BiTNode, *BiTree;
//����ջ�ṹ��
typedef struct {
	int top;
	BiTree base[MAXSIZE];
}SqStatck;
//һ����ջ��һЩ��ز���
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
//�ж�ջ�Ƿ�Ϊ��
Status StatckEmpty(SqStatck * sq) {
	if (sq->top == -1)
		return 1;
	else
		return 0;
	return OK;
}
//������������ز���
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
	printf("������������������ǣ�\n");
	NRPreOrder(BT);
	printf("�ܽ����Ŀ��\n");
	printf("\n%d\n",SumNode);
    return 0;
}

