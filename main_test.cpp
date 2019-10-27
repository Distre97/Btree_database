#include "table.h"
#include "create_test_data.h"
#include "BTree.h"

int main()
{
	string t1="t1";
	test t(10,t1);
	BTree<int> btr(4);
	int a[] = {1,3,5,7,4,2,8,0,6,9,29,13,25,11,32,55,34,22,76,45
        ,14,26,33,88,87,92,44,54,23,12,21,99,19,27,57,18,72,124,158,234
    ,187,218,382,122,111,222,333,872,123};
    for (int i=0;i<49;i++){
    	btr.Insert(a[i]);
    }
	// table ta(t1);
	// delete t;
	return 0;
}
