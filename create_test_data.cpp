#include "create_test_data.h"
#include <stdlib.h>
#include <time.h>

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
			int r ;
			while(true){//判断是否为字母
				r = (rand()%58)+65;
				if((r>=65&&r<=90)||(r>=97&&r<=122))
					break;
			}
			// printf("%c", r);
			atri += (char)r;
		}
		printf(" ");
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
	long long a=0;
	int_2_l_l temp;
	vector<long long> data;
	srand((unsigned)time(NULL));
	for(int j=0;j<test::_number;j++)
	{	

		data.clear();
		for(int i=0;i<100;i++)
		{
			temp.a = rand();
			temp.b = rand();
			a = (long long)(temp.a*temp.b)%1000;
			data.push_back(a);
		}
		test::data.push_back(data);
	}
}

//写入属性名
void test::save_atri()
{
	test::_save_file.seekp(0,ios::end);//从流末尾写入
	for(int i=0;i<100;i++)
	{
		test::_save_file << test::atri[i];
	}
}

//写具体数据
void test::save_data()
{
	char* arr;
	test::_save_file.seekp(0,ios::end);//从流末尾写入
	for(int i=0;i<test::_number;i++)
	{
		for(int j=0;j<100;j++)
		{
			arr = (char*)&test::data.at(i).at(j);
			test::_save_file.write(arr,8);
		}
	}
}

