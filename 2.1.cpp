/*
一元稀疏多项式计算器。
（1）设Pn（x）和Qm（x）分别为两个一元稀疏多项式，利用单链表存储Pn(x)和Qm(x)。
（2）从键盘输入一元多项式的信息，建立一元稀疏多项式Pn(x)和Qm(x)，并输出。
（3）实现Pn(x)和Qm(x)相加，并输出两者的和Pn(x)+Qm(x)。
（4）实现Pn(x)和Qm(x)相减，并输出两者差Pn(x)-Qm(x)。
（5）就地逆置两者的差Pn(x)-Qm(x)。
*/
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define Status int
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define ElemType int
typedef struct polynomialList {
	ElemType coefficient;//系数
	ElemType exponent;//指数
	struct polynomialList * next;
} LNode, * pol_list;
Status InitList(pol_list * L){ 
	/* 构造一个空的线性链表 */
   pol_list head;
   head=(pol_list)malloc(sizeof(LNode)); /* 生成头结点 */
   if(head)
   {
	   head->next=NULL;
    * L= head;
     return OK;
   }
   else
     return ERROR;
 }
//前插法建立链表
void creakPol_list(pol_list * L, int n) {
        pol_list p,head;
		head = * L;
	p = (pol_list)malloc(sizeof(LNode));
	if (!p) exit(OVERFLOW);
	int i; 
	for (i = 0;i < n;i++) {
		p = (pol_list)malloc(sizeof(LNode));
		if (!p)  exit(OVERFLOW);
		printf("please input two num one is coefficient,one is exponent:\n ");
		scanf("%d", &p->coefficient);
		scanf("%d",&p->exponent);
		p->next =head->next;
		head->next = p;
	}
	*L = head;
}
Status ListDelete(pol_list * L, int pos, ElemType * e) {
	pol_list head;
	head = *L;
	pol_list p = head;
	pol_list q;
	int j = 0;
	while (p->next &&j < pos - 1)
	{
		j++;    p = p->next;
	}
	if (!(p->next) || j < pos - 1) return ERROR;
	q = p->next;
	p->next = q->next;
	* e = q->coefficient;
	free(q);
	return OK;
}
//合并链表按照加法或则减法原则进行 
	void MergeList_pol_list(pol_list * L1, pol_list * L2,int opera) {
		pol_list p1,p2,q1,q2;	
		q1 = *L1;
		q2 = *L2;
		p1=q1->next;
		int j;
		ElemType  e1,e2;
		while(p1) {
			j = 0;
			p2 = q2->next;
			while (p2) {
				j++;
 				if (p1->exponent==p2->exponent) {
					if(opera ==0)
						p1->coefficient = p1->coefficient + p2->coefficient;
					else
					{
						p1->coefficient = p1->coefficient - p2->coefficient;
					}
					p2 = p2->next;
					ListDelete(L2, j, &e2);
				}
				else
					p2 = p2->next;
			}
			p1 = p1->next;
		}
		p1 = q1->next;
		while (p1->next) p1 = p1->next;
		p2 = q2->next;
		if (p2)  p1->next = p2;
	}
	//排序 按递减有序排序
	void sortList(pol_list * L1) {
		pol_list p1, p2;
		int temp;
		ElemType e1, e2;
		p1 = (*L1)->next;
		while (p1 ) {
			p2 = p1->next;
			while (p2) {
				if (p1->exponent < p2->exponent) {
					temp = p1->exponent;
					p1->exponent = p2->exponent;
					p2->exponent = temp;
					temp = p1->coefficient;
					p1->coefficient = p2->coefficient;
					p2->coefficient = temp;
				}
				p2 = p2->next;
			}
			p1 = p1->next;
		}
	}
	//逆置链表
	Status reverse_list(pol_list * L) {
		pol_list q, p, head;
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
	//链表的输出 
	Status visit(pol_list * L) {
		pol_list head, p;
		head = *L;
		p = head->next;
		printf("-----------------------------------------\n");
		printf("系数    指数\n");
		while (p) {
			printf("%d\t %d\t\n", p->coefficient, p->exponent);
			p = p->next;
		}
		return OK;
	}
	//销毁链表
	Status DestroyList(pol_list * L) {
		while (*L) {
			pol_list p = *L;
			*L = (*L)->next;
			free(p);
		}
		*L = NULL;
		return OK;
	}
int main()
{
	pol_list L1=NULL,L2=NULL,head,p;
	InitList(&L1);
	InitList(&L2);
	int n, opera;
	printf("对于第一个多项式你想输入多少个？？\n");
	scanf("%d",&n);
	creakPol_list(&L1,n);
	printf("对于第二个多项式你想输入多少个？？\n");
	scanf("%d", &n);
    creakPol_list(&L2, n);
	printf("please input 0 do add(+) else do sub(-)\n");
	scanf("%d",&opera);
	MergeList_pol_list(&L1,&L2, opera);
	sortList(&L1);

	visit(&L1);
	if (opera != 0) {
		reverse_list(&L1);
		printf("逆置后：\n");
		visit(&L1);
	}
    return 0;
}

