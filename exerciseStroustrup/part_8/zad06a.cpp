// Zrobic zadanie 1 ze str. 800, Kazdy "Try this" po kolei nazywac zad06a.cpp, zad06b.cpp, zad06c.cpp itd.

#include "std_lib_facilities.hpp"

template<typename In, typename T>
       In pro_find(In first, In last, const T& val)
       {
                 while (first != last && *first != val) ++first;
                     return first;
       }

template<typename In, typename T>
         In pleb_find(In first, In last, const T& val)
         {
                for (In p = first; p != last; ++p)
                         if (*p == val) return p;
                             return last;
          }
int main()
{
    try {
            vector<int> vi { 1, 1, 2, 3, 5, 8, 13, 21 };
            list<char> lc { 'v', 'a', 'l', 'e', 'r', 'i', 'y' };

            cout << "Enter an integer to find in vi:\n";
            int x;
            cin >> x;

             auto vit = pro_find(vi.begin(), vi.end(), x);
             auto vit2 = pleb_find(vi.begin(), vi.end(), x);
             if (vit == vit2)
             {
                 cout << "Both 'find's produced same output for vectors.\n";
             }

                 if (vit != vi.end()) {
                     cout << "Found " << x << " in vi!\n";
                                 } else {
                     cout << "That number is in another vector..\n";
                                                 }

                     cout << "Guess a letter in my name:\n";
                         char ch;
                     cin >> ch;

 auto lit = pro_find(lc.begin(), lc.end(), ch);
 auto lit2 = pleb_find(lc.begin(), lc.end(), ch);
         if (lit == lit2)
         {
            cout << "Both 'find's produced same output for lists.\n";
         }
         if (lit != lc.end())
         {
               cout << "Found " << ch << " in lc!\n";
         } else {
                    cout << "That is not a letter in my  name..\n";
                }
    }
    catch(exception& e) {
            cerr << "Exception: " << e.what() << '\n';
                return 1;
    }
    catch(...) {
            cerr << "Unknown exception\n";
                return 2;
    }
}
