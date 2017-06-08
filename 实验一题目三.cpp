// 实验一第三题.cpp : 定义控制台应用程序的入口点。


#include "stdafx.h"
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define FALSE 0
#define TRUE 1
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INT_SIZE 100
#define LISTINCREMENT 10
typedef int Status;

typedef struct STUDENT {
	//定义学生结构体类型，包括姓名，学号，年龄，成绩
	char name[20];
	char stuno[10];
	int sex;
	int score[3];
	int avenueScore;
}ElemType;
typedef struct {
	ElemType * elem;//存储空间基址
	int length;//当前长度
	int listsize;//当前分配的存储容量
}SqList;

//初始化操作
Status Inilist_sq(SqList *L) {
	//构造一个空的线性表
	//存储空间基址，初始化线性表时利用malloc函数分配100个单位空间。
	L->elem = (ElemType *)malloc(LIST_INT_SIZE * sizeof(ElemType));
	if (!L->elem) {
		exit(OVERFLOW);//空间分配失败
	}
	L->length = 0;//设置链表的初始长度为0
	L->listsize = LIST_INT_SIZE;//初始存储容量
	return OK;//空间分配成功
}
//插入操作
Status ListInsert_sq(SqList * L, int i, ElemType e) {
	if (i < 1 || i > L->length + 1)//判断所插入的元素是否超过或则小与当前长度
		return ERROR;

	if (L->length >= L->listsize) {//判断当前新元素的加入是否会使得之前分配的内存已经不够用，如果不够用就分配一个新的内存

		ElemType * newbase = (ElemType *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));/*realloc函数在这里是增加内
																											存的意思，第一个参数为原来的首地址，第二个参数为现在的长度 */

		if (!newbase)//判断是否成功分配了新的空间
			exit(OVERFLOW);
		L->elem = newbase;//将新分配的空间的首地址赋值给原来的基址
		L->listsize = +LISTINCREMENT;
	}
	ElemType * q = &(L->elem[i - 1]);//找到要插入的元素的地址赋值给q
	ElemType * p = &(L->elem[L->length - 1]);//找到最后一个元素赋值给p
											 //把元素后移
	for (;p >= q;p--)
		*(p + 1) = *p;//把要插入的元素赋值给q
	*q = e;
	L->length++;
	return OK;
}
//删除操作
Status ListDelete(SqList * L, char *stuno, ElemType * e) {
	int i = 0;
	ElemType *p, *q;
	while (strcmp(L->elem[i].stuno, stuno) != 0) {
		i++;
	}
	*e = L->elem[i];
	p = &(L->elem[i]);
	q = &(L->elem[L->length - 1]);
	for (;p <= q;p++)
		*p = *(p + 1);
	L->length--;
	return OK;
}
//销毁链表
Status DesroyList(SqList *L) {
	free(L->elem);
	return OK;
}
//修改课程分数
Status reviseList(SqList * L, char * stuno, int i) {
	int j = 0;
	while (strcmp(L->elem[j].stuno, stuno) != 0)
		j++;
	if (j <= L->length) {
		printf("请输入你要修改的课程的分数\n");
		scanf("%d", &(L->elem[j].score[i]));
		printf("%d", L->elem[j].score[i]);
	}
	else {
		printf("你要修改的学号不存在\n");
		return ERROR;
	}
	return OK;
}
Status GetElem(SqList * L, char * stuno, ElemType * e) {
	int i = 0;
	while (strcmp(L->elem[i].stuno, stuno) != 0) 
		i++;
	e = &(L->elem[i]);
	printf("姓名    学号        性别       高数     大英      程序    平均成绩\n");
	printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\n", e->name, e->stuno,
		e->sex, e->score[0], e->score[1], e->score[2], e->avenueScore);
	return OK;
}
//赋值给学生的操作
void  assignment(SqList * L) {
	int i = 0, len;
	ElemType e;
	printf("您要插入入的学生个数:\n");
	scanf("%d", &len);
	for (i = 1;i <= len;i++)
	{
		printf("请输入姓名 学号 性别（0男1女） 高数成绩 大学英语成绩 程序设计基础成绩 : \n");
		scanf("%s %s %d %d %d %d", e.name, e.stuno, &e.sex, &e.score[0], &e.score[1], &e.score[2]);
		e.avenueScore = (e.score[0] + e.score[1] + e.score[2]) / 3;
		ListInsert_sq(L, i, e);
	}
}

//打印表L
Status printlist(SqList L) {
	int i;
	printf("姓名    学号        性别       高数     大英      程序    平均成绩\n");
	for (i = 0;i<L.length;i++)
		printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\n", L.elem[i].name, L.elem[i].stuno,
			L.elem[i].sex, L.elem[i].score[0], L.elem[i].score[1], L.elem[i].score[2], L.elem[i].avenueScore);
	printf("\n");
	return OK;
}
//菜单
void menu(int m, SqList *L) {
	int i = 0;
	//ElemType e;
	ElemType e;
	char stuno[10];
	switch (m) {
	case 1:
		printf("请你输入学号查找学生信息\n");
		scanf("%s",stuno);
		GetElem(L,stuno,&e);
		break;
	case 2:
		printf("请输入学生学号，要修改的课程:0代表高数，1代表英语，2代表程序设计\n");
		scanf("%s %d", stuno, &i);
		reviseList(L, stuno, i);
		break;
	case 3:
		assignment(L);
		printf("\n插入后的线性表是：\n");
		printlist(*L);
		break;
	case 4:
		printf("请输入学生学号\n");
		scanf("%s", stuno);
		ListDelete(L, stuno, &e);
		printf("\n删除后的线性表是：\n");
		printlist(*L);
		break;
	default:
		printf("你输错了命令！！！命令只有1到4！！");
	}
}
int main()
{
	SqList  L;
	int m = 0;
	Inilist_sq(&L);
	while (m != -1)
	{
		printf("----------------------------------------------------------\n");
		printf("1、查询\n2、修改\n3、插入\n4、删除\n退出请输入-1\n");
		scanf("%d", &m);
		menu(m, &L);
	}
	DesroyList(&L);
	return 0;
}

