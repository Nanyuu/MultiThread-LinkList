#include<iostream>
#include"List_Init.h"
#include<malloc.h>

using namespace std;

#define ERROR 0



void list_init(NodeList &L)
{
	L = (NodeList)malloc(sizeof(Noder));
	if (L)
	{
		L->next = L->prior = L;
		L->data = 0;
		//cout << "init success" << endl;
	}
	else
	{
		exit(OVERFLOW);
	}
}

bool list_empty(NodeList &L)
{
	if (L->next == L && L->prior == L)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int list_length(NodeList &L)
{
	NodeList p = L->next;
	int i = 1;
	if (list_empty(L))
	{
		return 0;
	}
	while (p->next!=L)
	{
		i++;
		p = p->next;
	}
	return i;
}

bool GetElem(NodeList &L, int i, int *e)
{
	int j = 1;
	NodeList p = L->next;
	while (p!=L&&j<i)
	{
		p = p->next;
		j++;
	}
	if (p == L || j > i)
	{
		return false;
	}
	*e = p->data;
	return true;
}

int LocateElem(NodeList &L, int e)
{
	int i = 0;
	NodeList p = L->next;
	while (p!=L)
	{
		i++;
		if (p->data == e)
		{
			return i;
			p = p->next;
		}
		return ERROR;
	}
}

NodeList list_getElemPrior(NodeList &L, int i)
{
	int j;
	NodeList p = L; /* pָ��ͷ��� */
	if (i<0 || i>list_length(L)) /* iֵ���Ϸ� */
		return NULL;
	for (j = 1; j <= i; j++)
		p = p->next;
	return p;
}

int List_insert(NodeList L, int i, int e)
{ 
 
	NodeList p, s;
	if (i<1 || i>list_length(L) + 1) /* iֵ���Ϸ� */
		return ERROR;
	p = list_getElemPrior(L, i - 1); /* ��L��ȷ����i��Ԫ��ǰ����λ��ָ��p */
	if (!p) /* p=NULL,����i��Ԫ�ص�ǰ��������(��ͷ���Ϊ��1��Ԫ�ص�ǰ��) */
		return ERROR;
	s = (NodeList)malloc(sizeof(Noder));
	if (!s)
		return ERROR;
	s->data = e;
	s->prior = p; /* �ڵ�i-1��Ԫ��֮����� */
	s->next = p->next;
	p->next->prior = s;
	p->next = s;
	return 1;
}

int ListDelete(NodeList L, int i)
{ /* ɾ����ͷ����˫��ѭ�����Ա�L�ĵ�i��Ԫ�أ�i�ĺϷ�ֵΪ1��i�ܱ� */
	NodeList p;
	if (i < 1) /* iֵ���Ϸ� */
		return ERROR;
	p = list_getElemPrior(L, i); /* ��L��ȷ����i��Ԫ�ص�λ��ָ��p */
	if (!p) /* p=NULL,����i��Ԫ�ز����� */
		return ERROR;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return 1;
}

void Listclear(NodeList &L)
{
	NodeList q = L->next;
	NodeList P = L->next;
	while (P!=L)
	{
		q = P->next;
		free(P);
		P = q;
	}
	L->next = L->prior = L;
}