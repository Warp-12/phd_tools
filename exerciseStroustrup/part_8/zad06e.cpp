// Zrobic zadanie 1 ze str. 800, Kazdy "Try this" po kolei nazywac zad06a.cpp, zad06b.cpp, zad06c.cpp itd.

#include "std_lib_facilities.hpp"

int main()
{
    try
    {
        unordered_map<string, int> films = {
                    { "Star wars 4", 1977 },
                    { "Star wars 5", 1980 },
                    { "Star wars 6", 1983 },
                    { "Star wars 1", 1999 },
                    { "Star wars 2", 2002 },
                    { "Star wars 3", 2005 },
                    { "Star wars 7", 2015 },
                    { "Star wars 8", 2017 }
                        };

            for (const auto& f : films)
                cout << f.first << '\t' << f.second << '\n';

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
