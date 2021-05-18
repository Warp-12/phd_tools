// Zadanie 8: wykonac exercise 4 ze str. 408

#include "std_lib_facilities.hpp"

enum format {decimal, octal, hexadecimal};


ostream& operator<<(ostream& ost,format form)
{
	if(form==decimal)
	{
		return ost << "decimal\t";
	}

	else if(form==octal)
	{
		return ost << "octal\t";
	}

        else if(form==hexadecimal)
	{
		return ost << "hexadecimal";
	}


}
void print(int n, format form)
{
	cout << showbase;
	
	if(form==decimal)
	{
		cout << dec << setw(5) << n;
	}

	else if(form==octal)
	{
		cout << oct << setw(5) << n;
	}
	
	else if(form==hexadecimal)
	{
		cout << hex << setw(5) << n;
	}
     
        cout << " " << form << "\tconverts to " << dec << setw(5) << n << " " << decimal << '\n';

}
int n=0;
char ch;
int main()
{
	cout << "Please enter several integers in any combynation of octal, decimal, hexadecimal using the 0, 0x base suffix\n";
	while(cin>>ch)
	{
		if(ch=='0')
		{
			cin.get(ch);
			if(ch=='x')
			{
				cin >> hex >> n;
				print(n,hexadecimal);
			}
			else if(isdigit(ch))
			{
				cin.unget();
				cin >> oct >> n;
				print(n,octal);
			}
			else
			{
				cin.unget();
				print(0,octal);
			}
			
		}
		else if(isdigit(ch))
		{
			cin.unget();
			cin >> dec >> n;
			print(n,decimal);
		}
		else break;
	}
}

