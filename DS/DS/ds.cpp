#if 0
//2019.12.26
//1.
//�������������кϲ���Ϊһ����������
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
//�����ַ�����һ������һ�ε��ַ�
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
//˳���Ĳ���
#include<iostream>
#include<assert.h>
#include<windows.h>
using namespace std;

//��̬˳���ṹ
//���ƣ��洢Ԫ�ظ��������ޣ������ٸ��㿪��
typedef int  DataType;
typedef struct SeqList
{
	DataType* array;  //����
	int capacity;     //��ʾ�ռ��ܴ�С
	int size;        //��¼��ЧԪ�ظ���
}SeqList;

//˳�������ӿ�ʵ��


//˳���ĳ�ʼ��
void SeqListInit(SeqList* ps, int capacity)
{
	//��ps��ָ���SeqList���ͽṹ����������ֶγ�ʼ��
	//����capacity��С��һ�οռ�
	//size,��¼Ԫ�ظ���

	//������
	//�ж��Ƿ�����ɹ�
	//������������С�ڵ���0
	//psָ�벻��Ϊ�գ�Ϊ�վͲ��ô�����
	if (NULL == ps)
	{
		assert(0);
		return;  //����ȥ
	}

	ps->capacity = capacity <= 0 ? 10 : capacity;
	ps->array = (DataType*)malloc(ps->capacity*sizeof(DataType));
	ps->size = 0;
}

//˳��������
void SeqListDestroy(SeqList* ps)
{
	if (ps)
	{
		free(ps->array);  //�ͷ�����Ŀռ�
		ps->array = NULL; //ָ���ÿ�
		ps->capacity = 0; //������0
		ps->size = 0;     //Ԫ�ظ�����0
	}
}

//����
void SeqListCheckCapacity(SeqList* ps)// ���ռ䣬������ˣ���������
{
	size_t newcapacity;
	assert(ps);
	if (ps->size == ps->capacity)
	{
		newcapacity = (ps->capacity == 0) ? 4 : ps->capacity * 2;//��Ŀ�����
		ps->array = (DataType*)realloc(ps->array, sizeof(DataType)*newcapacity);
		ps->capacity = newcapacity;
	}
}

//β�� O(1)
void SeqListPushBack(SeqList* ps, DataType data)
{
	if (NULL == ps)
	{
		assert(0);
		return;
    }
	//��������������Ƿ���Ҫ����
	SeqListCheckCapacity(ps);


	ps->array[ps->size] = data;
	ps->size++;
}

//βɾ  O(1)
void SeqListPopBack(SeqList* ps)
{

	//psָ���˳���Ľṹ�����ͱ����Ƿ�Ϊ��
	if (NULL == ps)
	{
		assert(0);
		return;
	}

	//˳���Ϊ��:˳������,ֻ��˳�����û����ЧԪ��
	if (0 == ps->size)
	{
		return;
	}

	ps->size--;
}

//ͷ��  O(N)
void SeqListPushFront(SeqList* ps, DataType data)
{
	if (NULL == ps)
	{
		assert(0);
		return;
	}
	//����Ƿ���Ҫ����
	SeqListCheckCapacity(ps);

	//����Ԫ��
	//1.��˳����е�����Ԫ������Ųһ��λ�ã��Ӻ���ǰһ��һ��Ų
	for (int i = ps->size - 1; i >= 0; i--)  //i:��Ųλ�õ�Ԫ���±�
	{
		ps->array[i + 1] = ps->array[i];//Ų�����棨i->i+1��
	}
	//2.����Ԫ��
	ps->array[0] = data;
	ps->size++;
}

//ͷɾ
void SeqListPopFront(SeqList* ps)
{
	if (NULL == ps)
	{
		assert(0);
		return;
	}

	//�ж��Ƿ���Ԫ��
	if (0 == ps->size)
	{
		return;
	}

	//��0��λ��֮���Ԫ��һ����ǰŲһ��λ��,ֱ�Ӹ��Ǿ���
	for (int i = 1; i < ps->size; i++)
	{
		ps->array[i - 1] = ps->array[i];
	}
	ps->size--;
}

//����λ�õĲ���
void SeqListInsert(SeqList* ps, int pos, DataType data)
{
	if (NULL == ps)
	{
		assert(0);
		return;
	}
	//�������
	SeqListCheckCapacity(ps);

	//����Ԫ��
	//1.��˳�����posλ�ÿ�ʼ��Ԫ������Ųһ��λ�ã��Ӻ���ǰһ��һ��Ų
	for (int i = ps->size - 1; i >= pos; i--)  //i:��Ųλ�õ�Ԫ���±�
	{
		ps->array[i + 1] = ps->array[i];//Ų�����棨i->i+1��
	}
	//2.����Ԫ��
	ps->array[pos] = data;
	ps->size++;
}

//����λ�õ�ɾ��
void SeqListErase(SeqList* ps, int pos)
{
	if (NULL == ps)
	{
		assert(0);
		return;
	}
	//��pos��һ��λ�ÿ�ʼ�����θ���ǰ���Ԫ��
	for (int i = pos+1; i < ps->size; i++)
	{
		ps->array[i - 1] = ps->array[i];
	}
	ps->size--;
}

//��˳����в���ֵΪdata��Ԫ�أ������±�
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

//���˳������Ƿ�Ϊ��
int SeqListEmpty(SeqList* ps)
{
	if (NULL == ps)
	{
		assert(0);
		return 0;
	}

	return ps->size == 0;
}

//��˳����е�Ԫ�����
void SeqListClear(SeqList* ps)
{
	if (NULL == ps)
	{
		assert(0);
		return;
	}

	ps->size = 0;
}
//��ӡ˳���
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
	//β��
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
//��ͷ��㵥�����������
#include<stdio.h>
#include<assert.h>
#include<malloc.h>
#include<Windows.h>

typedef int DateType;

typedef struct SLNode
{
	int data;//��ǰ����
	struct SLNode* next;//��һ��λ��
}SLNode;//������
//�Լ���֤������������������ṹ�壬��typedef�Ͳ���,SLNode������

/*
�����������Ҫ�޸�ͷָ��(L)��ָ�򣬾ʹ��ݶ���ָ��
�������Ҫ�޸ģ�����һ��ָ��
*/
//β��/ɾ
void SLPushBack(SLNode** head, DateType data);
void SLPopBack(SLNode** head);
//ͷ��/ɾ
void SLPushFront(SLNode** head, DateType data);
void SLPopFront(SLNode** head);
//��posλ��֮�����data
void SLInsertAfter(SLNode*  pos, int data);
//��posλ�õĽڵ�ɾ��(�п����ǵ�һ���ڵ�)
void SLErase(SLNode** head, SLNode* pos);
//��ȡ����ڵ����
int SLSize(SLNode* head);
//���������ҵ�ֵΪdata�Ľڵ�
SLNode* SLFind(SLNode* head, int data);
//��������
void SLDestroy(SLNode** head);
//��ӡ��ǰ����(û���޸ģ�ֻ��Ҫ��ӡ����һ��ָ�����)
void PrintfSList(SLNode* head);
//���Ժ���
void TestSList1();
void TestSList();


//����ڵ�
SLNode* BuySLNode(DateType data)
{
	//����һ��SLNode�ṹ�����͵�newNode
	SLNode* newNode = (SLNode*)malloc(sizeof(SLNode));
	if (NULL == newNode)
	{
		printf("����ڵ�ʧ�ܣ�\n");
		assert(newNode);
	}

	newNode->data = data; //�����ݴ�����
	newNode->next = NULL; //����һ����ַ���ÿ�
	return newNode;
}
//β��
//head�е����ݾ���&L
//�����Ҫ�ı�ʵ��L��ָ��,*head�������L����
//ע�⣺��������������ڵ�����
//�����������Ѿ�����,ֻ����������û����Ч�ڵ�
//�������ڣ���û��ͷָ��

//assert:һ��������Գ���ķǷ����
//if�жϣ�����������һ�ֿ��������
void SLPushBack(SLNode** head, DateType data)
{
	//1.Ҫ�ȱ������������һ���ڵ�tail
	//  ���һ���ڵ���ص�,nextΪNULL
	//  ����һ����ʱָ��tail,���������ʼλ�ò��ϱ���(���tail->next�Ƿ�Ϊ�ռ���)
	//2.�����һ���ڵ��next��ָ���½ڵ�
	// tail->next=newNode
	
	//�����Ƿ����
	assert(head);
	SLNode* newNode = BuySLNode(data);
	
	//�����Ƿ�Ϊ������(û���κνڵ������)
	if (NULL == *head)
	{
		//��һ���ڵ�Ϊ��,��һ���ڵ�Ĳ��뷽ʽ
		*head = newNode;
	}
	else
	{
		//˵���������нڵ�
		//β��
		//1.��ȥ�����������һ���ڵ�(nextΪNULL)
		SLNode* tail = *head;
		while (tail->next)
		{
			//ע�⣺tail++;(������˳���ı�����ʽ(ֱ��++)�Ǵ����)
			tail = tail->next;
		}
		//2.���½ڵ����������һ���ڵ�֮��
		tail->next = newNode;
	}
}
//βɾ
void SLPopBack(SLNode** head)
{
	//��ɾ��ʱ������ʲô���ӣ�
	//1.������ L=NULL;����Ҫɾ��,ֱ�ӷ��أ�
	//2.������ֻ��һ���ڵ㣺L--->1--->NULL;��1�ڵ�ɾ��,�����Ϊ������ L=NULL;
	//3.�������ж���ڵ㣺L--->1--->2--->3--->4--->5--->NULL;
	//while(cur->next)  cur=cur->next  �ҵ����һ���ڵ�(β)
	//������prev����cur��ǰһ���ڵ�
	//prev->next=cur->next; free(cur); ����

	assert(head);
	
	//������
	if (NULL == *head)
		return;
	else if (NULL == (*head)->next)
	{
		//������ֻ��һ���ڵ�
		free(*head);
		*head = NULL;
	}
	else
	{
		//�ж���ڵ�
		//����cur���ҵ����һ���ڵ�,����prev����cur��ǰһ���ڵ�
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
//ͷ��
void SLPushFront(SLNode** head, DateType data)
{
	//1.������ L=NULL; ����ɹ���L--->1--->NULL;
	//2.�ǿ� L--->1--->2--->3--->4--->NULL;
	//0��ָ��1;L��ָ��0;(˳���ܸı�)  L--->0--->1--->2--->3--->4--->NULL;
	//newNode->next=*head;
	//*head=newNode;
	assert(head);

	SLNode* newNode = BuySLNode(data);
	newNode->next = *head;
	*head = newNode;
}
//ͷɾ
void SLPopFront(SLNode** head)
{
	//head--->4--->3--->2--->1--->NULL;
	//������head--->3-->2--->1--->NULL;
	//��ɾ����һ���ڵ�(4);


	//�����Ƿ����
	assert(head);
	//�����Ƿ�Ϊ��
	if (NULL == *head)
	{
		return;
	}
	else
	{
		//һ���ڵ�Ͷ���ڵ㶼����(SLPopBack�Ͳ���)
		//����Ҫɾ���ȱ�������(headָ��ľ�����Ҫɾ����)
		SLNode* delNode = *head;
		*head = delNode->next;
		free(delNode);
	}
}
//��posλ��֮�����data
void SLInsertAfter(SLNode*  pos, int data)
{
	//�������
	if (NULL == pos)
	{
		return;
	}
	SLNode* newNode = NULL;
	newNode = BuySLNode(data);
	newNode->next = pos->next;
	pos->next = newNode;
}
//��posλ��֮��Ľڵ�ɾ��(��һ���ڵ�ɾ����)
void SLEraseAfter(SLNode** head, SLNode* pos)
{
	//pos���������
	//pos�����һ���ڵ�
	//�����ӣ���ɾ�ڵ�
	SLNode* delNode = NULL;
	if (NULL == pos || NULL == pos->next)
	{
		return;
	}
	delNode = pos->next;
	pos->next = delNode->next;
	free(delNode);
}
//��ȡ����ڵ����
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
//���������ҵ�ֵΪdata�Ľڵ�
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
//��������
void SLDestroy(SLNode** head)
{
	assert(head);
	SLNode *cur = *head;
	//�����ӣ���ɾ��
	//ͷɾ��
	while (cur)
	{
		*head = cur->next;
		free(cur);
		cur = *head;
	}
}
//��ӡ��ǰ����
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
//���Ժ���
void TestSList1()
{
	//L:�յ�����
	SLNode* L = NULL;
	//β�� 1,2,3,4,5
	SLPushBack(&L, 1);
	SLPushBack(&L, 2);
	SLPushBack(&L, 3);
	SLPushBack(&L, 4);
	SLPushBack(&L, 5);
	PrintfSList(L);
	
	//SLInsertAfter(L, 8);
	//PrintfSList(L);

    //βɾ
	//SLPopBack(&L);
	//PrintfSList(L);
	
	//ͷɾ
	//SLPopFront(&L);
	//PrintfSList(L);

	////����λ�ú����
	//SLInsertAfter(SLFind(L, 3), 6);
	//PrintfSList(L);

	////��ӡ�ڵ����
	//printf("%d\n",SLSize(L));

	////ɾ��pos֮��Ľڵ�
	//SLEraseAfter(&L,SLFind(L, 3));
	//PrintfSList(L);

	////����
	//SLDestroy(&L);
	//PrintfSList(L);

}
//���Ժ���
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
//��ͷ���˫��ѭ������
//���Բ��ö���ָ�룬��Ϊͷ���λ�ò���ı�
//���еĲ������ǻ���ͷ���֮��ȥ������
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

//����ڵ�ռ�
DListNode *BuyDListNode(DataType data);
//������������ͷ���
DListNode* CreatDList();
//β��/ɾ
void DListPushBack(DListNode* pHead, DataType data);
void DListPopBack(DListNode* pHead);
//ͷ��/ɾ
void DListPushFront(DListNode* pHead, DataType data);
void DListPopFront(DListNode*pHead);
//��posλ�ò����½ڵ�(��posλ��ǰ�����)
void DListInsert(DListNode* pos, DataType data);
//ɾ��posλ�ýڵ�
void DListErase(DListNode* pos);
//����Data���ݽڵ�
DListNode* DListFind(DListNode* pHead, DataType data);
//��������
void DListDestroy(DListNode* pHead);


//����ڵ�ռ�
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
//����ͷ���
//��ͷ����˫��ѭ������
//������Ҳ��ͷ��㣬���Լ�ָ�Լ�
DListNode* CreatDList()
{
	DListNode* head = BuyDListNode(0);
	head->next = head;
	head->prev = head;
	return head;
}
//β��
void DListPushBack(DListNode* pHead, DataType data)
{
	if (NULL == pHead)
	{
		return ;
	}
	//����ڵ�
	DListNode* newNode = BuyDListNode(data);

	//�������ٶϿ�
	newNode->prev = pHead->prev;//��pHead->prev(�����е����һ���ڵ�)��newNode->prev
	newNode->next = pHead;
	pHead->prev->next = newNode;
	pHead->prev = newNode;
}
//βɾ
void DListPopBack(DListNode* pHead)
{ 
	assert(pHead);//assert��һ�����Ժ꣬��debug������Ч��release���²�����
	if (NULL == pHead)
	{
		assert(0);
		return;
	}
	//����Ƿ�Ϊ������
	if (pHead->next == pHead)
	{
		return;
	}
	//��������ɾ��
	DListNode *pos = pHead->prev;

	pHead->prev = pos->prev;
	pos->prev->next = pHead;
	free(pos);

}
//ͷ��
void DListPushFront(DListNode* pHead, DataType data)
{
	if (NULL == pHead)
	{
		return;
	}
	//����posλ�õĲ���
	DListInsert(pHead->next, data);
}
//ͷɾ
void DListPopFront(DListNode* pHead)
{
	if (NULL == pHead)
	{
		return;
	}
	//����posλ�õ�ɾ��
	DListErase(pHead->next);
}
//��posλ�ò����½ڵ�(��posλ��ǰ�����)
void DListInsert(DListNode* pos, DataType data)
{
	DListNode* newNode = BuyDListNode(data);
	//�������ٶϿ�
	newNode->prev = pos->prev;
	newNode->next = pos;
	newNode->prev->next = newNode;
	pos->prev = newNode;
}
//ɾ��posλ�ýڵ�
void DListErase(DListNode* pos)
{
	if (NULL == pos)
	{
		return;
	}
	//�����ӣ���ɾ��
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(pos);
}
//����Data���ݽڵ�
DListNode* DListFind(DListNode* pHead, DataType data)
{
	//��������Ƿ����
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
//��������
//���Ҫ�ı�ͷָ��ʹ��ָ��NULL�����Ա��봫�ݶ���ָ��
void DListDestroy(DListNode** pHead)
{
	DListNode* cur = NULL;
	//��֤�������
	if (NULL == pHead)
	{
		return;
	}
	//ɾ����Ч�ڵ�
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
//��ӡ˫��ѭ������
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
//���Ժ���
void Test1()
{
	//����ͷ���
	DListNode* head = CreatDList();
	//β��
	DListPushBack(head, 1);
	DListPushBack(head, 2);
	DListPushBack(head, 3);
	DListPushBack(head, 4);
	DListPushBack(head, 5);
	PrintfDList(head);

	//��������
	DListDestroy(&head);
}
//���Ժ���
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
//ջ�ṹʵ��
//��̬ջ-->ջ�д洢Ԫ�ظ�������
//ʵ��Ӧ���к����þ�̬ջ����ΪԪ������
//�ڱ�������Ҫ�õ�ջ��û�нṹʱ����ʱʵ��ջ�ṹ-->���飺ʵ�־�̬��ջ(����ʵ��)
#include<iostream>
#include<assert.h>
#include<malloc.h>

typedef int DataType;
#define MAX_SIZE 100

typedef struct Stack
{
	DataType* array;
	int capacity;  //����
	int size;
}Stack;

//ջ�ĳ�ʼ��
void StackInit(Stack* ps);
//�������
void CheckCapacity(Stack* ps);
//��ջ
void StackPush(Stack* ps);
//��ջ
void StackPop(Stack* ps);
//��ȡջ��Ԫ��
DataType StackTop(Stack* ps);
//��ȡջ����ЧԪ�ظ���
DataType StackSize(Stack* ps);
//���ջ�Ƿ�Ϊ��
DataType StackEmpty(Stack* ps);
//����
void StackDestroy(Stack* ps);


//ջ�ĳ�ʼ��
void StackInit(Stack* ps)
{
	assert(ps);
	ps->array = (DataType*)malloc(sizeof(DataType) * 10);
	ps->capacity = 10;
	ps->size = 0;
}
//�������
void CheckCapacity(Stack* ps)
{
	//1.�����¿ռ�
	//2.����Ԫ��
	//3.�ͷžɿռ�
	if (ps->size >= ps->capacity)
	{
		//�����¿ռ�
		int newCapacity = ps->capacity * 2;
		DataType* temp = (DataType*)malloc(sizeof(DataType)*newCapacity);

		if (temp)
		{
			//����Ԫ��
			//memcpy(temp,ps->array,sizeof(DataType)*ps->capacity);
			for (int i = 0; i < ps->size; i++)
			{
				temp[i] = ps->array[i];
			}
			//�ͷžɿռ�
			free(ps->array);

			ps->array = temp;
		}
	}
}
//��ջ
void StackPush(Stack* ps,DataType data)
{
	assert(ps);
	//��������Ƿ�
	CheckCapacity(ps);

	//����Ԫ��
	ps->array[ps->size] = data;
	ps->size++;
}
//��ջ
void StackPop(Stack* ps)
{
	if (StackEmpty(ps))
	{
		return;
	}
	ps->size--;
}
//��ȡջ��Ԫ��
DataType StackTop(Stack* ps)
{
	assert(ps);
	return ps->array[ps->size-1];
}
//��ȡջ����ЧԪ�ظ���
DataType StackSize(Stack* ps)
{
	assert(ps);
	return ps->size;
}
//���ջ�Ƿ�Ϊ��
DataType StackEmpty(Stack* ps)
{
	assert(ps);
	return 0 == ps->size;
}
//����
void StackDestroy(Stack* ps)
{
	assert(ps);
	free(ps);
	ps->capacity=0;
	ps->size = 0;
}



//���Ժ���
void Test1()
{
	Stack s;
	//ջ�ĳ�ʼ��
	StackInit(&s);
	//��ջ
	StackPush(&s, 1);
	StackPush(&s, 2);
	StackPush(&s, 3);
	StackPush(&s, 4);
	StackPush(&s, 5);
	printf("%d\n",StackTop(&s));
	printf("%d\n",StackSize(&s));
	StackPop(&s);
	//����
	StackDestroy(&s);
}
//���Ժ���
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
//���нṹʵ��
#include<iostream>
#include<assert.h>
#include<malloc.h>

typedef int QDataType;

//���еײ�ʹ�������еĽڵ�ṹ
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
//����ڵ�
QNode* BuyQNode(int val);
//���еĳ�ʼ��
void QueueInit(Queue* q);
//�����
void QueuePush(Queue* q);
//������
void QueuePop(Queue* q);
//��ȡ��������ЧԪ�ظ���
QDataType QueueSize(Queue* q);
//�������Ƿ�Ϊ��
QDataType QueueEmpty(Queue* q);
//��ȡ��ͷԪ��
QDataType QueueFront(Queue* q);
//��ȡ��βԪ��
QDataType QueueBack(Queue* q);
//���ٶ���
void QueueDestroy(Queue* q);


//����ڵ�
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
//���еĳ�ʼ��
//�Ӹ�ͷ���
void QueueInit(Queue* q)
{
	assert(q);
	q->head = BuyQNode(0);
	q->size = 0;
	q->rear = q->head;
}
//�����
void QueuePush(Queue* q, QDataType val)
{
	assert(q);
	QNode* newNode = BuyQNode(val);
	q->rear->next = newNode;
	q->rear = newNode;
	q->size++;
}
//������
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
//��ȡ��������ЧԪ�ظ���
int QueueSize(Queue* q)
{
	assert(q);
	return q->size;
}
//�������Ƿ�Ϊ��
int QueueEmpty(Queue* q)
{
	assert(q);
	return 0 == q->size;
}
//��ȡ��ͷԪ��
QDataType QueueFront(Queue* q)
{
	assert(!QueueEmpty(q));
	return q->head->next->val;
}
//��ȡ��βԪ��
QDataType QueueBack(Queue* q)
{
	assert(!QueueEmpty(q));
	return q->rear->val;
}
//���ٶ���
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


//���Ժ���
void Test1()
{
	Queue q;
	//��ʼ��
	QueueInit(&q);
	//�����
	QueuePush(&q, 1);
	QueuePush(&q, 2);
	QueuePush(&q, 3);
	QueuePush(&q, 4);
	QueuePush(&q, 5);
	
	printf("size=%d\n", QueueSize(&q));
	printf("Front=%d\n", QueueFront(&q));
	printf("Back=%d\n", QueueBack(&q));
	
	
	////������
	//void QueuePop(Queue* q);
	////��ȡ��������ЧԪ�ظ���
	//QDataType QueueSize(Queue* q);
	////�������Ƿ�Ϊ��
	//QDataType QueueEmpty(Queue* q);
	////��ȡ��ͷԪ��
	//QDataType QueueFront(Queue* q);
	////��ȡ��βԪ��
	//QDataType QueueBack(Queue* q);
}
//���Ժ���
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