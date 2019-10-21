#include <iostream>
#include <string>
using namespace std;
class test{

private:
    int file_name;
    
public:
    test(int a){
        this->file_name=a;
        // cout<<this->file_name<<"\n";
    }
    ~test(){
        // cout<<s<<" end\n";
    }
    void f(int a){
        this->s=a;
    }


    int s;

};

// class test_p:public test
// {
//     test_p(int a){
        
//         this->f(a);
//     }
//     ~test_p(){
//         cout<<this->file_name<<"\n";
//     }

//     void p(int b){
//         this->s = b;
//         cout<<this->s<<"\n";
//     }

// };
void long_2_char(long long num,char* arr)
{

    arr = (char*)&num;
}

int main()
{
    // test *t = new test(5);
    // t->f(3);
    // delete t;
    // string stri="aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    // char a='a';
    // size_t c=stri.length();
    // size_t d=stri.size()+c;
    long long n = 0x1232434612324361;
    char* arr;
    // long_2_char(n,arr);
    // arr = (char*)&n;
    char* c = (char*)&n;
    
    cout<<c[0]<<"end ";
    for(int i = 7;i>=0;i--)
        cout<<arr[i];
    return 0;
}

