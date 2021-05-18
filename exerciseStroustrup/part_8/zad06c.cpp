// Zrobic zadanie 1 ze str. 800, Kazdy "Try this" po kolei nazywac zad06a.cpp, zad06b.cpp, zad06c.cpp itd.

#include "std_lib_facilities.hpp"

//------------------------------------------------------------------------------

struct Record {
       Record(double up, int un) : unit_price(up), units(un) { }
       double unit_price;
       int units;  
};

//------------------------------------------------------------------------------
double price(double v, const Record& r)
{
       return v + r.unit_price * r.units;  
}

//-----------------------------------------------------------------------------

void f(const vector<Record>& vr)
{
       double total = accumulate(vr.begin(),vr.end(),0.0,price);
       cout << "Total is " << total << "\n";
}

//------------------------------------------------------------------------------
                      

int main()
{
try {
        Record rec1 = Record(3.4,10);
        Record rec2 = Record(15.5,4);
        Record rec3 = Record(10,7);
        Record rec4 = Record(1.3,2);
        vector<Record> vr;
        vr.push_back(rec1);
        vr.push_back(rec2);
        vr.push_back(rec3);
        vr.push_back(rec4);
        f(vr);

}
    catch(exception& e) {
            cerr << "Exception: " << e.what() << '\n';
                return 1;
    }
    catch(...) {
            cerr << "Unknown exception\n";
                return 2;
    }
}
