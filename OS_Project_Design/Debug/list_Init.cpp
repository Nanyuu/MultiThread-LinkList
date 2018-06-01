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
	NodeList p = L; /* p指向头结点 */
	if (i<0 || i>list_length(L)) /* i值不合法 */
		return NULL;
	for (j = 1; j <= i; j++)
		p = p->next;
	return p;
}

int List_insert(NodeList L, int i, int e)
{ 
 
	NodeList p, s;
	if (i<1 || i>list_length(L) + 1) /* i值不合法 */
		return ERROR;
	p = list_getElemPrior(L, i - 1); /* 在L中确定第i个元素前驱的位置指针p */
	if (!p) /* p=NULL,即第i个元素的前驱不存在(设头结点为第1个元素的前驱) */
		return ERROR;
	s = (NodeList)malloc(sizeof(Noder));
	if (!s)
		return ERROR;
	s->data = e;
	s->prior = p; /* 在第i-1个元素之后插入 */
	s->next = p->next;
	p->next->prior = s;
	p->next = s;
	return 1;
}

int ListDelete(NodeList L, int i)
{ /* 删除带头结点的双链循环线性表L的第i个元素，i的合法值为1≤i≤表长 */
	NodeList p;
	if (i < 1) /* i值不合法 */
		return ERROR;
	p = list_getElemPrior(L, i); /* 在L中确定第i个元素的位置指针p */
	if (!p) /* p=NULL,即第i个元素不存在 */
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