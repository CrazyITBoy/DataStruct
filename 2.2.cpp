// 线性表链式存储的ADT.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define ERROR 0
#define OVERFLOW -2
#define OK 1
typedef int Status;
typedef int ElemType;
typedef struct LNode {
	ElemType data;
	struct LNode * next;
}LNode, *LinkList;
//初始化操作
Status InitList(LinkList * L) {
	LinkList head = (LinkList)malloc(sizeof(LNode));
	if (!head) exit(OVERFLOW);
	head->next = NULL;
	*L = head;
	return OK;
}
//前插法建立链表
void creakLinkList(LinkList * L, int n) {
	LinkList p, head;
	int i;
	head = *L;
	head->next = head;
	for (i = 0;i < n;i++) {
		p = (LinkList)malloc(sizeof(LNode));
		if (!p)  exit(OVERFLOW);
		printf("please input a num\n");
		scanf("%d", &p->data);
		p->next = head->next;
		head->next = p;
	}
}
//把链表一分为二，表一只有奇数，表二只有偶数
void split(LinkList * L, LinkList * L1, LinkList * L2) {
	LinkList head, head2,p,r,q;
	head2= (LinkList)malloc(sizeof(LNode));
	head = *L;
	head2->next = head2;
	p= head;
	while (p->next != head) {
		q = p->next;
		r = q;
		if (q == head) {
			*L1 = head;
			*L2 = head2;
			break;
		}
		if (r->data % 2 == 0) {
			p->next = q->next;
			r->next = head2->next;
			head2->next = r;
		}
		else
		p = p->next;
	}
	*L1 = head;
	*L2 = head2;
}
//排序 按递减有序排序
void sortList(LinkList * L1) {
	LinkList p1, p2;
	int temp;
	ElemType e1, e2;
	p1 = (*L1)->next;
	while (p1!= *L1) {
		p2 = p1->next;
		while (p2!= *L1) {
			if (p1->data < p2->data) {
				temp = p1->data;
				p1->data = p2->data;
				p2->data = temp;
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
}
//删除大于mink且小于maxk的元素
void Delete_List(LinkList * L,int mink,int maxk) {
	LinkList head,p,q;
	head = *L;
	q = head;
	p = head->next;
	while (p!=head) {
		if (p->data > mink&&p->data < maxk) {
			q->next = p->next;
			p->next = NULL;
			free(p);
			p=q->next;
		}
		else
		{
			q = p;
			p = p->next;
		}
	}
}
void visit(LinkList * L) {
	LinkList head, p;
	head = *L;
	p = head->next;
	printf("-----------------------------------------\n");
	while (p!=head) {
		printf("%d  ", p->data);
		printf("\n");
		p = p->next;
	}
}
int main()
{
	LinkList L, L1, L2;
	int n,mink,maxk;
	InitList(&L);
	printf("请您输入一个数代表链表L的元素个数\n");
	scanf("%d",&n);
	creakLinkList(&L,n);
	printf("请您输入mink和maxk:\n");
	scanf("%d %d",&mink,&maxk);
	Delete_List(&L,mink,maxk);
	sortList(&L);
	visit(&L);
	split(&L,&L1,&L2);
	visit(&L1);
	visit(&L2);
    return 0;
}

