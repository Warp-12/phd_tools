// zadanie 11: wykonac Exercise 9 ze str.219

#include "std_lib_facilities.hpp"

int main()
{
    cout << "Please input a number: \n";
    int numb1, numb2, numb3, numb4, numb5, numb6, numb7;
    while(cin >> numb1 && numb1!='|')
    {
        if(numb1>=1000 && numb1<10000)
        {
            numb2=numb1/1000;
            numb3=numb1-numb2*1000;
            numb4=numb3/100;
            numb5=numb3-numb4*100;
            numb6=numb5/10;
            numb7=numb5-numb6*10;

            cout << numb1 << " is " << numb2 << " thousands and "<< numb4 <<" hundreds and "<< numb6 <<" tens and "<< numb7 << " ones.\n";
        }
        else
            if(numb1>=100 && numb1<1000)
            {

                numb2=numb1/100;
                numb3=numb1-numb2*100;
                numb4=numb3/10;
                numb5=numb3-numb4*10;

                cout << numb1 << " is " << numb2 << " hundreds and " << numb4 << " tens and " << numb5 << " ones.\n";

            }
            else
                if(numb1>=10 && numb1<100)
                {
                    numb2=numb1/10;
                    numb3=numb1-numb2*10;

                    cout << numb1 << " is " << numb2 << " tens and "<< numb3 << " ones.\n";
                }
                else
                    if(numb1>=1 && numb1<10)
                    {
                        numb2=numb1-0;

                        cout << numb1 << " is " << numb2 << " ones.\n";
                    }
                    else
                        cout<<"ERROR: BAD INPUT!!!\n";
    }
        return 0;
}

