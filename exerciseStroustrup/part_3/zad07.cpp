// zadanie 7: wykonac Exercise 7 ze str. 301

#include "std_lib_facilities.hpp"

constexpr int number_name{5};
bool isin(const vector<string>& v, const string& s)
{
	for(string x : v)
		if(x == s) return true;
	return false;
	
}

void get_names(vector<string>& name)
{
	cout << "Please input  " << number_name << " people names: \n";
	for(int i=0; i < number_name; i++) 
	{
		string n;
		cin >> n;
		while(isin(name, n))
		{
			cout << "ERROR: duplicated name: " << n << "\n";
			cin >> n;
		}
		name.push_back(n);
	}
}

void get_ages(const vector<string>& name, vector<double>& age)

{
    cout << "Please enter the age of person: \n";
    for (string n : name)
    {
        cout << "How old is " << n << "? ";
        double a{0}; 
        while (!(cin >> a))
	{
            cout << "Sorry, I don't understand you! How old is " << n << "? ";
            cin.clear();;
        }
        age.push_back(a);
    }
} 


void print_pairs(const vector<string>& name, const vector<double>& age)

{
    size_t limit = name.size();     
    for (size_t i = 0; i < limit; ++i)
        cout << '\t' << name[i] << " is " << age[i] << " years old.\n";
}

size_t name_idx(const vector<string>& name, const string& n)

{
    size_t limit = name.size();
    for (size_t i = 0; i < limit; ++i)
        if (name[i] == n) return i;
    error("name_idx(): No element found!");
}

void sort_pairs(vector<string>& name, vector<double>& age)

{
    vector<string> orig_name{name};   
    vector<double> orig_age{age};     

    sort(name.begin(), name.end());
    size_t limit = name.size();
    for (size_t i = 0; i < limit; ++i)
        age[i] = orig_age[name_idx(orig_name, name[i])];
}
int main()
{
try {
    vector<string> name;
    vector<double> age;

    get_names(name);
    get_ages(name, age);
    cout << "\nOK! So you tell me about these people:\n";
    print_pairs(name, age);
    sort_pairs(name, age);
    cout << "\nThat sorted by name are:\n";
    print_pairs(name, age);
    cout << '\n';

    return 0;
}
catch(exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch(...)
{
    cerr << "Unknown exception!\n";
return 2;
}
}
