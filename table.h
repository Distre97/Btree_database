//table.h
#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#define TREE_SIZE 4
#define COLUM_SIZE 800
#define BIGERTHEN "bigt"
#define SMALLTHEN "smallt"
#define BETWEEN "betwn"

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include "ulity.h"
#include "BTree.h"
//读写互斥量,最多支持31个读者
extern char r_count;

class table{

private:
    std::vector<string> _index_file_name;
    string file_name;

public:
    table(string name){//初始化时读取文件
        this->file_name = name;
        Read_atri(_atri_in_file);
    }
    ~table(){//程序结束时关闭文件
        in_file.close();
    }

	ifstream in_file;//用于读取
    ofstream out_file;//用于写入新增的数据
    int atri_l=0;//属性名总长度
    vector<string> _atri_in_file;//从文件中获取属性名
    vector<vector<long long > > _data_in_file;//从文件中获取数据
    // vector<string> atri;//需要查找的属性
    vector<vector<long long > > data;//查找到的值

    /* 两两椒峰，铜台玉竹，赤珠更醉人 */

	void Search(string type,string atri,long long* value,vector<vector<long long>> v);
    void Search_by_Index(string type,string atri,long long value,vector<vector<long long>> v,BTree<long long > a);
    bool Exist_index(string atri);
    bool Append(string* atri,int* value);
    BTree<char> Index_atri(string atri);
    BTree<long long> Index(string atri);
    void Read_atri(vector<string> atri);
    string get_file_name();
    int _get_atri_l();
    int get_data_colum();
};
BTree<long long> Index_from_files(string file_name);
int get_file_length(string file_name);
int get_index_length(string name);

#endif