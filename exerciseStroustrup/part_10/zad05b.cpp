// Zrobic zad 1 ze str 986, pliki po kolei nazywac zad05a.cpp, zad05b.cpp itd

#include "std_lib_facilities.hpp"
#include <bitset>
int main()
{

	    int i;
        while (cin>>i)
        cout << dec << i << " == "
	         << hex << "0x" << setw(8)
			 << setfill('0') << i << " == "
	    	 << bitset<8*sizeof(int)>(i) << '\n';
}

