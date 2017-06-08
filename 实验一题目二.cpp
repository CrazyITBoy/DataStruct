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
	if (i < 1 || i > L->length + 1)//判断所插入的元素是否超过或则小与当前长度
		return ERROR;
	if (L->length >= L->listSize) {//判断当前新元素的加入是否会使得之前分配的内存已经不够用，如果不够用就分配一个新的内存
		int * newbase = (int *)realloc(L->elem, (L->listSize + LISTINCREMENT) * sizeof(int));/*realloc函数在这里是增加内
																							 存的意思，第一个参数为原来的首地址，第二个参数为现在的长度 */
		if (!newbase)//判断是否成功分配了新的空间
			exit(OVERFLOW);
		L->elem = newbase;//将新分配的空间的首地址赋值给原来的基址
		L->listSize += LISTINCREMENT;
	}
	//找到要插入的元素的地址赋值给q,找到最后一个元素赋值给p
	int * q = &(L->elem[i - 1]);
	int * p = &(L->elem[L->length - 1]);
	//把元素后移
	for (;p >= q;p--)
		*(p + 1) = *p;
	//把要插入的元素赋值给q
	*q = e;
	L->length++;
	return OK;
}
//递减排序
Status SortUnionLIst(SqList *L) {
	int t;
	int i ;
	//外层循环决定一共走多少趟
	for ( i = 0;i<L->length - 1;i++)
		//内层循环 如果一个数比另外一个数大，则交换他们
		for (int j = 0;j < L->length - i - 1;j++)
			if (L->elem[j] > L->elem[j + 1]) {
				t = L->elem[j];
				L->elem[j] = L->elem[j + 1];
				L->elem[j + 1] = t;
			}
	return OK;
}
//逆置顺序表
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
//集合合并
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
//销毁线性表
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
	printf("请输入集合一的6个数据：\n");
	for (i = 0;i < 6;i++) {
		scanf("%d", &elem[i]);
		ListInsert_sq(&L1, i + 1, elem[i]);
	}
	printf("请输入集合二的3个数据：\n");
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

