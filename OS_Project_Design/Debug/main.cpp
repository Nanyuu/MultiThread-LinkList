#include "List_Init.h"
#include"MultiThread.h"
#include "Testt.h"
#include<windows.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void main()
{
	NodeList L;
	list_init(L);
	char c;
	//if (list_empty(L))
	//{
	//	cout << "list is empty" << endl;
	//}

	/*for (int i = 0; i < 100; i++)
	{
		List_insert(L, i, i);
	}
	cout << list_length(L) << endl;
	NodeList p = list_getElemPrior(L, 88);
	cout << p->data << endl;*/
	int Elem;
	int i = 0;
	int j =100;
	int E_Delete=1;
	cout << "����1�����̲߳��룬ÿ�������ʾ�б���" << endl;
	cout << "����2, ��ȡ������ʾ���е�����Ԫ��" << endl;
	cout << "����3�� ɾ�������е����һ��Ԫ��" << endl;
	cout << "����4�����ж��̶߳�д����" << endl;
	cout << "����5�� ���������" << endl;
	cout << "����6��ִ�е�Ԫ����" << endl;
	cout << "����7��ִ�м��ɲ���" << endl;
	cout << "����8��ִ��ѹ������" << endl;
	for (;;)
	{
		
		cin >> c;
		system("cls");
		cout << "����1�����̲߳��룬ÿ�������ʾ�б���" << endl;
		cout << "����2, ��ȡ������ʾ���е�����Ԫ��" << endl;
		cout << "����3�� ɾ�������е����һ��Ԫ��" << endl;
		cout << "����4�����ж��̶߳�д����" << endl;
		cout << "����5�� ���������" << endl;
		cout << "����6��ִ�е�Ԫ����" << endl;
		cout << "����7��ִ�м��ɲ���" << endl;
		cout << "����8��ִ��ѹ������" << endl;
		if (c == '1')
		{
			cout << "u entered 1 " << endl;
			for (; i < j; i++)
			{
				useThread(i, i, L);
			}
			j = i+100;
		}
		else if (c == '2')
		{
			cout << "u entered 2 " << endl;
			cout << "elem is:";
			for (int i = 1; i < list_length(L)+1; i++)
			{
				GetElem(L, i, &Elem);
				cout <<Elem << " ";
				Sleep(10);
			}
			cout << endl;
			cout << "����ѡ��:";
		}
		else if (c == '3')
		{
			cout << "u entered 3" << endl;
			if (ListDelete(L, E_Delete))
			{
				cout << "ɾ���ɹ�" << endl;
				cout << "����ѡ��:";
			}
			j = j - 1;
			i = i - 1;
			
		}
		else if (c == '4')
		{
			cout << "u entered 4" << endl;
			Read_Write_Test(L);
		}
		else if (c == '5')
		{
			cout << "u entered 5" << endl;
			cout << "list length is" << list_length(L) << endl;
		}
		else if( c =='0')
		{
			cout << "exit" << endl;
			break;
		}
		else if (c == '6')
		{
			int Recall = 0;
			cout << "--------------����ִ�е�Ԫ���ԣ�-------------" << endl;
			cout << "1��ִ�в������" << endl;
			if (!Test_Insert(L))
			{
				continue;
			}
			cout << "2��ִ��ɾ������" << endl;
			if (!Test_Delete(L))
			{
				continue;
			}
		}
		else
		{
			cout << "input wrong" << endl;
		}
	}

	
	//cout << "list_length is:" << list_length(L) << endl;
	Sleep(1000);
	getchar();
}