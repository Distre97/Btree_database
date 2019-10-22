#include <iostream>
#include <string>
#include <fstream>
using namespace std;

ofstream f;
void wri_(string s,int num)
{
    f.seekp(0,ios::end);

    for(int i=0;i<10;i++)
    {
        f.write((char*)&s,num);
    }

}
void wri_2(string s,int num)
{
    f.seekp(0,ios::end);

    for(int i=0;i<10;i++)
    {
        f.write((char*)&s,num);
    }
}
int main()
{
    f.open("t.txt",ios::app);
    string s="bc";
    string s2="a";
    f.seekp(0,ios::end);
    // for(int i=0;i<10;i++)
    // {
    //     f.write((char*)&s,2);
    // }
    wri_2(s,2);
    wri_(s2,1);
    return 0;
}

