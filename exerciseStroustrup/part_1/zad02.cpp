// zadanie 2: Wykonać "Exercise 2" ze strony 85 w książce.
// Write a program in C++ that converts from miles to kilometers. Your
// program should have a reasonable prompt for the user to enter a number
// of miles. Hint: There are 1.609 kilometers to the mile.

#include "std_lib_facilities.hpp"

int main()
{
	// skorzystać z materiałów w prezentacji.
    const double km_per_mile = 1.609;
    int value;
    char units;
    cout << "Please enter value and units\n";
    while (cin >> value >> units)
    {
        if(units=='m')
        {
            cout << value << " mile == " << value*km_per_mile << " km.\n";
        }
        else if(units=='k')
        {
            cout << value << " km == " << value/km_per_mile << " miles\n";
        }
        else
            return 0;
        
    }
}
