// zadanie 12: wykonac Exercise 10 ze str.219

#include "std_lib_facilities.hpp"
//===================================================
int fact(int n)
{
    int factorial = 1;

    for(int i = 1; i <=n; ++i)
    {
        factorial *= i;
    }

    return factorial;
}
//===================================================
int perm( int a, int b)
{
    int permutation;
    permutation = (fact(a)) / (fact(a-b));
    return permutation;
}
//===================================================
int comb( int a, int b)
{
    int combination;
    combination = perm(a,b) / fact(b);
    return combination;
}
//===================================================
bool err( int a, int b)
{
    bool statment=false;
    if(a==0 || b==0){statment=true;       cout << "ERROR: Numbers couldn't be equal zero!!!\n";}
    else if(a<=b){statment=true;          cout << "ERROR: Second number couldn't be greater than first number!!!\n";}
    else if(a<0 || b<0){statment=true;    cout << "ERROR: Negative numbers are forbidden!!!\n";}
    return statment;
}
//===================================================

int main()
{
    int result_p, result_c,numb1, numb2;
    char c, print;
    bool log_error=false;
    cout << "Please enter two integer numbers: \nInput 'p' for calculation permutations, or 'c' for combinations\nInput 'y' for printing or 'n' for no\nInput in the order number 1, number 2, 'p' or 'c', 'y' or 'n', without comma\n";
//================================================================================================================================================
    while(cin >> numb1 >> numb2 >> c >> print)
    {

        log_error=err(numb1, numb2);
        if(log_error==true){ cout << "Exit program.\n"; return 1;}


        switch(c)
        {

            case 'p' :
            {
                result_p=perm(numb1, numb2);

                switch(print)
                {
                    case 'y' : cout << "Permutation of " << numb1 << " and " << numb2 << " is equal " << result_p << ".\n"; break;
                    case 'n' : break;
                    default  : log_error=true; break;
                }
                break;
            }

            case 'c' :
            {
                result_c=comb(numb1, numb2);
                switch (print)
                {
                    case 'y' : cout << "Combination of " << numb1 << " and " << numb2 << " is equal " << result_c << ".\n"; break;
                    case 'n' : break;
                    default  : log_error=true; break;
                }
                break;

            }
            default : log_error=true; break;
        }

    }
    return 0;
}
//===================================================
