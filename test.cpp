#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "BTree.h"
using namespace std;

struct P
{
    int i;
    char s;
};


int main()
{
    // string t1="t1";
    // P t1,t2;
    // t1.i=1;
    // t1.s='a';
    // t2=t1;
    // printf("%c\n", t2.s);
    // test t(10,t1);
    BTree<int> btr(4);
    Pair<int> p;
    int s=130;
    int t=100;
    Triple<int> ST;
    // vector<int> res;
    int a[] = {1,3,5,7,4,2,8,0,6,9,29,13,25,11,32,55,34,22,76,45
        ,14,26,33,88,87,92,44,54,23,12,21,99,19,27,57,18,72,124,158,234
    ,187,218,382,122,111,222,333,872,123};
    for (int i=0;i<49;i++){
        p.item = a[i];
        p.num = i+1;
        btr.Insert(p);
        // printf("%d\n",p.item); 
        // printf("%d\n", i); 
    }
    // ST = btr.Search(s);
    // btr.Print(btr.m_proot);
    btr.Search_(btr.m_proot,0,t,s);

    for(int i=0;i<result.size();i++)
    {
        printf("%d\n", result.at(i));
    }
    // Triple<int> t = btr.Search(100);
    // if(t.m_item.item == 100)   
    //     printf("%d\n", t.m_pfind->GetKey(t.m_nfind).num);
    // else
    //     printf("no this member!\n");
    // printf("%d\n", t.m_nfind);
    // table ta(t1);
    // delete t;
    return 0;

}

