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
	/*�ҵ���i����ŵ�Ԫ�أ�����ҵ��򷵻ز��޸�e���Ҳ����򷵻�0*/
int LocateElem(NodeList &L, int e);
	/*�ҵ���һ����e��ͬ��Ԫ����ţ���������ţ����û���ҵ��򷵻�0*/
NodeList list_getElemPrior(NodeList &L, int i);
	/*�ҵ���i��Ԫ�ص�ǰ���������ظ�ָ�� L������ i����i��Ԫ�أ�*/
int List_insert(NodeList L, int i, int e);
	/* �ڴ�ͷ����˫��ѭ�����Ա�L�е�i��λ��֮ǰ����Ԫ��e��i�ĺϷ�ֵΪ1��i�ܱ�+1 */
int ListDelete(NodeList L, int i);
	 /* ɾ����ͷ����˫��ѭ�����Ա�L�ĵ�i��Ԫ�أ�i�ĺϷ�ֵΪ1��i�ܱ� */

void Listclear(NodeList &L);
	/*�������*/