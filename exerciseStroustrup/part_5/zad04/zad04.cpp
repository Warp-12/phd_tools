
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.hpp"    // get access to our window library
#include "Graph.hpp"            // get access to our graphics library facilities

//------------------------------------------------------------------------------


int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib
    
    Point tl(200,100);
    Simple_window win(tl,1000,800,"My window");
    win.wait_for_button();
    win.set_label("My window ");
    Lines grid;
    int x_size = 800;
    int y_size = 800;
    for (int i = 100; i<=x_size; i+=100) {
        grid.add(Point(i,0),Point(i,y_size));
        grid.add(Point(0,i),Point(x_size,i));
    }
    win.attach(grid);
    win.wait_for_button();
    win.set_label("My window #1");

    Vector_ref<Graph_lib::Rectangle> vr;
    for (int i = 0; i<8; ++i) {
        vr.push_back(new Graph_lib::Rectangle(Point(i*100,i*100),101,101));
        vr[vr.size()-1].set_fill_color(Color::red);
        win.attach(vr[vr.size()-1]);
    }
    win.wait_for_button();
    win.set_label("My window #2");

    Image rocket1(Point(200,0),"rocket.jpg");
    win.attach(rocket1);
    Image rocket2(Point(500,200),"rocket.jpg");
    win.attach(rocket2);
    Image rocket3(Point(100,500),"rocket.jpg");
    win.attach(rocket3);

    Image bd(Point(0,0),"bd.jpg");
    win.attach(bd);

    int x = 0;
    int y = 0;
    int dx = 0;
    int dy = 0;

    while (true) 
    {
        x = randint(8);
        y = randint(8);
        dx = 100*x - bd.point(0).x;
        dy = 100*y - bd.point(0).y;
        bd.move(dx,dy);
	
        win.wait_for_button();
        win.set_label("My window #3");
    }
}
//------------------------------------------------------------------------------
