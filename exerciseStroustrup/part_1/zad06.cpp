// zadanie 2: Wykonać "Drill" ze strony 83 w książce.

#include "std_lib_facilities.hpp"

int main()
{
	cout << "Please enter your first name (followed by 'enter'):\n";
	string first_name;	// first_name is a variable of type string
	cin >> first_name;	// read characters into first_name
	cout << "Hello, " << first_name << "!\n";
	cout << "Enter the name of the person you want write to:\n";
	string recipient_name;	
	cin >> recipient_name;	
        cout << "Enter the name of another friend:\n";
        string friend_name;
        cin >> friend_name;
	char friend_sex;
	friend_sex=0;
	cout << "Please specified your's friend gender, write 'm' if male or 'f' if female: \n";
        cin >> friend_sex;
	int age;
	cout << "Please enter age of recipient only in int type :\n";
        cin >> age;
	string simple_error("you're kidding!");
	cout << "Dear " << recipient_name << ",\n";
	cout << "How are you? I am fine. I miss you.  " << "\n";
	cout << "I have two wonderful dogs and I think" << "\n"; 
        cout << "that they are the best pets because  " << "\n";
        cout << "dogs are loyal, faithful and reliable friends!" << "\n";
        cout << "Have you seen " << friend_name << " lately?\n";
	
	if(friend_sex =='m')
	{
		cout << "If you see " << friend_name << " please ask him to call me.\n";
	}
	if(friend_sex =='f')
	{
		cout << "If you see " << friend_name << " please ask her to call me.\n";
	}
	cout << "I heard you just had a birthday and you are " << age << " years old.\n";
	if(age<=0 || age>=110)
	{
	 cout << simple_error;
	}
	else
	if(age<=12)
	{
	 cout << "Next year you will be " << age+1 << ".\n";
	}
	else
	if(age==17)
	{
	 cout << "Next year you will be able to vote.\n";
	}
	else
	if(age>70 && age<110) 
	{
	 cout << "I hope you are enjoying retirement.\n";
	}

	cout << endl << endl;
	cout << "Your sincerely " << first_name << ".\n"; 
}

