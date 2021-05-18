// zadanie 5: Wykonać "Exercise 10" ze strony 86 w książce.
// Write a program that takes an operation followed by two operands and
// outputs the result. For example:
// + 100 3.14
// * 4 5
// Read the operation into a string called operation and use an
// if-statement to figure out which operation the user wants, for example,
// if (operation=="+"). Read the operands into variables of type double.
// Implement this for operations called +, –, *, /, plus, minus, mul, and div
// with their obvious meanings.

#include "std_lib_facilities.hpp"

int main()
{
	string operation;
	double val1{0},val2{0};
	cin >> operation >> val1 >> val2;
	if(operation == "+" || operation == "plus")
        {
		cout << val1+val2 << "\n";
	}

	if(operation == "-" || operation == "minus")
	{
		cout << val1-val2 << "\n";
	}

	if(operation == "*" || operation == "mul")
        {
		cout << val1*val2 << "\n";
	}

	if(operation == "/" || operation == "div") 
	{
		cout << val1/val2 << "\n";
	}
	

	cout << "end\n";
}

