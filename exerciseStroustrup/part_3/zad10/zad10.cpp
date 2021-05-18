// zadanie 10: wykonac Exercise 10 ze str. 340
// wewnątrz int main() napisać krótki programik testujący/uzywajacy wszystkie elementy klasy

#include "std_lib_facilities.hpp"
#include "Chrono.h"

int main()
{
    constexpr int inc{5};   
    constexpr int cols{4};
    int col{0};

    
    for (int i = 1700; i < 2200; i+=inc) {
        cout << i << ": ";
        if (Chrono::leapyear(i)) cout << "LEAP year    ";
        else cout << "Common year  ";
        ++col;
        if (col == cols) {
            cout << '\n';
            col = 0;
        }
    }
    cout << '\n';
    
    return 0;
}
