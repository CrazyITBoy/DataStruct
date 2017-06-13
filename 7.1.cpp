// ��Ŀһ.cpp : �������̨Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<conio.h>
#define Init_STACT_SIZE 100
typedef struct Tree
{
	int data;
    struct Tree * lchild,* rchild;
}BTNode,*BiTree; 
typedef struct {
	int  top;//ջ��ָ��
	BiTree base[Init_STACT_SIZE];//ջ����ָ��
}Sqstack;
//----------------------������ջ�Ĳ���
//��ʼ��ջ
void InitStatck(Sqstack * sq) {
	sq->top = -1;
}
//��ջ
void PushStatck(Sqstack * sq, BiTree * e) {
	if (sq->top == (Init_STACT_SIZE - 1)) {
		exit(-1);
	}
	else
		sq->base[++sq->top] = *e;
}
//��ջ
void PopStack(Sqstack * sq, BiTree * e) {
	if (sq->top == -1)
		exit(-3);
	*e = sq->base[sq->top--];
}
//�ж�ջ�Ƿ�Ϊ��
int StackEmpty(Sqstack * sq) {
	if (sq->top == -1)
		return 1;
	else
		return 0;
}
BiTree initDSTable() {
	BiTree BT;
	BT = NULL;
	return BT;
}
bool EQ(int key1, int key2) {
	if (key1 == key2)
		return true;
	else
		return false;
}
bool LT(int key1, int key2) {
	if (key1 < key2)
		return true;
	else
		return false;
}
bool searchBST(BiTree BT,int key,BiTree f, BiTree * p ) {
	if (!BT) { *p = f;return false; }
	else if (EQ(key, BT->data)) {
		*p = BT;
		return true;
	}
	else if (LT(key, BT->data))
		return searchBST(BT->lchild,key,BT,p);
	else return searchBST(BT->rchild, key, BT, p);
}
void insertBST(BiTree * BT, int e) {
	BiTree  p;
	BiTree  s;
	if (!searchBST(* BT, e, NULL, &p)) {
		s = (BiTree)malloc(sizeof(BTNode));
		s->data = e;
		s->lchild = s->rchild = NULL;
	}
	if (!p) *BT = s;
	else if (LT(e, p->data))
		p->lchild =s;
	else
		p->rchild = s;
}
void create(BiTree * BT) {
	int num;
	int key;
	printf("��������������Ҫ�������������\n");
	scanf("%d",&num);
	printf("\n����������Ҫ���������\n");
		for (int i = 0;i < num;i++) {
		scanf("%d", &key);
		insertBST(BT, key);
	}
}
int Delete(BiTree *p, BiTree * father) {
	BiTree q, s;
	if (!(*p)->rchild)
	{
		q = (*p); 
		(* father)->lchild = (*p)->lchild;
		free(q);
	}
	else if (!(*p)->lchild) {
		q = (*p);(*father)->rchild = (*p)->rchild;; free(q);
	}
	else
	{
			q = (*p);  s = (*p)->lchild;
			while (s->rchild) { 
				q = s; 
				s = s->rchild; }
			(*p)->data = s->data;
			if (q != (*p))
				q->rchild = s->lchild;
			else q->lchild = s->lchild;
			delete s;
		}
		return 1;
}
//ɾ���ڵ�
int DeleteBST(BiTree * p, BiTree * father,int key) {
	BiTree  T;
	T = *p;
	if (!T)
		return 0;
	else {
		if (EQ(key,T->data))
		{
			return Delete(&T,father);
		}
		else if (LT(key, T->data))
			return DeleteBST(&(T->lchild),&T, key);
		else
			return DeleteBST(&(T->rchild), &T,key);
	}
}

void NRPreOrder(BiTree BT) {
	BiTree p;
	Sqstack sq;
	InitStatck(&sq);
	if (BT == NULL) return ;
	p = BT;
	while (p || !StackEmpty(&sq))
	{
		while (p)
		{
			printf("%d  ", p->data);               /*���ʽ���������*/
			PushStatck(&sq, &p);                         /*����ǰָ��pѹջ*/
			p = p->lchild;              /*ָ��ָ��p������*/
		}
		if (!StackEmpty(&sq))
		{
			PopStack(&sq, &p);                         /*��ջ�е���ջ��Ԫ��*/
			p = p->rchild;                     /*ָ��ָ��p���Һ��ӽ��*/
		}
	}
}
int main()
{
	int numK;
	BiTree BT;	BT=initDSTable();
	create(&BT);
	printf("��������Ľ��\n");
	NRPreOrder(BT);
	printf("\n������Ҫɾ���Ĺؼ���\n");
	scanf("%d",&numK);
	DeleteBST(&BT, &BT,numK);
	printf("\nɾ��ĳ���ڵ����������Ľ��\n");
	NRPreOrder(BT);
    return 0;
}

