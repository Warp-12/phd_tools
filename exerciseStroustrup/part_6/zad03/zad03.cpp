/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<FL/Fl.h>
#include<FL/Fl_Box.h>
#include<FL/Fl_Window.h>
#include<FL/Fl_Output.h>
#include "GUI.hpp"
#include "std_lib_facilities.hpp"

using namespace Graph_lib;

//-------------------------------------------------------------------------------------------------------------------------------------------------------

class Graphic_window : public ::Graph_lib::Window {
public:
        Graphic_window(Point, int, int, const string&);
        void quit() {hide();}
        void f(Fct);

private:
        Button quit_button;
        Menu function_menu;
        In_box r_min_box;
        In_box r_max_box;
        In_box x_scale_box;
        In_box y_scale_box;
        Axis x;
        Axis y;
        Vector_ref<Function> funcs;

};

//--------------------------------------------------------------------------------------------------------------------------------------------------------
Graphic_window::Graphic_window(Point p, int width, int hight, const string& lable):
    Window (p,width,hight,lable),
    quit_button (Point(x_max()-80,0),80,30,"Quit", [](Address, Address pw){reference_to<Graphic_window>(pw).quit();}),
    function_menu (Point(0,0),80,30,Menu::vertical,""),
    r_min_box      (Point(140,0),100,30,"r_min:"),
    r_max_box      (Point(300,0),100,30,"r_max:"),
    x_scale_box    (Point(140,35),100,30,"x_scale"),
    y_scale_box    (Point(300,35),100,30,"y_scale:"),
    x (Axis::x, Point(width/8,hight/2), width*6/8,0,"X"),
    y (Axis::y, Point(width/2,hight*7/8), hight*6/8,0,"Y")
{
    srand (time(NULL));
    attach(quit_button);
    
    function_menu.attach(new Button(Point(0,0),0,0,"Sin()", [](Address, Address pw){ reference_to<Graphic_window>(pw).f(sin);  } ));
    function_menu.attach(new Button(Point(0,0),0,0,"Cos()", [](Address, Address pw){ reference_to<Graphic_window>(pw).f(cos);  } ));
    function_menu.attach(new Button(Point(0,0),0,0,"Log()", [](Address, Address pw){ reference_to<Graphic_window>(pw).f(log);  } ));
    function_menu.attach(new Button(Point(0,0),0,0,"Exp()", [](Address, Address pw){ reference_to<Graphic_window>(pw).f(exp);  } ));
    function_menu.attach(new Button(Point(0,0),0,0,"Acos()",[](Address, Address pw){ reference_to<Graphic_window>(pw).f(acos); } ));
    function_menu.attach(new Button(Point(0,0),0,0,"Asin()",[](Address, Address pw){ reference_to<Graphic_window>(pw).f(asin); } ));
    function_menu.attach(new Button(Point(0,0),0,0,"Atan()",[](Address, Address pw){ reference_to<Graphic_window>(pw).f(atan); } ));
    
    attach(function_menu);
    attach(r_min_box);
    attach(r_max_box);
    attach(x_scale_box);
    attach(y_scale_box);
    x.set_color(Color::red);
    y.set_color(Color::red);
    attach(x);
    attach(y);
}

//=======================================================================================================================================================
int rand_int(int min, int max)
{
        return rand() % max + min;
}

string In_box::get_string()
{
        Fl_Input& pi = reference_to<Fl_Input>(pw);
        const char* p = pi.value();
        return p;
}

int str_to_int(string str)
{
        stringstream ss;
        ss << str;
        int value = 0;
        ss >> value;
        return value;
}
//=======================================================================================================================================================
void Graphic_window::f(Fct g)
{
        int r_min   = str_to_int(r_min_box.get_string());
        int r_max   = str_to_int(r_max_box.get_string());
        int x_scale = str_to_int(x_scale_box.get_string());
        int y_scale = str_to_int(y_scale_box.get_string());
        funcs.push_back(new Function(g,r_min,r_max,Point(x_max()/2,y_max()/2),200,x_scale,y_scale));
        funcs[funcs.size()-1].set_color(rand_int(0,256));
        attach(funcs[funcs.size()-1]);
        redraw();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
	try 
	{
		Graphic_window g_win{Point{100,100},800,600,"My window#3"};
		return gui_main();
	}	
	catch(exception& e)
	{
		cerr << "exception: " << e.what() << '\n';
		return 1;
	}
	catch(...)
	{
		cerr<<"Some exception\n";
		return 2;
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
