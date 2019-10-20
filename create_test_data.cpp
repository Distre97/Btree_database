#include "create_test_data.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>

void test::create_atri()
{
	int atri_len;
	string atri;

	srand((unsigned)time(NULL));
	atri_len = (rand()%8)+3;//变量名长度在3---10之间
	
	srand((unsigned)time(NULL));//重置随机种子
	for(int j=0;j<100;j++)
	{
		for(int i=0;i<atri_len;i++)
		{
			int r ;
			while(true){//判断是否为字母
				r = (rand()%58)+65;
				if((r>=65&&r<=90)||(r>=97&&r<=122))
					break;
			}
			atri.at(i)=(char)r;
		}
		test::atri.push_back(atri);
	}
}

void test::create_data()
{
	long a=0;
	vector<long> data;
	
	for(int j=0;j<test::_number;j++)
	{	
		srand((unsigned)time(NULL));//每生成一行就换一个随机种子
		data.clear();
		for(int i=0;i<100;i++)
		{
			int temp1 = rand();
			int temp2 = rand();
			a = (long)(temp1*temp2);
			data.push_back(a);
		}
		test::data.push_back(data);
	}
}

//写入属性名，每个属性名之间用@分离
void test::save_atri()
{
	for(int i=0;i<100;i++)
	{
		test::_save_file << test::atri.at(i) <<"@";
	}
	test::_save_file << endl;
}

//写具体数据
void test::save_data()
{
	for(int i=0;i<test::_number;i++)
	{
		for(int j=0;j<100;j++)
		{
			test::_save_file << test::data.at(i).at(j);
		}
		test::_save_file << endl;
	}
}





