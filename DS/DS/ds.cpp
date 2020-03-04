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