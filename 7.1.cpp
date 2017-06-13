// 题目一.cpp : 定义控制台应用程序的入口点。
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
	int  top;//栈顶指针
	BiTree base[Init_STACT_SIZE];//栈顶底指针
}Sqstack;
//----------------------以下是栈的操作
//初始化栈
void InitStatck(Sqstack * sq) {
	sq->top = -1;
}
//入栈
void PushStatck(Sqstack * sq, BiTree * e) {
	if (sq->top == (Init_STACT_SIZE - 1)) {
		exit(-1);
	}
	else
		sq->base[++sq->top] = *e;
}
//出栈
void PopStack(Sqstack * sq, BiTree * e) {
	if (sq->top == -1)
		exit(-3);
	*e = sq->base[sq->top--];
}
//判断栈是否为空
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
	printf("请您输入数据你要输入的数字总数\n");
	scanf("%d",&num);
	printf("\n请输入您将要输入的数据\n");
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
//删除节点
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
			printf("%d  ", p->data);               /*访问结点的数据域*/
			PushStatck(&sq, &p);                         /*将当前指针p压栈*/
			p = p->lchild;              /*指针指向p的左孩子*/
		}
		if (!StackEmpty(&sq))
		{
			PopStack(&sq, &p);                         /*从栈中弹出栈顶元素*/
			p = p->rchild;                     /*指针指向p的右孩子结点*/
		}
	}
}
int main()
{
	int numK;
	BiTree BT;	BT=initDSTable();
	create(&BT);
	printf("先序遍历的结果\n");
	NRPreOrder(BT);
	printf("\n请输如要删除的关键数\n");
	scanf("%d",&numK);
	DeleteBST(&BT, &BT,numK);
	printf("\n删除某个节点的先序遍历的结果\n");
	NRPreOrder(BT);
    return 0;
}

