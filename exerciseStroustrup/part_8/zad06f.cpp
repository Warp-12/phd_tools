// Zrobic zadanie 1 ze str. 800, Kazdy "Try this" po kolei nazywac zad06a.cpp, zad06b.cpp, zad06c.cpp itd.

#include "std_lib_facilities.hpp"

int main()
{
    try
    {
        string from, to;
                cin >> from >> to;      

                ifstream is { from };    
                ofstream os { to }; 
/*
                istream_iterator<string> ii { is };
                istream_iterator<string> eos;
                ostream_iterator<string> oo { os, "\n" };
                vector<string> b { ii, eos };
                sort(b.begin(), b.end());
                copy(b.begin(), b.end(), oo);
                const int max_size = 50;
                vector<string> b {max_size};
                copy(ii, eos, b.begin());
                for (const auto a : b) cout << a << ' ';
                cout << '\n';
 */
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
