// Zrobic drill ze str 798.

#include "std_lib_facilities.hpp"

//------------------------------------------------------------------------

struct Item {
 
        string name;
        int iid;
        double value;
        Item() :name(), iid(0), value(0) { }
        Item(string n, int i, double v) :name(n), iid(i), value(v) { }


};

//----------------------------------------------------------------------

ostream& operator<<(ostream& os, const Item& it)
{
        return os << it.name << '\t'
                  << it.iid << '\t'
                  << it.value;
}

//-----------------------------------------------------------------------

istream& operator>>(istream& is, Item& it)
{
            string ss;
            int ii;
            double dd;
            is >> ss >> ii >> dd;
            if(!is) return is;
            it =Item{ss, ii, dd};
            return is;
}

//------------------------------------------------------------------------

struct Sort_val {
       bool operator()(const Item& a, const Item& b)
                {
                       return a.value > b.value;
                }
};

//------------------------------------------------------------------------

class Smaller {
      double val;
public:
            Smaller(double vv) : val{vv} { }
            bool operator()(const Item& x) const { return x.value < val; }
};

//------------------------------------------------------------------------

class    Find_by_name {
         string name;
public:
         Find_by_name(const string& nn) : name{nn} { }
         bool operator()(const Item& x) const { return x.name == name; }
};

//------------------------------------------------------------------------

class   Find_by_iid {
        int iid;
public:
        Find_by_iid(int id) : iid{id} { }
        bool operator()(const Item& x) const { return x.iid == iid; }
};

//------------------------------------------------------------------------

template<typename C>
void print(const C& c, char sep = ' ')
{
        for (const auto& a : c)
            cout << a << sep  << '\n';
}


//------------------------------------------------------------------------

void f(map<string, int>& m)
{
    string s;
    int i=0;
    while(m.size() < 10)
    {
        cin >> s >> i;
        m.insert(make_pair(s, i));
    }
}


//------------------------------------------------------------------------
template<typename T, typename U>
void print_map(const map<T,U>& m)
{
            cout << "Map contents:" << '\n';
                for(const auto& a : m)
                {
                    cout << a.first << '\t' << a.second << '\n';
                }
}

//------------------------------------------------------------------------
class Less{
    double v;
public:
    Less(double vv) : v{vv} { }
    bool operator()(const double val){return val < v;}
};


//------------------------------------------------------------------------

template<typename C>
void print_vec(const C& c, char sep = '\n')
{
    cout << "Container elements: \n";
        for (const auto ele : c)
            cout << ele << sep  << '\n';
}
//------------------------------------------------------------------------

int main()
{
try{
const string iname {"input.txt"};

    ifstream ifs {iname};
      if (!ifs) throw runtime_error("Could not read from file: " + iname);
    vector<Item> vi;
         for(Item ii; ifs >> ii;)
         {
             vi.push_back(ii);
         }
    
    list<Item> li (vi.size());

    copy(vi.begin(), vi.end(), li.begin());

                sort(vi.begin(), vi.end(),
                        [](const Item& a, const Item& b) { return a.name < b.name; });        
                sort(vi.begin(), vi.end(),
                        [](const Item& a, const Item& b) { return a.iid < b.iid; });
                sort(vi.begin(), vi.end(), Sort_val());

                Item tmp {"shoes", 91, 1.13};  

                vi.insert( find_if(vi.begin(), vi.end(), Smaller(tmp.value)),tmp);

                tmp = Item{"Photos", 88, 449.95};
       
                        vi.insert( find_if(vi.begin(), vi.end(), Smaller(tmp.value)), tmp);

                        vi.erase(find_if(vi.begin(), vi.end(), Find_by_name("descs")));
                        vi.erase(find_if(vi.begin(), vi.end(), Find_by_name("cups")));

                        vi.erase(find_if(vi.begin(), vi.end(), Find_by_iid(12)));
                        vi.erase(find_if(vi.begin(), vi.end(), Find_by_iid(87)));
            
           print(li, '\n');

            li.sort([](const Item& a, const Item& b) { return a.name < b.name;   });
            li.sort([](const Item& a, const Item& b) { return a.iid < b.iid;     });
            li.sort([](const Item& a, const Item& b) { return a.value > b.value; });


            tmp = {"horse", 99, 1.34};
            li.insert(find_if(li.begin(), li.end(), Smaller(tmp.value)), tmp);

            tmp = {"oven", 988, 49.95};
            li.insert(find_if(li.begin(), li.end(), Smaller(tmp.value)), tmp);
             
                li.erase(find_if(li.begin(), li.end(), Find_by_name("tablet")));
                li.erase(find_if(li.begin(), li.end(), Find_by_name("phone")));

                li.erase(find_if(li.begin(), li.end(), Find_by_iid(124)));
                li.erase(find_if(li.begin(), li.end(), Find_by_iid(45)));

                print(li, '\n');

                map<string, int> msi;

               msi["Ala"]      = 4;
               msi["Koko"]     = 34;
               msi["Tera"]     = 6;
               msi["Gogo"]     = 38;
               msi["Lili"]     = 64;
               msi["Ann"]      = 62;
               msi["Baracuda"] = 33;
               msi["Yoda"]     = 24;
               msi["Solo"]     = 13;
               msi["Sitripio"] = 9;

               print_map(msi);

               msi.erase(msi.begin(), msi.end());
            
               print_map(msi);

               f(msi);

               print_map(msi);

    int tot= accumulate(msi.begin(), msi.end(), 0 ,
            [](int sum, const pair<string,int>& p) 
            {return sum+=p.second;});

    cout << "Total of integers: " << tot << '\n';


    map<int, string> mis;

    for(const auto& a: msi)
    { 
        mis[a.second] = a.first;
    
    }
    print_map(mis);



const string inamefloat {"input_f.txt"};

ifstream ifst{inamefloat};

if(!ifst)throw runtime_error("Could not read from file: " + inamefloat);

vector<double> vd;

for(double d; ifst >> d;)
{
    vd.push_back(d);
}

 print_vec(vd);

vector<int> vic (vd.size());

    copy(vd.begin(), vd.end(), vic.begin());

for(int i=0; i< vd.size(); i++)
{
    cout << vd[i] << '\t' << vic[i] << '\n';

}
double double_sum = accumulate(vd.begin(), vd.end(), 0.0);
    cout << "Sum of vector of double: " << double_sum << '\n';

double diff_sum = inner_product(vd.begin(), vd.end(), vic.begin(),
                                0.0, plus<double>(), minus<double>());

    cout << "The difference between the sum of vd and sum of vic: " << diff_sum << '\n';
reverse(vd.begin(), vd.end());

    print_vec(vd);
double vd_mean = double_sum /vd.size();
    
    cout << " The mean of vd is: " << vd_mean << '\n';

    vector<double> vd2(vd.size());

auto it = copy_if(vd.begin(), vd.end(), vd2.begin(), Less(vd_mean));

vd2.resize(distance(vd2.begin(), it));

print_vec(vd2);
    sort(vd.begin(), vd.end());

    print_vec(vd);

}
catch(exception& e) {
        cerr << "Exception: " << e.what() << '\n';
            return 1;
}
catch(...) {
        cerr << "Unknown exception\n";
            return 2;
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
