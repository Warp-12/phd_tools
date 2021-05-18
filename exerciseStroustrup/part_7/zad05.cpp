// Zrobic drill ze str 707.

#include "std_lib_facilities.hpp"

//-------------------------------------------------

template<typename T> struct S {
    public:
            S(T v);
            T& get();
            const T& get() const;
            S& operator=(const T&);
  
    private:
            T val;
};

//-------------------------------------------------

template<typename T> ostream& operator<<(ostream& os, const vector<T>&);
template<typename T> istream& operator>>(istream& is, vector<T>&);

//-------------------------------------------------

template<typename T>
S<T>::S(T v)
{
    val = v;
}

//-------------------------------------------------

template<typename T> 
T& S<T>::get()
{
       return val; 
}

//-------------------------------------------------

template<typename T> 
const T& S<T>::get() const
{
       return val; 
}

//-------------------------------------------------

template<typename T> 
S<T>& S<T>::operator=(const T& t)
{
        val = t;
}

//-------------------------------------------------

template<typename T>
void read_val(T& v)
{
        cin >> v;
}

//-------------------------------------------------

template<typename T>
istream& operator>>(istream& is, vector<T>& v)
{
        for (int i=0; i<v.size(); i++)
                    is >> v[i];
            return is;
}

//-------------------------------------------------

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
        for (int i=0; i<v.size(); i++)
                    os << v[i] << " ";
            return os;
}

//-------------------------------------------------

int main()
{
    S<int> numb(int(2));
    S<char> symbol(char('k'));
    S<double> numbd(double(1.2));
    S<string> word(string("word"));
    S<vector<int>> vec(vector<int> (10));

    cout << "Type int: ";
    read_val(numb.get());
    cout << numb.get() << '\n';

    cout << "Type char: ";
    read_val(symbol.get());
    cout << symbol.get() << '\n';

    cout << "Type double: ";
    read_val(numbd.get());
    cout << numbd.get() << '\n';

    cout << "Type string: ";
    read_val(word.get());
    cout << word.get() << '\n';

    cout << "Type vector of " << vec.get().size() << " int:\n";
    read_val(vec.get());
    cout << vec.get() << '\n';

    word = "other word";
    cout << word.get() << '\n';

    vector<int> nvec(5);
    vec = nvec;
    cout << vec.get() << '\n';

}

