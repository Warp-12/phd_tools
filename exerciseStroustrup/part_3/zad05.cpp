// zadanie 5: wykonac Exercise 2 i 3 ze str. 300

#include "std_lib_facilities.hpp"

void print(const string& labeling, const vector<int>& store)

{
    cout << labeling << ": { ";
    for (int i :store )
    { 
        cout << i << " , ";
    }
        cout << "}\n";
}
int check(int num1, int num2)
{
    if (((num2 > 0) && (num1 > (numeric_limits<int>::max() - num2))) || ((num2 < 0) && (num1 < (numeric_limits<int>::min() - num2))))
    {
        error("check(): integer add overflows.");
    }
    else
        return num1+num2;
}
void fibonacci(int x, int y, vector<int>& v, int n)
{
   
    if (n < 2)
    {
        error("fibonacci(): n must be >= 2.");
    }
    v.push_back(x);
    v.push_back(y);

    for (int i = 2; i < n; ++i)
    {
        v.push_back(check(v[i-2],v[i-1]));
    } 
}

int main()
{

	try
	{
	    vector<int> store;
	    
	    fibonacci(1, 2, store, 25);
	    print("Fibonacci(25): ", store);
	    store.clear();   // for using for next pair of numbers and number of fibbonacci variable it should be clean



	    return 0;
	}

	catch(exception& e)
	{
	    cerr << e.what() << "\n";
	    return 1;
	}

	catch(...)
	{
	    cerr << "Unknwon exception!!\n";
	return 2;
	}
}
