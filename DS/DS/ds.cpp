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
#include<iostream>
#include<assert.h>
#include<malloc.h>
#include<Windows.h>
using namespace std;
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
SLNode* reverseList(SLNode* head) {
	SLNode *p;
	for (p = NULL; head; swap(head, p))
		swap(p, head->next);
	return p;
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

	//��ת����,ԭ���㷨
	//PrintfSList(reverseList(L));
	
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


#if 0
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
	if (0 == q->size)
	{
		q->rear = q->head;
	}
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


#if 0
//8
//2020.3.23
//�ѵ�ʵ��
#include<iostream>
#include<assert.h>
#include<malloc.h>

typedef int HPDataType;

int Less(int left, int right);
int Greater(int left, int right);
//pCompare:��һ������ָ��-->��ʾ����int ����Ϊ�������Ͳ�����һϵ�к���
//int (*pCompare(int left,int right));

//pCompare:����ָ������
typedef int(*PCOM)(int left, int right);
typedef struct Heap
{
	HPDataType* array;
	int capacity;
	int size;
	PCOM Compare; //��ʱ����Compareָ��Less����Greater,ֻҪ�������������������ͣ���������Compare���ա�
}Heap;

//�ѵĴ���
void HeapCreate(Heap* hp, HPDataType* a, int size, PCOM compare);
//�ѵ�����
void HeapDestory(Heap* hp);
//�ѵĲ���
void HeapPush(Heap*  hp, HPDataType data);
//�ѵ�ɾ��
void HeapPop(Heap* hp);
//ȡ�Ѷ�Ԫ��
HPDataType HeapTop(Heap* hp);
//�ѵ����ݸ���
int HeapSize(Heap* hp);
//�ѵ��п�
int HeapEmpty(Heap* hp);
//�ѵ�����
void HeapDestroy(Heap* hp);
//�������
void CheckCapacity(Heap* hp);

//��������ж�����
void HeapSort(int* a, int size);


int Less(int left, int right)
{
	return left < right;
}
int Greater(int left, int right)
{
	return left > right;
}
//Ԫ�ؽ���
void Swap(HPDataType* left, HPDataType* right)
{
	*left ^= *right;
	*right ^= *left;
	*left ^= *right;
}
//���ϵ���
void AdjustUP(Heap* hp,int child)
{
	//���²���ĺ��ӽڵ���������ʵ�λ��
	int parent = (child - 1) >> 1;

	while (child)
	{
		if (hp->Compare(hp->array[child] ,hp->array[parent]))
		{
			Swap(&hp->array[child], &hp->array[parent]);
			//С��Ԫ�������ƶ������ܻᵼ���ϲ㲻����ѵ�����
			//��Ҫ�������ϵ���
			child = parent;
			parent = (child - 1) >> 1;
		}
		else
		{
			return;
		}
	}
}
//���µ���(ֻ�жѶ�Ԫ�ز�����ѵĽṹ)
//���裺��������С��
//parent:��Ҫ������Ԫ���ڶѽṹ�е��±�(��0��ʼ)
//    ��parent�ͺ����еĽ�С�߽��бȽ�
//       ��-->parent����ѵ�����
//       ��-->��parent�ͽ�С�ĺ��ӽ��н���
//                      ����֮����µ��������ܻ᲻����ѵ����ʣ�����Ҫ�������µ���
void AdjustDown(Heap* hp, int parent)
{
	//child���ã����parent�Ľ�С����
	//Ĭ�ϱ�����ӡ���Ϊ��ȫ��������һ���ڵ��������û���ҡ�
	int child = parent * 2 + 1;

	//whileѭ����������֤���Ӵ��ڣ�������Ӳ����ڣ��Һ��ӿ϶�Ҳ������
	while (child<hp->size)
	{
		//�ȱ�֤�Һ��Ӵ��ڣ��������������н�С�ĺ��ӣ���ֹԽ��
		//����Һ��ӣ����ӣ�child++
		if (child+1< hp->size&&hp->Compare(hp->array[child + 1] ,hp->array[child]))
		{ 
			child++;
		}

		//���parent�Ƿ�Ƚ�С�ĺ���childС
		if (hp->Compare(hp->array[child] ,hp->array[parent]))
		{
			Swap(&hp->array[child], &hp->array[parent]);

			//parent���Ԫ�������ƶ������ܻᵼ������������ѵ�����
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			//���õ�����
			return;
		}
	}
}
void CheckCapacity(Heap* hp)
{
	assert(hp);
	if (hp->size >= hp->capacity)
	{
		//��Ҫ����
		//1.�����¿ռ�
		int newCapacity = hp->size * 2;
		HPDataType* temp = (HPDataType*)malloc(sizeof(HPDataType)*newCapacity);
		if (NULL == temp)
		{
			return;
		}
		//����Ԫ��
		for (int i = 0; i < hp->size;i++)
		{
			temp[i] = hp->array[i];
		}
		//memcpy(temp,hp->array,hp->size*sizeof(HPDataType));
		
		//3.�ͷžɿռ�
		free(hp->array);
		hp->array = temp;
		hp->capacity = newCapacity;
	}
}
//�ѵĴ���
void HeapCreate(Heap* hp, HPDataType* arr, int size, PCOM compare)
{
	assert(hp);
	//1.�Ƚ�arr�е�Ԫ�طŵ��ѵĽṹ��
	//��ʼ���ѵĽṹ
   	hp->array = (HPDataType*)malloc(sizeof(HPDataType)*size);
	if (NULL == hp->array)
	{
		assert(0);
		return;
	}
	hp->capacity = size;
	memcpy(hp->array, arr, sizeof(HPDataType)*size);
	hp->size = size;
	hp->Compare = compare;

	//2.�Զ��е�Ԫ�ؽ��е���
	//�������ϣ��ӵ�һ����Ҷ�ӽڵ㿪ʼ����
	for (int root = (size - 2) >> 1; root >= 0; root--)
	{
		AdjustDown(hp, root);
	}
}
//�ѵ�����
void HeapDestory(Heap* hp)
{

}
//�ѵĲ���
void HeapPush(Heap*  hp, HPDataType data)
{
	//1.��Ԫ�ز��뵽���
	//2.���ϵ���һ��
	assert(hp);
	CheckCapacity(hp);
	hp->array[hp->size++] = data;
	AdjustUP(hp, hp->size - 1);

}
//�ѵ�ɾ��(ɾ�Ѷ�Ԫ�أ�
void HeapPop(Heap* hp)
{
	//1.�ѶѶ�Ԫ�غ����һ��Ԫ�ؽ��н���
	//2.size-1
	//3.�ӶѶ��������µ���
	assert(hp);
	if (HeapEmpty(hp))
	{
		return;
	}
	Swap(&hp->array[0], &hp->array[hp->size - 1]);
	hp->size--;
	AdjustDown(hp, 0);
}
//ȡ�Ѷ�Ԫ��
HPDataType HeapTop(Heap* hp)
{
	assert(hp&&!HeapEmpty(hp));
	return hp->array[0];

}
//�ѵ����ݸ���
int HeapSize(Heap* hp)
{
	assert(hp);
	return hp->size;
}
//�ѵ��п�
int HeapEmpty(Heap* hp)
{
	assert(hp);
	return 0 == hp->size;
}
///////////////////////////////////////////
//��������ж�����
//����С�ѣ����򽨴��
void HeapAdjust(int* array, int size,int parent)
{
	//С�ѣ��������µ���
	int child = parent * 2 + 1;
	while (child < size)
	{
		if (child + 1 < size&&array[child + 1] < array[child])
		{
			child++;
		}
		if (array[child] < array[parent])
		{
			int temp = array[child];
			array[child] = array[parent];
			array[parent] = temp;

			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			return;
		}
	}
}
void HeapSort(int* array, int size)
{
	//����
	for (int root = (size - 2) >> 1; root >= 0; root--)
	{
		HeapAdjust(array, size, root);
	}
	//���ö�ɾ����˼������������
	int end = size - 1;
	while (end)
	{
		int temp = array[0];
		array[0] = array[end];
		array[end] = temp;
		
		HeapAdjust(array, end, 0);
		end--;
	}
}
///////////////////////////////////////////
//�ѵ�����
void HeapDestroy(Heap* hp)
{
	assert(hp);
	if (hp->array)
	{
		free(hp->array);
		hp->array = NULL;
		hp->capacity = 0;
		hp->size = 0;
	}
}


//���Ժ���
void Test1()
{
	int array[] = { 5, 3, 8, 4, 2, 7, 6, 1, 0 };
	//HeapSort(array, sizeof(array)/sizeof(array[0]));
	Heap hp;
	HeapCreate(&hp, array, sizeof(array) / sizeof(array[0]),Greater);
	printf("size=%d\n", HeapSize(&hp));
	printf("Top=%d\n", HeapTop(&hp));
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
//9
//2020.3.28
//��������ʵ�����������
#include<iostream>
#include<assert.h>
#include<malloc.h>
#include<queue>
using namespace std;

typedef int BTDataType;

typedef struct BinTreeNode
{
	BTDataType val;
	struct BinTreeNode* pLeft;
	struct BinTreeNode* pRight;
}BTNode;

BTNode* BuyBinTreeNode(BTDataType val)
{
	BTNode* pNewNode = (BTNode*)malloc(sizeof(BTNode));
	if (NULL == pNewNode)
	{
		assert(0);
		return NULL;
	}
	pNewNode->pLeft = NULL;
	pNewNode->pRight = NULL;
	pNewNode->val = val;
	return pNewNode;
}
//BTNode* CreatBinTree()
//{
//	//            1
//	//          /   \ 
//	//         2     4
//	//       /     /   \
//	//      3     5     6
//	BTNode* node1 = BuyBinTreeNode(1);
//	BTNode* node2 = BuyBinTreeNode(2);
//	BTNode* node3 = BuyBinTreeNode(3);
//	BTNode* node4 = BuyBinTreeNode(4);
//	BTNode* node5 = BuyBinTreeNode(5);
//	BTNode* node6 = BuyBinTreeNode(6);
//	//BTNode* node7 = BuyBinTreeNode(7);
//	//BTNode* node8 = BuyBinTreeNode(8);
//	//BTNode* node9 = BuyBinTreeNode(9);
//
//	BTNode* pRoot = node1;
//	node1->pLeft = node2;
//	node2->pLeft = node3;
//	node1->pRight = node4;
//	node4->pLeft = node5;
//	node4->pRight = node6;
//	//node3->pRight = node7;
//	//node5->pRight = node8;
//	//node8->pRight = node9;
//	return pRoot;
//
//}


//ǰ�����
void PreOrder(BTNode* pRoot);
//�������
void InOrder(BTNode* pRoot);
//�������
void PostOrder(BTNode* pRoot);
//�������
void LevelOrder(BTNode *pRoot);
//�ж��Ƿ�Ϊ��ȫ������
bool isCBT(BTNode* pRoot);
//��ȡ�������нڵ����
int GetNodeCount(BTNode* pRoot);
//��ȡҶ�ӽڵ����
int GetLeafCount();
//��ȡ��K��ڵ����
int GetKLevelCount();
//��ȡ�������߶�
int GetHeight();
//����XԪ������������Ӧ�Ľڵ�
BTNode* Find(BTNode* pRoot, BTDataType x);
//��ȡpNode��˫��
BTNode* FindParent(BTNode* pRoot, BTNode* pNode);
//������������
void TreeDestroy(BTNode** pRoot);
//����������   invalid:NULL�ڵ�ı�Ƿ���
BTNode* CreateBinTree(int * array, int size, int index, BTDataType invalid);









//����������   invalid:NULL�ڵ���
BTNode* _CreateBinTree(int * array, int size, int* index, BTDataType invalid)
{
	BTNode* pRoot = NULL;
	if (*index < size&&array[*index] != invalid)
	{
		//�������ڵ�
		pRoot = BuyBinTreeNode(array[*index]);

		//�������ڵ��������
		++(*index);
		pRoot->pLeft = _CreateBinTree(array, size, index, invalid);

		//�ݹ鴴�����ڵ��������
		++(*index);
		pRoot->pRight = _CreateBinTree(array, size, index, invalid);
	}
	return pRoot;
}
BTNode* CreateBinTree(int * array, int size, BTDataType invalid)
{
	int index = 0;
	return _CreateBinTree(array, size, &index, invalid);
}

//�������
void PreOrder(BTNode* pRoot)
{
	if (pRoot)
	{
		printf("%d ", pRoot->val);
		PreOrder(pRoot->pLeft);
		PreOrder(pRoot->pRight);
	}
}
//�������
void InOrder(BTNode* pRoot)
{
	if (pRoot)
	{
		InOrder(pRoot->pLeft);
		printf("%d ", pRoot->val);
		InOrder(pRoot->pRight);
	}
}
//�������
void PostOrder(BTNode* pRoot)
{
	if (pRoot)
	{
		PostOrder(pRoot->pLeft);
		PostOrder(pRoot->pRight);
		printf("%d ", pRoot->val);

	}
}
//�������
void LevelOrder(BTNode *pRoot)
{
	queue<BTNode*> q;
	if (pRoot == NULL)
	{
		return;
	}
	q.push(pRoot);

	while (!q.empty())
	{
		BTNode* front = q.front();
		q.pop();

		if (front->pLeft) q.push(front->pLeft);
		if (front->pRight) q.push(front->pRight);
		cout<<front->val<<" ";
	}
}

//�ж��Ƿ�Ϊ��ȫ������
bool isCBT(BTNode* pRoot)//�ж���pRootΪͷ�ڵ�Ķ������Ƿ�Ϊ��ȫ������
{
	assert(pRoot);
	if (pRoot == NULL)
		return true;
	
	queue < BTNode* >q;//ͨ������qʵ�ֶ������Ĳ�α�����ͨ����α������ж��Ƿ�Ϊ��ȫ������
	q.push(pRoot);//����ͷ�ڵ�
	
	bool leaf = false;//leaf�����������һ��״̬�Ƿ�����ֻҪ��ǰ�ڵ�����Ӻ��Һ��Ӷ�Ϊ�ջ������Ӳ�Ϊ�գ��Һ���Ϊ��ʱ�����״̬�ͷ�����
	                  //ֻҪ���������״̬���Ժ���ʵ��Ľڵ���붼��Ҷ�ڵ㣩
	
	while (!q.empty())
	{
		BTNode* p = q.front();
		q.pop();
		if ((leaf && (p->pLeft != NULL || p->pRight != NULL)) || (p->pLeft == NULL&&p->pRight != NULL))//��Щ�ж����������еĲ���������ȫ������������������һ���ڶ���||ǰ�����������������״̬�Ѿ����������ǵ�ǰ���ʵ��Ľڵ㲻��Ҷ�ڵ㣨�����ӻ����Һ��ӣ�������������ǰ�ڵ����Һ��ӣ�û������
			return false;
		if (p->pLeft != NULL)//���Ӳ�Ϊ�գ����뵽������ȥ
			q.push(p->pLeft);
		if (p->pRight != NULL)//�Һ��Ӳ�Ϊ�գ����뵽������ȥ
			q.push(p->pRight);
		if ((p->pLeft != NULL&&p->pRight == NULL) || (p->pLeft == NULL&&p->pRight == NULL))//���if�������ж�״̬�Ƿ�Ҫ����
			leaf = true;
	}
	return true;
}
//��ȡ�������нڵ����
//int count=0;
//int GetNodeCount(BTNode* pRoot)
//{   
//	
//	if (pRoot)
//	{
//		::count++;
//		GetNodeCount(pRoot->pLeft);
//		GetNodeCount(pRoot->pRight);
//	}
//	return ::count;
//}
int GetNodeCount(BTNode* pRoot)
{
	if (NULL==pRoot)
	{
		return 0;
	}
	return 1+GetNodeCount(pRoot->pLeft)+
		   GetNodeCount(pRoot->pRight);
}
//��ȡҶ�ӽڵ����
int GetLeafCount(BTNode* pRoot)
{
	if (NULL == pRoot)
	{
		return 0;
	}
	if (NULL == pRoot->pLeft&&NULL == pRoot->pRight)
	{
		return 1;
	}
	return GetLeafCount(pRoot->pLeft)+GetLeafCount(pRoot->pRight);
}
//��ȡ��K��ڵ����
int GetKLevelCount(BTNode* pRoot,int k)
{
	if (NULL == pRoot || k < 1)
	{
		return 0;
	}
	if (1 == k)
	{
		return 1;
	}
	//int left=GetKLevelCount(pRoot->pLeft, k - 1);
	//int right=GetKLevelCount(pRoot->pRight, k - 1);
	//return left+right;
	return GetKLevelCount(pRoot->pLeft, k - 1) + GetKLevelCount(pRoot->pRight, k - 1);
}
//��ȡ�������߶�
int GetHeight(BTNode* pRoot)
{
	if (NULL == pRoot)
	{
		return 0;
	}
	int leftHeight = GetHeight(pRoot->pLeft);
	int rightHeight = GetHeight(pRoot->pRight);
	return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}
//����XԪ������������Ӧ�Ľڵ�
BTNode* Find(BTNode* pRoot, BTDataType x)
{
	BTNode* pNode = NULL;
	if (NULL == pRoot)
	{
		return NULL;
	}
	if (pRoot->val == x)
	{
		return pRoot;
	}
	//Find(pRoot->pLeft, x);
	//Find(pRoot->pRight, x);
	if ((pNode = Find(pRoot->pLeft, x)) || (pNode = Find(pRoot->pRight, x)))
	{
		return pNode;
	}
	return NULL;
}
//��ȡpNode��˫��
BTNode* GetParent(BTNode* pRoot, BTNode* pNode)
{
	BTNode* pParent = NULL;
	if (NULL == pRoot || NULL == pNode || pNode == pRoot)
	{
		return NULL;
	}
	if (pRoot->pLeft == pNode || pRoot->pRight == pNode)
	{
		return pRoot;
	}
	//pParent = GetParent(pRoot->pLeft, pNode);
	//pParent = GetParent(pRoot->pRight, pNode);
	//if (NULL != pParent)
	//{
	//	return pParent;
	//}
	if ((pParent = GetParent(pRoot->pLeft, pNode)) || (pParent = GetParent(pRoot->pRight, pNode)))
	{
		return pParent;
	}
	return NULL;
}
//������������
void DestroyNode(BTNode* node)
{
     free(node);
     return;
 }

void TreeDestroy(BTNode** pRoot)
 {
	assert(pRoot);
	if (*pRoot == NULL)
	{
		//����
		return;
    }
	TreeDestroy(&((*pRoot)->pLeft));
	TreeDestroy(&((*pRoot)->pRight));
	DestroyNode(*pRoot);
	*pRoot = NULL;
	return;
 }

//���Ժ���
void Test1()
{
	int array[] = { 1, 2, 3, -1, -1, -1, 4, 5, -1, -1, 6 };
	BTNode* pRoot = CreateBinTree(array, sizeof(array) / sizeof(array[0]), -1);
	
	cout << "�������Ϊ�� "; 
	PreOrder(pRoot);
	cout << endl;

	cout << "�������Ϊ�� ";
	InOrder(pRoot);
	cout << endl;

	cout << "�������Ϊ:  ";
	PostOrder(pRoot);
	cout << endl;

	cout << "�������Ϊ:  ";
	LevelOrder(pRoot);
	cout << endl;

	//�ж��Ƿ�Ϊ��ȫ������
	if (isCBT(pRoot))//�ж���pRootΪͷ�ڵ�Ķ������Ƿ�Ϊ��ȫ������
	{
		cout << "is CBT" << endl;
	}
	else
	{
		cout << "no is CBT" << endl;
	}

	//��ȡ�ڵ����
	cout << "�ڵ����Ϊ:  ";
	cout<<GetNodeCount(pRoot)<<endl;
	
	//��ȡҶ�ӽڵ�
	cout << "Ҷ�ӽڵ���Ϊ:";
	cout<<GetLeafCount(pRoot)<<endl;

	//�߶�
	cout << "�������߶�Ϊ:";
	cout << GetHeight(pRoot)<<endl;

	//��K��ڵ����
	cout << "��3��ڵ����Ϊ:";
	cout<<GetKLevelCount(pRoot, 3)<<endl;

	//����XԪ������������Ӧ�Ľڵ�
	if (Find(pRoot, 3))
	{
		cout << "�ڵ��ҵ���!" <<endl;
	}
	else
	{
		cout << "�ڵ�û�ҵ�!" << endl;
	}
	BTNode* pNode = Find(pRoot, 3);
	BTNode* pParent = GetParent(pRoot, Find(pRoot, 3));
	//��˫��
	if (pParent)
	{
		cout << "˫��is "<<pParent->val << endl;
	}
	else
	{
		cout << "˫��û�ҵ�!" << endl;
	}
	//����
	TreeDestroy(&pRoot);
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
//10
//2020.4.1
//����
#include<iostream>
#include<assert.h>
#include<malloc.h>
#include<queue>
#include<stack>
using namespace std;

// ��������
void InsertSort(int* a, int n);
// ϣ������
void ShellSort(int* a, int n);
// ѡ������
void SelectSort(int* a, int n);
// ������
void AdjustDown(int* a, int n, int root);
void HeapSort(int* a, int n);
// ð������
void BubbleSort(int* a, int n);
// ��������ݹ�ʵ��
// ��������hoare�汾
int PartSort1(int* a, int left, int right);
// ���������ڿӷ�
int PartSort2(int* a, int left, int right);
// ��������ǰ��ָ�뷨
int PartSort3(int* a, int left, int right);
void QuickSort(int* a, int left, int right);
// �������� �ǵݹ�ʵ��
void QuickSortNonR(int* a, int size);
// �鲢����ݹ�ʵ��
void MergeSort(int* a, int n);
// �鲢����ǵݹ�ʵ��
void MergeSortNonR(int* a, int n);
// ��������
void CountSort(int* a, int n);





//void Swap(int* a, int* b)
//{
//	int temp=*a;
//	*a = *b;
//	*b = temp;
//}


//1.��������
//Ӧ�ó���:������С,�ӽ�����
//1.1ֱ�Ӳ�������
//ʱ�临�Ӷ�:O(n^2)
//�ռ临�Ӷ�:O(1)
void InsertSort(int* array, int size)
{
	for (int i = 1; i < size; i++)
	{
		int key = array[i];
		int end = i - 1;
		//��λ��
		while (end >= 0 && key < array[end])
		{
			array[end + 1] = array[end];
			end--;
		}
		//��������
		array[end + 1] = key;
	}
}
//1.2ϣ������ 
//����������,������
//�Ȱ���ĳһ�������飬���ڽ��в��������۰���ٲ�����ֱ��Ϊ1
//������ѭ�� �����Ϊ������
//ʱ�临�Ӷ�:O(N^1.3-N^2��
//�ռ临�Ӷ�:O(1)
void ShellSort(int* array, int size)
{
	int gap = size;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (int i = gap; i < size; i++)
		{
			int key = array[i];
			int end = i - gap;
			//��λ��
			while (end >= 0 && key < array[end])
			{
				array[end + gap] = array[end];
				end-=gap;
			}
			//��������
			array[end + gap] = key;
		}
	}
}
//2.ѡ������
//2.1ѡ������
//ʱ�临�Ӷ�:O(N^2)
//�ռ临�Ӷ�:O(1)
void SelectSort(int* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		int minPos = i;
		for (int j = i ; j < size; j++)
		{
			if (array[j] < array[minPos])
			{
				minPos = j;
			}
		}
		swap(array[i], array[minPos]);
	}
}
//2.2������
//���򽨴�ѣ�����С��
//ʱ�临�Ӷ�:O(NlogN)
//�ռ临�Ӷ�:O(1)
//С��
void HeapSort(int* array, int size)
{
	//����
	//�ӵ�һ����Ҷ�ӽڵ㿪ʼ���˵���
	for (int root = (size - 2) >> 1; root >= 0; root--)
	{
		AdjustDown(array, size, root);
	}
	//���ö�ɾ����˼������������
	int end = size - 1;
	while (end)
	{
		int temp = array[0];
		array[0] = array[end];
		array[end] = temp;

		AdjustDown(array, end, 0);
		end--;
	}
}
void AdjustDown(int* array, int size, int parent)
{
	//С�ѣ��������µ���
	int child = parent * 2 + 1;
	while (child < size)
	{
		if (child + 1 < size&&array[child + 1] < array[child])
		{
			child++;
		}
		if (array[child] < array[parent])
		{
			int temp = array[child];
			array[child] = array[parent];
			array[parent] = temp;

			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			return;
		}
	}
}
//3.��������
//3.1ð������
//ʱ�临�Ӷ�:O(n^2)
//�ռ临�Ӷ�:O(1)
//����
void BubbleSort(int* array, int size)
{
	for (int i = 0; i < size; i++)
	{
        int flag = 1;
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (array[j]>array[j+1])
			{
				swap(array[j], array[j+1]);
				flag = 0;
			}
		}
		if (flag) break;
	}
}
//3.2��������
//ʱ�临�Ӷ�:O(N*logN)
//ʱ�临�Ӷ�:O(logN)--O(N)
//���ȶ�����
//��������ݹ�ʵ��
//��������hoare�汾(ǰ�󽻻�)
int GetIndexOfMid(int* array, int left, int right)
{
	int a = array[left];
	int b = array[(left + right) / 2];
	int c = array[right];
	if (a > b)
	{
		if (b > c)
		{
			return (left + right) / 2;
		}
		if (a<c)
		{
			return left;
		}
		else
		{
			return right;
		}
	}
	if (a<b)
	{
		if (a > c)
		{
			return left;
		}
		if (b<c)
		{
			return (left + right) / 2;
		}
		else
		{
			return right;
		}
	}
	return 0;
	//return a > b ? (b > c ? b : a < c ? a : c) : (a > c ? a : b < c ? b : c);
}
int PartSort1(int* array, int left, int right)
{
	int begin = left;
	int end = right - 1;
	int key = array[end];

	while (begin < end)
	{
		//��begin��ǰ�����ң��ұȻ�׼ֵ���Ԫ�أ��ҵ�֮��ֹͣ
		while (begin<end&&array[begin] <= key)
			begin++;
		//��end�Ӻ���ǰ�ң��ҵ��Ȼ�׼ֵС��Ԫ�أ��ҵ�֮��ֹͣ
		while (begin<end&&array[end] >= key)
			end--;

		if (begin < end)
		{
			swap(array[begin], array[end]);
		}
	}
	
	if (begin!=right-1)
	swap(array[begin], array[right-1]);
	
	return begin; //��div
}
// ���������ڿӷ�
int PartSort2(int* array, int left, int right)
{
	int begin = left;
	int end = right - 1;
	int key = array[begin]; //array[begin]���ǵ�һ����

	while (begin < end)
	{
		// ����������С��key��������array[begin]
		while (begin < end && array[end] >= key)
			end--;
		if (begin < end)
		{
			array[begin] = array[end]; //��array[end]�array[begin]�У�array[end]���γ���һ���µĿ�
			begin++;
		}

		// ���������Ҵ��ڻ����key��������array[end]
		while (begin < end && array[begin] <= key)
			begin++;
		if (begin < end)
		{
			array[end] = array[begin]; //��array[begin]�array[end]�У�array[begin]���γ���һ���µĿ�
			end--;
		}
	}
	//�˳�ʱ��begin����end,��key�������С�
	array[begin] = key;

	return begin;//�����µ�div
}
// ��������ǰ��ָ�뷨
int PartSort3(int* array, int left, int right)
{
	int cur = 0;
	int prev = cur - 1;
	int key;
	int mid = GetIndexOfMid(array, left, right); //ȡǰ�к������м�ֵ��Ϊ��׼ֵ������ʱ�临�Ӷȹ���
	swap(array[mid], array[right - 1]);
	key = array[right - 1];

	while (cur < right)
	{
		if (array[cur] < key&&++prev != cur)
		{
			swap(array[prev], array[cur]);
		}
		cur++;
	}
	swap(array[++prev], array[right - 1]);
	return prev;
}

void QuickSort(int* array, int left, int right)
{
	//����ҿ�
	//�����Ԫ�أ��ݹ���ڣ�
	if (right - left < 5)
	{
		InsertSort(array + left, right - left);
	}
	else
	{
		int div = PartSort3(array, left, right);
		QuickSort(array, left, div);
		QuickSort(array, div + 1, right);
	}
}
// �������� �ǵݹ�ʵ��
void QuickSortNonR(int* a, int left, int right)
{
	stack<int> s;
	if (left < right)
	{
		s.push(left);
		s.push(right);
	}
	while (!s.empty())
	{
		int right = s.top();
		s.pop();
		int left = s.top();
		s.pop();


		int div = PartSort1(a, left, right);	
		if (left < div - 1)
	    {
		   s.push(left);
		   s.push(div - 1);
		}
		if (div + 1<right)
		{
		  s.push(div + 1);
		  s.push(right);
		}

		/*if (left < right)
		{
			int div = PartSort1(a, left, right);
			s.push(right);
			s.push(div + 1);
			s.push(div - 1);
			s.push(left);
		}*/
	}
}
void QuickSortNonR1(int* a, int size)
{
	stack<int> s;
	s.push(size);
	s.push(0);
	while (!s.empty())
	{
		int left = s.top();
		s.pop();
		int right = s.top();
		s.pop();

		if (right - left > 1)
		{

			int div = PartSort1(a, left, right);
			//div�ǻ�׼ֵ��λ��
			//��벿��[left,div)
			//�Ұ벿��[div+1,right)
			//�ȷ��ң��ٷ���
			s.push(right);
			s.push(div + 1);

			s.push(div);
			s.push(left);
		}
	}
}
//4.�鲢����
//�鲢����ݹ�ʵ��
//ʱ�临�Ӷ�:O(NlogN)
//�ռ临�Ӷ�:O(N)
//�ȶ�����
void MergeData(int* array, int left, int mid, int right,int* temp)
{
	//����ҿ�
	int begin1 = left, end1 = mid;
	int begin2 = mid, end2 = right;
	int index = left;

	while (begin1 < end1&&begin2 < end2)
	{
		if (array[begin1] <= array[begin2])
		{
			temp[index++] = array[begin1++];
		}
		else
			temp[index++] = array[begin2++];
	}
	while (begin1<end1)
		temp[index++] = array[begin1++];
	while (begin2<end2)
		temp[index++] = array[begin2++];
}
void _MergeSort(int* array, int left, int right, int* temp)
{
	if (right - left > 1)
	{
		int mid = left + ((right - left) >> 1);
		_MergeSort(array, left, mid, temp);
		_MergeSort(array, mid, right, temp);
		MergeData(array, left, mid, right, temp);//�鲢
		//����ʱ�ռ�temp������ԭ�ռ�array��ȥ
		memcpy(array + left, temp + left, (right - left)*sizeof(array[0]));
	}
}
void MergeSort(int* array, int size)
{
	int* temp = (int*)malloc(sizeof(array[0])*size);
	if (NULL == temp)
	{
		assert(0);
		return ;
	}
	_MergeSort(array, 0, size, temp);
	free(temp);
}
//�鲢����ǵݹ�ʵ��
void MergeSortNonR(int* array, int size)
{
	int gap = 1;
	int* temp = (int*)malloc(sizeof(array[0])*size);
	if (NULL == temp)
	{
		assert(0);
		return;
	}
	while (gap < size)
	{
		for (int i = 0; i < size; i += 2 * gap)
		{
			int left = i;
			int mid = left + gap;
			int right = mid + gap;
			//��ֹԽ��
			if (mid > size)
			{
				mid = size;
			}
			if (right > size)
			{
				right = size;
			}
			//�鲢
			MergeData(array, left, mid, right, temp);
		}
		memcpy(array, temp, size*sizeof(array[0]));
		gap <<= 1;
	}
	free(temp);
}
//��������
void CountSort(int* array, int size)
{
	//1.ͳ�����ݷ�Χ----�����Ǳ���ģ�������û����߷�Χ�ˣ��Ͳ���Ҫͳ���ˣ�
	int minValue = array[0];
	int maxValue = array[0];
	for (int i = 0; i < size; i++)
	{
		if (array[i] < minValue)
			minValue = array[i];
		if (array[i] > maxValue)
			maxValue = array[i];
	}
	//��ͬ����Ԫ�ظ���
	int range = maxValue - minValue + 1;
	//2.����ռ�
	int* ArrayCount = (int*)malloc(range*sizeof(int));
	if (NULL == ArrayCount)
	{
		assert(0);
		return;
	}
	memset(ArrayCount, 0, range*sizeof(int));
    //3.ͳ��û��Ԫ�س��ֵĴ���
	for (int i = 0; i < size; i++)
	{
		ArrayCount[array[i] - minValue]++;
	}
	//4.�����ݽ��л���
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		while (ArrayCount[i])
		{
			array[index++] = i + minValue;
			ArrayCount[i]--;
		}
	}
	free(ArrayCount);
}
//��ӡ����
void Printf(int *array, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", array[i]);
	}
	cout << endl;
}

void Swap1(int &a, int &b)
{
	int c;
	c = a;
	a = b; 
	b = c;
}
//���Ժ���
void Test1()
{
	int array[] = { 3, 6, 9, 4, 2, 8, 7, 10, 1, 5 };
	
	//InsertSort(array, sizeof(array) / sizeof(array[0]));
	//cout << "ֱ�Ӳ�������: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));
	

	//ShellSort(array, sizeof(array) / sizeof(array[0]));
	//cout << "ϣ������: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));


	//int a = 6, b = 7;
	//Swap1(a, b);
	//cout << a << b << endl;

	//SelectSort(array, sizeof(array) / sizeof(array[0]));
	//cout << "ѡ������: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));

	//HeapSort(array, sizeof(array)/sizeof(array[0]));
	//cout << "������: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));

	//BubbleSort(array, sizeof(array) / sizeof(array[0]));
	//cout << "ð������: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));

	//QuickSort(array, 0, sizeof(array) / sizeof(array[0]));
	//cout << "��������: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));

	//QuickSortNonR1(array,sizeof(array) / sizeof(array[0]));
	//cout << "��������ǵݹ�: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));

	//MergeSort(array, sizeof(array) / sizeof(array[0]));
	//cout << "�鲢����: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));

	//MergeSortNonR(array, sizeof(array) / sizeof(array[0]));
	//cout << "�鲢����ǵݹ�: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));

	//CountSort(array, sizeof(array) / sizeof(array[0]));
	//cout << "��������: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));

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