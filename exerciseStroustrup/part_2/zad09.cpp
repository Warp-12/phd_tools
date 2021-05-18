// zadanie 9: wykonac Exercise 11 ze str.171

#include "std_lib_facilities.hpp"
#include<climits>

int main()
{
    int numb1  = 1;
    int numb2  = 1;
    int numb_n = 0;
    int maxx   = INT_MAX;

    numb_n = numb1 + numb2;

    while(numb_n<maxx)
    {
        cout << numb_n <<".\n";

        numb1 = numb2; numb2 = numb_n; numb_n = numb1 + numb2;
        if(numb_n<0){break; }
    }
    cout << " Maximum number that could be store in int is :  " << numb2 <<".\n" ;
    return 0;


}

