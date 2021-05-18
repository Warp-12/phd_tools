// Zrobic zad 1 ze str 986, pliki po kolei nazywac zad05a.cpp, zad05b.cpp itd

#include "std_lib_facilities.hpp"
struct Message {
	int a;
	int b;
	int c;
};

struct Node {
	int a;
	int b;
};
void fragmentation()
{ 
	Message* m = new Message();
	Node* n1 = new Node();
	delete m;
	Node* n2 = new Node();
	Message* mm = 0;
	Node* nn1 = 0;
	Node* nn2 = 0;

	for(int i = 0;i <100;i++)
	{
		mm = new Message();
		nn1 = new Node();
		delete mm;
		nn2 =new Node();
	}
	cout << "Difference of fragmentation: " << nn2-n1 << '\n';
}

void without_fragmentation()
{
	Node* n1 = new Node();
	Node* n2 = new Node();
	Message* p = new Message();
	delete p;
	Message* mm = 0;
	Node* nn1 = 0;
	Node* nn2 = 0;
	for(int i=0; i <100; i++)
	{
		nn1 = new Node();
		nn2 = new Node();
		mm = new Message();
		delete mm;
	}
	cout << "Difference without fragmentation: " << nn2-n1 << '\n';
}
int main()
{
	cout << "sizeof(Message): " <<  sizeof(Message) << '\n';
	cout << "sizeof(Node): " <<  sizeof(Node) << '\n';
fragmentation();
without_fragmentation();
}

