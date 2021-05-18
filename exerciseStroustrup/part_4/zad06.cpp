// Zadanie 6: wykonac Drill ze str. 407

#include "std_lib_facilities.hpp"
int birth_year=1994;
int age=23;
int a;
int b;
int c;
int d;
int main()
{
	cout << showbase <<"Birth year: \n"  
	     << dec << birth_year << "\t(decimal)\n"
	     << hex << birth_year << "\t(hexadecimal)\n"
	     << oct << birth_year << "\t(octal)\n";

	cout << showbase   << "\nAge: \n"  
	     << dec << age << "\t(decimal)\n"
	     << hex << age << "\t(hexadecimal)\n"
	     << oct << age << "\t(octal)\n";

	cin  >> a >> hex  >> b >> oct  >> c >> d;
	cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';

	cout << 123456.89  << "\t(general)\n"
	     << fixed      << 1234567.89      << "\t(fixed)\n"
	     << scientific << 1234567.89      << "\t(scientific)\n";


cout << setw(10) << "Mateusz"  << " | " << setw(12) << "Morawiecki" << " | " << setw(16) << "+1050 4628956" << " | " << setw(29) << "mate.moraw@gmail.com"     << '\n'
     << setw(10) << "Piotr"    << " | " << setw(12) << "Glinski"    << " | " << setw(16) << "+4859 8590291" << " | " << setw(29) << "piotrglinski@wp.pl"       << '\n'
     << setw(10) << "Jaroslaw" << " | " << setw(12) << "Gowin"      << " | " << setw(16) << "+4823 7845856" << " | " << setw(29) << "jaroslaw.gowin@gmail.com" << '\n'
     << setw(10) << "Beata"    << " | " << setw(12) << "Szydlo"     << " | " << setw(16) << "+5964 7589671" << " | " << setw(29) << "bszydlo@gmail.com"        << '\n'
     << setw(10) << "Anna"     << " | " << setw(12) << "Zalewska"   << " | " << setw(16) << "+1513 4569875" << " | " << setw(29) << "annzale@wp.pl"            << '\n';
        
}

