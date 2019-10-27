#include "BTree.h"

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
//清除整个树，释放内存
// template<typename Type> BTree<Type>::~BTree(){
//     m_proot->Destroy(m_proot);
// }
/*******************************************
/func:根据值查找对应节点

/param:要查找的值item

/return；查找到的节点或最近的节点对应的三元组
********************************************/
template<typename Type> Triple<Type> BTree<Type>::Search(const Type item){
    Triple<Type> result;
    BTreeNode<Type> *pmove = m_proot, *parent = NULL;
    int i = 0;
    while (pmove){
        i = -1;
        //把指针移动到指定的位置
        while (item > pmove->m_pkey[++i]); 
        //找到了该节点，返回结果
        if (pmove->m_pkey[i] == item){
            result.m_pfind = pmove;
            result.m_nfind = i;
            result.m_ntag = 1;
            return result;
        }
        //没有找到则继续查找其孩子节点，递归的寻找
        parent = pmove;
        pmove = pmove->m_ptr[i];
    }
    //没有找到，设置标志位然后返回
    result.m_pfind = parent;
    result.m_nfind = i;
    result.m_ntag = 0;
    return result;
}
/*******************************************
/func:计算目前位置下的所有节点数量

/return；节点总数
********************************************/
template<typename Type> int BTree<Type>::Size(){
        return this->Size(this->m_proot);
}
template<typename Type> int BTree<Type>::Size(BTreeNode<Type> *root){
    if (NULL == root){
        return 0;
    }
    int size=root->m_nsize;
    for (int i=0; i<=root->m_nsize; i++){
        if (root->m_ptr[i]){
            size += this->Size(root->m_ptr[i]);
        }
    }
    return size;
}
/*******************************************
/func:插入一个节点

/param：节点的值

/return；是否插入成功的标志
********************************************/
template<typename Type> int BTree<Type>::Insert(const Type item){
    //如果树为空，则插入初始节点
    if (NULL == m_proot){
        m_proot = new BTreeNode<Type>(m_nMaxSize);
        m_proot->m_nsize = 1;
        //左右节点的关键字相同
        m_proot->m_pkey[1] = m_proot->m_pkey[0];
        m_proot->m_pkey[0] = item;
        //叶节点为空
        m_proot->m_ptr[0] = m_proot->m_ptr[1] =NULL;
        return 1;
    }
    //找到要插入节点的位置
    Triple<Type> find = this->Search(item);
    //判断该节点是否已经存在
    //存在则抛出异常
    if (find.m_ntag){
        cout << "The item is exist!" << endl;
        return 0;
    }
    BTreeNode<Type> *pinsert = find.m_pfind, *newnode;
    BTreeNode<Type> *pright = NULL, *pparent;
    Type key = item;
    int n = find.m_nfind;
    //若不存在该节点，且该节点中还有空位置，则插入关键字
    while (1){
        if (pinsert->m_nsize < pinsert->m_nMaxSize-1){
            InsertKey(pinsert, n, key, pright);
            return 1;
        }
        
        //获取中间值
        int m = (pinsert->m_nsize + 1) / 2;
        //插入值后，进行拆分
        InsertKey(pinsert, n, key, pright);
        //拆分需要新增一个节点
        newnode = new BTreeNode<Type>(this->m_nMaxSize);
 
        //拆分
        for (int i=m+1; i<=pinsert->m_nsize; i++){      
            newnode->m_pkey[i-m-1] = pinsert->m_pkey[i];
            newnode->m_ptr[i-m-1] = pinsert->m_ptr[i];
            pinsert->m_pkey[i] = pinsert->m_Infinity;
            pinsert->m_ptr[i] = NULL;
        }
        newnode->m_nsize = pinsert->m_nsize - m - 1;
        pinsert->m_nsize = m;
 
        for (int i=0; i<=newnode->m_nsize; i++){
            if (newnode->m_ptr[i]){
                newnode->m_ptr[i]->m_pparent = newnode;
                for (int j=0; j<=newnode->m_ptr[i]->m_nsize; j++){
                    if (newnode->m_ptr[i]->m_ptr[j]){
                        newnode->m_ptr[i]->m_ptr[j]->m_pparent = newnode->m_ptr[i];
                    }
                }
            }
        }
        for (int i=0; i<=pinsert->m_nsize; i++){
            if (pinsert->m_ptr[i]){
                pinsert->m_ptr[i]->m_pparent = pinsert;
                for (int j=0; j<=pinsert->m_nsize; j++){
                    if (pinsert->m_ptr[i]->m_ptr[j]){
                        pinsert->m_ptr[i]->m_ptr[j]->m_pparent = pinsert->m_ptr[i];
                    }
                }
            }
        }
        
        key = pinsert->m_pkey[m];
        pright = newnode;
        if (pinsert->m_pparent){
            pparent = pinsert->m_pparent;
            n = -1;
            pparent->m_pkey[pparent->m_nsize] = pparent->m_Infinity;
            while (key > pparent->m_pkey[++n]);
            newnode->m_pparent = pinsert->m_pparent;
            pinsert = pparent;
        }
        else {
            m_proot = new BTreeNode<Type>(this->m_nMaxSize);
            m_proot->m_nsize = 1;
            m_proot->m_pkey[1] = m_proot->m_pkey[0];
            m_proot->m_pkey[0] = key;
            m_proot->m_ptr[0] = pinsert;
            m_proot->m_ptr[1] = pright;
            newnode->m_pparent = pinsert->m_pparent = m_proot;
            return 1;
        }
    }
}
/*******************************************
/func:插入一个关键字

/param：待插入节点

/param：插入位置

/param：关键字

/param：右节点（有空位置则为NULL，没有空位置则进行调整）
********************************************/
template<typename Type> void BTree<Type>::InsertKey(BTreeNode<Type> *pinsert, int n, const Type item, BTreeNode<Type> *pright){
    pinsert->m_nsize++;
    //比目标位置大的均往后移位
    for (int i=pinsert->m_nsize; i>n; i--){
        pinsert->m_pkey[i] = pinsert->m_pkey[i-1];
        pinsert->m_ptr[i+1] = pinsert->m_ptr[i];
    }
    //插入
    pinsert->m_pkey[n] = item;
    pinsert->m_ptr[n+1] = pright;
    //如果没有空位置，则进行调整
    if (pinsert->m_ptr[n+1]){
        pinsert->m_ptr[n+1]->m_pparent = pinsert;
        for (int i=0; i<=pinsert->m_ptr[n+1]->m_nsize; i++){
            if (pinsert->m_ptr[n+1]->m_ptr[i]){
                pinsert->m_ptr[n+1]->m_ptr[i]->m_pparent = pinsert->m_ptr[n+1];
            }
        }
    }

}
/*******************************************
/func:提升为头节点

/param：待改变节点

/param：位置
********************************************/
// template<typename Type> void BTree<Type>::PreMove(BTreeNode<Type> *root, int n){
//     root->m_pkey[root->m_nsize] = root->m_Infinity;
//     for (int i=n; i<root->m_nsize; i++){
//         root->m_pkey[i] = root->m_pkey[i+1];
//         root->m_ptr[i+1] = root->m_ptr[i+2];
//     }
    
//     root->m_nsize--;
// }
// /*******************************************
// /func:合并子树

// /param：左孩子

// /param：父节点

// /param：右孩子

// /param：位置
// ********************************************/
// template<typename Type> void BTree<Type>::Merge(BTreeNode<Type> *pleft, BTreeNode<Type> *pparent, BTreeNode<Type> *pright, int n){
//     pleft->m_pkey[pleft->m_nsize] = pparent->m_pkey[n];
//     BTreeNode<Type> *ptemp;
    
//     for (int i=0; i<=pright->m_nsize; i++){
//         pleft->m_pkey[pleft->m_nsize+i+1] = pright->m_pkey[i];
//         pleft->m_ptr[pleft->m_nsize+i+1] = pright->m_ptr[i];
//         ptemp = pleft->m_ptr[pleft->m_nsize+i+1];
//         if (ptemp){
//             ptemp->m_pparent = pleft;
//             for (int j=0; j<=ptemp->m_nsize; j++){
//                 if (ptemp->m_ptr[j]){
//                     ptemp->m_ptr[j]->m_pparent = ptemp;
//                 }
//             }
//         }
//     }
    
//     pleft->m_nsize = pleft->m_nsize + pright->m_nsize + 1;
//     delete pright;//删除孩子节点，释放内存
//     PreMove(pparent, n);//递归调整
// }
// /*******************************************
// /func:左调整（左边不平衡）

// /param：右孩子

// /param：父节点

// /param：右孩子

// /param：位置
// ********************************************/
// template<typename Type> void BTree<Type>::LeftAdjust(BTreeNode<Type> *pright, BTreeNode<Type> *pparent, int min, int n){
//     BTreeNode<Type> *pleft = pparent->m_ptr[n-1], *ptemp;
//     if (pleft->m_nsize > min-1){
//         for (int i=pright->m_nsize+1; i>0; i--){
//             pright->m_pkey[i] = pright->m_pkey[i-1];
//             pright->m_ptr[i] = pright->m_ptr[i-1];
//         }
//         pright->m_pkey[0] = pparent->m_pkey[n-1];
        
//         pright->m_ptr[0] = pleft->m_ptr[pleft->m_nsize];
//         ptemp = pright->m_ptr[0];
//         if (ptemp){
//             ptemp->m_pparent = pright;
//             for (int i=0; i<ptemp->m_nsize; i++){
//                 if (ptemp->m_ptr[i]){
//                     ptemp->m_ptr[i]->m_pparent = ptemp;
//                 }
//             }
//         }
//         pparent->m_pkey[n-1] = pleft->m_pkey[pleft->m_nsize-1];
//         pleft->m_pkey[pleft->m_nsize] = pleft->m_Infinity;
//         pleft->m_nsize--;
//         pright->m_nsize++;
//     }
//     else {
//         Merge(pleft, pparent, pright, n-1);
//     }
// }
 
// template<typename Type> void BTree<Type>::RightAdjust(BTreeNode<Type> *pleft, BTreeNode<Type> *pparent, int min, int n){
//     BTreeNode<Type> *pright = pparent->m_ptr[1], *ptemp;
//     if (pright && pright->m_nsize > min-1){
//         pleft->m_pkey[pleft->m_nsize] = pparent->m_pkey[0];
//         pparent->m_pkey[0] = pright->m_pkey[0];
//         pleft->m_ptr[pleft->m_nsize+1] = pright->m_ptr[0];
//         ptemp = pleft->m_ptr[pleft->m_nsize+1];
//         if (ptemp){         //change the tree's parent which is moved
//             ptemp->m_pparent = pleft;
//             for (int i=0; i<ptemp->m_nsize; i++){
//                 if (ptemp->m_ptr[i]){
//                     ptemp->m_ptr[i]->m_pparent = ptemp;
//                 }
//             }
//         }
//         pright->m_ptr[0] = pright->m_ptr[1];
//         pleft->m_nsize++;
//         PreMove(pright,0);
//     }
//     else {
//         Merge(pleft, pparent, pright, 0);
//     }
// }
 
// template<typename Type> BTreeNode<Type>* BTree<Type>::GetParent(const Type item){
//     Triple<Type> result = this->Search(item);
//     return result.m_pfind->m_pparent;
// }