// zadanie 5: wykonac Exercise 11 ze str.129

#include "std_lib_facilities.hpp"

int prime(int n)
{
  bool is_prime = true;

  for(int i = 2; i <= n/2; i++)
  {
      if(n % i == 0)
      {
          is_prime = false; break;
      }
  }
      if(is_prime){return 0;}
      else        {return 1;}
}
vector<int> primes={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};

vector<int> my_prime;

int main()
{
    for(int i=2; i<=100; i++)
    {
        if(prime(i)==0)
        {
               my_prime.push_back(i);

               for(int i; i<my_prime.size(); i++)
               {
                    cout << "Prime number from my calculated vector: " << my_prime[i] << " prime number from prime vector: " << primes[i] << " \n";
               }
        }
    }
}

