#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include "BTreeNode.h"
 
template<typename Type> class BTree{
public:
    BTree(int size): m_nMaxSize(size), m_proot(NULL){}
    ~BTree();
    Triple<Type> Search(const Type item);
    int Size();
    int Size(BTreeNode<Type> *root);
    bool Insert(const Type item);
    bool Remove(const Type item);
    BTreeNode<Type> *GetParent(const Type item);
 
private:
    BTreeNode<Type> *m_proot;
    const int m_nMaxSize;

    void InsertKey(BTreeNode<Type> *pinsert, int n, const Type item, BTreeNode<Type> *pright); 
    void PreMove(BTreeNode<Type> *root, int n); 
    void Merge(BTreeNode<Type> *pleft, BTreeNode<Type> *pparent, BTreeNode<Type> *pright, int n); 
    void LeftAdjust(BTreeNode<Type> *pright, BTreeNode<Type> *pparent, int min, int n); 
    void RightAdjust(BTreeNode<Type> *pleft, BTreeNode<Type> *pparent, int min, int n); 

};
 
#endif
