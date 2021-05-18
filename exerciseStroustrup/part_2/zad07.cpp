// zadanie 7: wykonac Exercise 7 ze str.170

#include "std_lib_facilities.hpp"

int main()
{
    double a,b,c,d,x1,x2;

    input:cout << "\nPlease enter the value of quadratic equation a,b and c: \n";
    cin >> a >> b >> c;

    if(a==0) goto finish;
    d=pow(b,2) - 4*a*c;

    if(d>=0)
    {   x1=(-b+sqrt(b*b-4*a*c))/(2*a);
        x2=(-b-sqrt(b*b-4*a*c))/(2*a);
        cout << "This equation have roots: " << x1 << " " << x2 << "\n"; goto finish;
    }
    else
    {
        cout << "The value of a,b,c enterred incorect\nEquation doesnt have real roots!!!\n";
        cout << "How do you know that your results are plausible?\nCan you check that they are correct?";
        goto input;
    }

    finish:return 0;

}

