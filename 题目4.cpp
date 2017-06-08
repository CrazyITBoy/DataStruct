// 题目4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<malloc.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define Status int
#define OK 1
#define OVERFLOW -2
#define ERROR 0
#define ElemType char
typedef struct Letter_sql {
	ElemType * Letter;
	int length;
	int listsize;
}Lsql;
Status InitLIst(Lsql * L){
	L = (Lsql *)malloc(LIST_INIT_SIZE*sizeof(Lsql));
	if (!L) exit(OVERFLOW);
	L->length = 0;
	L->listsize = LIST_INIT_SIZE;
	return OK;
}
Status ListInsert(Lsql * L, int n, ElemType e) {
	Lsql * newbase;
	char *p, *q;
	if (n<1 || n>L->length)
		return ERROR;
	if (L->length + 1 > L->listsize) {
	newbase = (Lsql *)realloc(L, (LIST_INIT_SIZE + LISTINCREMENT) * sizeof(Lsql));
	if (!newbase) return ERROR;
	L = newbase;
	L->listsize = L->listsize + LISTINCREMENT;
    }
	p = &(L->Letter[n-1]);
	for (q = &(L->Letter[L->length - 1]);p <= q;q--) 
		*(q + 1) = *q;
	*q = e;
	++L->length;
	return OK;
}
Status MergeList(Lsql *L1, Lsql *L2,Lsql *L3) {
	int operation;
	printf("请您输入1做并运算\n请您输入2做交运算\n请您输入3做差运算\n请您输入4做补运算\n");
	scanf("%d",operation);
	switch (operation)
	{
	case 1:
		break;

	default:
		printf("你输入的指令有误");
	}


}
int main()
{
	Lsql  L1,L2,L3;
	ElemType e;
	int i;
	InitLIst(&L1);
	for (i = 0;i < 10;i++) {
		printf("please input a char\n");
		scanf("%d",&e);
		ListInsert(&L1, i + 1, e);
	
		InitLIst(&L2);
		for (i = 0;i < 10;i++) {
			printf("please input a char\n");
			scanf("%d", &e);
			ListInsert(&L2, i + 1, e);
		}
	MergeList(&L1,&L2,&L3);
    return 0;
}

