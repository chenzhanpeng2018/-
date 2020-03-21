#if 0
//2019.12.26
//1.
//将两个有序序列合并成为一个有序序列
#include<iostream>
#include<windows.h>
using namespace std;
int main()
{
	int M1[] = { 1, 3, 4, 6, 8 };
	int M2[] = { 2, 5, 8, 9, 20, 30};
	int size1 = sizeof(M1)/sizeof(M1[0]);
	int size2 = sizeof(M2)/sizeof(M2[0]);
	//printf("%d %d", size1, size2);
	int index1 = 0;
	int index2 = 0;
	int index = 0;
	int M[100];
	while (index1<size1&&index2<size2)
	{
		if (M1[index1] <= M2[index2])
		{
			M[index++] = M1[index1++];
		}
		else
		{
			M[index++] = M2[index2++];
		}
	}
	while (index1 < size1)
	{
		M[index++] = M1[index1++];
	}
	while (index2 < size2)
	{
		M[index++] = M2[index2++];
	}


	int i = 0;
	for (; i < size1 + size2; i++)
	{
		printf("%d ", M[i]);
	}
	system("pause");
	return 0;
}
#endif

#if 0
//2.
//查找字符串第一个出现一次的字符
#include<iostream>
#include<windows.h>
using namespace std;

int main()
{
	char str[100]="abcdfeabcd";
	int all[256]={0};
	int len=strlen(str);
	int i=0;
	for(;i<len;i++)
	{
		all[str[i]]++;	
	} 

	for(i=0;i<len;i++)
	{
		if(1==all[str[i]])
		{
			printf("%c\n",str[i]);
			break; 
		}
	}
	system("pause");
	return 0;
}
#endif


#if 0
//3.
//顺序表的操作
#include<iostream>
#include<assert.h>
#include<windows.h>
using namespace std;

//动态顺序表结构
//优势：存储元素个数不受限，不够再给你开辟
typedef int  DataType;
typedef struct SeqList
{
	DataType* array;  //数组
	int capacity;     //表示空间总大小
	int size;        //记录有效元素个数
}SeqList;

//顺序表基本接口实现


//顺序表的初始化
void SeqListInit(SeqList* ps, int capacity)
{
	//将ps所指向的SeqList类型结构体变量个个字段初始化
	//申请capacity大小的一段空间
	//size,记录元素个数

	//条件：
	//判断是否申请成功
	//所给容量不能小于等于0
	//ps指针不能为空，为空就不用处理了
	if (NULL == ps)
	{
		assert(0);
		return;  //跳出去
	}

	ps->capacity = capacity <= 0 ? 10 : capacity;
	ps->array = (DataType*)malloc(ps->capacity*sizeof(DataType));
	ps->size = 0;
}

//顺序表的销毁
void SeqListDestroy(SeqList* ps)
{
	if (ps)
	{
		free(ps->array);  //释放申请的空间
		ps->array = NULL; //指针置空
		ps->capacity = 0; //容量置0
		ps->size = 0;     //元素个数置0
	}
}

//扩容
void SeqListCheckCapacity(SeqList* ps)// 检查空间，如果满了，进行增容
{
	size_t newcapacity;
	assert(ps);
	if (ps->size == ps->capacity)
	{
		newcapacity = (ps->capacity == 0) ? 4 : ps->capacity * 2;//三目运算符
		ps->array = (DataType*)realloc(ps->array, sizeof(DataType)*newcapacity);
		ps->capacity = newcapacity;
	}
}

//尾插 O(1)
void SeqListPushBack(SeqList* ps, DataType data)
{
	if (NULL == ps)
	{
		assert(0);
		return;
    }
	//检测容量，考虑是否需要扩容
	SeqListCheckCapacity(ps);


	ps->array[ps->size] = data;
	ps->size++;
}

//尾删  O(1)
void SeqListPopBack(SeqList* ps)
{

	//ps指向的顺序表的结构体类型变量是否为空
	if (NULL == ps)
	{
		assert(0);
		return;
	}

	//顺序表为空:顺序表存在,只是顺序变中没有有效元素
	if (0 == ps->size)
	{
		return;
	}

	ps->size--;
}

//头插  O(N)
void SeqListPushFront(SeqList* ps, DataType data)
{
	if (NULL == ps)
	{
		assert(0);
		return;
	}
	//检测是否需要扩容
	SeqListCheckCapacity(ps);

	//插入元素
	//1.将顺序表中的所有元素往后挪一个位置，从后往前一个一个挪
	for (int i = ps->size - 1; i >= 0; i--)  //i:待挪位置的元素下标
	{
		ps->array[i + 1] = ps->array[i];//挪到后面（i->i+1）
	}
	//2.插入元素
	ps->array[0] = data;
	ps->size++;
}

//头删
void SeqListPopFront(SeqList* ps)
{
	if (NULL == ps)
	{
		assert(0);
		return;
	}

	//判断是否有元素
	if (0 == ps->size)
	{
		return;
	}

	//将0号位置之后的元素一次向前挪一个位置,直接覆盖就行
	for (int i = 1; i < ps->size; i++)
	{
		ps->array[i - 1] = ps->array[i];
	}
	ps->size--;
}

//任意位置的插入
void SeqListInsert(SeqList* ps, int pos, DataType data)
{
	if (NULL == ps)
	{
		assert(0);
		return;
	}
	//容量检测
	SeqListCheckCapacity(ps);

	//插入元素
	//1.将顺序表中pos位置开始的元素往后挪一个位置，从后往前一个一个挪
	for (int i = ps->size - 1; i >= pos; i--)  //i:待挪位置的元素下标
	{
		ps->array[i + 1] = ps->array[i];//挪到后面（i->i+1）
	}
	//2.插入元素
	ps->array[pos] = data;
	ps->size++;
}

//任意位置的删除
void SeqListErase(SeqList* ps, int pos)
{
	if (NULL == ps)
	{
		assert(0);
		return;
	}
	//从pos后一个位置开始，依次覆盖前面的元素
	for (int i = pos+1; i < ps->size; i++)
	{
		ps->array[i - 1] = ps->array[i];
	}
	ps->size--;
}

//在顺序表中查找值为data的元素，返回下标
int SeqListFind(SeqList* ps, DataType data)
{
	if (NULL == ps)
	{
		assert(0);
		return 0;
	}

	for (int i = 0; i < ps->size; i++)
	{
		if (data == ps->array[i])
		{
			return i;
		}
	}

	return -1;
}

//检测顺序表中是否为空
int SeqListEmpty(SeqList* ps)
{
	if (NULL == ps)
	{
		assert(0);
		return 0;
	}

	return ps->size == 0;
}

//将顺序表中的元素清空
void SeqListClear(SeqList* ps)
{
	if (NULL == ps)
	{
		assert(0);
		return;
	}

	ps->size = 0;
}
//打印顺序表
void PrintfSList(SeqList* ps)
{
	for (DataType i = 0; i < ps->size; i++)
	{
		printf("%d ", ps->array[i]);
	}
}
int main()
{
	SeqList  L;
	SeqListInit(&L, 10);
	//尾插
	SeqListPushBack(&L, 1);
	SeqListPushBack(&L, 2);
	SeqListPushBack(&L, 3);
	SeqListPushBack(&L, 4);
	SeqListPushBack(&L, 5);
	PrintfSList(&L);
	printf("\n");
	SeqListInsert(&L, 0, 15);
	PrintfSList(&L);

	system("pause");
	return 0;
}
#endif



#if 0
//4
//无头结点单链表基本操作
#include<stdio.h>
#include<assert.h>
#include<malloc.h>
#include<Windows.h>

typedef int DateType;

typedef struct SLNode
{
	int data;//当前内容
	struct SLNode* next;//下一个位置
}SLNode;//重命名
//自己验证：按照上述方法定义结构体，加typedef和不加,SLNode的区别

/*
如果方法中需要修改头指针(L)的指向，就传递二级指针
如果不需要修改，传递一级指针
*/
//尾插/删
void SLPushBack(SLNode** head, DateType data);
void SLPopBack(SLNode** head);
//头插/删
void SLPushFront(SLNode** head, DateType data);
void SLPopFront(SLNode** head);
//在pos位置之后插入data
void SLInsertAfter(SLNode*  pos, int data);
//把pos位置的节点删除(有可能是第一个节点)
void SLErase(SLNode** head, SLNode* pos);
//获取链表节点个数
int SLSize(SLNode* head);
//在链表中找到值为data的节点
SLNode* SLFind(SLNode* head, int data);
//销毁链表
void SLDestroy(SLNode** head);
//打印当前链表(没有修改，只需要打印，传一级指针就行)
void PrintfSList(SLNode* head);
//测试函数
void TestSList1();
void TestSList();


//申请节点
SLNode* BuySLNode(DateType data)
{
	//申请一个SLNode结构体类型的newNode
	SLNode* newNode = (SLNode*)malloc(sizeof(SLNode));
	if (NULL == newNode)
	{
		printf("申请节点失败！\n");
		assert(newNode);
	}

	newNode->data = data; //把内容存下来
	newNode->next = NULL; //把下一个地址先置空
	return newNode;
}
//尾插
//head中的内容就是&L
//如果想要改变实参L的指向,*head结果就是L本身
//注意：空链表和链表不存在的区别
//空链表：链表已经存在,只不过链表中没有有效节点
//链表不存在：都没有头指针

//assert:一般用于针对程序的非法情况
//if判断：程序正常的一种可能性情况
void SLPushBack(SLNode** head, DateType data)
{
	//1.要先遍历到链表最后一个节点tail
	//  最后一个节点的特点,next为NULL
	//  借助一个临时指针tail,从链表的起始位置不断遍历(检测tail->next是否为空即可)
	//2.让最后一个节点的next域指向新节点
	// tail->next=newNode
	
	//链表是否存在
	assert(head);
	SLNode* newNode = BuySLNode(data);
	
	//链表是否为空链表(没有任何节点的链表)
	if (NULL == *head)
	{
		//第一个节点为空,第一个节点的插入方式
		*head = newNode;
	}
	else
	{
		//说明链表中有节点
		//尾插
		//1.先去找链表中最后一个节点(next为NULL)
		SLNode* tail = *head;
		while (tail->next)
		{
			//注意：tail++;(这种像顺序表的遍历方式(直接++)是错误的)
			tail = tail->next;
		}
		//2.将新节点连接在最后一个节点之后
		tail->next = newNode;
	}
}
//尾删
void SLPopBack(SLNode** head)
{
	//在删除时链表是什么样子？
	//1.空链表 L=NULL;不需要删除,直接返回；
	//2.链表中只有一个节点：L--->1--->NULL;将1节点删除,链表成为空链表 L=NULL;
	//3.链表中有多个节点：L--->1--->2--->3--->4--->5--->NULL;
	//while(cur->next)  cur=cur->next  找到最后一个节点(尾)
	//并且用prev保存cur的前一个节点
	//prev->next=cur->next; free(cur); 就行

	assert(head);
	
	//空链表
	if (NULL == *head)
		return;
	else if (NULL == (*head)->next)
	{
		//链表中只有一个节点
		free(*head);
		*head = NULL;
	}
	else
	{
		//有多个节点
		//借助cur先找到最后一个节点,并用prev保存cur的前一个节点
		SLNode* cur = *head;
		SLNode* prev = NULL;
		while (cur->next)
		{
			prev = cur;
			cur = cur->next;
		}
		prev->next = cur->next;
		free(cur);
	}
}
//头插
void SLPushFront(SLNode** head, DateType data)
{
	//1.空链表 L=NULL; 插入成功后：L--->1--->NULL;
	//2.非空 L--->1--->2--->3--->4--->NULL;
	//0先指向1;L再指向0;(顺序不能改变)  L--->0--->1--->2--->3--->4--->NULL;
	//newNode->next=*head;
	//*head=newNode;
	assert(head);

	SLNode* newNode = BuySLNode(data);
	newNode->next = *head;
	*head = newNode;
}
//头删
void SLPopFront(SLNode** head)
{
	//head--->4--->3--->2--->1--->NULL;
	//先连接head--->3-->2--->1--->NULL;
	//再删除第一个节点(4);


	//链表是否存在
	assert(head);
	//链表是否为空
	if (NULL == *head)
	{
		return;
	}
	else
	{
		//一个节点和多个节点都适用(SLPopBack就不行)
		//把需要删的先保存起来(head指向的就是需要删除的)
		SLNode* delNode = *head;
		*head = delNode->next;
		free(delNode);
	}
}
//在pos位置之后插入data
void SLInsertAfter(SLNode*  pos, int data)
{
	//参数检测
	if (NULL == pos)
	{
		return;
	}
	SLNode* newNode = NULL;
	newNode = BuySLNode(data);
	newNode->next = pos->next;
	pos->next = newNode;
}
//把pos位置之后的节点删除(第一个节点删不了)
void SLEraseAfter(SLNode** head, SLNode* pos)
{
	//pos如果不存在
	//pos是最后一个节点
	//先连接，再删节点
	SLNode* delNode = NULL;
	if (NULL == pos || NULL == pos->next)
	{
		return;
	}
	delNode = pos->next;
	pos->next = delNode->next;
	free(delNode);
}
//获取链表节点个数
//head--->1--->2--->3--->4--->NULL
int SLSize(SLNode* head)
{
	int count = 0;
	SLNode* cur = head;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return count;
}
//在链表中找到值为data的节点
SLNode* SLFind(SLNode* head, int data)
{
	SLNode* cur = head;
	while (cur)
	{
		if (data == cur->data)
		{
			return cur;
		}
		cur=cur->next;
	}
	return NULL;
}
//销毁链表
void SLDestroy(SLNode** head)
{
	assert(head);
	SLNode *cur = *head;
	//先连接，再删除
	//头删法
	while (cur)
	{
		*head = cur->next;
		free(cur);
		cur = *head;
	}
}
//打印当前链表
void PrintfSList(SLNode* head)
{
	SLNode* cur = head;
	while (cur)
	{
		printf("%d--->",cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}

////////////////////////////////////////
//测试函数
void TestSList1()
{
	//L:空的链表
	SLNode* L = NULL;
	//尾插 1,2,3,4,5
	SLPushBack(&L, 1);
	SLPushBack(&L, 2);
	SLPushBack(&L, 3);
	SLPushBack(&L, 4);
	SLPushBack(&L, 5);
	PrintfSList(L);
	
	//SLInsertAfter(L, 8);
	//PrintfSList(L);

    //尾删
	//SLPopBack(&L);
	//PrintfSList(L);
	
	//头删
	//SLPopFront(&L);
	//PrintfSList(L);

	////任意位置后插入
	//SLInsertAfter(SLFind(L, 3), 6);
	//PrintfSList(L);

	////打印节点个数
	//printf("%d\n",SLSize(L));

	////删除pos之后的节点
	//SLEraseAfter(&L,SLFind(L, 3));
	//PrintfSList(L);

	////销毁
	//SLDestroy(&L);
	//PrintfSList(L);

}
//测试函数
void TestSList()
{
	TestSList1();
}
int main()
{
	TestSList();
	system("pause");
	return 0;
}

#endif

#if 0
//5
//带头结点双向循环链表
//可以不用二级指针，因为头结点位置不会改变
//所有的操作都是基于头结点之后去操作的
#include<iostream>
#include<assert.h>
#include<malloc.h>

typedef int DataType;

typedef struct DListNode
{
	DataType data;
	struct DListNode *next;
	struct DListNode *prev;
}DListNode;

//申请节点空间
DListNode *BuyDListNode(DataType data);
//创建空链表，含头结点
DListNode* CreatDList();
//尾插/删
void DListPushBack(DListNode* pHead, DataType data);
void DListPopBack(DListNode* pHead);
//头插/删
void DListPushFront(DListNode* pHead, DataType data);
void DListPopFront(DListNode*pHead);
//在pos位置插入新节点(往pos位置前面插入)
void DListInsert(DListNode* pos, DataType data);
//删除pos位置节点
void DListErase(DListNode* pos);
//查找Data数据节点
DListNode* DListFind(DListNode* pHead, DataType data);
//销毁链表
void DListDestroy(DListNode* pHead);


//申请节点空间
DListNode *BuyDListNode(DataType data)
{
	DListNode* newNode = (DListNode*)malloc(sizeof(DListNode));
	if (NULL == newNode)
	{
		assert(0);
		return NULL;
	}
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}
//申请头结点
//带头结点的双向循环链表
//空链表也有头结点，且自己指自己
DListNode* CreatDList()
{
	DListNode* head = BuyDListNode(0);
	head->next = head;
	head->prev = head;
	return head;
}
//尾插
void DListPushBack(DListNode* pHead, DataType data)
{
	if (NULL == pHead)
	{
		return ;
	}
	//申请节点
	DListNode* newNode = BuyDListNode(data);

	//先连接再断开
	newNode->prev = pHead->prev;//把pHead->prev(链表中的最后一个节点)给newNode->prev
	newNode->next = pHead;
	pHead->prev->next = newNode;
	pHead->prev = newNode;
}
//尾删
void DListPopBack(DListNode* pHead)
{ 
	assert(pHead);//assert是一个调试宏，在debug底下有效，release底下不存在
	if (NULL == pHead)
	{
		assert(0);
		return;
	}
	//检测是否为空链表
	if (pHead->next == pHead)
	{
		return;
	}
	//先连接再删除
	DListNode *pos = pHead->prev;

	pHead->prev = pos->prev;
	pos->prev->next = pHead;
	free(pos);

}
//头插
void DListPushFront(DListNode* pHead, DataType data)
{
	if (NULL == pHead)
	{
		return;
	}
	//调用pos位置的插入
	DListInsert(pHead->next, data);
}
//头删
void DListPopFront(DListNode* pHead)
{
	if (NULL == pHead)
	{
		return;
	}
	//调用pos位置的删除
	DListErase(pHead->next);
}
//在pos位置插入新节点(往pos位置前面插入)
void DListInsert(DListNode* pos, DataType data)
{
	DListNode* newNode = BuyDListNode(data);
	//先连接再断开
	newNode->prev = pos->prev;
	newNode->next = pos;
	newNode->prev->next = newNode;
	pos->prev = newNode;
}
//删除pos位置节点
void DListErase(DListNode* pos)
{
	if (NULL == pos)
	{
		return;
	}
	//先连接，再删除
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(pos);
}
//查找Data数据节点
DListNode* DListFind(DListNode* pHead, DataType data)
{
	//检测链表是否存在
	if (NULL == pHead)
	{
		return NULL;
	}
	DListNode* cur = pHead->next;
	while (cur != pHead)
	{
		if (cur->data== data)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
//销毁链表
//最后要改变头指针使其指向NULL，所以必须传递二级指针
void DListDestroy(DListNode** pHead)
{
	DListNode* cur = NULL;
	//保证链表存在
	if (NULL == pHead)
	{
		return;
	}
	//删除有效节点
	cur = (*pHead)->next;
	while (cur != *pHead)
	{
		(*pHead)->next = cur->next;
		free(cur);
		cur = (*pHead)->next;
	}
	free(*pHead);
	*pHead = NULL;
}
//打印双向循环链表
void PrintfDList(DListNode* pHead)
{
	if (NULL == pHead)
	{
		return;
	}
	DListNode *cur = pHead->next;
	printf("pHead-->");
	while (cur != pHead)
	{
		printf("%d-->", cur->data);
		cur = cur->next;
	}
	printf("pHead\n");
}
//测试函数
void Test1()
{
	//申请头结点
	DListNode* head = CreatDList();
	//尾插
	DListPushBack(head, 1);
	DListPushBack(head, 2);
	DListPushBack(head, 3);
	DListPushBack(head, 4);
	DListPushBack(head, 5);
	PrintfDList(head);

	//销毁链表
	DListDestroy(&head);
}
//测试函数
void Test()
{
	Test1();
}
int main()
{
	Test();
	system("pause");
	return 0;
}
#endif

#if 0
//6
//栈结构实现
//静态栈-->栈中存储元素个数受限
//实际应用中很少用静态栈，因为元素受限
//在笔试中需要用到栈而没有结构时，临时实现栈结构-->建议：实现静态的栈(容易实现)
#include<iostream>
#include<assert.h>
#include<malloc.h>

typedef int DataType;
#define MAX_SIZE 100

typedef struct Stack
{
	DataType* array;
	int capacity;  //容量
	int size;
}Stack;

//栈的初始化
void StackInit(Stack* ps);
//容量检测
void CheckCapacity(Stack* ps);
//入栈
void StackPush(Stack* ps);
//出栈
void StackPop(Stack* ps);
//获取栈顶元素
DataType StackTop(Stack* ps);
//获取栈中有效元素个数
DataType StackSize(Stack* ps);
//检测栈是否为空
DataType StackEmpty(Stack* ps);
//销毁
void StackDestroy(Stack* ps);


//栈的初始化
void StackInit(Stack* ps)
{
	assert(ps);
	ps->array = (DataType*)malloc(sizeof(DataType) * 10);
	ps->capacity = 10;
	ps->size = 0;
}
//检测容量
void CheckCapacity(Stack* ps)
{
	//1.申请新空间
	//2.拷贝元素
	//3.释放旧空间
	if (ps->size >= ps->capacity)
	{
		//申请新空间
		int newCapacity = ps->capacity * 2;
		DataType* temp = (DataType*)malloc(sizeof(DataType)*newCapacity);

		if (temp)
		{
			//拷贝元素
			//memcpy(temp,ps->array,sizeof(DataType)*ps->capacity);
			for (int i = 0; i < ps->size; i++)
			{
				temp[i] = ps->array[i];
			}
			//释放旧空间
			free(ps->array);

			ps->array = temp;
		}
	}
}
//入栈
void StackPush(Stack* ps,DataType data)
{
	assert(ps);
	//检测容量是否够
	CheckCapacity(ps);

	//插入元素
	ps->array[ps->size] = data;
	ps->size++;
}
//出栈
void StackPop(Stack* ps)
{
	if (StackEmpty(ps))
	{
		return;
	}
	ps->size--;
}
//获取栈顶元素
DataType StackTop(Stack* ps)
{
	assert(ps);
	return ps->array[ps->size-1];
}
//获取栈中有效元素个数
DataType StackSize(Stack* ps)
{
	assert(ps);
	return ps->size;
}
//检测栈是否为空
DataType StackEmpty(Stack* ps)
{
	assert(ps);
	return 0 == ps->size;
}
//销毁
void StackDestroy(Stack* ps)
{
	assert(ps);
	free(ps);
	ps->capacity=0;
	ps->size = 0;
}



//测试函数
void Test1()
{
	Stack s;
	//栈的初始化
	StackInit(&s);
	//入栈
	StackPush(&s, 1);
	StackPush(&s, 2);
	StackPush(&s, 3);
	StackPush(&s, 4);
	StackPush(&s, 5);
	printf("%d\n",StackTop(&s));
	printf("%d\n",StackSize(&s));
	StackPop(&s);
	//销毁
	StackDestroy(&s);
}
//测试函数
void Test()
{
	Test1();
}
int main()
{
	Test();
	system("pause");
	return 0;
}
#endif


#if 1
//7
//队列结构实现
#include<iostream>
#include<assert.h>
#include<malloc.h>

typedef int QDataType;

//队列底层使用链表中的节点结构
typedef struct QNode
{
	struct QNode* next;
	QDataType val;
}QNode;

struct Queue
{
	QNode* head;
	QNode* rear;
	int size;
};
//申请节点
QNode* BuyQNode(int val);
//队列的初始化
void QueueInit(Queue* q);
//入队列
void QueuePush(Queue* q);
//出队列
void QueuePop(Queue* q);
//获取队列中有效元素个数
QDataType QueueSize(Queue* q);
//检测队列是否为空
QDataType QueueEmpty(Queue* q);
//获取队头元素
QDataType QueueFront(Queue* q);
//获取队尾元素
QDataType QueueBack(Queue* q);
//销毁队列
void QueueDestroy(Queue* q);


//申请节点
QNode* BuyQNode(int val)
{
	QNode* newNode = (QNode*)malloc(sizeof(QNode));
	if (NULL == newNode)
	{
		assert(0);
		return NULL;
	}
	newNode->val = val;
	newNode->next = NULL;
	return newNode;
}
//队列的初始化
//加个头结点
void QueueInit(Queue* q)
{
	assert(q);
	q->head = BuyQNode(0);
	q->size = 0;
	q->rear = q->head;
}
//入队列
void QueuePush(Queue* q, QDataType val)
{
	assert(q);
	QNode* newNode = BuyQNode(val);
	q->rear->next = newNode;
	q->rear = newNode;
	q->size++;
}
//出队列
void QueuePop(Queue* q)
{
	QNode* pDelNode = NULL;
	if (QueueEmpty(q))
	{
		return;
	}
	pDelNode = q->head->next;
	q->head->next = pDelNode->next;
	free(pDelNode);
	q->size--;
}
//获取队列中有效元素个数
int QueueSize(Queue* q)
{
	assert(q);
	return q->size;
}
//检测队列是否为空
int QueueEmpty(Queue* q)
{
	assert(q);
	return 0 == q->size;
}
//获取队头元素
QDataType QueueFront(Queue* q)
{
	assert(!QueueEmpty(q));
	return q->head->next->val;
}
//获取队尾元素
QDataType QueueBack(Queue* q)
{
	assert(!QueueEmpty(q));
	return q->rear->val;
}
//销毁队列
void QueueDestroy(Queue* q)
{
	assert(q);
	QNode* cur =q->head->next;
	while(cur)
	{
		q->head->next=cur->next;
		free(cur);
		cur = q->head;
	}
	free(q);
	q = NULL;
}


//测试函数
void Test1()
{
	Queue q;
	//初始化
	QueueInit(&q);
	//入队列
	QueuePush(&q, 1);
	QueuePush(&q, 2);
	QueuePush(&q, 3);
	QueuePush(&q, 4);
	QueuePush(&q, 5);
	
	printf("size=%d\n", QueueSize(&q));
	printf("Front=%d\n", QueueFront(&q));
	printf("Back=%d\n", QueueBack(&q));
	
	
	////出队列
	//void QueuePop(Queue* q);
	////获取队列中有效元素个数
	//QDataType QueueSize(Queue* q);
	////检测队列是否为空
	//QDataType QueueEmpty(Queue* q);
	////获取队头元素
	//QDataType QueueFront(Queue* q);
	////获取队尾元素
	//QDataType QueueBack(Queue* q);
}
//测试函数
void Test()
{
	Test1();
}
int main()
{
	Test();
	system("pause");
	return 0;
}
#endif