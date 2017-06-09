// 矩阵快速转置与矩阵相加.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
#define Status int 
#define Elemtype int
#define MAXSIZE 12500
#define OK 1
#define OVERFLOW -1
typedef struct {
	int i,j;//该元素的下标
	Elemtype e;
}tripe;
typedef struct {
	tripe data[MAXSIZE +1];
	int mu, nu, tu;//行数 列数 非零元个数
}TSMatrix;
//随机稀疏矩阵
Status createArray(int mu, int nu, Elemtype * *  Array) {
	int i, j;
	
	for (i = 0;i < mu;i++)
		for (j = 0;j < nu;j++)
			Array[i][j] = rand()%3;
	return OK;
}
//二维矩阵转换成三元顺序表
Status createSMatrix(int mu, int nu, TSMatrix * A, Elemtype * * Array){
	int i, j;
	int tu=0;
	for(i=0;i<mu;i++)
		for (j = 0;j < nu;j++) {
			if (Array[i][j] != 0) {
				tu++;
				A->data[tu].e = Array[i][j];
				A->data[tu].i = i+1;
				A->data[tu].j = j+1;
	}	
		}
	A->data[0].e = tu;
	A->data[0].i = mu;
	A->data[0].j = nu;
	A->mu = mu;
	A->nu = nu;
	A->tu = tu;
	A->tu = tu;
	return OK;
}
//快速逆置矩阵
Status FastTransposeSMtrix(TSMatrix * A, TSMatrix * TA) {
	int col, t, p, q;
	int cept[MAXSIZE + 1];
	int num[MAXSIZE + 1];
	TA->data[0].i=TA->mu = A->nu; TA->data[0].j= TA->nu = A->mu; TA->data[0].e=TA->tu = A->tu;
	if (TA->tu) {
		for (col = 1;col <= A->nu;++col) 
			num[col] = 0;
		for (t = 1;t <= A->tu;t++) 
			++num[A->data[t].j];
		cept[1] = 1;
		for (col = 2;col <= A->nu;col++)	cept[col] = cept[col - 1] + num[col - 1];
		for (p = 1;p <= A->tu;++p) {
			col = A->data[p].j; 
			q = cept[col];
			TA->data[q].i = A->data[p].j;
			TA->data[q].j = A->data[p].i;
			TA->data[q].e = A->data[p].e;
			++cept[col];
		}			
	}
	return OK;
}
/* 三元组表示的稀疏矩阵加法: C=A+B */
Status AddTSM(TSMatrix A, TSMatrix B, TSMatrix * C)
{
	int ai, bi, ci, aj, bj, cj, as, bs, cs;
	as = bs = cs = 1;
	if (A.mu != B.mu || A.nu != B.nu) {
		return -1;
	}
	C->data[0].i=C->mu = A.mu;
	C->data[0].j=C->nu = A.nu;
	C->data[0].e=C->tu = A.tu;
	while (as <= A.tu && bs <= B.tu) {
		ai = A.data[as].i;
		bi = B.data[bs].i;
		if (ai > bi) {
			ci = bi;
			while (ci == B.data[bs].i) {
				C->data[cs].i = ci;
				C->data[cs].j = B.data[bs].j;
				C->data[cs].e = B.data[bs].e;
				++bs;
				++cs;
			}
		}
		else if (ai < bi) {
			ci = ai;
			while (ci == A.data[as].i) {
				C->data[cs].i = ci;
				C->data[cs].j = A.data[as].j;
				C->data[cs].e = A.data[as].e;
				++as;
				++cs;
			}
		}
		else if (ai == bi) {
			ci = ai;
			aj = A.data[as].j;
			bj = B.data[bs].j;
			if (aj > bj) {
				C->data[cs].i = ci;
				C->data[cs].j = bj;
				C->data[cs].e = B.data[bs].e;
				++cs;
				++bs;
			}
			else if (aj < bj) {
				C->data[cs].i = ci;
				C->data[cs].j = aj;
				C->data[cs].e = A.data[as].e;
				++cs;
				++as;
			}
			else if (aj == bj) {
				if (A.data[as].e + B.data[bs].e != 0) {
					C->data[cs].i = ci;
					C->data[cs].j = aj;
					C->data[cs].e = A.data[as].e + B.data[bs].e;
					++cs;
				}
				++as;
				++bs;
			}
		}
	}
	//以上为稀疏矩阵A或B中的元素完全加完的情况  
	//以下为稀疏矩阵A或B中的元素部分剩余的情况  
	while (as <= A.tu) {
		C->data[cs].i = A.data[as].i;
		C->data[cs].j = A.data[as].j;
		C->data[cs].e = A.data[as].e;
		++cs;
		++as;
	}
	while (bs <= B.tu) {
		C->data[cs].i = B.data[bs].i;
		C->data[cs].j = B.data[bs].j;
		C->data[cs].e = B.data[bs].e;
		++cs;
		++bs;
	}
	C->tu = --cs;
	return OK;
}
//把三元组转换成矩阵输出
Status InputJUzhen(TSMatrix * A) {
	int t = 1, m, n, tt = 0;
	while (t <A->tu) {
		for (m = 0;m < A->mu;m++) {
			for (n = 0;n < A->nu;n++)
				if ((m + 1) == A->data[t].i&(n + 1) == A->data[t].j) {
					printf("%d\t", A->data[t].e);
					t++;
				}
				else {
					printf("0\t");
				}
				printf("\n");
		}
	}
	if (A->data[t].i<A->mu) {
		for (;m < A->mu;m++) {
			for (;n < A->nu;n++)
				printf("0\t");
			printf("\n");

		}
			
	}
	return OK;
}

Status viewArr(int mu,int nu,Elemtype * * Array) {
	int i,j;
	for (i = 0;i < mu;i++) {
		for (j = 0;j < nu;j++) {
			printf("%d\t", Array[i][j]);
		}
		printf("\n");
	}
		
	return OK;
}
Status viewSMtraix(TSMatrix * A) {
	int i, j;
	printf("i         j       e\n");
	for (i = 0;i<A->tu+1;i++)
			printf("%d\t%d\t%d\t\n", A->data[i].i, A->data[i].j,A->data[i].e);
	return OK;
}

int main()
{ 
	srand((unsigned)time(NULL));
	int mu, nu,i,j;
	TSMatrix  A, TA,B,C;
	Elemtype * * ArrayA;
	Elemtype * * ArrayB;
	printf("请输入矩阵M的行数与列数:\n");
	scanf("%d %d",&mu,&nu);
	ArrayA = (Elemtype **)malloc(mu*sizeof(Elemtype *));
	ArrayB = (Elemtype **)malloc(mu * sizeof(Elemtype *));
	for(i=0;i<mu;i++)
	ArrayA [i] = (Elemtype  *)malloc(nu * sizeof(Elemtype));
	for (i = 0;i<mu;i++)
	ArrayB[i] = (Elemtype  *)malloc(nu * sizeof(Elemtype));

	createArray(mu,nu,ArrayA);
	createSMatrix(mu,nu,&A,ArrayA);
	createArray(mu, nu, ArrayB);
	createSMatrix(mu, nu, &B, ArrayB);
	printf("矩阵A矩阵表示:\n");
	viewArr(mu, nu, ArrayA);
	printf("矩阵B矩阵表示:\n");
	viewArr(mu, nu, ArrayB);
	printf("三元组顺序表A:\n");
	viewSMtraix(&A);
	FastTransposeSMtrix(&A,&TA);
	printf("快速转置后矩阵A三元组表示:\n");
    viewSMtraix(&TA);
	printf("快速转置后矩阵A矩阵表示:\n");
	InputJUzhen(&TA);
	AddTSM(A,B,&C);
	printf("A矩阵加B矩阵得到c矩阵三元组表示:\n");
	viewSMtraix(&C);
	printf("A矩阵加B矩阵得到c矩阵矩阵表示:\n");
	InputJUzhen(&C);
    return 0;
}

