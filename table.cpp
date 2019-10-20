#include "table.h"
#include <iostream>
using namespace std;



void table::Search(string type,string atri,long value,vector<vector<long>> v)
{
	ifstream index;
	//先判断有没索引文件
	if(Exist_index(atri)==1)
	{
		index.open(atri);
		if(index.is_open())
		{
			//有索引文件且能被打开，则使用索引搜索
			Search_by_Index(type,atri,value,v);
		}
		else
			Error("opening index file");
	}
	else
	{
		//没有的话先建立再查询
		Index(1,atri);
		index.open(atri);
		if(index.is_open())
		{
			Search_by_Index(type,atri,value,v);
		}
		else
			Error("opening index file");		
	}
}

void table::Search_by_Index(string type,string atri,long value,
	vector<vector<long>> v){
	cout<<"search by index\n";
}



int table::Exist_index(string atri)
{
	ifstream file;
	file.open(atri);
	if(file.is_open())
		return 1;
	else
		return 0;
}

void Error(string stri)
{
	cout<<"error in"<<str<<"\n";
}


