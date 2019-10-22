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
    std::vector<string> _index_file_name;


public:
    table(string name){//初始化时读取文件
        this->tab_file.open(name,ios::out|ios::in);
        assert(this->tab_file.is_open());
    }

    ~table(){//程序结束时关闭文件
        tab_file.close();
    }

	ifstream in_file;//用于读取
    ofstream out_file;//用于写入新增的数据

    vector<string> _atri_in_file;//从文件中获取属性名
    vector<vector<long long>> _data_in_file;//从文件中获取数据
    vector<string> atri;//需要查找的属性
    vector<vector<long long>> data;//查找到的值

    //查找属性atri=value的所有行，存入vector<vector<long>>中
	void Search(string type,string atri,long long value,vector<vector<long long>> v);
    //通过索引查找
    void Search_by_Index(string type,string atri,long value,vector<vector<long>> v);
    //判断有无文件atri
    int Exist_index(string atri);
	//添加一行
    int Append(string* atri,int* value);
    //建立索引
    void Index(int type,string atri);
    //并发
    // void Commit();    
    //读取文件并存入内存中
    void Read_data_and_atri(vector<string> atri,vector<vector<long long>> data);

};


void Error(string stri);
