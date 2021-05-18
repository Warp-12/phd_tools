// zadanie 1:
//  (a) poprawić błędy w programie - tak żeby się skompilował.
//  (b) zmenić komunikat w tak aby pisywał dwie linijki w okienku,
//      przy ograniczeniu, że wolno wywołać `cout` tylko raz!

#include "std_lib_facilities.hpp"

int main()
{
    string s;
    
    s = " Goodbye,\n cruel world! ";
    
    cout << s << "\n";

    return 0;
}
