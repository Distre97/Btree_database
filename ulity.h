#ifndef ULITY_H_INCLUDE
#define ULITY_H_INCLUDE
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

/*******************************************

实现互斥访问
RSoinLock实现读者访问，每次申请4个r_count;
WSpinLock实现写者访问，只有r_count为0时才可写入

********************************************/

/* 碧波沉醉天江水，船笛幽扬清风月  */

template<typename T>
class RSpinLock
{   
    public:
        RSpinLock( T * addr ) : m_addr(addr)
        {   
            while( true  )
            {   
                T old = * m_addr;
                old &= (T)~1;
                //若无写者则添加读者
                if( __sync_bool_compare_and_swap( m_addr, old, old | 2 ) ) 
                {   
                	//读者到达上限则创建读者失败
                	if(__sync_bool_compare_and_swap(m_addr, (T)128, 130) )
                	{
                		break;
                	}
                	//添加读者
                    __sync_fetch_and_add( m_addr, 4 ); 
                    break;                            
                }   
            }   

        }   
        ~RSpinLock( )
        {   
        	//读者减一，若后续无读者则归零
            __sync_fetch_and_sub( m_addr, 4 );  
            __sync_bool_compare_and_swap( m_addr, 2, 0 ); 
        }   
    private: T * m_addr;
};  

template<typename T>
class WSpinLock
{   
    public:
        WSpinLock( T * addr ) : m_addr(addr)
        {   
        	//循环读取互斥量是否为0
            while( !__sync_bool_compare_and_swap( m_addr, 0, 1 ) );
        }   
        ~WSpinLock( )
        {   
        	//写入完成后把互斥量归零
            *m_addr = 0;
        }   
    private: T * m_addr;
};

// {
//     WSpinLock<char> locker( &r_count );
//     /* 上锁后的操作 */
// }// 跳出代码块后，自动调用 locker 析构函数，释放掉锁
// RSpinLock<char> l1(&x);
// {
//     /* 上锁后的操作 */
// }
/*******************************************
/func:打印错误信息(内联函数)

/param：错误提示字符串
********************************************/
inline Error(string stri)
{
    cout<<"error in"<<stri<<"\n";
}

#endif