// Zrobic zad 1 ze str. 887

#include "std_lib_facilities.hpp"

//=============================================================================================
using Line_iter = vector<string>::const_iterator;

class Message {
        Line_iter first;
            Line_iter last;
    public:
                Message(Line_iter p1, Line_iter p2) : first{p1}, last{p2} { }
                    Line_iter begin() const { return first; }
                        Line_iter end() const { return last; }
};
//==============================================================================================


using Mess_iter = vector<Message>::const_iterator;

struct Mail_file {
        string name;                   
            vector<string> lines;     
                vector<Message> m;             

                    Mail_file(const string& s);    

                        Mess_iter begin() const { return m.begin(); }
                            Mess_iter end() const { return m.end(); }
};


//------------------------------------------------------------------------------

Mail_file::Mail_file(const string& fname)
{
        ifstream ifs {fname};
            if (!ifs) 
            {
                   cerr << "Could not read from file " << fname << '\n';
                   exit(1);
            }

                for (string s; getline(ifs,s); )
                            lines.push_back(s);

                    auto first = lines.begin();
                        for (auto p = lines.begin(); p != lines.end(); ++p)
                        {
                                    if (*p == "----")
                                    {
                                                 if (p != first)
                                                 m.push_back(Message{first,p});
                                                 first = p + 1;
                                    }
                        }
}
//------------------------------------------------------------------------------
int is_prefix(const string& s, const string& p)
{
        int n = p.size();
            if (string(s,0,n)==p) return n;
                return 0;
}

//------------------------------------------------------------------------------


bool find_from_addr(const Message* m, string& s)
{
        for (Line_iter p = m->begin(); p!=m->end(); ++p)
                    if (int n = is_prefix(*p,"From: ")) {
                                    s = string(*p,n);
                                                return true;
                                                        }
            return false;
}

//------------------------------------------------------------------------------
string find_subject(const Message* m)
{
    for (Line_iter p = m->begin(); p!=m->end(); ++p)
            if (int n = is_prefix(*p,"Subject: ")) return string(*p,n);
                return "";
                }


//------------------------------------------------------------------------------


int main()
{
try {
        cout << "Enter an email file to process:\n";
            string fname;
                cin >> fname;

                    Mail_file mfile {fname};

                             multimap<string,const Message*> sender;
                        
                                for (const auto& m : mfile)
                                {
                                         string s;
                                               if (find_from_addr(&m,s))
                                               {
                                                             sender.insert(make_pair(s,&m));
                                
                                               }
                                }
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
