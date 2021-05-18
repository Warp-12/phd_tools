#ifndef Arc_H
#define Arc_H
#include "Graph.hpp"
#include "arc.hpp"

namespace Graph_lib
{
class Arc : public ::Graph_lib::Shape {
    int x, y, r, s, e;
    // We really should check the arguments ....
public:
    Arc (Point c, int r0, int s0, int e0);
    void draw_lines() const ;
};
}
#endif
