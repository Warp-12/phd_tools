// zadanie 2: wykonac Exercise 3 ze str.128

#include "std_lib_facilities.hpp"

int main()
{
     double  suma, var_min, var_max, ave_dis, a, temp_vp,temp_vn  ;

    vector<double> v;
    var_max=-1000000;
    var_min=1000000;
    suma=0.0;
    a=0.0;

    cout << "Please enter the distance between city's in km.: \n";
    while( cin >> a )
    {
        v.push_back(a);

                        for(int i = 0 ; i < v.size(); i++)
                        {
                           suma+=v[i];
                           if(var_min>suma){var_min=suma;}
                           if(var_max<suma){var_max=suma;}
                           cout << "Greatest distance: " << var_max << "smalest distance: " << var_min << "\n";
                           cout << "The total distance  " << suma << " from " << i << " to " << i+1 << " km.\n";
                           cout << "Mean distance is " << suma/v.size()  << " between " << i << " and " << i+1<< " km.\n";
                        }
    }


}

