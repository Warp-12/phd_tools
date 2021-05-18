// Zrobic zad 2 ze str. 923

#include "std_lib_facilities.hpp"
#include "Matrix.h"
#include "MatrixIO.h"

using namespace Numeric_lib;
//================================================================================
namespace Numeric_lib
{

    struct Triple1{ void operator()(int& numb){numb *= 3;}};

    struct Triple2{int operator()(int numb){return 3*numb;}};

    struct Triple3{int operator()(int& numb){numb *=3; return numb;}};

}
//==============================================================================
int main()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    Matrix<int> m1(arr);
    cout << "m1:\t\t\t\t\t" << m1 << '\n';

    m1.apply(Triple1());
    cout << "m1 with apply(Triple1()):\t\t" << m1 << '\n';

    Matrix<int> m2 = apply(Triple2(),m1);
    cout << "m1 with apply(Triple2(),m1):\t\t" << m1 << '\n';
    cout << "m2:\t\t\t\t\t" << m2 << '\n';

    m2.apply(Triple3());
    cout << "m2 with apply(Triple3()):\t\t" << m2 << '\n';
    Matrix<int> m3 = apply(Triple3(),m2);
    cout << "m2 with apply(Triple(),m2):\t\t" << m2 << '\n';
cout << "m3:\t\t\t\t\t" << m3 << '\n';
}

