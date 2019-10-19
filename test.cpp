#include <iostream>
#include <string>
using namespace std;
class test{

private:
    int file_name;
    
public:
    test(int a){
        this->file_name=a;
        cout<<this->file_name<<"\n";
    }
    ~test(){
        cout<<s<<" end\n";
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

int main()
{
    test *t = new test(5);
    t->f(3);
    delete t;
    string stri="i am c";
    cout<<stri;
    return 0;
}

