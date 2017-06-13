// 题目二.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include<stdio.h>
#include<malloc.h>
#include<math.h>
typedef struct {
	int key;
	int searchLength = 0;
}HashNum;
typedef struct {
	HashNum * elem;
	int ListSize;//表长
	int count;//元素总数目
	int mod;//模数
}HashTable;
void InitHashTable(HashTable * HB,int size) {
	HB->ListSize = size+2;
	HB->mod = HB->ListSize;
	HB->elem = (HashNum *)malloc((size+2)*sizeof(HashNum));
	for(int i=0;i<HB->ListSize;i++)
	HB->elem[i].key = NULL;
	HB->count = 0;
}
void oneExploreHash(HashTable * HB,int * num) {
	int index;
	for (int i = 0;i < HB->ListSize - 2;i++) {
		index = num[i] % (HB->mod);//访问地址的改变
		while (HB->elem[index].key) {
			HB->elem[index].searchLength++;//冲突次数累加
			index = (index + 1) % (HB->mod);//访问地址的改变
		}
		HB->elem[index].searchLength++;//冲突次数累加
		HB->elem[index].key = num[i];//不冲突填表
	}
}
void TwoExploreHash(HashTable * HB, int * num) {
	int index,j=0;
	int mnum;//用来记录第一次取模后的位置
	for (int i = 0;i < HB->ListSize - 2;i++) {
		index = num[i] % (HB->mod);
		while (HB->elem[index].key) {
			j++;
			mnum=index;
			for(int m=0;m<2;m++){//对这个位置正负方向探测
			HB->elem[index].searchLength++;
			index = (mnum + (int)pow(-1, m)*j*j)%(HB->mod);
			if (!HB->elem[index].key)//找到不冲突就不向另一个方向访问
				break;
			}
		}
		j = 0;
		HB->elem[index].searchLength++;//冲突次数
		HB->elem[index].key = num[i];//找到不冲突填表
	}
}
int search(HashTable HB,int findkey,int *  p,int c) {
	//c用来代表是哪种探测一次或则二次
	int t = 1;
	int m;
	int searchnum=1;//查找次数，用于判断是否不存在这个数
	*p = (findkey) % (HB.mod);
	while (HB.elem[*p].key!=findkey&&searchnum<=HB.ListSize) {
		if (c == 1) {//一次探测
			*p = (*p + c) % (HB.mod);
		}
		else//二次探测
		{
			m = *p;//用来记录第一次取模的位置
			for (int j = 0;j < 2;j++) {//左右探测
				*p = (m + (int)pow((-1), j + 1)*(int)pow(t, c)) % (HB.mod);
				searchnum++;//查找次数加一
				if (HB.elem[*p].key == findkey)
					break;
			}
			t++;
		}
	}
	if (HB.elem[*p].key == findkey)
		return 1;
	else
		return 0;
}
int main()
{
	HashTable HB,HB1;
	int * num;
	int i;
	int size;
	int key;
	int p;
	printf("请输入您需要输入多少个数据\n");
	scanf("%d",&size);
	num = (int *)malloc(size * sizeof(int));
	printf("请输入一组数据\n");
	for (i = 0;i < size;i++)
		scanf("%d",&num[i]);
	InitHashTable(&HB,size);
	InitHashTable(&HB1, size);
	printf("下面一次探测和二次探测对你输入的数据验证\n");
//--------------------------一次线性探测
	printf("\n\n");
		printf("下面使用一次线性探测创建hash表\n");
	oneExploreHash(&HB,num);
	printf("\n请您输入要查找的关键数（一次线性探测）\n");
	scanf("%d",&key);
	if (search(HB, key, &p, 1) == 1)
		printf("\n查找成功,位置是%d\n", p);
	else
		printf("\n查找失败\n");
	printf("\n\n\n\n");
	//----------------二次探测
	printf("下面使用二次线性探测创建hash表\n");
	TwoExploreHash(&HB1,num);
	printf("\n请您输入要查找的关键数（二次线性探测）\n");
	scanf("%d", &key);
	if (search(HB1, key, &p, 2) == 1)
		printf("\n查找成功,位置是%d\n", p);
	else
		printf("\n查找失败\n");
    return 0;
}

