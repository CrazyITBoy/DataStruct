#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<conio.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef  int Status;
typedef struct LIST {
	int * elem;
	int length;
	int listSize;
}SqList;
Status InitList(SqList * L) {
	L->elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L->elem)
		exit(OVERFLOW);
	L->length = 0;
	L->listSize = LIST_INIT_SIZE;
	return OK;
}
Status ListInsert_sq(SqList * L, int i, int e) {
	if (i < 1 || i > L->length + 1)//�ж��������Ԫ���Ƿ񳬹�����С�뵱ǰ����
		return ERROR;
	if (L->length >= L->listSize) {//�жϵ�ǰ��Ԫ�صļ����Ƿ��ʹ��֮ǰ������ڴ��Ѿ������ã���������þͷ���һ���µ��ڴ�
		int * newbase = (int *)realloc(L->elem, (L->listSize + LISTINCREMENT) * sizeof(int));/*realloc������������������
																							 �����˼����һ������Ϊԭ�����׵�ַ���ڶ�������Ϊ���ڵĳ��� */
		if (!newbase)//�ж��Ƿ�ɹ��������µĿռ�
			exit(OVERFLOW);
		L->elem = newbase;//���·���Ŀռ���׵�ַ��ֵ��ԭ���Ļ�ַ
		L->listSize += LISTINCREMENT;
	}
	//�ҵ�Ҫ�����Ԫ�صĵ�ַ��ֵ��q,�ҵ����һ��Ԫ�ظ�ֵ��p
	int * q = &(L->elem[i - 1]);
	int * p = &(L->elem[L->length - 1]);
	//��Ԫ�غ���
	for (;p >= q;p--)
		*(p + 1) = *p;
	//��Ҫ�����Ԫ�ظ�ֵ��q
	*q = e;
	L->length++;
	return OK;
}
//�ݼ�����
Status SortUnionLIst(SqList *L) {
	int t;
	int i ;
	//���ѭ������һ���߶�����
	for ( i = 0;i<L->length - 1;i++)
		//�ڲ�ѭ�� ���һ����������һ�������򽻻�����
		for (int j = 0;j < L->length - i - 1;j++)
			if (L->elem[j] > L->elem[j + 1]) {
				t = L->elem[j];
				L->elem[j] = L->elem[j + 1];
				L->elem[j + 1] = t;
			}
	return OK;
}
//����˳���
Status InverseList(SqList *L) {
	int *p, *q,t;
	p =&(L->elem[0]);
	q = &(L->elem[L->length-1]);
	for (;p <= q;p++, q--) {
		t = *p;
		*p = *q;
		*q = t;
	}
	return OK;
}
//���Ϻϲ�
void MergeList_sq(SqList * L1, SqList * L2, SqList * L3) {
	int *p1, *p2, *p3, *p1_last, *p2_last;
	L3->listSize = L3->length = L1->length + L2->length;
	p3 = (int *)malloc((L3->listSize) * sizeof(int));
	if (!p3)
		exit(OVERFLOW);
	L3->elem = p3;
	p1 = (L1->elem);
	p2 = (L2->elem);
	p1_last = &(L1->elem[L1->length - 1]);
	p2_last = &(L2->elem[L2->length - 1]);
	while (p1 <= p1_last&&p2 <= p2_last) {
		if (*p1 <= *p2)
			* p3++ = *p1++;
		else
			*p3++ = *p2++;
	}
	while (p1 <= p1_last)  *p3++ = *p1++;
	while (p2 <= p2_last) *p3++ = *p2++;
}
void PrintList(SqList *L) {
	int i = 0;
	printf("\n");
	for (;i < L->length;i++)
		printf("%d ", L->elem[i]);
	printf("\n");
}
//�������Ա�
Status DesroyList(SqList *L) {
	free(L->elem);
	return OK;
}
int main()
{
	SqList L1, L2, L3;
	int i, j;
	int  elem[10];
	InitList(&L1);
	InitList(&L2);
	InitList(&L3);
	printf("�����뼯��һ��6�����ݣ�\n");
	for (i = 0;i < 6;i++) {
		scanf("%d", &elem[i]);
		ListInsert_sq(&L1, i + 1, elem[i]);
	}
	printf("�����뼯�϶���3�����ݣ�\n");
	for (i = 0;i < 3;i++) {
		scanf("%d", &elem[i]);
		ListInsert_sq(&L2, i + 1, elem[i]);
	}
	SortUnionLIst(&L1);
	SortUnionLIst(&L2);
	MergeList_sq(&L1, &L2, &L3);
	InverseList(&L3);
	PrintList(&L1);
	PrintList(&L2);
	DesroyList(&L1);
	DesroyList(&L2);
	PrintList(&L3);
	DesroyList(&L3);
	return 0;
}

