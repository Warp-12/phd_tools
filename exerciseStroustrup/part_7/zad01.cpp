// Zrobic pierwszy drill ze str 663: "Array drill".

#include "std_lib_facilities.hpp"

int ga[] = {1,2,4,16,32,64,128,256,512};

void f(int A[], int sz)
{

int la[10];
memcpy(la, ga, 10*sizeof(int));
    
    for(int i=0; i<10; i++)
    {
        cout << la[i] << " " << '\n';
    }

int *p = new int[sz];

memcpy(p,A,sz*sizeof(int));

    for(int i=0; i<sz; i++)
    {
        cout << p[i] << " " << '\n';    
    }

    delete [] p;

}

unsigned long factorial(unsigned long n)
{
    if(n>0) return n*factorial(n-1);
    else return 1;
}

int main()
{
    f(ga,10);
    
    int aa[10];

    for(int i=1; i<=10; i++)
    {
        aa[i-1] = factorial(i);
    }
    
    f(aa,10);

    return 0;
}

