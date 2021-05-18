// Zrobic zad 3 ze str. 887

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
typedef vector<Message>::const_iterator Mess_iter;

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
string find_prefix(const Message* m, const string& s)
{
        regex pat("^" + s + "(.*)$");
            smatch matches;
                    for (Line_iter p = m->begin(); p!=m->end(); ++p)
                                if (regex_match(*p,matches,pat))
                                                return matches[1];
                        return "";
}

string find_from_addr(const Message* m)
{
        return find_prefix(m,"From: ");
}

string find_subject(const Message* m)
{
        return find_prefix(m,"Subject: ");
}




//------------------------------------------------------------------------------


int main()
{
try {
        cout << "Enter an email file to process:\n";
            string fname;
                cin >> fname; 
                cin.ignore();
                    Mail_file mfile {fname};

                             multimap<string,const Message*> sender;
                        
                                for (Mess_iter p = mfile.begin(); p!=mfile.end(); p++)
                                {
                                     const Message& m= *p;
                                               string s = find_from_addr(&m);
                                         if(s!="")      
                                                sender.insert(make_pair(s,&m));
                                
                                               
                                }
 cout << "Enter sender: ";
     string sname;
         getline(cin,sname);
             typedef multimap<string,const Message*>::const_iterator MCI;
                 pair<MCI,MCI> pp = sender.equal_range(sname);
                     for (MCI p = pp.first; p!=pp.second; ++p)
                         cout << find_subject(p->second) << '\n';


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
