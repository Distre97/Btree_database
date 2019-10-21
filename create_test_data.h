#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <cassert>
using namespace std;

class test{

private:
	int _number;//数据的行数
	string _file_name;//
	ofstream _save_file;//
	int _sum_size;
public:

	vector<vector<long long>> data;
	vector<string> atri;
	vector<int> _size;//存储每个属性名的大小

	//初始化数据
	test(int number,string file_name){
		this->_sum_size = 0;
		this->_number = number;
		this->_file_name = file_name;
		this->_save_file.open(file_name,ios::app|ios::binary);
		if(!_save_file.is_open())
			// assert(1);
			cout<<"error for files open"<<endl;
		else
		{
			// _save_file.seekp(0,ios::end);
			create_atri();
			create_data();
			save_atri();
			save_data();
			cout<<"over!"<<endl;
		}
	}
	~test(){
		//关闭文件释放内存
		this->_save_file.close();
		// vector<vector<long long>>.swap(data);
		// vector<string>.swap(atri);
		// vector<int>.swap(_size);
	}

	//随机产生属性名
	void create_atri();
	//随机产生数据值，一次100个，即一行
	void create_data();
	//保存数据，原子函数
	void save_data();
	//保存属性名
	void save_atri();
	//把long long类型转化为char*类型
	// void long_2_char(long long num,char* arr);

};

#endif