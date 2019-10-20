#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED
#endif

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
	ifstream _save_file;//
public:

	vector<vector<long>> data;
	vector<string> atri;

	//初始化数据
	test(int number,string file_name){
		this->_number = number;
		this->_file_name = file_name;
		this->_save_file.open(file_name,ios::out|ios::in);
		if(!_save_file.is_open())
			assert(1);
		else
		{
			create_atri();
			create_data();
			save_atri();
			save_data();
		}
	}
	~test(){
		this->_save_file.close();
	}

	//随机产生属性名
	void create_atri();
	//随机产生数据值，一次100个，即一行
	void create_data();
	//保存数据，原子函数
	void save_data();
	//保存属性名
	void save_atri();

};