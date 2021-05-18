// Zrobic drugi drill ze str 663: "std library vector drill".

#include "std_lib_facilities.hpp"

vector<int> gv{1,2,4,8,16,32,64,128,256,512};
void f(vector<int> v)
{
    vector<int> lv{gv};

    for(int i=0; i<lv.size(); i++)
    {
        cout << lv[i] << " " << '\n';
    }

    vector<int> lv2{v};

    for(int i=0; i<lv2.size(); i++)
    {
        cout << lv2[i] << " " << '\n';
    }
}

unsigned long factorial(unsigned long n)
{
    if(n>0) return n*factorial(n-1);
    else return 1;
}

int main()
{
    f(gv);
    vector<int> vv;

    for(int i=0;i<=10; i++)
        vv.push_back(factorial(i));
    f(vv);

    return 0;

}

