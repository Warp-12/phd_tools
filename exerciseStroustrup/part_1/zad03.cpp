// zadanie 3: Wykonać "Exercise 4 oraz 5" ze strony 86 w książce.
// 4. Write a program that prompts the user to enter two integer values. Store
// these values in int variables named val1 and val2. Write your program to
// determine the smaller, larger, sum, difference, product, and ratio of these
// values and report them to the user.
// 5. Modify the program above to ask the user to enter floating-point values
// and store them in double variables. Compare the outputs of the two pro-
// grams for some inputs of your choice. Are the results the same? Should
// they be? What’s the difference?

#include "std_lib_facilities.hpp"

int main()
{
    char c;	
    
    cout << " Enter 'i' for integer value, or 'f' for floating-poit value\n";
    cin >> c;

    if(c == 'i')
    {
    int val1, val2, min, max,sum, diff, prod, rat; 

	cout << "Enter two integer value: \n";
	cin >> val1 >> val2;

        sum=val1+val2;
	diff=val1-val2;
	prod=val1*val2;
	rat=val1/val2;

	if(val1>val2){max=val1; min=val2;}
	else
	if(val2>val1){max=val2; min=val1;}

	cout << "larger = " << max << "\n" << "smaller = " << min << "\n" << "sum = " << sum << "\n" << "difference = " << diff << "\n" <<  "product = " << prod << "\n" << "ratio = " << rat << "\n";
    }
	
    if(c == 'f')
    {
    float val3, val4;
    double val3_d,val4_d, max_d, min_d, sum_d, diff_d, prod_d, rat_d;

	cout << "Enter two float value: \n";
	cin >> val3 >> val4;
	

        sum_d=val3+val4;
	diff_d=val3-val4;
	prod_d=val3*val4;
	rat_d=val3/val4;

	if(val3>val4){max_d=val3; min_d=val4;}
	else
	if(val4>val3){max_d=val4; min_d=val3;}

	cout << "larger = " << max_d << "\n" << "smaller = " << min_d << "\n" << "sum = " << sum_d << "\n" << "difference = " << diff_d << "\n" <<  "product = " << prod_d << "\n" << "ratio = " << rat_d << "\n";
   }
}
