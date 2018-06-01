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
HANDLE Dfailcount;
HANDLE Dsuccesscout;

int Dfailcount_num = 0;
int Dsuccesscout_num = 0;
int Readcount = 0;
int allthread = 600;
int allreadcount = 0;
int pressure_ALL = 100000;
int pressure_Delete_Success = 0;
int pressure_Delete_Fail = 0;
int pressure_Read_count = 0;
int pressure_Write_count = 0;
void PerformRead(NodeList &L);
void RandomWrite(NodeList &L);
int RandomDelete(NodeList &L);
void Pressure_Test(NodeList &L);
void Test_out(int m);
unsigned __stdcall Delete(void *pa);
unsigned __stdcall Read(void *pa);
unsigned __stdcall Write(void *pa);
unsigned __stdcall Pressure_Delete(void *pa);
unsigned __stdcall Pressure_Read(void *pa);
unsigned __stdcall Pressure_Write(void *pa);
void clearNum();

int seed = 1;
int times = 0;
int fail_Times = 0;
int thread_A = 0;


unsigned __stdcall DoInsert(void *pA)
{
	
	ThreadInfo *Info;
	Info = (ThreadInfo*)pA;
	int x = ((ThreadInfo *)(pA))->List_Elem;	
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
	clearNum();
	Listclear(L);
	ThreadInfo *a = new ThreadInfo[1];
	a[0].List_Location = i;
	a[0].List_Elem = e;
	a[0].L = L;
	a[0].Thread_Num = i;
	HANDLE Thread_Handle;

	h_mutex = CreateMutex(NULL, FALSE, "mutex_for_thread");
	Thread_Handle =(HANDLE)_beginthreadex(NULL, 0, DoInsert, (void*)&a[0], 0, NULL);
	CloseHandle(Thread_Handle);

	return 0;
}

void Read_Write_Test(NodeList &L)
{
	clearNum();
	Listclear(L);
	int WRITE_thread_num = 1;
	ThreadInfo *a = new ThreadInfo[40000];
	a[0].L = L;
	Rcount = CreateMutex(NULL, FALSE, "mutex_for_Rcount");
	fmutex = CreateMutex(NULL, FALSE, "mutex_for_fmutex");
	h_mutex = CreateMutex(NULL, FALSE, "mutex_for_thread");
	Dfailcount = CreateMutex(NULL, FALSE, "mutex_for_Dfailcount");
	Dsuccesscout = CreateMutex(NULL, FALSE, "mutex_for_Dsuccesscount");
	HANDLE Read_Handle;
	HANDLE Write_Handle;
	HANDLE Delete_Handle;
	for (int m = 1; m < 30000; m++)
	{
		a[m].L = L;
		a[m].Thread_Num = m;
	}

	for (int i = 0; i < 600; i++)
	{
		Read_Handle = (HANDLE)_beginthreadex(NULL, 0, Read, (void*)&a[0], 0, NULL);
		if (i % 500 == 1)
		{
			Read_Handle = (HANDLE)_beginthreadex(NULL, 0, Read, (void*)&a[0], 0, NULL);
			CloseHandle(Read_Handle);
		}
		Write_Handle = (HANDLE)_beginthreadex(NULL, 0, Write, (void*)&a[WRITE_thread_num], 0, NULL);
		Delete_Handle = (HANDLE)_beginthreadex(NULL, 0, Delete, (void *)&a[WRITE_thread_num], 0, NULL);

		WRITE_thread_num++;
		
	}
	while (allthread)
	{
		Sleep(1000);
	}
	CloseHandle(Write_Handle);
	CloseHandle(Read_Handle);
	CloseHandle(Delete_Handle);
	int NUM = Dsuccesscout_num + Dfailcount_num;
	if (NUM==600)
	{
		cout << "�����̲߳��Գɹ���һ��600��ɾ���̣߳��ɹ�" << Dsuccesscout_num << "��,��Ϊ�ձ�ɾ��ʧ��" << Dfailcount_num << "��" << endl;
		cout << "�����̲߳��Գɹ���һ��600�������߳�,�ɹ�" << times << "��" << endl;
		cout << "�����̲߳��Գɹ���һ��ִ��602�������񣬳ɹ�" << allreadcount << "��" << endl;
		cout << "��ǰ��������һ���У�" << list_length(L) << "��"<<endl;
	}
}

void Pressure_Test(NodeList &L)
{
	clearNum();
	Listclear(L);
	int WRITE_thread_num = 1;
	ThreadInfo *a = new ThreadInfo[40000];
	a[0].L = L;
	Rcount = CreateMutex(NULL, FALSE, "mutex_for_Rcount");
	fmutex = CreateMutex(NULL, FALSE, "mutex_for_fmutex");
	h_mutex = CreateMutex(NULL, FALSE, "mutex_for_thread");
	Dfailcount = CreateMutex(NULL, FALSE, "mutex_for_Dfailcount");
	Dsuccesscout = CreateMutex(NULL, FALSE, "mutex_for_Dsuccesscount");
	HANDLE Read_Handle;
	HANDLE Write_Handle;
	HANDLE Delete_Handle;
	for (int m = 1; m < 30000; m++)
	{
		a[m].L = L;
		a[m].Thread_Num = m;
	}

	for (int i = 0; i < 600; i++)
	{
		//if (i % 500 == 1)
		//{
		//	Read_Handle = (HANDLE)_beginthreadex(NULL, 0, Pressure_Read, (void*)&a[0], 0, NULL);
		//	CloseHandle(Read_Handle);
		//}
		Write_Handle = (HANDLE)_beginthreadex(NULL, 0, Pressure_Write, (void*)&a[WRITE_thread_num], 0, NULL);
		Delete_Handle = (HANDLE)_beginthreadex(NULL, 0, Pressure_Delete, (void *)&a[WRITE_thread_num], 0, NULL);
	}
	int m = pressure_Delete_Fail + pressure_Delete_Success + pressure_Write_count;
	while (m < 120000)
	{
		
		m = pressure_Delete_Fail + pressure_Delete_Success + pressure_Write_count;
		Test_out(m);
		Sleep(50);
	}
	if (m == 120000)
	{
		cout << "���12��������д����" << endl;
		cout << "pressure_Delete fail: " << pressure_Delete_Fail << endl;
		cout << "pressure_Delete success:" << pressure_Delete_Success << endl;
		cout << " pressure_write:" << pressure_Write_count << endl;
	}
}

unsigned __stdcall Read(void *pa)
{
	WaitForSingleObject(Rcount,INFINITE);
	if (0==Readcount)
	{
		WaitForSingleObject(fmutex,INFINITE);
	}
	Readcount++;
	allreadcount++;

	ReleaseMutex(Rcount);
	ThreadInfo *Info;
	Info = (ThreadInfo*)pa;

	PerformRead(Info->L);

	WaitForSingleObject(Rcount, INFINITE);
	
	
	Readcount--;
	if (0 ==Readcount)
	{
		//cout <<"��ȡ���" << endl;
		//cout << "thread: NUM = ";
		ReleaseMutex(fmutex);
	}
	ReleaseMutex(Rcount);
	
	return 0;
}


unsigned __stdcall Pressure_Read(void *pa)
{
	for (int i = 0; i < 1000; i++)
	{
		WaitForSingleObject(Rcount, INFINITE);
		if (0 == Readcount)
		{
			WaitForSingleObject(fmutex, INFINITE);
		}
		Readcount++;
		allreadcount++;

		ReleaseMutex(Rcount);
		ThreadInfo *Info;
		Info = (ThreadInfo*)pa;

		PerformRead(Info->L);

		WaitForSingleObject(Rcount, INFINITE);


		Readcount--;
		if (0 == Readcount)
		{
			//cout <<"��ȡ���" << endl;
			//cout << "thread: NUM = ";
			ReleaseMutex(fmutex);
		}
		ReleaseMutex(Rcount);
	}

	return 0;
}

unsigned __stdcall Pressure_Write(void *pa)
{
	for (int i = 0; i < 100; i++)
	{
		WaitForSingleObject(h_mutex, INFINITE);
		WaitForSingleObject(fmutex, INFINITE);
		ThreadInfo *Info;
		Info = (ThreadInfo*)pa;

		//cout << Info->Thread_Num  << "  ";
		RandomWrite(Info->L);
		ReleaseMutex(fmutex);

		ReleaseMutex(h_mutex);
	}
	return 0;
}

unsigned __stdcall Pressure_Delete(void *pa)
{
	for (int i = 0; i < 100; i++)
	{
		WaitForSingleObject(h_mutex, INFINITE);
		WaitForSingleObject(fmutex, INFINITE);
		ThreadInfo *Info;
		Info = (ThreadInfo*)pa;

		//cout << Info->Thread_Num << "  ";
		RandomDelete(Info->L);
		ReleaseMutex(fmutex);

		ReleaseMutex(h_mutex);
	}
	return 0;
}



unsigned __stdcall Write(void *pa)
{
	
	WaitForSingleObject(h_mutex,INFINITE);
	WaitForSingleObject(fmutex, INFINITE);
	ThreadInfo *Info;
	Info = (ThreadInfo*)pa;
	
	//cout << Info->Thread_Num  << "  ";
	RandomWrite(Info->L);
	ReleaseMutex(fmutex);

	ReleaseMutex(h_mutex);
	return 0;
}

unsigned __stdcall Delete(void *pa)
{

	WaitForSingleObject(h_mutex, INFINITE);
	WaitForSingleObject(fmutex, INFINITE);
	ThreadInfo *Info;
	Info = (ThreadInfo*)pa;

	//cout << Info->Thread_Num << "  ";
	RandomDelete(Info->L);
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

		}
		else
			cout << "��ȡʧ��" << endl;
	}
}

void RandomWrite(NodeList &L)
{
	srand(unsigned(time(0)));
	int range = list_length(L) + 1;
	int random_LOC = rand() % range;
	srand(unsigned(time(0))*seed);
	int random_Elem = rand()%20;
	seed++;
	if (List_insert(L, random_LOC+1, random_Elem))
	{
		times++;
		pressure_Write_count++;
	}
	else
	{
		fail_Times++;
	}
}

int RandomDelete(NodeList &L)
{
	if (list_length(L)==0)
	{
		WaitForSingleObject(Dfailcount,INFINITE);
		Dfailcount_num++;
		pressure_Delete_Fail++;
		allthread--;
		ReleaseMutex(Dfailcount);
		return TRUE;
	}

	srand(unsigned(time(0)));
	int range = list_length(L);
	int random_LOC = rand() % range;
	srand(unsigned(time(0))*seed);
	int random_Elem = rand() % 20;
	seed++;
	if (ListDelete(L, random_LOC+1))
	{
		WaitForSingleObject(Dsuccesscout, INFINITE);
		Dsuccesscout_num++;
		pressure_Delete_Success++;
		allthread--;
		ReleaseMutex(Dsuccesscout);
		return TRUE;
	}
	else
	{
		WaitForSingleObject(Dfailcount, INFINITE);
		Dfailcount_num++;

		ReleaseMutex(Dfailcount);
		cout << "ɾ��ʧ��" <<"allthread="<<allthread<< endl;
		return FALSE;
	}
}

void clearNum()
{
	Dfailcount_num = 0;
	Dsuccesscout_num = 0;
	Readcount = 0;
	allthread = 600;
	allreadcount = 0;
	pressure_ALL = 100000;
	pressure_Delete_Success = 0;
	pressure_Delete_Fail = 0;
	pressure_Read_count = 0;
	pressure_Write_count = 0;

}

void Test_out(int m)
{
	system("cls");
	cout << "����1�����̲߳��룬ÿ�������ʾ�б��� MultiThread_Insert" << endl;
	cout << "����2, ��ȡ������ʾ���е�����Ԫ�� Read list,show all element" << endl;
	cout << "����3�� ɾ�������е����һ��Ԫ�� Delete the last element" << endl;
	cout << "����4�����ж��̶߳�д���� Do the multithread Read/Write Test" << endl;
	cout << "����5�� ���������  Print the length of list" << endl;
	cout << "����6��ִ�е�Ԫ���� Unit Testing " << endl;
	cout << "����7��ִ�м��ɲ��� Integration Testing" << endl;
	cout << "����8��ִ��ѹ������ Stress Testing" << endl;
	cout << "����0���˳��� exit" << endl;
	cout << "u entered 8" << endl;
	cout << "--------------����ִ��ѹ�����ԣ�-----------" << endl;

	float a =  float(m/120000.0)*100;

	cout << "��ǰ���ȣ�" << a << "%" << endl;
}
