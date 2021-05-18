// zadanie 8: wykonac Exercise 13 ze str. 301

#include "std_lib_facilities.hpp"

void print(const string& label, const vector<int>& data)
{
    cout << label << ": { ";
    for (int i : data)
        cout << i << ' ';
    cout << "}\n";
}

void print(const string& label, const vector<string>& data)

{
    cout << label << ": { ";
    for (string i : data)
        cout << "\"" << i << "\" ";
    cout << "}\n";
}

vector<int> gen_length_vector(const vector<string>& v)

{
    vector<int> lv;

    for (string s : v)
        lv.push_back(s.size());

    return lv;
}

vector<string> longest_string(const vector<string>& v)

{
   if (v.size() == 0) error("longest_string(): empty vector");

   size_t max{v[1].size()};  

   for (string s : v)
       if (s.size() > max) max = s.size();

   vector<string> lv;
   for (string s: v)
       if (s.size() == max) lv.push_back(s);

   return lv;
}

vector<string> shortest_string(const vector<string>& v)
{
   if (v.size() == 0) error("shortest_string(): empty vector");

   size_t min{v[1].size()};    
   for (string s : v)
       if (s.size() < min) min = s.size();

   vector<string> sv;
   for (string s: v)
       if (s.size() == min) sv.push_back(s);

   return sv;
}

string first_string(const vector<string>& v)

{
    if (v.size() == 0) error("first_string(): empty vector");

    vector<string> tmp{v};
    sort(tmp.begin(), tmp.end());
    return tmp[0];
}

string last_string(vector<string> v)

{
    if (v.size() == 0) error("last_string(): empty vector");

    string last{v[0]};
    for (string s : v)
        if (s > last) last = s;

    return last;
}

int main(){
try
{
    vector<string> data{"one", "two", "three", "four", "five", "six", "seven"};

    print("The strings vector is", data);
    print("The corresponding lengths are", gen_length_vector(data));
    print("The longest strings are", longest_string(data));
    print("The shortest strings are", shortest_string(data));
    cout << "The first lexicographically string is: \""
         << first_string(data) << "\"\n";
    cout << "The last lexicographically string is: \""
         << last_string(data) << "\"\n";

    return 0;
}
catch(exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch(...)
{
    cerr << "Unknown exception!!\n";
    return 2;
}
}
