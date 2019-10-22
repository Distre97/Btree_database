#include "create_test_data.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

void test::create_atri()
{
	int atri_len;
	string atri="";

	srand((unsigned)time(NULL));
	atri_len = (rand()%8)+3;//变量名长度在3---10之间
	
	for(int j=0;j<100;j++)
	{
		
		for(int i=0;i<atri_len;i++)
		{
			// srand((unsigned)time(NULL));//重置随机种子
			int r ;
			while(true){//判断是否为字母
				r = (rand()%58)+65;
				if((r>=65&&r<=90)||(r>=97&&r<=122))
					break;
			}
			atri += (char)r;
		}
		// cout<<" "<<atri;
		test::_size.push_back(atri.size());//当前长度加入容器
		test::_sum_size += atri.size();//总长度增加
		atri = atri+'@';//作为属性名之间的分割符
		test::atri.push_back(atri);//加入容器

		//插入属性和属性名长度的键值对
		test::atri_size.insert(make_pair(atri,atri.size()));
		
		atri.erase(atri.begin(),atri.end());//删除临时字符串
		atri_len = (rand()%8)+3;//重置长度
	}
}

void test::create_data()
{
	long a=0;
	vector<long long> data;
	srand((unsigned)time(NULL));
	for(int j=0;j<test::_number;j++)
	{	

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
	cout<<"create success"<<endl;
}

//写入属性名
void test::save_atri()
{
	test::_save_file.seekp(0,ios::end);//从流末尾写入
	// long l = test::_save_file.tellp();//当前流指针位置
	// char* buffer;
	// long size;
	// size=test::_save_file.tellp();

	for(int i=0;i<100;i++)
	{
		// buffer = new char [l];
		// test::_save_file<<test::atri.at(i)<<"@";
		
		test::_save_file.write((char*)&test::atri[i],test::_size.at(i));
	}
	cout<<"write success"<<endl;
}

//写具体数据
void test::save_data()
{
	char* arr;
	test::_save_file.seekp(0,ios::end);//从流末尾写入
	cout<<test::data.size();
	// cout<<test::_number<<endl;
	// string show = "";
	for(int i=0;i<test::_number;i++)
	{
		for(int j=0;j<100;j++)
		{
			arr = (char*)&test::data.at(i).at(j);
			// test::long_2_char(test::data.at(i).at(j),arr);
			test::_save_file.write(arr,8);
		}
		// test::_save_file<<endl;
		
	}
	cout<<"data success"<<endl;
}

// void test::long_2_char(long long num,char* arr)
// {
// 	arr = (char*)&num;
	// arr = new char[8];
	// int byt = 56;
	// for(int i=7;i>=0;i--)
	// {
	// 	long long temp = num<<byt;
	// 	arr[i] = temp>>56;
	// 	byt -= 8;
	// }
	// cout<<"_2_ ";
// }




