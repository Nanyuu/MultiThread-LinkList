#include "List_Init.h"
#include "MultiThread.h"
#include "Testt.h"
#include <iostream>
using namespace std;

bool Test_Insert(NodeList &L)
{
	int recall;
	for (int i=1; i <= 10; i++)
	{
		if (List_insert(L, i, i))
		{
			continue;
		}
		else
		{
			std::cout << "                insert wrong " << endl;
			return FALSE;
			
		}
	}
	if (list_length(L) != 10)
	{
		std::cout << "                   length wrong" << endl;
		return FALSE;
		
	}
	else
	{
		std::cout << "                    insert Test Successed" << endl;
		return TRUE;
	}
}


bool Test_Delete(NodeList &L)
{
	int Initial_Length = list_length(L);
	//if (Initial_Length ==0)
	//{
	//	std::cout << "           Delete run but list is empty"<<endl;
	//	return TRUE;
	//}
	int final_Length = -1;
	if (!ListDelete(L, Initial_Length-1))
	{
		std::cout << "            Delete fail,reason:Delete NULL" << endl;
		return FALSE;
	}
	final_Length = list_length(L);
	if(final_Length != Initial_Length-1)
	{
		std::cout << "           Delete fail,reason:list_length Wrong"<<endl;
		return FALSE;
	}
	else
	{
		std::cout << "            Delete success";
		return TRUE;
	}
}
