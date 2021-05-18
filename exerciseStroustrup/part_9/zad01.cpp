// Zrobic drill ze str 886.

// Uwaga: termin oddania zadan z tygodnia_09 (oraz tygodnia_10) to 8 maja, godzina 23:59 !!!

// Uwaga: dnia 26 kwietnia nie bedzie wykladu, cwiczenia odbeda sie normalnie. Tzn bedzie wyklad e-learningowy: prezentacja i rozdzial z ksiazki do przeczytania samodzielnie.

// Uwaga: Nastepny wyklad bedzie 10 maja !!!, cwiczenia odbeda sie normalnie.

#include "std_lib_facilities.hpp"

int main()
{
    ifstream infile("input.txt");
    if(!infile) cerr << "No such file\n";
    const string pattern_st = "\\w{2}\\s*\\d{5}(-\\d{4})?";
    regex pat(pattern_st);
    cout << "Pattern: " << pattern_st << '\n';

    int line_counter=0;
    string line;
    while (getline(infile,line))
    {
        line_counter++;
        smatch matches;
        if (regex_search(line,matches,pat))
        {
            cout << line_counter << ": " << matches[0] << '\n';
        if (1<matches.size() && matches[1].matched)
            cout << "\t: " << matches[1] << '\n';

        }
    }
 }


