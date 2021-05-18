// Zrobic zadanie 2 ze str. 708

#include "std_lib_facilities.hpp"

//----------------------------------------------------

template<typename T, typename U>
double mult(vector<T> vt, vector<U> vu)
{
      
  double sum_mult = 0;
  
  if(vt.size() <= vu.size())
  {
      for(int i=0; i<vt.size(); i++)
      {
            sum_mult+=(vt[i] * vu[i]);
      }
      
      for(int i=0;i < vu.size(); i++)
      {
             sum_mult+=vu[i];
      }
  }
  
  else
  {
      for(int i=0; i<vu.size(); i++)
      {
         sum_mult+=(vt[i] * vu[i]);
      }
     
      for(int i=0;i < vt.size(); i++)
      {
         sum_mult+= vt[i];
      }
  }
      return sum_mult;
}

//----------------------------------------------------
template<class T>  ostream& operator<<(ostream& os, const vector<T>& v)
{
      os << "{";
      for (int i = 0; i<v.size()-1; ++i)
      os << ' ' << v[i] << ',';
      os << ' ' << v[v.size()-1] << " }";
      return os;
}

//----------------------------------------------------

int main()
{
  vector<double> vt;

  for(int i=0; i<10; i++)
  {
      vt.push_back(i);

  }
      cout << "vt: " << vt << '\n';
   
  vector<int> vu;
  
  for(int i=0; i<7; i++)
  {
      vu.push_back(i);
  }
      cout << "vt: " << vt << '\n';

   cout <<  "multiply(vt,vu): " << mult(vt,vu) << '\n';       
   cout <<  "multiply(vu,vt): " << mult(vu,vt) << '\n';       
 
 
return 0;
}

