// Zrobic zadanie 13 ze str. 888

#include "std_lib_facilities.hpp"

int main()
{
         string s = "\n";
         regex pat(".");
         smatch matches;
             if (regex_match(s,matches,pat))
         
                 cout << "'.' matches '\\n'\n";
                 else
                 cout << "'.' does not match '\\n'\n";
}

