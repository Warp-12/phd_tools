// zadanie 3: wykonac Exercise 5 ze str.128

#include "std_lib_facilities.hpp"

int main()
{
    char oper;
    double var1, var2;
    cout << "Please enter two variables: ";
    cin >> var1 >> var2;
    cout << "Please enter one of operations  + , - , * , / : ";
    cin >> oper;

    switch(oper)
    {
        case '+':{ cout << "The sum of "      << var1 << " and " << var2 << " is " << var1+var2 << "\n"; break;}

        case '-':{ cout << "The subtract of " << var1 << " and " << var2 << " is " << var1-var2 << "\n"; break;}

        case '*':{ cout << "The multiply of " << var1 << " and " << var2 << " is " << var1*var2 << "\n"; break;}

        case '/':{ cout << "The divide of "   << var1 << " and " << var2 << " is " << var1/var2 << "\n"; break;}

    }


}

