 /*1.设计并验证以下算法：设顺序表L中的数据元素为整数且非递增有序，删除其值相同的元素，即顺序表L中西安通的元素只保留一个，并逆置删除后的顺序表L。
 （1）根据键盘输入输入数据建立顺序表L.
 （2）输出顺序表L、删除值相同多余元素后的顺序表L、逆置的顺序表L.
 （3）假设顺序表L的长度为n，要求以O(n)的时间复杂度完成后对值相同多余元素的删除。*/
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define LIST_INT_SIZE 100  //线性表存储空间的初始分配量
#define  LISTINCREMENT 10 //线性表存储空间奉陪的增量
#define Status int
#define OK 1
#define OVERFLOW 0
#define ERROR -1
typedef struct {
	int * elem;//存储空间基址
	int length;//当前长度
	int listsize;//当前分配的存储容量
}SqList;
//初始空链表
Status Inilist_sq(SqList *L) {
	L->elem = (int *)malloc(LIST_INT_SIZE * sizeof(int));
	if (!L->elem) {
		exit(OVERFLOW);
	}
	L->length = 0;//设置链表的初始长度为0
	L->listsize = LIST_INT_SIZE;//初始存储容量
	return OK;
}
//销毁线性链表
Status DesroyList(SqList * L) {
	free(L->elem);
	return OK;
}
//插入操作
Status ListInsert_sq(SqList * L, int i, int e) {
	if (i < 1 || i > L->length + 1)//判断所插入的元素是否超过或则小与当前长度
		return ERROR;
	if (L->length >= L->listsize) {//判断当前新元素的加入是否会使得之前分配的内存已经不够用，如果不够用就分配一个新的内存
		int * newbase = (int *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(int));/*realloc函数在这里是增加内
																							 存的意思，第一个参数为原来的首地址，第二个参数为现在的长度 */
		if (!newbase)//判断是否成功分配了新的空间
			exit(OVERFLOW);
		L->elem = newbase;//将新分配的空间的首地址赋值给原来的基址
		L->listsize = +LISTINCREMENT;
	}
	//找到要插入的元素的地址赋值给q,找到最后一个元素赋值给p
	int * q = &(L->elem[i - 1]);
	int * p = &(L->elem[L->length - 1]);
	//把元素后移
	for (;p >= q;p--)
		*(p + 1) = *p;
	//把要插入的元素赋值给q
	*q = e;
	L->length++;
	return OK;
}
//删除表中相同元素的操作
void purgr_sq(SqList *L) {
	int k = -1;//判断表尾
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
//逆置顺序表
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
//递减排序
Status SortUnionLIst(SqList *L) {
	int t;
	int i = 0;
	//外层循环决定一共走多少趟
	for (int i = 0;i<L->length - 1;i++)
		//内层循环 如果一个数比另外一个数大，则交换他们
		for (int j = 0;j < L->length - i - 1;j++) 
			if (L->elem[j] < L->elem[j+1]) {
				t = L->elem[j];
				L->elem[j] = L->elem[j+1];
				L->elem[j+1] = t;
			}
	return OK;
}
//输出线性表的操作
Status printlist(SqList * L) {//输入表L
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
	printf("请输入想要输入的数据个数：\n");
	scanf("%d",&length);
	printf("请你开始输入数据：\n");
	for (i = 0;i < length;i++) {
		scanf("%d",&num);
		ListInsert_sq(&L,i+1,num);
	}
	SortUnionLIst(&L);//递减排序
	printlist(&L);//输出排序后的线性表

	purgr_sq(&L);//删除置相通的元素
	printf("删除重复的元素后的线性表：\n");
	printlist(&L);

	InverseList(&L);
	printf("逆置后的线性表\n");
	printlist(&L);
	DesroyList(&L);//销毁线性表
	return 0;
}

