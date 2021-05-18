// Zrobic exercise 1 ze str.754. Kazdy "Try this" po kolei nazywac zad02a.cpp, zad02b.cpp, zad02c.cpp itd.

#include "std_lib_facilities.hpp"
//-----------------------------------------------------------------------------------------
 
 void cp(int* f1, int* e1, int* f2)
{
      while(true)
      {
               *f2 = *f1;
             if(f1 == e1)
                   return;
                f2++;
                f1++;
       }
 
 }

void prt(int A[], int n)
{
        for (int i=0; i<n; i++)
        {
             cout << A[i] << " ";
        }
             cout << endl;
}

//-----------------------------------------------------------------------------------------

int main()
{
     int A[5] = {1,2,3,4,5}, B[5] = { 6,7,8,9,10 };
     int *Abegin = &A[0], *Aend = &A[4];
     int *Bbegin = &B[0], *Bend = &B[4];

                 prt(A,5);
                 prt(B,5);

                         cp(Abegin,Aend,Bbegin);

                             prt(A,5);
                             prt(B,5);

                             return 0;
}

