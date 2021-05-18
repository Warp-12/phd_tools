/////////////////////////////////////////////////////////////////////////////////////////////////

#include "std_lib_facilities.hpp"

//===============================================================================================

int main()
    try
    {
         int numb_1 = 0;
         int numb_2 = 0;
         int numb_3 = 0;
         cout << "Addresses in stack:\n" << &numb_1 << '\n' << &numb_2 << '\n' << &numb_3 << '\n';
         int stack_dif = &numb_2 - &numb_1;
         if (stack_dif>0) cout << "Stack addresses grows up\n";
         else             cout << "Stack addresses grows down\n";

         int* numbs_1 = new int(0);
         int* numbs_2 = new int(0);
         int* numbs_3 = new int(0);
         cout << "Addresses on store:\n" << numbs_1 << '\n' << numbs_2 << '\n' << numbs_3 << '\n';
         int store_dif = numbs_2 - numbs_1;
         if (store_dif>0) cout << "Store addresses grows up\n";
         else             cout << "Store addresses grows down\n";

         delete numbs_1;
         delete numbs_2;
         delete numbs_3;

    }
    catch (exception& e) 
    {
          cerr << "exception: " << e.what() << endl;
    }
    catch (...) 
    {
           cerr << "exception\n";
    }

//////////////////////////////////////////////////////////////////////////////////////////////////
