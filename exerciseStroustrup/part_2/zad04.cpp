// zadanie 4: wykonac Exercise 10 ze str.129

#include "std_lib_facilities.hpp"
int var_p1, var_p2;



int main()
{

    cout << "You have to choose one of the three sign:\n if rock type 0,\n if paper type 1,\n if scissors type 2, \n to exit type 3\n Chose your sing: \n";
    while(cin >> var_p2 || var_p2==3)
    {

        vector<int> v={0, 1, 2};
        srand(time(0));
        int random_var =rand()%v.size();
        var_p1 =v[random_var];
        if(var_p2==3){cout << "Exit!\n"; return 0;}
        else
        switch(var_p1)
        {
           case 0:if(var_p2 == 0){cout << "\nYou choose rock,  Computer also, result dead heat!  \n"; break;}
                  if(var_p2 == 1){cout << "\nYou choose paper, Computer  rock, You win!      \n"; break;}
                  if(var_p2 == 2){cout << "\nYou choose scissors, Computer  rock, You lose!  \n"; break;}

           case 1:if(var_p2 == 0){cout << "\nYou choose rock,  Computer  paper, You lose!    \n"; break;}
                  if(var_p2 == 1){cout << "\nYou choose paper, Computer  also, result dead heat!  \n"; break;}
                  if(var_p2 == 2){cout << "\nYou choose scissors, Computer  paper, You win!  \n"; break;}


           case 2:if(var_p2 == 0){cout << "\nYou choose rock,  Computer  scissor, You win!     \n"; break;}
                  if(var_p2 == 1){cout << "\nYou choose paper, Computer  scissor, You lose!    \n"; break;}
                  if(var_p2 == 2){cout << "\nYou choose scissors, Computer  also, result dead heat! \n"; break;}


        }

    }

}

