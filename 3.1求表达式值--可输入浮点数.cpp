// 求表达式值--可输入浮点数.cpp : 定义控制台应用程序的入口点。
//
/*
首先讲一个中缀表达式转换成逆波兰式，然后对逆波兰式求值。
（1）表达式求值是程序设计语言编译中的一个基本问题。通常，表达式由运算符、操作数、界限符组成，算式表达式中最常见的表示法形式由中缀、前缀和后缀表达式。中缀表示法是书写表达式的常见方式，前缀和后缀表示法主要用于计算机科学领域。
  a.中缀表达式：运算符在两操作数的中间。在运算中存在运算符的优先权与综合性的问题。列如运算a/b-(c+d)*f时，编译器即至左向右逐一检查，当检查到第一个运算符除时还无法知道是否执行；待检查到第一个运算符‘-' 时,因为知道除的级别高于减，才知道执行‘a/b’；当检查到“（”时，可知道先执行括号里的内容。
 b.前缀表达式：运算符放在两操作数的前面。这种表达式经常用于计算机科学，特别是编译器设计方面。为纪念其发明家Jan Lukasiewicz,该表达式也称波兰表达式。
c.后缀表达式：运算符放在两操作数的后面。后缀表达式也称逆波兰表达式，因其表达式求值变得轻松，所以被普遍使用。
             前缀和后缀表示法有以下共同特征:操作数的顺序与等价的中缀表达式中操作数的顺序一致、不需要括号、操作数的优先级不相关。
（2）要求从键盘读入一个包括加减乘除、括号与正整数的中缀表达式，将其转换成后缀表达式存入一张线性表并输出，对后缀表达式求值并输出。
（3）将中缀表达式转换成后缀表达式的过程中，需要定义一个操作符栈；对后缀表达式求值的过程中，需要定义一个操作数栈。
（4）教材“表3.1算符间的优先关系”可用一个二维数组来描述：
char prior[7][7] = { 
'>','>','<','<','<','>','>',
'>','>','<','<','<','>','>',
'>','>','>','>','<','>','>',
'>','>','>','>','<','>','>',
'<','<','<','<','<','=',' ',
'>','>','>','>',' ','>','>',
'<','<','<','<','<',' ','=',
};
*/
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
#define SElemType1 char  //运算符类型
#define SElemType2 float//运算数类型
char operato[7] = { '+','-','*','/','(',')','#' };//给运算符给一个序号
//运算符结构体
typedef struct {
	SElemType1 * top;//栈顶指针
	SElemType1 * base;//栈顶底指针
	int stacksize;//栈长
}SqOPTRstack;
//运算数结构体
typedef struct {
	SElemType2 * top;//栈顶指针
	SElemType2 * base;//栈顶底指针
	int stacksize;//栈长
}SqOPNDstack;

//运算符的一些基本操作
//1.初始化
Status InitOPTRStack(SqOPTRstack * S) {
	S->base = (SElemType1 *)malloc(STACK_INIT_SIZE * sizeof(SElemType1));
	if (!S->base) exit(OVERFLOW);
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return OK;
}
//2.获得栈顶元素
SElemType1 GetOPTRTOP(SqOPTRstack * S) {
	if (S->top == S->base) return ERROR;
	char e = *(S->top - 1);
	return e;
}
//3.压栈
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
//4.出栈
Status PopOPTR(SqOPTRstack * S, SElemType1 * e) {
	if (S->top == S->base) return ERROR;
	*e = *(--S->top);
	return OK;
}
//运算数的一些基本操作
////1.初始化
Status InitOPNDStack(SqOPNDstack * S) {
	S->base = (SElemType2 *)malloc(STACK_INIT_SIZE * sizeof(SElemType2));
	if (!S->base) exit(OVERFLOW);
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return OK;
}
//2.获得栈顶元素
float GetOPNDTOP(SqOPNDstack * S) {
	if (S->top == S->base) return ERROR;
	return *(S->top - 1);
}
//3.压栈
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
//4.出栈
float PopOPND(SqOPNDstack * S) {
	if (S->top == S->base) return ERROR;
	float e = *--S->top;
	return e;
}



//用于判断数据是数字，小数点还是运算符
bool In(char c) {
	if ((c >= '0'&&c <= '9') || c == '.') {
		return false;
	}
	else
		return true;
}
//定义优先级
char prior[7][7] = { '>','>','<','<','<','>','>',
'>','>','<','<','<','>','>',
'>','>','>','>','<','>','>',
'>','>','>','>','<','>','>',
'<','<','<','<','<','=',' ',
'>','>','>','>',' ','>','>',
'<','<','<','<','<',' ','=',
};
//比较c1,c2的优先级，返回一个大于或者小于
char Precede(char c1, char c2) {
	int i, j;
	for (i = 0;i<7;i++)
		if (operato[i] == c1) break;
	for (j = 0;j < 7;j++)
		if (operato[j] == c2) break;
	return prior[i][j];
}
//根据运算符，对a,b做运算，返回运算结果
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
//中缀转后缀核心
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
	printf("请输入表达式（不用输入=输入#号结束）:\n");
	float num = EvaluateExpression();
	printf("=");
	printf("%f\n", num);
	return 0;
}



