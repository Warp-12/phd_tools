// Zrobic drill ze str. 984

#include "std_lib_facilities.hpp"
#include<bitset>
//===========================================================================
void prints(const vector<short unsigned int>& v)
{
	    for (auto i : v)
			cout << setw(5) << dec << i << " == "
			     << "0x" << setfill('0')
		         << setw(4) << hex << i << " == "
		         << setfill(' ')
		         << bitset<8*sizeof(short unsigned int)>{i} << '\n';
}
int main()
{
	unsigned int v = 1;
	
	for (int i = 0; i<sizeof(v)*8; ++i)
	{
			        cout << v << '\n';
					        v <<= 1;
    }
    
	vector<short unsigned int> v_hex {
	         0xffff,     // a
	         0x0001,     // b
	         0x8000,     // c
             0x00ff,     // d
             0xff00,     // e
	         0x5555,     // f
	         0xaaaa      // g
 };
//drill_4
cout << "   Decimal and hexadecimal prints  \n"
     << "===================================\n";
 prints(v_hex);
//drill_5

 vector<short unsigned int> v_bit;

	 short unsigned int a = ~0;
	 v_bit.push_back(a);
	 short unsigned int b = 1;
	 v_bit.push_back(b);
	 short unsigned int c = 1;
	 c <<= 15;
	 v_bit.push_back(c);
	 short unsigned int d = 1;
	 
	 for(int i = 1; i < 8; ++i)
	 {
			short unsigned int t = 1;
	        t <<= i;
            d |= t;            
	 }
	 v_bit.push_back(d);
     short unsigned int e = ~d;
     v_bit.push_back(e);
     short unsigned int f = 1;
      
	 for(int i = 2; i < 15; i += 2)
	 {
          short unsigned int t = 1;
          t <<= i;
          f |= t;
     }
      
	 v_bit.push_back(f);
     short unsigned int g = ~f;
     v_bit.push_back(g);

	 cout << "    Print of manipulation operations   \n"
	      << "=======================================\n";
     prints(v_bit);
	 unsigned int xx = -3; cout << dec << xx << '\n';
}

