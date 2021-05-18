// Zadanie 9: wykonac exercise 9 ze str. 409, lecz bez rozdzielania na dwa programy:

// niech program jako dane wejściowe otwiera plik zad09.input,
// wynik binarny niech zapisuje do pliku zad09.binary, w drugiej
// części (w tym samym programie) następnie niech czyta
// zad09.binary i zapisuje końcowy wynik do pliku zad09.output

#include "std_lib_facilities.hpp"
const string binary_f="zad09.binary";
string name_i, name_o;

void convert_into_binary(const string& name)
{            
		ifstream ifst(name.c_str());
                if(!ifst) error("can't open input file ", name);

                ofstream outfst(binary_f.c_str(), ios_base::binary);
                if(!outfst) error("can't open output file ", binary_f);

		char ch;

                while(ifst.get(ch))
                {
			outfst.write(as_bytes(ch),sizeof(char));
			
                }
}
void convert_from_binary(const string& name)
{
				
                ofstream outfst(name.c_str());
                if(!outfst) error("can't open output file ", name);
                
		ifstream ifst(binary_f.c_str(),ios_base::binary);
                if(!ifst) error("can't open input file ", binary_f);
                
		char ch;
		while(ifst.read(as_bytes(ch), sizeof(char)))
                {
			outfst << ch;
			
                }
}
int main()
{
	 try{
		name_i="zad09.input";
		convert_into_binary(name_i);
		
		name_o="zad09.output";
		convert_from_binary(name_o);
		
		cout << "Converting done!\n";
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

