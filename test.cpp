#include <iostream>
#include <string>
#include <fstream>


using namespace std;

class a{
private:
    string s;
public:
    a(string t)
    {
        this->s=t;
    }

    string f()
    {
        return this->s;
    }
};



int main()
{
    a t("aa");
    cout<<t.f();
    return 0;

}

