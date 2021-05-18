// Zrobic zadanie 6 ze str. 709

#include "std_lib_facilities.hpp"

template<class T> class Number {
        T val;
public:
     Number(T value = 0) : val{value} { }

     T get() const { return val; }

     T& operator=(const T& value) { val = value; return *this; }
};

template<typename T>
ostream& operator<<(ostream& os, const Number<T>& n)
{
        return os << n.get();
}

template<typename T>
istream& operator>>(istream& is, Number<T>& n)
{
         T x;
         is >> x;
         Number<T> nn {x};
         n = nn;
         return is;
}

template<typename T, typename U>
Number<T> operator+(const Number<T>& t, const Number<U>& u)
{
        return t.get() + u.get();
}

template<typename T, typename U>
Number<T> operator-(const Number<T>& t, const Number<U>& u)
{
        return t.get() - u.get();
}

template<typename T, typename U>
Number<T> operator*(const Number<T>& t, const Number<U>& u)
{
        return t.get() * u.get();
}

template<typename T, typename U>
Number<T> operator/(const Number<T>& t, const Number<U>& u)
{
        return t.get() / u.get();
}

template<typename T, typename U>
Number<T> operator%(const Number<T>& t, const Number<U>& u)
{
        return int(t.get()) % int(u.get());
}

int main()
{
      try {

           Number<int>    x    {5};
           Number<double> y = 10.5;
          

           cout << "Number<int>: " << x << " Number<double>: " <<  y << '\n';
               
           cout << " Please enter integer : ";
           Number<int> numb;

           cin >> numb;
           cout << " You enter: " << numb << '\n';
            
           cout << "Sum of int + double:        " << x + y << '\n';
           cout << "Difference of int - double: " << x - y << '\n';
           cout << "Multiply of int*double:     " << x * y << '\n';
           cout << "Division of double/int:     " << y / x << '\n';
           cout << "Modulo   of int%double:     " << x % y << '\n';

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

