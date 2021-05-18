
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
    
    Graph_lib::Rectangle rect(Point(100,100),150,100);
    rect.set_color(Color::blue);
    win.attach(rect);

    Graph_lib::Polygon polyg;
    polyg.add(Point(100,250));
    polyg.add(Point(250,250));
    polyg.add(Point(250,300));
    polyg.add(Point(100,300));
    polyg.set_color(Color::red);
    win.attach(polyg);

    win.wait_for_button();

    Graph_lib::Rectangle name_rect(Point(300,25),100,30);
    win.attach(name_rect);

    Text t(Point(325,50),"Howdy!");
    win.attach(t);
    win.set_label("My window #2");
    win.wait_for_button();
    
    Closed_polyline letter_p;
    letter_p.add(Point(100,100));
    letter_p.add(Point(150,100));
    letter_p.add(Point(170,125));
    letter_p.add(Point(170,150));
    letter_p.add(Point(150,175));
    letter_p.add(Point(100,175));
    letter_p.add(Point(100,250));
    letter_p.set_color(Color::yellow);
    letter_p.set_style(Line_style(Line_style::dash,4));
    win.set_label("My window #3");   
    win.attach(letter_p);

    Open_polyline letter_v;
    letter_v.add(Point(190,100));
    letter_v.add(Point(215,250));
    letter_v.add(Point(240,100));
    letter_v.set_color(Color::green);
    letter_v.set_style(Line_style(Line_style::dashdot,4));
    win.set_label("My window #4");   
    win.attach(letter_v);

    
    win.wait_for_button();


    Graph_lib::Rectangle rect1(Point(300,100),100,100);
    rect1.set_fill_color(Color::white);
    win.attach(rect1);

    Graph_lib::Rectangle rect2(Point(400,100),100,100);
    rect2.set_fill_color(Color::red);
    win.attach(rect2);

    Graph_lib::Rectangle rect3(Point(500,100),100,100);
    rect3.set_fill_color(Color::white);
    win.attach(rect3);

    Graph_lib::Rectangle rect4(Point(300,200),100,100);
    rect4.set_fill_color(Color::red);
    win.attach(rect4);

    Graph_lib::Rectangle rect5(Point(400,200),100,100);
    rect5.set_fill_color(Color::white);
    win.attach(rect5);

    Graph_lib::Rectangle rect6(Point(500,200),100,100);
    rect6.set_fill_color(Color::red);
    win.attach(rect6);

    Graph_lib::Rectangle rect7(Point(300,300),100,100);
    rect7.set_fill_color(Color::white);
    win.attach(rect7);

    Graph_lib::Rectangle rect8(Point(400,300),100,100);
    rect8.set_fill_color(Color::red);
    win.attach(rect8);

    Graph_lib::Rectangle rect9(Point(500,300),100,100);
    rect9.set_fill_color(Color::white);
    win.attach(rect9);

    win.set_label("My window #5");   
    win.wait_for_button();
    
    Circle c (Point(700,100),10);
    c.set_fill_color(Color::red);
    

    Closed_polyline poly_hex;
    poly_hex.add(Point(795,100));
    poly_hex.add(Point(700,0));
    poly_hex.add(Point(600,100));
    poly_hex.add(Point(600,300));
    poly_hex.add(Point(700,400));
    poly_hex.add(Point(795,300));
    poly_hex.add(Point(700,200));
    poly_hex.set_fill_color(Color::dark_blue);
    poly_hex.set_style(Line_style(Line_style::dashdotdot,4));
    win.attach(poly_hex);
    win.attach(c);

    win.set_label("My window #6");
    win.wait_for_button();



}
//------------------------------------------------------------------------------
