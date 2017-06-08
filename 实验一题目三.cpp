// ʵ��һ������.cpp : �������̨Ӧ�ó������ڵ㡣


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
	//����ѧ���ṹ�����ͣ�����������ѧ�ţ����䣬�ɼ�
	char name[20];
	char stuno[10];
	int sex;
	int score[3];
	int avenueScore;
}ElemType;
typedef struct {
	ElemType * elem;//�洢�ռ��ַ
	int length;//��ǰ����
	int listsize;//��ǰ����Ĵ洢����
}SqList;

//��ʼ������
Status Inilist_sq(SqList *L) {
	//����һ���յ����Ա�
	//�洢�ռ��ַ����ʼ�����Ա�ʱ����malloc��������100����λ�ռ䡣
	L->elem = (ElemType *)malloc(LIST_INT_SIZE * sizeof(ElemType));
	if (!L->elem) {
		exit(OVERFLOW);//�ռ����ʧ��
	}
	L->length = 0;//��������ĳ�ʼ����Ϊ0
	L->listsize = LIST_INT_SIZE;//��ʼ�洢����
	return OK;//�ռ����ɹ�
}
//�������
Status ListInsert_sq(SqList * L, int i, ElemType e) {
	if (i < 1 || i > L->length + 1)//�ж��������Ԫ���Ƿ񳬹�����С�뵱ǰ����
		return ERROR;

	if (L->length >= L->listsize) {//�жϵ�ǰ��Ԫ�صļ����Ƿ��ʹ��֮ǰ������ڴ��Ѿ������ã���������þͷ���һ���µ��ڴ�

		ElemType * newbase = (ElemType *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));/*realloc������������������
																											�����˼����һ������Ϊԭ�����׵�ַ���ڶ�������Ϊ���ڵĳ��� */

		if (!newbase)//�ж��Ƿ�ɹ��������µĿռ�
			exit(OVERFLOW);
		L->elem = newbase;//���·���Ŀռ���׵�ַ��ֵ��ԭ���Ļ�ַ
		L->listsize = +LISTINCREMENT;
	}
	ElemType * q = &(L->elem[i - 1]);//�ҵ�Ҫ�����Ԫ�صĵ�ַ��ֵ��q
	ElemType * p = &(L->elem[L->length - 1]);//�ҵ����һ��Ԫ�ظ�ֵ��p
											 //��Ԫ�غ���
	for (;p >= q;p--)
		*(p + 1) = *p;//��Ҫ�����Ԫ�ظ�ֵ��q
	*q = e;
	L->length++;
	return OK;
}
//ɾ������
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
//��������
Status DesroyList(SqList *L) {
	free(L->elem);
	return OK;
}
//�޸Ŀγ̷���
Status reviseList(SqList * L, char * stuno, int i) {
	int j = 0;
	while (strcmp(L->elem[j].stuno, stuno) != 0)
		j++;
	if (j <= L->length) {
		printf("��������Ҫ�޸ĵĿγ̵ķ���\n");
		scanf("%d", &(L->elem[j].score[i]));
		printf("%d", L->elem[j].score[i]);
	}
	else {
		printf("��Ҫ�޸ĵ�ѧ�Ų�����\n");
		return ERROR;
	}
	return OK;
}
Status GetElem(SqList * L, char * stuno, ElemType * e) {
	int i = 0;
	while (strcmp(L->elem[i].stuno, stuno) != 0) 
		i++;
	e = &(L->elem[i]);
	printf("����    ѧ��        �Ա�       ����     ��Ӣ      ����    ƽ���ɼ�\n");
	printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\n", e->name, e->stuno,
		e->sex, e->score[0], e->score[1], e->score[2], e->avenueScore);
	return OK;
}
//��ֵ��ѧ���Ĳ���
void  assignment(SqList * L) {
	int i = 0, len;
	ElemType e;
	printf("��Ҫ�������ѧ������:\n");
	scanf("%d", &len);
	for (i = 1;i <= len;i++)
	{
		printf("���������� ѧ�� �Ա�0��1Ů�� �����ɼ� ��ѧӢ��ɼ� ������ƻ����ɼ� : \n");
		scanf("%s %s %d %d %d %d", e.name, e.stuno, &e.sex, &e.score[0], &e.score[1], &e.score[2]);
		e.avenueScore = (e.score[0] + e.score[1] + e.score[2]) / 3;
		ListInsert_sq(L, i, e);
	}
}

//��ӡ��L
Status printlist(SqList L) {
	int i;
	printf("����    ѧ��        �Ա�       ����     ��Ӣ      ����    ƽ���ɼ�\n");
	for (i = 0;i<L.length;i++)
		printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\n", L.elem[i].name, L.elem[i].stuno,
			L.elem[i].sex, L.elem[i].score[0], L.elem[i].score[1], L.elem[i].score[2], L.elem[i].avenueScore);
	printf("\n");
	return OK;
}
//�˵�
void menu(int m, SqList *L) {
	int i = 0;
	//ElemType e;
	ElemType e;
	char stuno[10];
	switch (m) {
	case 1:
		printf("��������ѧ�Ų���ѧ����Ϣ\n");
		scanf("%s",stuno);
		GetElem(L,stuno,&e);
		break;
	case 2:
		printf("������ѧ��ѧ�ţ�Ҫ�޸ĵĿγ�:0���������1����Ӣ�2����������\n");
		scanf("%s %d", stuno, &i);
		reviseList(L, stuno, i);
		break;
	case 3:
		assignment(L);
		printf("\n���������Ա��ǣ�\n");
		printlist(*L);
		break;
	case 4:
		printf("������ѧ��ѧ��\n");
		scanf("%s", stuno);
		ListDelete(L, stuno, &e);
		printf("\nɾ��������Ա��ǣ�\n");
		printlist(*L);
		break;
	default:
		printf("������������������ֻ��1��4����");
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
		printf("1����ѯ\n2���޸�\n3������\n4��ɾ��\n�˳�������-1\n");
		scanf("%d", &m);
		menu(m, &L);
	}
	DesroyList(&L);
	return 0;
}

