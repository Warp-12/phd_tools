// Zrobic zadanie 5 ze str. 709

#include "std_lib_facilities.hpp"
//-----------------------------------------------------------------------------

class Int {
    int val;
public:
    Int(int ii = 0 ) : val{ii} { }

    int get() const {return val;}

    Int& operator=(const int ii) {val = ii; return *this; }

};

ostream& operator<<(ostream& os, const Int& ii)
{
    return os << ii.get();
}

istream& operator<<(istream& is, Int& ii)
{
    int x=0;
    is >> x;
    ii =x;
    return is;
}

int operator+(const Int& a, const Int& b)
{
    return a.get() + b.get();
}

int operator-(const Int& a, const Int& b)
{
    return a.get() - b.get();
}

int operator*(const Int& a, const Int& b)
{
    return a.get() * b.get();
}

int operator/(const Int& a, const Int& b)
{
    return a.get() / b.get();
}
int main()
{
    try {
   
    Int x   {5};
    Int y = 10;
    Int z = x * y;

    cout << x << ' ' << y << ' ' << z << '\n';
    cout << x + y << '\n';
    cout << x - y << '\n';
    cout << x * y << '\n';
    cout << y / x << '\n';

    }

    catch(exception& e)
    {
        cerr << "Exception: " << e.what() << '\n';

        return 1;

    }

    catch(...)
    {
        cerr << "Unknown exception\n";

        return 2;

    }
}

