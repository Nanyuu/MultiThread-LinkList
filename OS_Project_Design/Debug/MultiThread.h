#pragma once
#include<windows.h>
#include"List_Init.h"

struct ThreadInfo
{
	int Thread_Num;
	int List_Location;
	int List_Elem;
	NodeList L;
};

DWORD useThread(int i, int e, NodeList &L);
  /*�����߳��ڵ�i�����ݺ����e*/
DWORD Reader(int i, int e, NodeList &L, int j);
	/*�����̶߳�������*/
void Read_Write_Test(NodeList &L);
	/*���ڲ��Զ������д��*/

void Pressure_Test(NodeList &L);
    /*���ڽ���ѹ������*/