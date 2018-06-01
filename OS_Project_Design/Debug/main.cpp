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
	cout << "输入1，多线程插入，每次完成显示列表长度 MultiThread_Insert" << endl;
	cout << "输入2, 读取链表，显示其中的所有元素 Read list,show all element" << endl;
	cout << "输入3， 删除链表中的最后一个元素 Delete the last element" << endl;
	cout << "输入4，进行多线程读写测试 Do the multithread Read/Write Test" << endl;
	cout << "输入5， 输出链表长度  Print the length of list" << endl;
	cout << "输入6，执行单元测试 Unit Testing " << endl;
	cout << "输入7，执行集成测试 Integration Testing" << endl;
	cout << "输入8，执行压力测试 Stress Testing" << endl;
	cout << "输入0，退出。 exit" << endl;
	for (;;)
	{
		
		cin >> c;
		system("cls");
		cout << "输入1，多线程插入，每次完成显示列表长度 MultiThread_Insert" << endl;
		cout << "输入2, 读取链表，显示其中的所有元素 Read list,show all element" << endl;
		cout << "输入3， 删除链表中的最后一个元素 Delete the last element" << endl;
		cout << "输入4，进行多线程读写测试 Do the multithread Read/Write Test" << endl;
		cout << "输入5， 输出链表长度  Print the length of list" << endl;
		cout << "输入6，执行单元测试 Unit Testing " << endl;
		cout << "输入7，执行集成测试 Integration Testing" << endl;
		cout << "输入8，执行压力测试 Stress Testing" << endl;
		cout << "输入0，退出。 exit" << endl;
		if (c == '1')
		{
			Listclear(L);
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
			cout << "继续选择:";
		}
		else if (c == '3')
		{
			cout << "u entered 3" << endl;
			if (ListDelete(L, E_Delete))
			{
				cout << "删除成功" << endl;
				cout << "继续选择:";
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
			cout << "u entered 6" << endl;
			int Recall = 0;
			Listclear(L);
			cout << "--------------正在执行单元测试！-------------" << endl;
			cout << "1、执行插入测试" << endl;
			if (!Test_Insert(L))
			{
				continue;
			}
			cout << "2、执行删除测试" << endl;
			if (!Test_Delete(L))
			{
				continue;
			}
			cout << "3、执行清空测试" << endl;
			if (!Test_Clear(L))
			{
				continue;
			}
		}
		else if (c == '7')
		{
			cout << "u entered 7" << endl;
			cout << "---------------执行集成测试!----------------" << endl;
			Read_Write_Test(L);

		}
		else if (c == '8')
		{
			cout << "u entered 8" << endl;
			cout << "--------------正在执行压力测试！-----------" << endl;
			Pressure_Test(L);
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