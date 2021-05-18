
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.hpp"    // get access to our window library
#include "Graph.hpp"            // get access to our graphics library facilities

//------------------------------------------------------------------------------

double sgn(double d)
{
    if (d>0) return 1;
    else if (d<0) return -1;
    else return 0;
}

int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib
    
    int a = 4;
    int b = 4;
    double m = 0.5;
    double n = 0.5;
    int N = 50;

    const double pi = 3.14159;
    a = 100 * a;  
    b = 100 * b;

    Point tl(300,25);
    Simple_window win(tl,a*2+20,b*2+20,"Superellipse");

    vector<Point> points;

    for (double theta = 0; theta < 2*pi; theta += 2*pi/N) {
        double x = pow(abs(cos(theta)),2/m) * a * sgn(cos(theta)) + a + 10;
        double y = pow(abs(sin(theta)),2/n) * b * sgn(sin(theta)) + b + 10;
        points.push_back(Point(x,y));
    }

    Open_polyline inside1;
    for (int i = 0; i<points.size()/4; ++i) {
        inside1.add(points[i]);
        for (int j = i; j<points.size(); ++j) {
            if (i!=j) {
                inside1.add(points[j]);
                inside1.add(points[i]);
            }
        }
    }
    inside1.set_color(Color::red);
    win.attach(inside1);

    Open_polyline inside2;
    for (int i = points.size()/4; i<points.size()/2; ++i) {
        inside2.add(points[i]);
        for (int j = i; j<points.size(); ++j) {
            if (i!=j) {
                inside2.add(points[j]);
                inside2.add(points[i]);
            }
        }
    }
    inside2.set_color(Color::green);
    win.attach(inside2);

    Open_polyline inside3;
    for (int i = points.size()/2; i<3*points.size()/4; ++i) {
        inside3.add(points[i]);
        for (int j = i; j<points.size(); ++j) {
            if (i!=j) {
                inside3.add(points[j]);
                inside3.add(points[i]);
            }
        }
    }
    inside3.set_color(Color::blue);
    win.attach(inside3);

    Open_polyline inside4;
    for (int i = 3*points.size()/4; i<points.size(); ++i) {
        inside4.add(points[i]);
        for (int j = i; j<points.size(); ++j) {
            if (i!=j) {
                inside4.add(points[j]);
                inside4.add(points[i]);
            }
        }
    }
    inside4.set_color(Color::yellow);
    win.attach(inside4);

    Closed_polyline superellipse;
    for (int i = 0; i<points.size(); ++i)
        superellipse.add(points[i]);
    superellipse.set_style(Line_style(Line_style::dot,4));
    win.attach(superellipse);

win.wait_for_button();

}
//------------------------------------------------------------------------------
