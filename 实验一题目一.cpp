#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define LIST_INT_SIZE 100  //���Ա�洢�ռ�ĳ�ʼ������
#define  LISTINCREMENT 10 //���Ա�洢�ռ���������
#define Status int
#define OK 1
#define OVERFLOW 0
#define ERROR -1
typedef struct {
	int * elem;//�洢�ռ��ַ
	int length;//��ǰ����
	int listsize;//��ǰ����Ĵ洢����
}SqList;
//��ʼ������
Status Inilist_sq(SqList *L) {
	L->elem = (int *)malloc(LIST_INT_SIZE * sizeof(int));
	if (!L->elem) {
		exit(OVERFLOW);
	}
	L->length = 0;//��������ĳ�ʼ����Ϊ0
	L->listsize = LIST_INT_SIZE;//��ʼ�洢����
	return OK;
}
//������������
Status DesroyList(SqList * L) {
	free(L->elem);
	return OK;
}
//�������
Status ListInsert_sq(SqList * L, int i, int e) {
	if (i < 1 || i > L->length + 1)//�ж��������Ԫ���Ƿ񳬹�����С�뵱ǰ����
		return ERROR;
	if (L->length >= L->listsize) {//�жϵ�ǰ��Ԫ�صļ����Ƿ��ʹ��֮ǰ������ڴ��Ѿ������ã���������þͷ���һ���µ��ڴ�
		int * newbase = (int *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(int));/*realloc������������������
																							 �����˼����һ������Ϊԭ�����׵�ַ���ڶ�������Ϊ���ڵĳ��� */
		if (!newbase)//�ж��Ƿ�ɹ��������µĿռ�
			exit(OVERFLOW);
		L->elem = newbase;//���·���Ŀռ���׵�ַ��ֵ��ԭ���Ļ�ַ
		L->listsize = +LISTINCREMENT;
	}
	//�ҵ�Ҫ�����Ԫ�صĵ�ַ��ֵ��q,�ҵ����һ��Ԫ�ظ�ֵ��p
	int * q = &(L->elem[i - 1]);
	int * p = &(L->elem[L->length - 1]);
	//��Ԫ�غ���
	for (;p >= q;p--)
		*(p + 1) = *p;
	//��Ҫ�����Ԫ�ظ�ֵ��q
	*q = e;
	L->length++;
	return OK;
}
//ɾ��������ͬԪ�صĲ���
void purgr_sq(SqList *L) {
	int k = -1;//�жϱ�β
	int j;
	for (int i = 0;i<L->length;i++) {
		j = 0;
		while (j <= k&&L->elem[j] != L->elem[i])
			++j;
		if (k == -1 || j>k)
			L->elem[++k] = L->elem[i];
	}
	L->length = k + 1;
}
//����˳���
Status InverseList(SqList *L) {
	int *p, *q,t;
	p =&(L->elem[0]);
	q = &(L->elem[L->length-1]);
	for (;p <= q;p++, q--) {
		t = *p;
		*p = *q;
		*q = t;
	}
	return OK;
}
//�ݼ�����
Status SortUnionLIst(SqList *L) {
	int t;
	int i = 0;
	//���ѭ������һ���߶�����
	for (int i = 0;i<L->length - 1;i++)
		//�ڲ�ѭ�� ���һ����������һ�������򽻻�����
		for (int j = 0;j < L->length - i - 1;j++) 
			if (L->elem[j] < L->elem[j+1]) {
				t = L->elem[j];
				L->elem[j] = L->elem[j+1];
				L->elem[j+1] = t;
			}
	return OK;
}
//������Ա�Ĳ���
Status printlist(SqList * L) {//�����L
	int i;
	for (i = 0;i<L->length;i++)
		printf("%d ", *(L->elem + i));
	printf("\n");
	return OK;
}
int main()
{
	SqList L;
	int length;
	int num;
	int i;
	Inilist_sq(&L);
	printf("��������Ҫ��������ݸ�����\n");
	scanf("%d",&length);
	printf("���㿪ʼ�������ݣ�\n");
	for (i = 0;i < length;i++) {
		scanf("%d",&num);
		ListInsert_sq(&L,i+1,num);
	}
	SortUnionLIst(&L);//�ݼ�����
	printlist(&L);//������������Ա�

	purgr_sq(&L);//ɾ������ͨ��Ԫ��
	printf("ɾ���ظ���Ԫ�غ�����Ա�\n");
	printlist(&L);

	InverseList(&L);
	printf("���ú�����Ա�\n");
	printlist(&L);
	DesroyList(&L);//�������Ա�
	return 0;
}

