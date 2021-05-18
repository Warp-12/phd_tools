#include "std_lib_facilities.hpp"
void swap_v(int a, int b){int temp; temp =a; a=b; b=temp;}
void swap_r(int& a,int& b){int temp; temp =a; a=b; b=temp;}
//void swap_cr(const int& a, const int& b){int temp; temp =a; a=b; b=temp;} //Function does not compile because we trying only to read reference. we can discart it 
int main()
{
int x =7;
int y =9;
//swap_v(x,y);//Compile but dont swap, because manage on copies of aruments
swap_r(x,y);// compile and swap  result
//swap_v(7,9);//compile but dont swap as temporary objects that are making inside function to store the argumrnts are destroyed
//swap_r(7,9);//Not compile as a referencecould not be initialized since there no object that be refered

cout << "x is now " << x << " and y is now " << y << "\n";
const int cx = 7;
const int cy = 9;
//swap_v(cx,cy);// Compiles because we are pasing copies of variables but it doesnt swap
//swap_r(cx,cy);Does not compile because we are trying to make non-const reference to const variable

// These two calls also causes truncation of its arguments.
// swap_v(7.7, 9.9);   // Compiles but does nothing. Same reason as swap_v(7,9)
// swap_r(7.7, 9.9);   // Does not compile. Same reason as swap_r(7,9) 

cout << "cx is now " << cx << " and cy is now " << cy << "\n";

double dx = 7.7;
double dy = 9.9;
//swap_v(dx,dy); Compile but does not swap same as previous swap_v calls.
//swap_r(dx,dy);//It does not compile, bad conversation from double to int
 cout << "dx is now " << dx << " and dy is now " << dy << "\n";

return 0;
}


