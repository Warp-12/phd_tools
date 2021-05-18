// zadanie 8: wykonac Exercise 8 ze str.170

#include "std_lib_facilities.hpp"

int main()
{
    int N, numb; int sum=0;
    char c='|';
    vector<int> v;
    cout << "Please enter the number of values you want to sum:\n";
    cin >> N;
    cout << "Please enter some integers (press '|' to stop)\n";

    while(cin >> numb )
    {
            if(numb==c){goto finish;}

            v.push_back(numb);
    }
    if(N>v.size())
    {
        cout << "ERROR: Number are less then vector have values!!!\n"; goto finish;
    }
    for(int i=0; i<N; i++)
    {
             sum+=v[i];
    }
    cout << "The sum of the first "  << N << " numbers ( ";
    for(int i=0; i<N; i++){cout << v[i] << " ";}
    cout << ") is " << sum << ".";

finish:return 0;
}

