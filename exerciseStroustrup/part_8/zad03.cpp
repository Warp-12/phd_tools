// Zrobic zad 11 ze str. 755

#include "std_lib_facilities.hpp"

vector<double> list_to_vec(const std::list<int>& l)
{
        vector<double> v (l.size());

        copy(l.begin(), l.end(), v.begin());

                return v;
}
int main()
{


    list<int> l { 1, 2, 3, 4, 5, 6, 7, 8 };

        vector<double> v = list_to_vec(l);

            for (auto& a : v)
                        cout << a << ' ';
            cout << '\n';
}

