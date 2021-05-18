// Zrobic zad 9 ze str. 665

#include "std_lib_facilities.hpp"

int var_in_stat_stor                          = 10;
int var_in_stat_stor_1                        = 100;
int var_in_stat_stor_2                        = 1000;
const int const_var_in_stat_stor              = 20;
static int stat_var_in_stat_stor              = 30;
static const int stat_const_var_in_stat_stor  = 40;

int main()
{
    
    int var_in_stack_stor                          = 10;
    int var_in_stack_stor_1                        = 100;
    int var_in_stack_stor_2                        = 1000;
    const int const_var_in_stack_stor              = 20;
    static int stat_var_in_stack_stor              = 30;
    static const int stat_const_var_in_stack_stor  = 40;

    cout << "\nStatic storage:\n";
    cout << "int:              " << &var_in_stat_stor            << '\n';
    cout << "int_1:            " << &var_in_stat_stor_1          << '\n';
    cout << "int_2:            " << &var_in_stat_stor_2          << '\n';
    cout << "const int:        " << &const_var_in_stat_stor      << '\n';
    cout << "static int:       " << &stat_var_in_stat_stor       << '\n';
    cout << "static const int: " << &stat_const_var_in_stat_stor << '\n';

    cout << "\nStack storage:\n";
    cout << "int:              " << &var_in_stack_stor            << '\n';
    cout << "int_1:            " << &var_in_stack_stor_1          << '\n';
    cout << "int_2:            " << &var_in_stack_stor_2          << '\n';
    cout << "const int:        " << &const_var_in_stack_stor      << '\n';
    cout << "static int:       " << &stat_var_in_stack_stor       << '\n';
    cout << "static const int: " << &stat_const_var_in_stack_stor << '\n';
    cout << "\nIn which direction does the stack grow?\n";
    cout << "\tAnswer: Downward toward lower addresses.\n";

    int* var_in_free_stor             = new int(10);
    int* var_in_free_stor_1           = new int(100);
    int* var_in_free_stor_2           = new int(1000);
    const int* const_var_in_free_stor = new const int(20);
 
    cout << "\nFree storage:\n";
    cout << "int*:       " << &*var_in_free_stor       << '\n';
    cout << "int1*:      " << &*var_in_free_stor_1     << '\n';
    cout << "int2*:      " << &*var_in_free_stor_2     << '\n';
    cout << "const int*: " << &*const_var_in_free_stor << '\n';

    int* ptr = new int[10000];

    cout << "\nint* ptr = new int[10000];\n";
    cout << "&*ptr:              " << &*ptr       << '\n';
    cout << "&ptr[0]:            " << &ptr[0]     << '\n';
    cout << "&ptr[1]:            " << &ptr[1]     << '\n';
    cout << "&ptr[2]:            " << &ptr[2]     << '\n';
    cout << "&ptr[9998]:         " << &ptr[9998]  << '\n';
    cout << "&ptr[9999]:         " << &ptr[9999]  << '\n';
    cout << "Error! &ptr[10000]: " << &ptr[10000] << '\n';
    cout << "\nQuestion: In an array on the free store, are elements with \
    higher indices allocated at higher or lower addresses?\n";
    cout << "\tAnswer: Allocated at higher address.\n";
                                                                       
 return 0;
}

