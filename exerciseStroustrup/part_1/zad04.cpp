// zadanie 4: Wykonać "Exercise 6 oraz 7" ze strony 86 w książce.
// 6. Write a program that prompts the user to enter three integer values, and
// then outputs the values in numerical sequence separated by commas. So,
// if the user enters the values 10 4 6, the output should be 4, 6, 10. If two
// values are the same, they should just be ordered together. So, the input
// 4 5 4 should give 4, 4, 5.
// 7. Do exercise 6, but with three string values. So, if the user enters the val-
// ues Steinbeck, Hemingway, Fitzgerald, the output should be Fitzgerald,
// Hemingway, Steinbeck.




#include "std_lib_facilities.hpp"


using namespace std;

int main()

{

    int val1, val2, val3, k;
    string wor1,wor2,wor3;


    cout << "Enter 1 for ordering integer value, 2 - for string value: \n";
    cin >> k;

    if(k == 1)
    {
      cout << "Please enter 3 integer value:";
      cin >> val1 >> val2 >> val3;

      int n;

      if(val1>val2){n=val1; val1=val2; val2=n;}
      if(val2>val3){n=val2; val2=val3; val3=n;}
      if(val1>val2){n=val1; val1=val2; val2=n;}

      cout << val1 << "\t" << val2 << "\t" << val3;
    }

   if(k ==2)
    {
      cout << "Please enter 3 string value:";
      cin >> wor1 >> wor2 >> wor3;

      string c;

      if(wor1>wor2){c=wor1; wor1=wor2; wor2=c;}
      if(wor2>wor3){c=wor2; wor2=wor3; wor3=c;}
      if(wor1>wor2){c=wor1; wor1=wor2; wor2=c;}

      cout << wor1 << "\t" << wor2 << "\t" << wor3;
    }
}
