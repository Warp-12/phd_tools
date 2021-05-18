// Zrobic zad 1 ze str 986, pliki po kolei nazywac zad05a.cpp, zad05b.cpp itd

#include "std_lib_facilities.hpp"


template<class T> void print(T i) { cout << i << '\t'; }

void print(char i) { cout << int(i) << '\t'; }

void print(signed char i) { cout << int(i) << '\t'; }

void print(unsigned char i) { cout << int(i) << '\t'; }

int main()
{
 int si = 128;           
 char c = si;            
 unsigned char uc = si;  
 signed char sc = si;    
 print(si);
 print(c);
 print(uc);
 print(sc);
 cout << '\n';


}

