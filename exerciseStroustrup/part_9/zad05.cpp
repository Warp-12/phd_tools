// Zrobic zad 8 ze str 887.

#include "std_lib_facilities.hpp"

int main()
{
  try 
  {
      while(true)
      {
                 string patt;
                 cout << "Enter pattern (q to exit): ";
                          
                 getline(cin,patt);   
                          if (patt=="q") break;
                          regex pattern;
                          
                          try
                          {
                               pattern = patt; 
                          }
                                
                          catch(regex_error)
                          {
                              cerr << "Not a valid regular expression: " << patt << '\n';
                              continue;
                          }

                 string fname;
                 cout << "Enter file name: ";
                   
                 getline(cin,fname);
                    ifstream ifs(fname);
                      if (!ifs) throw runtime_error("Can't open " + fname);
                 string line;
                   int line_counter = 0;
                        while (getline(ifs,line))
                        {
                              line_counter++;
                              smatch matches;
                                if(regex_search(line,matches,pattern))
                                      cout << setw(3) << line_counter << ": " << line << '\n';
                        }
      }
  }
catch (exception& e) {
        cerr << "Exception: " << e.what() << '\n';
}
catch (...) {
        cerr << "Exception\n";
}

}

