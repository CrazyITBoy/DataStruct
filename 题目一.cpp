#include "stdafx.h"
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>
#include<sys/timeb.h>
#define KeyType int
#define InfoType int
#define MAXSIZE 5000
#define MAXLength 20
#define LQ(a,b) ((a)<=(b))
#define LT(a,b) ((a)<(b))
int comparenum=0;
int gonum=0;
int swapnum=0;
int needinput=0;//这里决定每趟排序是否输出
typedef struct {
	KeyType key;
	InfoType otherinfo;
}RedType;
typedef struct {
	RedType * r;
	int length;
}SqList;
void initSqList(SqList * L) {
	L->r = (RedType *)malloc((MAXSIZE+1)*sizeof(RedType));
	if (!L->r) {
		printf("分配失败已经退出\n");
		exit(-1);
	}
	else
		L->length = 0;
}
void createSqList(SqList *L) {
	/*printf("请输入数据的长度\n");
	scanf("%d",&L->length);
	srand(time(NULL));
	for (int i = 1;i <= L->length;i++)
		L->r[i].key = rand();*/
	L->length = 12;
	int a[] = {520,144,589,246,377,899,17,125,433,999,213,66};
	for (int i = 1;i <=12;i++)
		L->r[i].key = a[i-1];
}
void outSort(SqList * L) {
	int i;
	for (i = 1;i <= L->length;i++) {
		printf("%d\t  ", L->r[i].key);
		if (i % 10 == 0)
			printf("\n");
	}
}
long getRunTime(struct timeb t1, struct timeb t2) {
	long t;
	t = (t2.time - t1.time) * 1000 + (t2.millitm - t1.millitm);
	return t;
}
//swap
void swap(RedType * type1,RedType * type2) {
	RedType  t;
	t = *type1;
	*type1 = *type2;
	*type2 = t;
}

//直接插入排序
void insertSort(SqList * L) {
	int i, j;
	for (i = 2;i < L->length;i++) {//进行多少趟排序
		if (L->r[i].key < L->r[i - 1].key) {
			comparenum++;
			L->r[0] = L->r[i];
			for (j = i - 1;L->r[0].key < L->r[j].key;j--) {//对那个元素进行排序
				L->r[j + 1] = L->r[j];
				comparenum++;
				gonum++;
			}
			L->r[j + 1] = L->r[0];
		}
		if (needinput == 1) {
			printf("\n第%d次排序:\n", i);
			outSort(L);
		}	
	}
}
//折半插入排序
void BinsertSort(SqList *L) {
	if (!L->length) {
		printf("L is empty\n");
		exit(-2);
	}
	int low, high;
	int i,j;
	int m;
	for (i = 0;i < L->length;i++) {
		low = 0;
		high = i - 1;
		L->r[0] = L->r[i];
		while (low <= high)
		{
			m = (low + high) / 2;
			if (L->r[0].key < L->r[m].key) {
				high = m - 1;
				comparenum++;
			}
			else
				low = m+1;
		}
		for (j = i - 1;j >= high - 1;--j) {
			L->r[j + 1] = L->r[j];
			gonum++;
		}
		L->r[high+1] = L->r[0];
		if (needinput == 1) {
			printf("\n第%d次排序:\n", i);
			outSort(L);
		}
	}
}
//希尔排序
void shellInsert(SqList *L, int dk) {
	int i, j;
	for (i = dk + 1;i <=L->length;++i)
		if (L->r[i].key < L->r[i - dk].key) {
			comparenum++;
			L->r[0] = L->r[i];
			for (j = i - dk;j > 0 && (L->r[j].key > L->r[0].key);j -= dk) {
				L->r[j + dk] = L->r[j];
				comparenum++;
				gonum++;
			}
			L->r[j + dk] = L->r[0];
		}
}

void shellSort(SqList *L,int * dlta,int t) {
	if (!L->length) {
		printf("L is empty\n");
		exit(-2);
	}
	for (int i = 0;i < t;i++) {
		shellInsert(L, dlta[i]);
		if (needinput == 1) {
			printf("\n第%d次排序:\n", i);
			outSort(L);
		}
	}
		
}

//冒泡排序
void BubbleSort(SqList * L) {
	if (!L->length) {
		printf("L is empty\n");
		exit(-2);
	}
	RedType t;
	int i, j;
	for (i = 1;i < L->length;i++)
		for (j = 1;j <= L->length - i;j++)
			if (L->r[j].key > L->r[j + 1].key) {
				swap(&L->r[j], &L->r[j + 1]);
				swapnum++;
				comparenum++;
			}
	if (needinput == 1) {
		printf("\n第%d次排序:\n", i);
		outSort(L);
	}
				
}
//一趟快速派速
int Partition(SqList * L, int low, int high) {
	L->r[0] = L->r[low];
	int pivotkey = L->r[low].key;
	while (low<high) {
		while (low < high&&L->r[high].key >= pivotkey) {
			--high;
			comparenum++;
		}
		L->r[low] = L->r[high];
		while (low < high&&L->r[low].key <= pivotkey) {
			comparenum++;
			++low;
		}
		L->r[high] = L->r[low];
		gonum++;
	}
	L->r[low] = L->r[0];
	return low;
}
//快速排序
int runnum=0;
void QSort(SqList * L,int low,int high) {
	int pivotloc;
	int i = 0;
	if (low<high) {
		pivotloc = Partition(L, low, high);
		if (needinput == 1) {
			printf("\n第%d次排序:\n", ++runnum);
			outSort(L);
		}
		QSort(L,low, pivotloc -1);
		QSort(L, pivotloc +1, high);
	}
}
void QuilSort(SqList *L) {
	QSort(L,1,L->length);
}

//选择排序
void selectSort(SqList * L) {
	if (!L->length) {
		printf("error");
		return;
	}
	int i, j,min;
	for (i = 0;i < L->length;i++) {
		min = i;
		for (j = i;j < L->length;j++) 
			if (L->r[min].key > L->r[j].key) {
				comparenum++;
				min = j;
			}
		if (min != i) {
			swap(&L->r[min], &L->r[i]);
			swapnum++;
		}
		if (needinput == 1) {
			printf("\n第%d次排序:\n", i);
			outSort(L);
		}
	}
}

//堆排序
void HeapAdjust(SqList *h, int s, int m) 
{
	RedType rc;
	int j;
	rc = (*h).r[s];
	for (j = 2 * s;j <= m;j *= 2)
	{ 
		if (j < m&&LT((*h).r[j].key, (*h).r[j + 1].key)) {
			comparenum++;
			++j;
		}
		comparenum++;
		if (!LT(rc.key, (*h).r[j].key)) 
			break; 
		(*h).r[s] = (*h).r[j];
		s = j;
	}
	(*h).r[s] = rc; 
}

void HeapSort(SqList *h)
{ 
	RedType t;
	int i;
	for (i = (*h).length / 2;i > 0;--i) {
		HeapAdjust(h, i, (*h).length);
		if (needinput == 1) {
			printf("\n第%d次排序:\n", i);
			outSort(h);
		}
	}	
	for (i = (*h).length;i>1;--i)
	{ 
		swap(&(*h).r[1], &(*h).r[i]);
		swapnum++;
		HeapAdjust(h, 1, i - 1); 
		if (needinput == 1) {
					printf("\n第%d次排序:\n", i);
					outSort(h);
				}
	}
}
//归并排序
void Merge(RedType SR[], RedType TR[], int i, int m, int n,SqList * L)
{ /* 将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n] */
	int j, k, l;
	for (j = m + 1, k = i;i <= m&&j <= n;++k) /* 将SR中记录由小到大地并入TR */
		if LQ(SR[i].key, SR[j].key) {
			TR[k] = SR[i++];
			comparenum++;
		}
		else
			TR[k] = SR[j++];
	if (i <= m)
		for (l = 0;l <= m - i;l++)
			TR[k + l] = SR[i + l]; /* 将剩余的SR[i..m]复制到TR */
	if (j <= n)
		for (l = 0;l <= n - j;l++)
			TR[k + l] = SR[j + l]; /* 将剩余的SR[j..n]复制到TR */
	if (needinput == 1) {
		printf("\n第%d次排序:\n", ++runnum);
		outSort(L);
	}
}
void MSort(RedType SR[], RedType TR1[], int s, int t,SqList  *L)
{ /* 将SR[s..t]归并排序为TR1[s..t] */
	int m;
	RedType TR2[MAXSIZE + 1];
	if (s == t)
		TR1[s] = SR[s];
	else
	{
		m = (s + t) / 2; 
		MSort(SR, TR2, s, m,L); /* 递归地将SR[s..m]归并为有序的TR2[s..m] */
		if (needinput == 1) {
			printf("\n第%d次排序:\n", ++runnum);
			outSort(L);
		}
		MSort(SR, TR2, m + 1, t,L); /* 递归地将SR[m+1..t]归并为有序的TR2[m+1..t] */
		if (needinput == 1) {
			printf("\n第%d次排序:\n", ++runnum);
			outSort(L);
		}
		Merge(TR2, TR1, s, m, t,L); /* 将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t] */
	}
}

void MergeSort(SqList *L)
{ /* 对顺序表L作归并排序。*/
	MSort((*L).r, (*L).r, 1, (*L).length,L);
}

int main()
{
	SqList L;
	struct timeb t1, t2;
	int menu=0;
	int t;
	int dlta[MAXLength];
	while (menu!=9) {
		swapnum = 0;
		comparenum = 0;
		gonum = 0;
		initSqList(&L);
		createSqList(&L);
		t = 0;
		dlta[t] = L.length / 2;
		while (dlta[t]>1)
		{
			dlta[t + 1] = dlta[t] / 2;
			t++;
		}
		printf("\n未排序结果：\n");
		outSort(&L);
		printf("\n请输入数字对随机序列排序\n");
		printf("1.直接插入排序\n");
		printf("2.折半排序\n");
		printf("3.哈希表排序\n");
		printf("4.冒泡排序\n");
		printf("5.快速排序\n");
		printf("6.选择排序\n");
		printf("7.堆排序\n");
		printf("8.归并排序\n");
		printf("9.break\n");
		scanf("%d", &menu);
		if (menu==9) break;
		int istestRunTime,isneed;
		printf("是否需要测试运行时间:(是 输入1，不是 输入0)\n");
		scanf("%d",&istestRunTime);
		printf("是否需要得到每一趟排序:(是 输入1，不是 输入0)\n");
		scanf("%d",&isneed);
		if(isneed==1)
		needinput=1;
		ftime(&t1);
		switch (menu)
		{
		case 1:
			insertSort(&L);
			ftime(&t2);
			printf("\n\n%d 个数排序共花时间：%ld毫秒\n", L.length, getRunTime(t1, t2));
			outSort(&L);
			break;
		case 2:
			BinsertSort(&L);
			ftime(&t2);
			printf("\n\n%d 个数排序共花时间：%ld毫秒\n", L.length, getRunTime(t1, t2));
			outSort(&L);
			break;
		case 3:
			shellSort(&L, dlta, t);
			ftime(&t2);
			printf("\n\n%d 个数排序共花时间：%ld毫秒\n", L.length, getRunTime(t1, t2));
			outSort(&L);
			break;
		case 4:
			BubbleSort(&L);
			ftime(&t2);
			printf("\n\n%d 个数排序共花时间：%ld毫秒\n", L.length, getRunTime(t1, t2));
			outSort(&L);
			break;
		case 5:
			QuilSort(&L);
			ftime(&t2);
			printf("\n\n%d 个数排序共花时间：%ld毫秒\n", L.length, getRunTime(t1, t2));
			outSort(&L);
			break;
		case 6:
			selectSort(&L);
			ftime(&t2);
			printf("\n\n%d 个数排序共花时间：%ld毫秒\n", L.length, getRunTime(t1, t2));
			outSort(&L);
			break;
		case 7:
			HeapSort(&L);
			ftime(&t2);
			printf("\n\n%d 个数排序共花时间：%ld毫秒\n", L.length, getRunTime(t1, t2));
			outSort(&L);
			break;
		case 8:
			MergeSort(&L);
			ftime(&t2);
			printf("\n\n%d 个数排序共花时间：%ld毫秒\n", L.length, getRunTime(t1, t2));
			outSort(&L);
			break;
		default:
			break;
		}
		printf("\n\n一共移动次数：%d 比较次数: %d 交换次数：%d\n\n", gonum, comparenum, swapnum);
	}
	
}