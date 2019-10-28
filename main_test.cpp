#include "table.h"
#include "create_test_data.h"
#include "BTree.h"

int main()
{
	string t1="t1";
	test t(10,t1);
	BTree<int> btr(4);

	return 0;
}
