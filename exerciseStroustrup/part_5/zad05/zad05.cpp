//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.hpp"    // get access to our window library
#include "Graph.hpp"            // get access to our graphics library facilities
#include "arc.hpp"
//------------------------------------------------------------------------------
/*namespace Graph_lib
{
class Arc : public ::Graph_lib::Shape {
    int x, y, r, s, e;
    // We really should check the arguments ....
public:
    Arc (Point c, int r0, int s0, int e0) :
        x(c.x), y(c.y), r(r0), s(s0), e(e0) {}
    void draw_lines () const {
       if (color().visibility()) fl_arc(x,y,2*r,2*r,s,e);
    }
};
}*/

int main ()
{
  using namespace Graph_lib;
    Point top_left(200,100);
    Simple_window win(top_left,800,800,"Boxed in");
    win.wait_for_button();
    win.set_label("My window ");
  
   ::Graph_lib::Arc arc1(Point(100,200),100,300,500);
    win.attach(arc1);
    win.wait_for_button();
    win.set_label("My windowa #1");

}
//------------------------------------------------------------------------------
