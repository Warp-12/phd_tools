// zadanie 4: wykonac Exercise 9 ze str. 378
// Uwaga: chodzi o to aby czytać jednocześnie z dwóch plików. W każdym z tych plików słowa są posortowane.
// Należy zapisać plik wyjściowy w którym wszystkie słowa także są posortowane oraz zawiera wszystkie słowa z obu plików.
// Uwaga: nie wolno samemu sortować tych słów, ponieważ oba pliki już są posortowane! Wywołanie polecenia sort(..) jest zakazane!

#include "std_lib_facilities.hpp"

int main()
{
	try{
		string name1, name2, outputname, word1, word2;
		outputname = "sort.txt";
		cout << "Please enter first name of file: \n";
		cin >> name1;
		cout << "Please enter second name of file: \n";
		cin >> name2;
	
		ifstream ist1(name1.c_str());
		if(!ist1) error("can't open input file ", name1);	
		
		ifstream ist2(name2.c_str());
		if(!ist2) error("can't open input file ", name2);	
		
		ofstream outst(outputname.c_str());
		if(!outst) error("can't open output file ", outputname);
	   
		ist1 >> word1;
		ist2 >> word2;

		while(true)
		{
		
			if(word1 <= word2)
			{
				outst << word1 << '\n';
				if(ist1.eof()) break;
				else ist1 >> word1;
			}
			else
			{
				outst << word2 << '\n';
				if(ist2.eof()) break;
				else ist2 >> word2;
			}

		}

		if(ist1.eof())
		{
			outst << word2 << '\n';
			while(ist2>>word2) outst << word2 << '\n';
		}
		else
		{
			outst << word1 << '\n';
			while(ist1>>word1) outst << word1 << '\n';
		}	
	   }

	catch (exception& e)
	{
	    cerr << "exception: " << e.what() << '\n';
	}
	catch (...)
	{
	    cerr << "exception\n";
	}
}

