// ��Ŀ��.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
// ��Ŀһ.cpp : �������̨Ӧ�ó������ڵ㡣
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
//����ջ�Ľṹ��
typedef struct {
	int  top;//ջ��ָ��
	BiTree base[Init_STACT_SIZE];//ջ����ָ��
}Sqstack;
//----------------------������ջ�Ĳ���
//��ʼ��ջ
Status InitStatck(Sqstack * sq) {
	sq->top = -1;
	return OK;
}
//��ջ
Status PushStatck(Sqstack * sq, BiTree * e) {
	if (sq->top == (Init_STACT_SIZE - 1)) {
		exit(FULL);
	}
	else
		sq->base[++sq->top] = *e;
}
//��ջ
Status PopStack(Sqstack * sq, BiTree * e) {
	if (sq->top == -1)
		exit(-3);
	*e = sq->base[sq->top--];
}
//�ж�ջ�Ƿ�Ϊ��
Status StackEmpty(Sqstack * sq) {
	if (sq->top == -1)
		return 1;
	else
		return 0;
}
//���ջ��Ԫ��
Status GetTop(Sqstack * sq ,BiTree * p) {
	if (sq->top == -1)
		exit(-3);
		else
			*p = sq->base[sq->top];
	return OK;
}
//�����Ƕ�������ز���
//����ն�����
Status InitBiTree(BiTree * BT) {
	*BT = NULL;
	return OK;
}
//������������
BiTree  In_Create_BT()
{
	BiTree  BT;
	char ch;
	ch = getch();
	if (ch == '#') return NULL;   //�������
	else {
		BT = (BiTree)malloc(sizeof(BiTNode));//�����½��
		BT->lchild = In_Create_BT();     //����������
		BT->data = ch;
		BT->rchild = In_Create_BT();     //����������
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
			Visit(&p->data, snode);            /*���ʽ���������*/
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

	printf("�������һ��������������:\n");
	BT1=In_Create_BT();
	printf("������ڶ���������������:\n");
	BT2=In_Create_BT();

	NRPreOrder(BT1,snode1);
	NRInOrder(BT1, snode2);

	NRPreOrder(BT2,snode3);
	NRInOrder(BT2, snode4);

	if ((strcmp(snode1, snode3) == 0) && (strcmp(snode2, snode4) == 0))
		printf("���Ŷ��������\n");
	else
		printf("���Ŷ����������\n");
    return 0;
}

