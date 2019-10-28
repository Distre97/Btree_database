#define BIGERTHEN 1
#define SMALLTHEN -1
#define BETWEEN 0
#define RETURN_SEARCH_COUNT 10
#include <iostream>
#include <vector>
// extern "C"{
// #include <cstdlib>
// }

using namespace std;
vector<int > result;
//声明模板类BTree
template<typename Type> class BTree;

template<typename Type> struct Pair
{
    Type item;
    int num;
};
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
        m_pkey = new Pair<Type>[size+1];
        m_ptr = new BTreeNode<Type> *[size+1];
        for (int i=0; i<=size; i++){
            m_ptr[i] = NULL;
            m_pkey[i].item = this->m_Infinity;
            m_pkey[i].num = -1;
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
    Pair<Type> GetKey(int i){
        if (this){
            return this->m_pkey[i];
        }
        Pair<Type> err;
        err.item = this->m_Infinity;
        err.num = -1;
        return err;
    }

    void Destroy(BTreeNode<Type> *root);

 /* 醉后不知天在水，满船清梦压星河 */

private:
    int m_nsize;//当前节点中关键字数
    int m_nMaxSize;//每一个叶节点中所存的关键字数
    Pair<Type> *m_pkey;//关键字表
    BTreeNode<Type> *m_pparent;//父节点
    BTreeNode<Type> **m_ptr;//孩子节点链表
    static const Type m_Infinity = 100000;//无穷大值，表示该节点关键字为空
};

//查找到后保存结果的三元组
template<typename Type> struct Triple{
    BTreeNode<Type> *m_pfind;//该节点
    int m_nfind;//是否存在
    bool m_ntag;//是否已经存在，或是否保存过
    Pair<Type> m_item;
};

template<typename Type> class BTree{
public:
    BTreeNode<Type> *m_proot;
    BTree(int size): m_nMaxSize(size), m_proot(NULL){}
    ~BTree();
    Triple<Type> Search(const Type item);
    int Size();
    int Size(BTreeNode<Type> *root);
    // bool Remove(const Type item);
    // BTreeNode<Type> *GetParent(const Type item);    
    int Insert(const Pair<Type> item);
    void Print(BTreeNode<Type> *start,int n=0);
    void Search_(BTreeNode<Type> *start, int type,Type item,Type item2=0,int n=0); 
private:
 
    const int m_nMaxSize;

    void InsertKey(BTreeNode<Type> *pinsert, int n, const Pair<Type> item, BTreeNode<Type> *pright); 
    // void PreMove(BTreeNode<Type> *root, int n); 
    // void Merge(BTreeNode<Type> *pleft, BTreeNode<Type> *pparent, BTreeNode<Type> *pright, int n); 
    // void LeftAdjust(BTreeNode<Type> *pright, BTreeNode<Type> *pparent, int min, int n); 
    // void RightAdjust(BTreeNode<Type> *pleft, BTreeNode<Type> *pparent, int min, int n); 

};
/*******************************************
*                                           *
*                   定                      *
*                                           *
*                                           *
*                                           *
*                   义                      *
*                                           *
*                                           *
*                                           *
*                   区                      *
*                                           *
*                                           *
*                                           *
********************************************/

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
template<typename Type> BTree<Type>::~BTree(){
    m_proot->Destroy(m_proot);
}
/*******************************************
/func:根据值查找对应节点

/param:要查找的值item

/return；查找到的节点或最近的节点对应的三元组
********************************************/
template<typename Type> Triple<Type> BTree<Type>::Search(const Type item){
    Triple<Type> result;
    BTreeNode<Type> *pmove = m_proot, *parent = NULL;
    int i = 0;
    while (pmove!=NULL){
        i = -1;
        //找到指定的位置
        // printf("%d\n", item);
        while (item > pmove->m_pkey[++i].item){
            // printf("%d %d\n", pmove->m_pkey[i].item,i); 
        }

        //找到了该节点且只有一个，返回结果
        if (pmove->m_pkey[i].item == item){
            result.m_pfind = pmove;
            result.m_nfind = i;
            result.m_ntag = 1;
            result.m_item.item = item;
            result.m_item.num = pmove->m_pkey[i].num;
            printf("the item is here!\n");
            return result;
        }
        //没有找到则继续查找其孩子节点，递归的寻找
        parent = pmove;
        pmove = pmove->m_ptr[i];
    }
    //没有找到，返回前一个最近的叶子节点
    result.m_pfind = parent;
    result.m_nfind = i;
    result.m_ntag = 0;
    // result.m_item.item = pmove->m_pkey[--i].item;
    // result.m_item.num = pmove->m_pkey[--i].num;
    // printf("the item is not here,but we return the closest item!\n");
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
template<typename Type> int BTree<Type>::Insert(const Pair<Type> item){
    //如果树为空，则插入初始节点
    if (NULL == m_proot){
        m_proot = new BTreeNode<Type>(m_nMaxSize);
        m_proot->m_nsize = 1;
        //左右节点的关键字相同
        m_proot->m_pkey[1] = m_proot->m_pkey[0];
        m_proot->m_pkey[0] = item;
        m_proot->m_pkey[0].num = 1;
        //叶节点为空
        m_proot->m_ptr[0] = m_proot->m_ptr[1] =NULL;
        return 1;
    }
    //找到要插入节点的位置
    Triple<Type> find = this->Search(item.item);
    //判断该节点是否已经存在
    //存在则抛出异常
    if (find.m_ntag){
        cout << "The item is exist!" << endl;
        return 0;
    }
    BTreeNode<Type> *pinsert = find.m_pfind, *newnode;
    BTreeNode<Type> *pright = NULL, *pparent;
    Pair<Type> key = item;
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
        for (int i=m+1; i<=pinsert->m_nsize; i++){//截取一半往后移   
            newnode->m_pkey[i-m-1]= pinsert->m_pkey[i];
            newnode->m_ptr[i-m-1] = pinsert->m_ptr[i];
            pinsert->m_pkey[i].item = pinsert->m_Infinity;
            pinsert->m_pkey[i].num = -1;
            pinsert->m_ptr[i] = NULL;
        }
        newnode->m_nsize = pinsert->m_nsize - m - 1;
        pinsert->m_nsize = m;
 
        for (int i=0; i<=newnode->m_nsize; i++){//挂在右边的节点下
            if (newnode->m_ptr[i]){
                newnode->m_ptr[i]->m_pparent = newnode;
                for (int j=0; j<=newnode->m_ptr[i]->m_nsize; j++){
                    if (newnode->m_ptr[i]->m_ptr[j]){
                        newnode->m_ptr[i]->m_ptr[j]->m_pparent = newnode->m_ptr[i];
                    }
                }
            }
        }
        for (int i=0; i<=pinsert->m_nsize; i++){//处理两边的平衡
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
        //更新父节点（根节点）
        if (pinsert->m_pparent){
            pparent = pinsert->m_pparent;
            n = -1;
            pparent->m_pkey[pparent->m_nsize].item = pparent->m_Infinity;
            pparent->m_pkey[pparent->m_nsize].num = -1;
            while (key.item > pparent->m_pkey[++n].item);
            newnode->m_pparent = pinsert->m_pparent;
            pinsert = pparent;
        }
        else {//没有就新建一个，把叶子提升为父节点
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
template<typename Type> void BTree<Type>::InsertKey(BTreeNode<Type> *pinsert, int n, const Pair<Type> item, BTreeNode<Type> *pright){
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

// /param：引起不平衡的点

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
// /*******************************************
// /func:右调整（左边不平衡）

// /param：左孩子

// /param：父节点

// /param：引起不平衡的点

// /param：位置
// ********************************************/
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
template<typename Type> void BTree<Type>::Print(BTreeNode<Type> *start,int n)
{
    if (NULL == start){
        return;
    }
    if (start->m_ptr[0]){
        Print(start->m_ptr[0], n+1);    
    }
    else {
        for (int j=0; j<n; j++){
            cout << "     ";
        }
        cout << "NULL" << endl;
    }
 
    for (int i=0; i<start->m_nsize; i++){
        for (int j=0; j<n; j++){
            cout << "     ";
        }
        cout << start->m_pkey[i].item << "," << start->m_pkey[i].num << "--->" <<endl;
        if (start->m_ptr[i+1]){
            Print(start->m_ptr[i+1], n+1);
        }
        else {
            for (int j=0; j<n; j++){
                cout << "     ";
            }
            cout << "NULL" << endl;
        }
    }
}

template<typename Type> void BTree<Type>::Search_(BTreeNode<Type> *start, int type,Type item,Type item2,int n){
    // BTreeNode<Type> *start = m_proot,*par=NULL;

    if(NULL == start){
        cout << "error index\n";
        return;
    }
    // bool flag=true;
    switch(type)
    {
        case SMALLTHEN:
            if(start->m_ptr[0]){
                Search_(start->m_ptr[0],type,item,item2,n+1);
            }
            for(int i=0; i<start->m_nsize; i++){
                if(start->m_pkey[i].item < item){
                    result.push_back(start->m_pkey[i].num);
                }
                else
                    break;
                if(start->m_ptr[i+1]){
                    Search_(start->m_ptr[i+1],type,item,item2,n+1);
                }
            }
            break;
        case BIGERTHEN:
            if(start->m_ptr[1]){

                Search_(start->m_ptr[1],type,item,item2,n+1);
            }
            for(int i=start->m_nsize-1; i>=0; i--){
                // if(start->m_pkey[i].item > item){
                    // printf("sss\n");
                    printf("%d  ", start->m_pkey[i].item);
                    // result.push_back(start->m_pkey[i].num);
                // }
                // else
                //     break;
                if(start->m_ptr[i-1]){
                    Search_(start->m_ptr[i-1],type,item,item2,n+1);
                }
            }
            break;
        case BETWEEN:
            // if(item2 == 0)
            // {
            //     cout<<"error! only one item\n";
            //     break;
            // }
            // j=0;
            // while(start!=NULL && start->m_pkey[++i].item<=item);
            // while(start!=NULL && start->m_pkey[i].item>item && start->m_pkey[i].item<item2){
            //     result[j] = start->m_pkey[i].num;
            //     j++;
            //     if(j>=RETURN_SEARCH_COUNT){break;}
            //     i++;
            // }
            break;
        default:
            cout<<"error search type\n";
            break;
    }
    // while (pmove!=NULL){
    //     i = -1;
    //     //找到指定的位置
    //     // printf("%d\n", item);
    //     while (item > pmove->m_pkey[++i].item){
    //         // printf("%d %d\n", pmove->m_pkey[i].item,i); 
    //     }

    //     //找到了该节点且只有一个，返回结果
    //     if (pmove->m_pkey[i].item == item && pmove->m_pkey[i+1].item > item){
    //         result.m_pfind = pmove;
    //         result.m_nfind = i;
    //         result.m_ntag = 1;
    //         result.m_item.item = item;
    //         result.m_item.num = pmove->m_pkey[i].num;
    //         printf("the item is here!\n");
    //         return result;
    //     }
    //     //没有找到则继续查找其孩子节点，递归的寻找
    //     parent = pmove;
    //     pmove = pmove->m_ptr[i];
    // }
}