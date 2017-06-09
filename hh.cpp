// ��Ŀһ����.cpp : �������̨Ӧ�ó������ڵ㡣
//

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
		exit(OVERFLOW);
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
//����������
Status InitBiTree(BiTree * BT) {
	*BT = NULL;
	return OK;
}
//����ݹ齨��������
BiTree  Post_Create_BT()
{
	BiTree  BT;
	char ch;
	ch = getch();
    if (ch == '#') return NULL;   //�������
	else {
		BT = (BiTree)malloc(sizeof(BiTNode));//�����½��
		BT->lchild = Post_Create_BT();     //����������
		BT->rchild = Post_Create_BT();     //����������
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
	printf("��������������У����򣩣�\n");
	BT=Post_Create_BT();
	NRPreOrder(BT);
	printf("�����������: %d\n˫�������: %d\n",singleNodeSum,doubleNodeSum);
	change_left_right(BT);
	printf("������������ı��������\n");
	NRPreOrder(BT);
    return 0;
}

