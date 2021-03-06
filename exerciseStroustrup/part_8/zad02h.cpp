#include "std_lib_facilities.hpp"

void ai_func(const int ai[], int sz)
{
    cout << "Number of elements in ai: " << sz << "\n";
}

void vi_func(const vector<int>& vi)
{
    cout << "Number of elements in vi: " << vi.size() << "\n";
}

void li_func(const list<int>& li)
{
    cout << "Number of elements in li: " << li.size() << "\n";
}

int main()
try {
    int ai[] = { 1, 2, 3, 4, 5 };
    ai_func(ai,sizeof(ai)/sizeof(*ai));

    vector<int> vi;
    for (int i = 1; i<6; ++i) vi.push_back(i);
    vi_func(vi);

    list<int> li;
    for (int i = 1; i<6; ++i) li.push_back(i);
    li_func(li);
}
catch (Range_error& re) {
    cerr << "bad index: " << re.index << "\n";
}
catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
}
catch (...) {
    cerr << "exception\n";
}

