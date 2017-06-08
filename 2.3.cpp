// ��Ŀ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define Status int
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define ElemType int
typedef struct Link_List {
	ElemType data;//����
	struct Link_List * next;
} LNode, * LinkList;

Status InitList(LinkList * L) {
	/* ����һ���յ��������� */
	LinkList head;
	head = (LinkList)malloc(sizeof(LNode)); /* ����ͷ��� */
	if (head)
	{
		head->next = NULL;
		*L = head;
		return OK;
	}
	else
		return ERROR;
}
//β�ӷ���������
Status creakList(LinkList * L, int n) {
	LinkList p,q,head;
	head = *L;
	p = q = NULL;
	int i;
	for (i = 0;i < n;i++) {
		p = (LinkList)malloc(sizeof(LNode));
		if (!p)  exit(OVERFLOW);
		printf("please input a int num one :\n ");
		scanf("%d", &p->data);
		if (i == 0){
			head->next = p;
			q = p;
	}
		else {
			q->next = p;
			q = p;
		}
		q->next = NULL;
	}
	return OK;
}
//�ж��Ƿ��Ƿǵ�������
bool judge_is_sort(LinkList *L) {
	LinkList p,q;
	ElemType e;
	q = (*L)->next;
	while (q) {
		e = q->data;
		p = q->next;
		while (p) {
			if (e >= p->data) p = p->next;
			else  return false;
		}
		q = q->next;
	}
	return true;
}
//ɾ���ڵ�
void purge_list(LinkList * L) {
	LinkList p, q, r,head;
	head = *L;
		p = head->next;
		while (p){
			q = p;
			while (q->next){
				if (q->next->data == p->data)	{
					r = q->next;
					q->next = r->next;
					free(r);
				}
				else
					q = q->next;
			}
			p = p->next;
		}
}
//��������
Status visit(LinkList * L) {
	LinkList head,p;
	head = *L;
	p = head->next;
	printf("-----------------------------------------\n");
	while (p) {
		printf("%d  ",p->data);
		p = p->next;
	}
	return OK;
}
//��������
Status reverse_list(LinkList * L) {
	LinkList q, p, head;
	head = *L;
	p = head->next;
	head->next = NULL;
	while (p) {
		q = p->next;
		p->next = head->next;
		head->next = p;
		p = q;
	}
	return OK;
}
//��������
Status DestroyList(LinkList * L) {
	while (*L) {
		LinkList p = *L;
		* L = (*L)->next;
		free(p);
	}
	* L = NULL;
	return OK;
}
int main()
{
	LinkList L,p, q;;
	int n,j;
	ElemType e;
	InitList(&L);
	printf("please input how many int nums you want input?\n");
	scanf("%d",&n);
	creakList(&L,n);
	visit(&L);
	printf("---------------------------------------|\n");
	if (judge_is_sort(&L)) {
		purge_list(&L);
		visit(&L);
		printf("----------------------------------\n");
		reverse_list(&L);
		visit(&L);
	}
	else
	{
		printf("������������Ƿǵ�����������������\n\n");
		main();
	}
	DestroyList(&L);
    return 0;
}

