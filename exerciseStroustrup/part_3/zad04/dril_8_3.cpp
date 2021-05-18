#include "std_lib_facilities.hpp"

namespace X
{
	int var {0};
        void print() { cout << "X::var value is " << var << "\n"; }
}

namespace Y
{
	int var {0};
        void print() { cout << "Y::var value is " << var << "\n"; }
}

namespace Z
{
	int var {0};
        void print() { cout << "Z::var value is " << var << "\n"; }
}

int main()
{
  X::var=7;
  X::print();
  using namespace Y;
  var = 9;
  print();
	{
		using Z::var;
		using Z::print;
		var =11;
		print();
	}

	print();
	X::print();
}
