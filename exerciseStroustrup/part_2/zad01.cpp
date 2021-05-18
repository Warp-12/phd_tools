#include "std_lib_facilities.hpp" // nagłówek, który używamy w tym kursie

int main()
{   double a, b, val, max,min, result, suma, suma_min, suma_max;
    char c;
    vector<double> v;
    c='|';
    b=0.0;
    suma_min=1000000.0;
    suma_max=-1000000.0;
    suma=0;
    string s, cm, in, ft, m;

    cout << "Please enter the value: \n";
    while( cin >> a && cin >> s)
    {
        if(a==c){goto finish;}
        if(s!="m")
        {
            if(s=="cm"){val=a/100.00; s="m"; cout << a  << " cm. is " << val << " m\n";}else
            if(s=="ft"){val=a*0.3048; s="m";  cout << a  << " ft. is " << val << " m\n";}else
            if(s=="in"){val=a*0.0254; s="m";  cout << a << " in. is " << val << " m\n";}else
            {cout << "Value without  unit or bad unit \n"; goto finish;}
        }
        else {val=a;}

        if(b!=0.0)
        {

            if(val<=b+0.01 && val>=b-0.01){cout << "the numbers are almost equal " << val << " = " << b;}
            else

            if(val!=b)
            {
                if(val<b){max=b;   min=val;}
                else     {max=val; min=b;}
                cout << "The larger value so far " << max << " m. the smaller value so far " << min << " m.\n";
                suma=min+max;
                if(suma<suma_min){suma_min=suma;}
                if(suma>suma_max){suma_max=suma;}
                cout << "The larger sum so far " << suma_max << " m. the smallest sum so far " << suma_min << " m.\n";
                v.push_back(val);
                sort(v);
                for(int i = 0 ; i < v.size(); i++)
                {
                    cout << "Sorted vector is ( " << v[i] << " ) \n";
                }

            }

        }
        else cout << "write next value\n";

            b=val;

    }


  finish:cout << "Exit!\n";
}
