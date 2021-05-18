// Zrobic zadanie 4 ze str. 800

#include "std_lib_facilities.hpp"

//----------------------------------------------------------------------------
template<class In, class Pred>
int my_count_if(In first, In last, const Pred& p)
{
      int ctr = 0;
      while(first != last)
      {
            if (p(*first)) ++ctr;
            ++first;
      }
      return ctr;
}
//------------------------------------------------------------------------------

template<class T>
class Less {
      T val;
public:
      Less(T v) :val(v) { }
      bool operator()(const T& v) const { return v<val; }
};

//------------------------------------------------------------------------------

template<class T>
class Greater{
      T val;
public:
      Greater(T v) :val(v) { }
bool operator()(const T& v) const { return v>val; }
};

//------------------------------------------------------------------------------

bool odd(int i) { return i%2 != 0; }

//------------------------------------------------------------------------------

int main()
{    vector<int> vi;
    for (int i = 0; i<10; ++i)
        vi.push_back(randint(10));
    cout << "vi:\n";
    for (vector<int>::iterator p = vi.begin(); p!=vi.end(); ++p)
        cout << *p << '\n';

    // Test 
    cout << "Enter value for less than count, -1 to exit: ";
    int val;
    while (cin>>val) {
        if (val==-1) break;
        int ctr = my_count_if(vi.begin(),vi.end(),Less<int>(val));
        cout << "There " << (ctr==1 ? "is " : "are ") << ctr << " value"
            << (ctr==1 ? " " : "s ") << "less than " << val << " in vi.\n"
            << "Next value: ";
    }

    // Test 
    cout << "Enter value for greater than count, -1 to exit: ";
    while (cin>>val) {
        if (val==-1) break;
        int ctr = my_count_if(vi.begin(),vi.end(),Greater<int>(val));
        cout << "There " << (ctr==1 ? "is " : "are ") << ctr << " value"
            << (ctr==1 ? " " : "s ") << "greater than " << val << " in vi.\n"
            << "Next value: ";
    }

    // Test 
    int ctr = my_count_if(vi.begin(),vi.end(),odd);
    cout << "There are " << ctr << " odd values in vi.\n";
}

