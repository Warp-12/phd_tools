// zadanie 11: wykonac Exercise 13 ze str. 340

#include "std_lib_facilities.hpp"

int re_cd(int a, int b)
{
    while (b != 0) {
        int c = b;
        b = a%b;
        a = c;
    }
    return a;
}

class Rational
{
	public:
		Rational() :num(0), den(1) { }
		Rational(int n) :num(n), den(1) { }
		Rational(int n, int d) :num(n), den(d) { norm(); }

		int get_num()           const { return num;   }
		int get_den()           const { return den; } 
		double convert_double() const { return double(num)/den;}

		void norm()
		{
			if(den == 0)error("denominator equal zero ");
			
			if(den < 0 )
			{
				den=-den; num =-num;
			}
			
			int n = re_cd(num,den);
			
			if( n > 1 )
			{
				num /=n; den /=n;
			}
		}
	private:
		int num;
		int den;
};

Rational operator+(const Rational& n1, const Rational& d1);
Rational operator-(const Rational& n1, const Rational& d1);
Rational operator*(const Rational& n1, const Rational& d1);
Rational operator/(const Rational& n1, const Rational& d1);

bool operator==(const Rational& n1, const Rational& d1);
bool operator!=(const Rational& n1, const Rational& d1);

ostream& operator<<(ostream& os, const Rational& nd);

Rational operator+(const Rational& n1, const Rational& d1)
{
	Rational nd(n1.get_num()*d1.get_den() + n1.get_den()*d1.get_num(), n1.get_den()*d1.get_den());
		 nd.norm();
	return nd;

}

Rational operator-(const Rational& n1, const Rational& d1)
{
	Rational nd(n1.get_num()*d1.get_den() - n1.get_den()*d1.get_num(), n1.get_den()*d1.get_den());
		 nd.norm();
	return nd;

}

Rational operator*(const Rational& n1, const Rational& d1)
{
	Rational nd(n1.get_num()*d1.get_num(), n1.get_den()*d1.get_den());
		 nd.norm();
	return nd;

}

Rational operator/(const Rational& n1, const Rational& d1)
{
	Rational nd(n1.get_num()*d1.get_den(), n1.get_den()*d1.get_num());
		 nd.norm();
	return nd;

}

bool operator==(const Rational& n1, const Rational& d1)
{
	return n1.get_num()*d1.get_den() == n1.get_den()*d1.get_num();

}

bool operator!=(const Rational& n1, const Rational& d1)
{
	return !(n1==d1);
}

ostream& operator<<(ostream& os, const Rational& nd)
{
	return cout << '(' << nd.get_num() << '/' << nd.get_den() << ')';
}

int main()
{
	try{
		
		Rational R1;
		Rational R2(9);
		Rational R3(8,5);

		cout << "R1: " << R1 << '\n'
		     << "R2: " << R2 << '\n'
		     << "R3: " << R3 << '\n';
		
		cout << "1/3 + 1/2 = " << Rational(1,3) + Rational(1/2) <<
               " = " << (Rational(1,3) + Rational(1/2)).convert_double() << '\n';
              
                cout << "7/3 - 40/7 = " << Rational(7,3) - Rational(40,7) <<
               " = " << (Rational(7,3) - Rational(40,7)).convert_double() << '\n';
              
	        cout << "10/11 * 17/18 = " << Rational(10,11) * Rational(17,18) <<
               " = " << (Rational(10,11) * Rational(17,18)).convert_double() << '\n';
              
	       cout << "(5/7) / (1/3) = " << Rational(5,7) / Rational(1,3) <<
              " = " << (Rational(5,7) / Rational(1,3)).convert_double() << '\n';

	       if (R1 == Rational(0,1)) cout << "R1 == 0/1" << '\n';
               if (Rational(1,2) == Rational(2,4)) cout << "1/2 == 2/4" << '\n';
               if (R2 != R2) cout << "R2 != R2" << '\n';

               cout << R3 << " = " << R3.convert_double() << '\n';
	}
	catch(exception& e)
	{
		cerr << "exception: " << e.what() << endl;
	}
	catch(...)
	{
		cerr << "exception" << endl;
	}

}
