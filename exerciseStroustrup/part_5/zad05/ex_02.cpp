#include "std_lib_facilities.h"
#include "Simple_window.h"
#include "Graph.h"
#include <iostream>

class Arc : public Shape {
    int x, y, r, s, e;
    // We really should check the arguments ....
public:
    Arc (Point c, int r0, int s0, int e0) :
        x(c.x), y(c.y), r(r0), s(s0), e(e0) {}
    void draw_lines () const {
       if (color().visibility()) fl_arc(x,y,2*r,2*r,s,e);
    }
};

class Box : public Shape {
// This is made to look like Rectangle; Line does not have a draw_lines()
// method, so cannot be used
    Lines lines;
    Vector_ref<Arc> arcs;
public:
    Box (Point bl, int h, int w) {
        if (h < 4 || w < 4) error("Boxes must be at least 4x4");
        double r;
        r = h/4;
        if (r > w/4) r = w/4;
        lines.add(Point(bl.x+r,bl.y),Point(bl.x+w-r,bl.y));
        lines.add(Point(bl.x+r,bl.y+h),Point(bl.x+w-r,bl.y+h));
        lines.add(Point(bl.x,bl.y+r),Point(bl.x,bl.y+h-r));
        lines.add(Point(bl.x+w,bl.y+r),Point(bl.x+w,bl.y+h-r));
        arcs.push_back(
            new Arc(Point(bl.x,bl.y+h-2*r),r,180,270));
        arcs.push_back(
            new Arc(Point(bl.x+w-2*r,bl.y+h-2*r),r,270,360));
        arcs.push_back(
            new Arc(Point(bl.x,bl.y),r,90,180));
        arcs.push_back(
            new Arc(Point(bl.x+w-2*r,bl.y),r,0,90));
    }
    void draw_lines () const {
        for (int i = 0; i < int(arcs.size()); ++i) arcs[i].draw_lines();
        lines.draw_lines();
    }
};

int main () {
    Point top_left(200,100);
    Simple_window win(top_left,800,800,"Boxed in");
    Box box1(Point(100,200),300,500);
    win.attach(box1);
    Box box2(Point(150,250),50,100);
    win.attach(box2);
    win.wait_for_button();
}
