// Zrobic drill ze str 922
//================================================================================

#include "std_lib_facilities.hpp"
#include "Matrix.h"
#include "MatrixIO.h"
#include <complex>
#include <numeric>
using Numeric_lib::Matrix;

//================================================================================
void sqrt_out()
		      {
		         int val;

		         cin >> val;

		         if (val < 0)
		         cout << "no square root\n";
                 else
                 cout << sqrt(val) << '\n';
	          }
//================================================================================
int main()
{
//drill_1
cout << "Size of:\n"
	                 << "char:    " << sizeof(char)    << '\n'
                     << "short:   " << sizeof(short)   << '\n'
	                 << "int:     " << sizeof(int)     << '\n'
                     << "long:    " << sizeof(long)    << '\n'
                     << "float:   " << sizeof(float)   << '\n'
                     << "double:  " << sizeof(double)  << '\n'
                     << "int*:    " << sizeof(int*)    << '\n'
			         << "double*: " << sizeof(double*) << "\n\n";
//drill_2
	 Matrix<int> a(10);
	 Matrix<int> b(100);
	 Matrix<double> c(10);
	 Matrix<int,2> d(10,10);
	 Matrix<int,3> e(10,10,10);

cout << "Size of:\n"
	              << "Matrix<int>(10):         " << sizeof(a) << '\n'
		          << "Matrix<int>(100):        " << sizeof(b) << '\n'
		          << "Matrix<double>(10):      " << sizeof(c) << '\n'
		          << "Matrix<int,2>(10,10):    " << sizeof(d) << '\n'
			      << "Matrix<int,3>(10,10,10): " << sizeof(e) << "\n\n";
//drill_3
cout << "Matrix elements:\n"
	              << "Matrix<int>(10):         " << a.size() << '\n'
			      << "Matrix<int>(100):        " << b.size() << '\n'
			      << "Matrix<double>(10):      " << c.size() << '\n'
			      << "Matrix<int,2>(10,10):    " << d.size() << '\n'
			      << "Matrix<int,3>(10,10,10): " << e.size() << "\n\n";

//drill_4

cout << "Enter ints for square-rooting:\n";
      
     for(int i = 0; i < 3; i++){sqrt_out();}

//drill_5
cout << "Enter 10 floats  into a Matrix:\n";
    const int entries = 10;

	   Matrix<double> md(entries);
		    for (int i = 0; i < entries; i++)
				        cin >> md[i];

			cout << md << '\n';
//drill_06
cout << "Enter the dimensions for the table: ";
    int m, n;
    cin >> m >> n;
    cout << '\n';

    Matrix<double,2> mult_table(m,n);

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            mult_table(i,j) = i == 0 || j == 0 ? i + j : i * j;

    for (int i = 0; i < mult_table.dim1(); ++i) {
        for (int j = 0; j < mult_table.dim2(); ++j)
            cout << setw(5) << mult_table(i,j) << '\n';
    }

//drill_7
    cout << "Enter 10 complex numbers:\n";
    Matrix<complex<double>> mcd (10);
    for (int i = 0; i < mcd.size(); ++i) {
        cin >> mcd[i];
    }

cout << "Total: " << accumulate(mcd.data(), mcd.data() + mcd.size(), complex<double>{}) << '\n';

//drill_8
    cout << "Enter 6 ints for a 2x3 Matrix:\n";
    Matrix<int,2> mm (2,3);
    for (int i = 0; i < mm.dim1(); ++i)
        for (int j = 0; j < mm.dim2(); ++j)
            cin >> mm[i][j];

    cout << mm << '\n';

}
//================================================================================
