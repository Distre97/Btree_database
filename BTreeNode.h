#ifndef BTREENODE_H_INCLUDED
#define BTREENODE_H_INCLUDED
#include <iostream>
#include <cstdlib>
using namespace std;


//声明模板类BTree
template<typename Type> class BTree;
 
template<typename Type> class BTreeNode{
public:
    friend BTree<Type>;//使其成为Node的友元类
    
    /*******************************************
    两种初始化定义

    /m_nsize：节点数

    /m_nMaxSize：树的最大节点数
    
    /m_pparent：父节点

    /m_ptr：孩子节点集合

    /m_pkey：叶子中的关键字
    ********************************************/
    BTreeNode(): m_nMaxSize(0), m_ptr(NULL), m_pparent(NULL){}
    BTreeNode(int size): m_nsize(0), m_nMaxSize(size), m_pparent(NULL){
        m_pkey = new Type[size+1];
        m_ptr = new BTreeNode<Type> *[size+1];
        for (int i=0; i<=size; i++){
            m_ptr[i] = NULL;
            m_pkey[i] = this->m_Infinity;
        }
    }
    ~BTreeNode(){
		if (m_nMaxSize){
			delete[] m_pkey;
			for (int i=0; i<=m_nMaxSize; i++){
				m_ptr[i] = NULL;
			}
		}
    }

    //判断树满
    bool IsFull(){
        return m_nsize == m_nMaxSize;
    }

    //获取关键字
    Type GetKey(int i){
        if (this){
            return this->m_pkey[i];
        }
        return -1;
    }

    void Destroy(BTreeNode<Type> *root);

 /* 醉后不知天在水，满船清梦压星河 */

private:
    int m_nsize;//当前节点中关键字数
    int m_nMaxSize;//每一个叶节点中所存的关键字数
    Type *m_pkey;//关键字链表
    BTreeNode<Type> *m_pparent;//父节点
    BTreeNode<Type> **m_ptr;//孩子节点链表
    static const Type m_Infinity = 100000;//无穷大值，表示该节点关键字为空
};

//查找到后保存结果的三元组
template<typename Type> struct Triple{
    BTreeNode<Type> *m_pfind;//该节点
    int m_nfind;//节点中对应关键字存在的位置
    bool m_ntag;//是否已经存在，或是否保存过
};
/*******************************************
/func:剪枝

/param：根节点
********************************************/
template<typename Type> void BTreeNode<Type>::Destroy(BTreeNode<Type> *root){
    if (NULL == root){
        return;
    }
    //迭代删除其子节点
    for (int i=0; i<root->m_nsize; i++){
        Destroy(root->m_ptr[i]);
    }
    delete root;
}
#endif
