//table.h
#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
using namespace std;

class table{

private:
    string _file_name;
    std::vector<string> _index_file_name;

    table(string name){//初始化时读取文件
    	this->tab_file.open(name,ios::out|ios::in);
    	assert(this->tab_file.is_open());
    }

    ~table(){//程序结束时关闭文件
    	tab_file.close();
    }

public:
	ifstream tab_file;
    //查找属性atri=value的所有行，存入vector<vector<long>>中
	void Search(string type,string atri,long value,vector<vector<long>> v);
    void Search_by_Index(string type,string atri,long value,vector<vector<long>> v);
    //判断有无文件atri
    int Exist_index(string atri);
	//添加一行
    int Append(string* atri,int* value);
    //建立索引
    void Index(int type,string atri);
    //
    void Commit();


};


void Error(string stri);
