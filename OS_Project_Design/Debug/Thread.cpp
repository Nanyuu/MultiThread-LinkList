#include<windows.h>
#include <process.h>
#include<iostream>
#include<cstdlib>
#include<time.h>
#include"MultiThread.h"
#include "List_Init.h"
using namespace std;

HANDLE h_mutex;
HANDLE fmutex;
HANDLE rmutex;
HANDLE Rcount;

int Readcount = 0;
void PerformRead(NodeList &L);
void RandomWrite(NodeList &L);
unsigned __stdcall Read(void *pa);
unsigned __stdcall Write(void *pa);
int seed = 1;
int times = 0;
int fail_Times = 0;
int thread_A = 0;


unsigned __stdcall DoInsert(void *pA)
{
	
	ThreadInfo *Info;
	Info = (ThreadInfo*)pA;
	int x = ((ThreadInfo *)(pA))->List_Elem;
	//cout << "x= " << x << endl;
	//cout << "thread info->location is " << Info->List_Location << endl;

	
	for (;;)
	{
		if (Info->List_Location-1 > list_length(Info->L))
		{
			Sleep(5);
		}
		else
		{
			break;
		}
	}
	WaitForSingleObject(h_mutex, INFINITE);
	int a = List_insert(Info->L, Info->List_Location, Info->List_Elem);
	//cout << "i get an " << a << endl;
	cout << " " << list_length(Info->L) + 1;
	Sleep(10);
	ReleaseMutex(h_mutex);
	return 0;

}

DWORD useThread(int i, int e, NodeList &L)
{
	ThreadInfo *a = new ThreadInfo[1];
	a[0].List_Location = i;
	a[0].List_Elem = e;
	a[0].L = L;
	a[0].Thread_Num = i;
	//cout << "a.list_location = " << i << endl;
	//cout << "a.L " << L->data << endl;
	HANDLE Thread_Handle;
	//unsigned int ThreadID;

	h_mutex = CreateMutex(NULL, FALSE, "mutex_for_thread");



	//void *c = (void*)&a[0];
	//ThreadInfo *d;
	//d = (ThreadInfo *)c;
	//cout << "d->elem "<<d->List_Elem << endl;

	Thread_Handle =(HANDLE)_beginthreadex(NULL, 0, DoInsert, (void*)&a[0], 0, NULL);
	CloseHandle(Thread_Handle);

	return 0;
}

void Read_Write_Test(NodeList &L)
{
	int WRITE_thread_num = 1;
	ThreadInfo *a = new ThreadInfo[40000];
	a[0].L = L;
	Rcount = CreateMutex(NULL, FALSE, "mutex_for_Rcount");
	fmutex = CreateMutex(NULL, FALSE, "mutex_for_fmutex");
	h_mutex = CreateMutex(NULL, FALSE, "mutex_for_thread");
	HANDLE Read_Handle;
	HANDLE Write_Handle;
	for (int m = 1; m < 30000; m++)
	{
		a[m].L = L;
		a[m].Thread_Num = m;
	}

	for (int i = 0; i < 1200; i++)
	{
		if (i % 500 == 1)
		{
			Read_Handle = (HANDLE)_beginthreadex(NULL, 0, Read, (void*)&a[0], 0, NULL);
			CloseHandle(Read_Handle);
		}
		//cout << "read_Handle="<<Read_Handle << endl;

			//WaitForSingleObject(NUMutex, INFINITE);
			//a[0].Thread_Num = WRITE_thread_num;
		Write_Handle = (HANDLE)_beginthreadex(NULL, 0, Write, (void*)&a[WRITE_thread_num], 0, NULL);
		WRITE_thread_num++;
		CloseHandle(Write_Handle);
			//ReleaseMutex(NUMutex);
		//cout <<"write_handle="<< Write_Handle << endl;
		//Sleep(5);
	}

	

}

unsigned __stdcall Read(void *pa)
{
	//WaitForSingleObject(h_mutex, INFINITE);
	//ReleaseMutex(h_mutex);
	WaitForSingleObject(Rcount,INFINITE);
	if (0==Readcount)
	{
		WaitForSingleObject(fmutex,INFINITE);
		cout << endl;
	}
	Readcount++;

	ReleaseMutex(Rcount);

	//WaitForSingleObject(Rcount, INFINITE);
	ThreadInfo *Info;
	Info = (ThreadInfo*)pa;

	PerformRead(Info->L);
	
	//ReleaseMutex(Rcount);

	WaitForSingleObject(Rcount, INFINITE);
	
	
	Readcount--;
	if (0 ==Readcount)
	{
		cout <<"读取完成" << endl;
		cout << "thread: NUM = ";
		ReleaseMutex(fmutex);
	}
	ReleaseMutex(Rcount);
	
	return 0;
}

unsigned __stdcall Write(void *pa)
{
	
	WaitForSingleObject(h_mutex,INFINITE);
	WaitForSingleObject(fmutex, INFINITE);
	ThreadInfo *Info;
	Info = (ThreadInfo*)pa;
	
	cout << Info->Thread_Num  << "  ";
	RandomWrite(Info->L);
	//if (Info->Thread_Num % 500 == 0)
	//{
	//	HANDLE Read_Handle_1;
	//	Read_Handle_1 = (HANDLE)_beginthreadex(NULL, 0, Read, (void*)Info, 0, NULL);
	//	CloseHandle(Read_Handle_1);

	//cout << "Write Thread " << Info->Thread_Num << "finished" << endl;
	//cout << "already insert " << list_length(Info->L) << endl;
	ReleaseMutex(fmutex);

	ReleaseMutex(h_mutex);
	return 0;
}

void PerformRead(NodeList &L)
{
	int Elem = 0;
	for (int i = 1; i < list_length(L) + 1; i++)
	{
		if (GetElem(L, i, &Elem))
		{
			//cout << Elem << " ";
		}
		else
			cout << "读取失败" << endl;
	}
	//cout << endl;
}

void RandomWrite(NodeList &L)
{
	//thread_A++;
	//cout <<thread_A << "thread_A" << endl;
	srand(unsigned(time(0)));
	int range = list_length(L) + 1;
	int random_LOC = rand() % range;
	srand(unsigned(time(0))*seed);
	int random_Elem = rand()%20;
	seed++;
	if (List_insert(L, random_LOC+1, random_Elem))
	{
		times++;
		//cout<<"   randomloc=="<<random_LOC << "random_LOC!" <<list_length(L)<<"   "<<times << "fail_time:"<<fail_Times<< endl;
		//cout << "insert success" << endl;
	}
	else
	{
		//cout << "insert fail" << endl;
		fail_Times++;
	}
}
