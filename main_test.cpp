#include "table.h"
#include "create_test_data.h"

int main()
{
	string t1="t1";
	test t(10,t1);
	// BTree<int> btr(4)
	table Ta(t1);
	long long d=500;
	string s="bite";
	Ta.Search(1,s,d);
	return 0;
}
