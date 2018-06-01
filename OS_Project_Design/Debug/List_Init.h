#pragma once



struct Node
{
	struct Node *next, *prior;
	int data;
};

typedef Node *NodeList, Noder;

void list_init(NodeList &L); // initialize the list
bool list_empty(NodeList &L); //Empty?
int list_length(NodeList &L); //return length.when list is only L,return 0
bool GetElem(NodeList &L, int i, int *e);
	/*找到第i个序号的元素，如果找到则返回并修改e，找不到则返回0*/
int LocateElem(NodeList &L, int e);
	/*找到第一个与e相同的元素序号，并返回序号，如果没有找到则返回0*/
NodeList list_getElemPrior(NodeList &L, int i);
	/*找到第i个元素的前驱，并返回改指针 L（链表） i（第i个元素）*/
int List_insert(NodeList L, int i, int e);
	/* 在带头结点的双链循环线性表L中第i个位置之前插入元素e，i的合法值为1≤i≤表长+1 */
int ListDelete(NodeList L, int i);
	 /* 删除带头结点的双链循环线性表L的第i个元素，i的合法值为1≤i≤表长 */

void Listclear(NodeList &L);
	/*清空链表*/