// ��Ŀ��.cpp : �������̨Ӧ�ó������ڵ㡣
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
	int ListSize;//��
	int count;//Ԫ������Ŀ
	int mod;//ģ��
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
		index = num[i] % (HB->mod);//���ʵ�ַ�ĸı�
		while (HB->elem[index].key) {
			HB->elem[index].searchLength++;//��ͻ�����ۼ�
			index = (index + 1) % (HB->mod);//���ʵ�ַ�ĸı�
		}
		HB->elem[index].searchLength++;//��ͻ�����ۼ�
		HB->elem[index].key = num[i];//����ͻ���
	}
}
void TwoExploreHash(HashTable * HB, int * num) {
	int index,j=0;
	int mnum;//������¼��һ��ȡģ���λ��
	for (int i = 0;i < HB->ListSize - 2;i++) {
		index = num[i] % (HB->mod);
		while (HB->elem[index].key) {
			j++;
			mnum=index;
			for(int m=0;m<2;m++){//�����λ����������̽��
			HB->elem[index].searchLength++;
			index = (mnum + (int)pow(-1, m)*j*j)%(HB->mod);
			if (!HB->elem[index].key)//�ҵ�����ͻ�Ͳ�����һ���������
				break;
			}
		}
		j = 0;
		HB->elem[index].searchLength++;//��ͻ����
		HB->elem[index].key = num[i];//�ҵ�����ͻ���
	}
}
int search(HashTable HB,int findkey,int *  p,int c) {
	//c��������������̽��һ�λ������
	int t = 1;
	int m;
	int searchnum=1;//���Ҵ����������ж��Ƿ񲻴��������
	*p = (findkey) % (HB.mod);
	while (HB.elem[*p].key!=findkey&&searchnum<=HB.ListSize) {
		if (c == 1) {//һ��̽��
			*p = (*p + c) % (HB.mod);
		}
		else//����̽��
		{
			m = *p;//������¼��һ��ȡģ��λ��
			for (int j = 0;j < 2;j++) {//����̽��
				*p = (m + (int)pow((-1), j + 1)*(int)pow(t, c)) % (HB.mod);
				searchnum++;//���Ҵ�����һ
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
	printf("����������Ҫ������ٸ�����\n");
	scanf("%d",&size);
	num = (int *)malloc(size * sizeof(int));
	printf("������һ������\n");
	for (i = 0;i < size;i++)
		scanf("%d",&num[i]);
	InitHashTable(&HB,size);
	InitHashTable(&HB1, size);
	printf("����һ��̽��Ͷ���̽����������������֤\n");
//--------------------------һ������̽��
	printf("\n\n");
		printf("����ʹ��һ������̽�ⴴ��hash��\n");
	oneExploreHash(&HB,num);
	printf("\n��������Ҫ���ҵĹؼ�����һ������̽�⣩\n");
	scanf("%d",&key);
	if (search(HB, key, &p, 1) == 1)
		printf("\n���ҳɹ�,λ����%d\n", p);
	else
		printf("\n����ʧ��\n");
	printf("\n\n\n\n");
	//----------------����̽��
	printf("����ʹ�ö�������̽�ⴴ��hash��\n");
	TwoExploreHash(&HB1,num);
	printf("\n��������Ҫ���ҵĹؼ�������������̽�⣩\n");
	scanf("%d", &key);
	if (search(HB1, key, &p, 2) == 1)
		printf("\n���ҳɹ�,λ����%d\n", p);
	else
		printf("\n����ʧ��\n");
    return 0;
}

