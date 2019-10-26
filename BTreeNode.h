#ifndef BTREENODE_H_INCLUDED
#define BTREENODE_H_INCLUDED
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

 /* 醉后不知天在水，满船秋梦压星河 */

private:
    int m_nsize;
    int m_nMaxSize;
    Type *m_pkey;
    BTreeNode<Type> *m_pparent;
    BTreeNode<Type> **m_ptr;
    static const Type m_Infinity = 1000;//每个节点可以存储的关键字数
};

//查找到后保存结果的三元组
template<typename Type> struct Triple{
    BTreeNode<Type> *m_pfind;
    int m_nfind;
    bool m_ntag;
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
