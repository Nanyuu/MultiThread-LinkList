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
  /*创建线程在第i个数据后插入e*/
DWORD Reader(int i, int e, NodeList &L, int j);
	/*创建线程读入数据*/
void Read_Write_Test(NodeList &L);
	/*用于测试多个读者写者*/

void Pressure_Test(NodeList &L);
    /*用于进行压力测试*/