//table.h
#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#endif

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include "ulity.h"

//读写互斥量,最多支持31个读者
extern char r_count;
// //写互斥量，只支持一个写者
// bool w_count=false;

class table{

private:
    std::vector<string> _index_file_name;
    string file_name;


public:
    table(string name){//初始化时读取文件
        this->file_name = name;
    }

    ~table(){//程序结束时关闭文件
        in_file.close();
    }

	ifstream in_file;//用于读取
    ofstream out_file;//用于写入新增的数据
    vector<string> _atri_in_file;//从文件中获取属性名
    vector<vector<long long>> _data_in_file;//从文件中获取数据
    vector<string> atri;//需要查找的属性
    vector<vector<long long>> data;//查找到的值

    /* 两两椒峰，铜台玉竹，赤珠更醉人 */

	void Search(string type,string atri,long long value,vector<vector<long long>> v);
    void Search_by_Index(string type,string atri,long long value,vector<vector<long long>> v);
    int Exist_index(string atri);
    int Append(string* atri,int* value);
    void Index(int type,string atri);
    void Read_data_and_atri(vector<string> atri,vector<vector<long long>> data);
    string get_file_name();
};


