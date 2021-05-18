// Zrobic zad 1 ze str.923

#include "std_lib_facilities.hpp"
#include "Matrix.h"
#include "MatrixIO.h"

using namespace Numeric_lib;
//====================================
namespace Numeric_lib
{

	void triple1(int& numb){numb *= 3;}

	int triple2(int numb){return 3*numb;}

	int triple3(int& numb){numb *=3; return numb;}

}

int main()
{
	 int arr[] = { 1, 2, 3, 4, 5 };
     Matrix<int> m1(arr);
     cout << "m1:\t\t\t\t" << m1 << '\n';

	 m1.apply(triple1);
	 cout << "m1 with apply(triple1):\t\t" << m1 << '\n';
 
     Matrix<int> m2 = apply(triple2,m1);
     cout << "m1 with apply(triple2,m1):\t" << m1 << '\n';
	 cout << "m2:\t\t\t\t" << m2 << '\n';

	 m2.apply(triple3);
     cout << "m2 with apply(triple3):\t\t" << m2 << '\n';
     Matrix<int> m3 = apply(triple3,m2);
     cout << "m2 with apply(triple3,m2):\t" << m2 << '\n';
	 cout << "m3:\t\t\t\t" << m3 << '\n';


}


