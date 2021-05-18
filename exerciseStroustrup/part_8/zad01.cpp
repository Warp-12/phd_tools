// Zrobic drill ze str 753.

// Uwaga: termin oddania zadan z tygodnia_09 (oraz tygodnia_10) to 8 maja, godzina 23:59 !!!

// Uwaga: dnia 26 kwietnia nie bedzie wykladu, cwiczenia odbeda sie normalnie. Tzn bedzie wyklad e-learningowy: prezentacja i rozdzial z ksiazki do przeczytania samodzielnie.

// Uwaga: Nastepny wyklad bedzie 10 maja !!!, cwiczenia odbeda sie normalnie.

#include "std_lib_facilities.hpp"

    template<typename C>
    void print_cont(const C&c, const std::string& s = "" )
    {
       cout << s << '\t';
        for(auto& a : c)
        {
            cout << '\n' << setw(14) <<  a <<  ' ' << '\n';
        }

    }

    template<typename C>
    void inc_cont(C& c, int n = 1)
    {
        for(auto& a: c)
        {
            a+=n;
        }


    }

    template<typename Iter1, typename Iter2>
    Iter2 mcop(Iter1 f1, Iter1 e1, Iter2 f2)
    { 
        for(Iter1 p = f1; p != e1; p++)
        {
            *f2++ =*p;
        }

        return f2;
    }

int main()
{
    const int size =10;

    int arr[size];

    for(int i=0; i<size; i++)
    {
            arr[i] = i;
    }

        print_cont(arr, "built-in []: ");
    
        array<int, size> arrr;
            copy(arr, arr+size, arrr.begin());
                print_cont(arrr, "array: ");
        
        vector<int> vec(size);
           copy(arr, arr + size, vec.begin());
             print_cont(vec, "vector: ");

        list<int> lis(size);
            copy(arr, arr + size, lis.begin());
              print_cont(lis, "list: ");

              cout << '\n';

        array<int, size> arrrr = arrr;
        vector<int>      vecc  = vec;
        list<int>        liss  = lis;
              print_cont(arrr, "arrr: ");
              print_cont(vecc, "vecc: ");
              print_cont(liss, "liss: ");

        inc_cont(arrrr, 2);
        inc_cont(vecc,  3);
        inc_cont(liss,  5);
                  print_cont(arrrr, "array inc'd:  ");
                  print_cont(vecc,  "vector inc'd: ");
                  print_cont(liss,  "list inc'd:   ");

        mcop(arrrr.begin(), arrrr.end(), vecc.begin());
        mcop(liss.begin(), liss.end(), arrrr.begin());
            print_cont(arrrr, "array copied: ");
            print_cont(vecc, "vector copied: ");
            print_cont(liss, "list copied: ");

             vector<int>::iterator vit;
                 vit = find(vecc.begin(), vecc.end(), 3);
                     if (vit != vecc.end())
                                 cout << "Found at: " << distance(vecc.begin(), vit) << '\n';
                         else
                                     cout << "Not found..\n";

                             list<int>::iterator lit;
                                 lit = find(liss.begin(), liss.end(), 27);
                                     if (lit != liss.end())
                                                 cout << "Found at: " << distance(liss.begin(), lit) << '\n';
                                         else
                                             cout << "Not found..\n";
}

