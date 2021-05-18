#include "arc.hpp"
#include "Graph.hpp" 
 namespace Graph_lib
{
 
Arc::Arc (Point c, int r0, int s0, int e0) :

	x(c.x), y(c.y), r(r0), s(s0), e(e0) 
{	
	void Arc::draw_lines() const
	{
        	if (color().visibility()) fl_arc(x,y,2*r,2*r,s,e);
	}
}
}
