//////////////////////////////////////////////////////////////////////////////////////////

#include "std_lib_facilities.hpp"


//----------------------------------------------------------------------------------------

void print_array10(ostream& os, int* a)
{
     for (int i = 0; i < 10; i++)
     {
         os << a[i] << '\n';
     }
}

void print_array(ostream& os, int* a, int n) 
{
     for (int i = 0; i < n; i++)
     {
         os << a[i] << '\n';
     }
}

void print_vector(ostream& os, vector<int> v)
{
     for (int i = 0; i < v.size(); i++)
     {
         os << v[i] << '\n';
     }
}




//========================================================================================

int main()
    try
    {
        int* numb = new int[10];

                   
        cout << ">>> 2 <<<\n";
             for (int i = 0; i < 10; i++)
             {
                 numb[i]=i;
                     cout << numb[i] << '\n';
             }
        
        delete[] numb;

        cout << ">>> 5 <<<\n";
        int* numb_2 = new int[10];
             for (int i = 0; i < 10; i++)
                 numb_2[i] = 100 + i;
                       print_array10(cout,numb_2);
                            delete[] numb_2;

        cout << ">>> 6 <<<\n";
              int* numb_3 = new int[11];
                  for (int i = 0; i < 11; i++)
                      numb_3[i] = 100 + i;
                            print_array10(cout,numb_3);
                                 cout << numb_3[10] << "\n";
                                      delete[] numb_3;
         cout << ">>> 8 <<<\n";
               int* numb_4 = new int[20];
                   for (int i = 0; i < 20; i++)
                       numb_4[i] = 100 + i;
                             print_array(cout,numb_4,20);
                                  delete[] numb_4;
         cout << ">>> 10 <<<\n";
               vector<int> v;
                   for (int i = 0; i < 10; i++)
                       v.push_back(100+i);
                             print_vector(cout,v);

         cout << '\n';
               vector<int> v2;
                   for (int i = 0; i < 11; i++)
                       v2.push_back(100+i);
                              print_vector(cout,v2);

         cout << '\n';
               vector<int> v3;
                   for (int i = 0; i < 20; ++i)
                       v3.push_back(100+i);
                              print_vector(cout,v3);

    }
    catch (exception& e) 
    {
          cerr << "exception: " << e.what() << endl;
    }
    catch (...) 
    {
           cerr << "exception\n";
    }

//////////////////////////////////////////////////////////////////////////////////////////
