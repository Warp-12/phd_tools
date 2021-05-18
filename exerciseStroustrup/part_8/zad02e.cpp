
// Zrobic exercise 1 ze str.754. Kazdy "Try this" po kolei nazywac zad02a.cpp, zad02b.cpp, zad02c.cpp itd.

#include "std_lib_facilities.hpp"
//------------------------------------------------------------------------------

template<class T> class allocatr {
public:
   
    T* allocate(int n);

    void deallocate(T* p) { free(p); }

    void construct(T* p, const T& v) { new(p) T(v); }

    void destroy(T* p) { p->~T(); }
};

//------------------------------------------------------------------------------

template<class T> T* allocatr<T>::allocate(int n)
{
    T* p = static_cast<T*>(malloc(n*sizeof(T)));
    if (p==0) error("allocate: could not allocate memory");
    return p;
}

//------------------------------------------------------------------------------

template<class T, class A = allocatr<T> > class vectr {
    A alloc;    
    int sz;        
    T* elem;       
    int space;  
    public:
    vectr() : sz(0), elem(0), space(0) { }
    explicit vectr(int s);

    vectr(const vectr&);                      
    vectr& operator=(const vectr&);          

    ~vectr();                                   

    T& operator[](int n) { return elem[n]; }   
    const T& operator[](int n) const { return elem[n]; }

    T& at(int n);
    const T& at(int n) const;                 

    int size() const { return sz; }          
    int capacity() const { return space; }

    void resize(int newsize, T val = T());
    void push_back(const T& d);
    void push_front(const T& d);
    void reserve(int newalloc);

};

//------------------------------------------------------------------------------

template<class T, class A> vectr<T,A>::vectr(int s)
    : sz(s), elem(alloc.allocate(s)), space(s)
{
    for (int i = 0; i<sz; ++i)
        alloc.construct(&elem[i],T());
}

//------------------------------------------------------------------------------

template<class T, class A> vectr<T,A>::vectr(const vectr& a)
    : sz(a.sz), elem(alloc.allocate(a.sz)), space(a.sz)
{
    for (int i = 0; i<sz; ++i)
        alloc.construct(&elem[i],a.elem[i]);
}

//------------------------------------------------------------------------------

template<class T, class A>
vectr<T,A>& vectr<T,A>::operator=(const vectr<T,A>& a)
{
    if (this==&a) return *this;

    if (a.sz<=space) {          
        for (int i = 0; i<a.sz; ++i)
            alloc.construct(&elem[i],a.elem[i]);
        sz = a.sz;
        return *this;
    }

    T* p = alloc.allocate(a.sz);         
    for (int i = 0; i<a.sz; ++i)          
        alloc.construct(&p[i],a.elem[i]);
    for (int i = 0; i<sz; ++i)             
        alloc.destroy(&elem[i]);
    alloc.deallocate(elem);                 
    space = sz = a.sz;      
    elem = p;                
    return *this;
}

//------------------------------------------------------------------------------

template<class T, class A> vectr<T,A>::~vectr()
{
    for (int i = 0; i<sz; ++i)
        alloc.destroy(&elem[i]);
    alloc.deallocate(elem);
}

//------------------------------------------------------------------------------

template<class T, class A> T& vectr<T,A>::at(int n)
{
    if (n<0 || sz<=n) throw Range_error(n);
    return elem[n];
}

//------------------------------------------------------------------------------

template<class T, class A> void vectr<T,A>::resize(int newsize, T val)
{
    reserve(newsize);
    for (int i = sz; i<newsize; ++i)    
        alloc.construct(&elem[i],val);
    for (int i = newsize; i<sz; ++i) 
        alloc.destroy(&elem[i]);
    sz = newsize;
}

//------------------------------------------------------------------------------

template<class T, class A> void vectr<T,A>::push_back(const T& val)
{
    if (space==0) reserve(8);              
    else if (sz==space) reserve(2*space);  
    alloc.construct(&elem[sz],val);        
    ++sz;                                  
}

//------------------------------------------------------------------------------

template<class T, class A> void vectr<T,A>::push_front(const T& val)
{
    if (space==0) reserve(8);
    else if (sz==space) reserve(2*space);
    for (int i = sz; i>0; --i) {                
        alloc.construct(&elem[i],elem[i-1]);
        alloc.destroy(&elem[i-1]);
    }
    alloc.construct(&elem[0],val);
    ++sz;
}

//------------------------------------------------------------------------------

template<class T, class A> void vectr<T,A>::reserve(int newalloc)
{
    if (newalloc<=space) return;        
    T* p = alloc.allocate(newalloc);   
    for (int i = 0; i<sz; ++i)          
        alloc.construct(&p[i],elem[i]);
    for (int i = 0; i<sz; ++i)          
        alloc.destroy(&elem[i]);
    alloc.deallocate(elem);            
    elem = p;
    space = newalloc;
}

//------------------------------------------------------------------------------


template<class T> void diag_vec(const vectr<T>& v, const string& desc)
{
    cout << desc << "\n";
    cout << "\tsize: " << v.size() << "\n";
    cout << "\tcapacity: " << v.capacity() << "\n\t";
    for (int i = 0; i<v.size(); ++i)
        cout << v[i] << ' ';
    cout << "\n";
}

//------------------------------------------------------------------------------

int main()
try {

    vectr<int> v;
    for (int i = 0; i<5; ++i)
        v.push_back(i);
    diag_vec(v,"After push_back");
    for (int i = 15; i<20; ++i)
        v.push_front(i);
    diag_vec(v,"After push_front");
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
