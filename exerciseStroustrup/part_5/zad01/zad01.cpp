
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

    Point tl(150,150);           // to become top left  corner of window

    Simple_window win(tl,800,400,"My window");    // make a simple window

    win.wait_for_button();       // give control to the display engine
    Axis xa (Axis::x,Point{20,320},300,10,"x axis");
    win.attach(xa);
    win.set_label("My window #2");
    win.wait_for_button();       // give control to the display engine
    
    Axis ya (Axis::y, Point{20,320},280,30,"y axis");
    ya.set_color(Color::dark_yellow);
    ya.label.set_color(Color::dark_magenta);
    win.attach(ya);
    win.set_label("My window #3");

    Function cosine (cos,0,100,Point{20,180},100,20,20); 
    cosine.set_color(Color::blue);
    win.attach(cosine);
    win.set_label("My window #4");
    
    Polygon poly;                // make a shape (a polygon)

    poly.add(Point(300,200));    // add a point
    poly.add(Point(275,175));    // add a point
    poly.add(Point(350,100));    // add another point
    poly.add(Point(425,175));    // add a point
    poly.add(Point(400,200));    // add a third point 

    poly.set_color(Color::dark_blue);  // adjust properties of poly
    poly.set_style(Line_style::dot);
    win.attach (poly);           // connect poly to the window
    win.set_label("My window #5");
    win.wait_for_button();       // give control to the display engine
    
    Rectangle r (Point{200,200}, 100,40);
    win.attach(r);
    win.set_label("My window #6");
    win.wait_for_button();

    Closed_polyline poly_rect;
    poly_rect.add(Point(100,50));
    poly_rect.add(Point(200,50));
    poly_rect.add(Point(200,130));
    poly_rect.add(Point(100,100));
    poly_rect.add(Point(125,75));
    win.attach(poly_rect);
    win.set_label("My window #7");
    win.wait_for_button();

    r.set_fill_color(Color::red);
    poly.set_style(Line_style(Line_style::dashdotdot,4));
    poly_rect.set_style(Line_style(Line_style::dashdot,2));
    poly_rect.set_fill_color(Color::yellow);
    win.set_label("My window #8");
    win.wait_for_button();
    
    Text t(Point(150,150),"Hello, graphical world!");
    win.attach(t);
    win.set_label("My window #9");
    win.wait_for_button();

    t.set_font(::Graph_lib::Font::times_italic);
    t.set_font_size(14);
    win.set_label("My window #10");
    win.wait_for_button();

    Image ii (Point(80,30),"rocket.jpg");
    win.attach(ii);
    win.set_label("My window #11");
    win.wait_for_button();


    ii.move(100,150);
    win.set_label("My window #12");
    win.wait_for_button();
   
    Circle c (Point(100,200),50);
    Ellipse e (Point(100,200),75,25);
    e.set_color(Color::dark_blue);
    Mark m (Point(100,200),'x');

    ostringstream oss;
    oss << "screen size: " << x_max() << "*" << y_max()
         << ": window size: " << win.x_max() << "*" << win.y_max();
    Text sizes (Point(100,20), oss.str());

    Image cal (Point(425,200),"CPP.gif");
    cal.set_mask(Point(10,10),800,200);
    win.attach(c);
    win.attach(m);
    win.attach(e);

    win.attach(sizes);
    win.attach(cal);

    win.set_label("My window #13");
    win.wait_for_button();
}

//------------------------------------------------------------------------------
