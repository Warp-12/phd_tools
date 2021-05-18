// Zrobic zadanie 1 ze str. 800, Kazdy "Try this" po kolei nazywac zad06a.cpp, zad06b.cpp, zad06c.cpp itd.

#include "std_lib_facilities.hpp"

//------------------------------------------------------------------------------

double weighted_value(const pair<string,double>& a,
       const pair<string,double>& b)
{
       return a.second * b.second;
}

//------------------------------------------------------------------------------
                      

int main()
{
try {

map<string, double> dow_price = {
      { "MMM", 81.86 },
      { "AA", 34.69 },
      { "MO", 54.45 },
      { "BA", 332.83 },
      { "INTC", 43.95 }
                    };
                                                 
map<string, double> dow_weight = {
                   { "MMM", 5.8549 },
                   { "AA", 2.4808 },
                   { "MO", 3.8940 },
                   { "BA", 1.7182 },
                   { "INTC", 2.8783 }
};


map<string, string> dow_name = {
                  { "MMM", "3M Co." },
                  { "AA", "Alcoa Inc." },
                  { "MO", "Altria Group Inc." },
                  { "BA", "Boeing Inc." },
                  { "INTC", "Intel Inc." }
    };


double alcoa_price = dow_price["AA"];
double boeing_price = dow_price["BA"];

        if (dow_price.find("INTC") != dow_price.end())
                    cout << "Intel is in the Dow\n";

for (const auto& p : dow_price) {
     const string& symbol = p.first;
           cout << symbol << '\t'
                << p.second << '\t'
                << dow_name[symbol] << '\n';
}
double dji_index =
        inner_product(dow_price.begin(), dow_price.end(),dow_weight.begin(),0.0,plus<double>(),weighted_value);  
        cout << "Dow Jones Industrial Index:" << dji_index << '\n';

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
