// ����ʽֵ--�����븡����.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMNENT 10
#define OVERFLOW -2
#define ERROR 0
#define OK 1
#define Status int
#define SElemType1 char  //���������
#define SElemType2 float//����������
char operato[7] = { '+','-','*','/','(',')','#' };//���������һ�����
//������ṹ��
typedef struct {
	SElemType1 * top;//ջ��ָ��
	SElemType1 * base;//ջ����ָ��
	int stacksize;//ջ��
}SqOPTRstack;
//�������ṹ��
typedef struct {
	SElemType2 * top;//ջ��ָ��
	SElemType2 * base;//ջ����ָ��
	int stacksize;//ջ��
}SqOPNDstack;

//�������һЩ��������
//1.��ʼ��
Status InitOPTRStack(SqOPTRstack * S) {
	S->base = (SElemType1 *)malloc(STACK_INIT_SIZE * sizeof(SElemType1));
	if (!S->base) exit(OVERFLOW);
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return OK;
}
//2.���ջ��Ԫ��
SElemType1 GetOPTRTOP(SqOPTRstack * S) {
	if (S->top == S->base) return ERROR;
	char e = *(S->top - 1);
	return e;
}
//3.ѹջ
Status PushOPTR(SqOPTRstack * S, SElemType1 * e) {
	if ((S->top - S->base) > S->stacksize) {
		S->base = (SElemType1 *)realloc(S, (STACK_INIT_SIZE + STACKINCREMNENT) * sizeof(SElemType1));
		if (!S->base) exit(OVERFLOW);
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMNENT;
	}
	*S->top++ = *e;
	return OK;
}
//4.��ջ
Status PopOPTR(SqOPTRstack * S, SElemType1 * e) {
	if (S->top == S->base) return ERROR;
	*e = *(--S->top);
	return OK;
}
//��������һЩ��������
////1.��ʼ��
Status InitOPNDStack(SqOPNDstack * S) {
	S->base = (SElemType2 *)malloc(STACK_INIT_SIZE * sizeof(SElemType2));
	if (!S->base) exit(OVERFLOW);
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return OK;
}
//2.���ջ��Ԫ��
float GetOPNDTOP(SqOPNDstack * S) {
	if (S->top == S->base) return ERROR;
	return *(S->top - 1);
}
//3.ѹջ
Status PushOPND(SqOPNDstack * S, SElemType2 * e) {
	if ((S->top - S->base) >= S->stacksize) {
		S->base = (SElemType2 *)realloc(S, (STACK_INIT_SIZE + STACKINCREMNENT) * sizeof(SElemType2));
		if (!S->base) exit(OVERFLOW);
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMNENT;
	}
	*S->top++ = *e;
	return OK;
}
//4.��ջ
float PopOPND(SqOPNDstack * S) {
	if (S->top == S->base) return ERROR;
	float e = *--S->top;
	return e;
}



//�����ж����������֣�С���㻹�������
bool In(char c) {
	if ((c >= '0'&&c <= '9') || c == '.') {
		return false;
	}
	else
		return true;
}
//�������ȼ�
char prior[7][7] = { '>','>','<','<','<','>','>',
'>','>','<','<','<','>','>',
'>','>','>','>','<','>','>',
'>','>','>','>','<','>','>',
'<','<','<','<','<','=',' ',
'>','>','>','>',' ','>','>',
'<','<','<','<','<',' ','=',
};
//�Ƚ�c1,c2�����ȼ�������һ�����ڻ���С��
char Precede(char c1, char c2) {
	int i, j;
	for (i = 0;i<7;i++)
		if (operato[i] == c1) break;
	for (j = 0;j < 7;j++)
		if (operato[j] == c2) break;
	return prior[i][j];
}
//�������������a,b�����㣬����������
float Operate(float a, char theta, float b) {
	switch (theta)
	{
	case '+':
		return a + b;
		break;
	case '-':
		return b - a;
		break;
	case '*':
		return a * b;
		break;
	case '/':
		return b / a;
		break;
	}
}
//��׺ת��׺����
float EvaluateExpression() {
	SqOPTRstack OPTR;
	SqOPNDstack OPND;
	char s[50];
	float itemp = 0, ftemp = 0, a, b;
	float i = 0;
	char x;
	char * c, theta, firstOPTR;
	firstOPTR = '#';
	c = &firstOPTR;
	InitOPTRStack(&OPTR);
	PushOPTR(&OPTR, c);
	InitOPNDStack(&OPND);
	scanf("%s", &s);
	c = s;
	do {
		if (!In(*c)) {
			if (*c != '.')
				itemp = itemp * 10 + (*c - 48);
			while (*c == '.')
			{
				while (!In(*(c + 1))) {
					i++;c++;
					ftemp = ftemp + (*c - 48) / pow(10, i);
				}
			}
			itemp += ftemp;
			if (In(*(c + 1))) {
				printf("%.3f ", itemp);
				PushOPND(&OPND, &itemp);

				itemp = 0;
				ftemp = 0;
				i = 0;
			}
			c++;
		}
		else {
			switch (Precede(GetOPTRTOP(&OPTR), *c)) {
			case '<':
				PushOPTR(&OPTR, c);
				c++;
				break;
			case '=':
				PopOPTR(&OPTR, &x);
				c++;
				break;
			case '>':
				PopOPTR(&OPTR, &theta);
				a = PopOPND(&OPND);b = PopOPND(&OPND);
				float num = Operate(a, theta, b);
				PushOPND(&OPND, &num);
				printf("%c ", theta);
				break;
			}
		}
	} while (*c != '#' || GetOPTRTOP(&OPTR) != '#');
	printf("\n%s", s);
	return GetOPNDTOP(&OPND);
}
int main() {
	printf("��������ʽ����������=����#�Ž�����:\n");
	float num = EvaluateExpression();
	printf("=");
	printf("%f\n", num);
	return 0;
}



