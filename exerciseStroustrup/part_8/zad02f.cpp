#include "std_lib_facilities.hpp"

template<class Iter> void advance(Iter& p, int n)
{
        if (n>0)
        {
                while (n>0) { ++p; --n; }
        }
        else if (n<0)
        {
                while (n<0) { --p; ++n; }
        }
}
int main()
{
}
