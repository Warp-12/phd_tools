#include "std_lib_facilities.hpp"
#include "Simple_window.hpp"
#include "Graph.hpp"
#include <iostream>

bool isprime (int arg) {
    int x = 1;
    for (int i = 2; i < arg; ++i) x = (x*i)%arg;
    return (x == arg-1);
}

class twin {
    static int offset, a, b, N;
    static double m, n;
public:
    static void set_consts (int p1, int p2, int p3, int p4,
            double q1, double q2) {
        offset = p1;
        a = p2;
        b = p3;
        N = p4;
        m = q1;
        n = q2;
    }
    int x, y;
    twin (double angle) {
        double x0, y0;
        double X = cos(angle), Y = sin(angle);
        x0 = pow(abs(X),2.0/m);
        if (X < 0.0) x0 = -x0;
        x = int(offset+a+a*x0+0.5);
        y0 = pow(abs(Y),2.0/n);
        if (Y < 0.0) y0 = -y0;
        y = int(offset+b+b*y0+0.5);
    }
};
int twin::offset, twin::a, twin::b, twin::N;
double twin::m, twin::n;

int main () {
    const int offset = 10, count = 100;
    int a, b, N;
    double m, n;
    cout << "Input the sizes in pixels\n";
    cin >> a >> b;
    if (a < 10 || a > 500 || b < 10 || b > 500)
        error("The sizes must be between 10 and 500 pixels\n");
    cout << "Input the exponents (as floating-point numbers)\n";
    cin >> m >> n;
    if (m <= 1.0 || m > 1000000 || n <= 1.0 || n > 1000000)
        error("The exponents must be above 1.0 and no more than 1000000\n");
    cout << "Input the number of points\n";
    cin >> N;
    if (N < 10 || ! isprime(N))
        error("The number of points must be a prime above 10\n");
    double twopi = 8.0*atan(1.0);

    twin::set_consts(offset,a,b,N,m,n);
    Point top_left(0,0);
    Simple_window win(top_left,2*a+2*offset,2*b+2*offset,"Superellipse");
    // Because it uses integers and checks for parallelism, Polygon isn't
    // really suitable
    Closed_polyline ell;
    ell.set_color(Color::cyan);
    for (int i = 0; i < count; ++i) {
        twin z((twopi*i)/count);
        ell.add(Point(z.x,z.y));
    }
    win.attach(ell);
    Closed_polyline two;
    two.set_color(Color::dark_red);
    int k = N/7;
    for (int i = 0; i < N; ++i) {
        twin z((twopi*k)/N);
        two.add(Point(z.x,z.y));
        k = (k+N/3)%N;
    }
    win.attach(two);
    win.wait_for_button();
}
