#include "table.h"
#include "create_test_data.h"

int main()
{
	// string t1="t1";
	// test t(10,t1);//生成名为t1的测试数据文件
	table Ta(t1);
	long long d=500;
	string s="WAN";
	Ta.Search(1,s,d);
	vector<string> vs;
	vector<long long> vl;
	vs.push_back(s);
	vl.push_back(d);
	Ta(vs,vl);
	return 0;
}
