#include<FL/Fl.h>
#include<FL/Fl_Box.h>
#include<FL/Fl_Window.h>
#include "GUI.hpp"


using namespace Graph_lib;

int xb = 300;
int yb = 200;

struct My_window : ::Graph_lib::Window{
       My_window(Point xy, int w, int h, const string& title);
       void wait_for_button();

 private:
       Button next_button;
       Button quit_button;
       bool is_pressed;
       bool b_quit;
       void next();
       void quit();
};


 My_window::My_window(Point xy, int w, int h, const string& title)
           :Window{xy,w,h,title},
           next_button{Point{w-70,0}, 70,20,"Next",[](Address, Address pw) {reference_to<My_window>(pw).next();}},
           quit_button{Point{w-70,20},70,20,"Quit",[](Address, Address pw) {reference_to<My_window>(pw).quit();}},
           is_pressed{false},
           b_quit{false}
{
        attach(next_button);
        attach(quit_button);
}
void My_window::wait_for_button() 
{
        if(1) {
                    while(!is_pressed && !b_quit) Fl::wait();
                    Fl::redraw();
                    is_pressed = false;
              
              }
}

void My_window::next() { is_pressed = true;}

void My_window::quit() { b_quit = true; hide(); }

struct Button_window : My_window{
            Button_window(Point xy, int x, int w, const string& label, int xn, int yn);
private:
 
   Menu menu1;
   Menu menu2;
   Menu menu3;
   Menu menu4;
   
   void b11();
   void b12();
   void b13();
   void b14();

   void b21();
   void b22();
   void b23();
   void b24();
  
   void b31();
   void b32();
   void b33();
   void b34();

   void b41();
   void b42();
   void b43();
   void b44();
   void get_xy(Point p);
   Out_box out_xy;
};

Button_window::Button_window(Point xy, int x, int w, const string& label, int xn, int yn)
        :My_window{xy,x,w,label}, out_xy{Point{100,0},70,20,"Button's (x,y): "},
        menu1{Point{xb,yb},50,50,Menu::vertical,"1"}, 
        menu2{Point{xb+50,yb},50,50,Menu::vertical,"2"},
        menu3{Point{xb+100,yb},50,50,Menu::vertical,"3"},
        menu4{Point{xb+150,yb},50,50,Menu::vertical,"4"}
{ 

    menu1.attach(new Button{Point {xb,yb},50,50,"1-1",[](Address, Address pw){reference_to<Button_window>(pw).b11();}});
    menu1.attach(new Button{Point {xb,yb+50},50,50,"1-2",[](Address, Address pw){reference_to<Button_window>(pw).b12();}});
    menu1.attach(new Button{Point {xb,yb+100},50,50,"1-3",[](Address, Address pw){reference_to<Button_window>(pw).b13();}});
    menu1.attach(new Button{Point {xb,yb+150},50,50,"1-4",[](Address, Address pw){reference_to<Button_window>(pw).b14();}});
     
    menu2.attach(new Button{Point {xb+50,yb},50,50,"2-1",[](Address, Address pw){reference_to<Button_window>(pw).b21();}});
    menu2.attach(new Button{Point {xb+50,yb+50},50,50,"2-2",[](Address, Address pw){reference_to<Button_window>(pw).b22();}});
    menu2.attach(new Button{Point {xb+50,yb+100},50,50,"2-3",[](Address, Address pw){reference_to<Button_window>(pw).b23();}});
    menu2.attach(new Button{Point {xb+50,yb+150},50,50,"2-4",[](Address, Address pw){reference_to<Button_window>(pw).b24();}});
    
    menu3.attach(new Button{Point {xb+100,yb},50,50,"3-1",[](Address, Address pw){reference_to<Button_window>(pw).b31();}});
    menu3.attach(new Button{Point {xb+100,yb+50},50,50,"3-2",[](Address, Address pw){reference_to<Button_window>(pw).b32();}});
    menu3.attach(new Button{Point {xb+100,yb+100},50,50,"3-3",[](Address, Address pw){reference_to<Button_window>(pw).b33();}});
    menu3.attach(new Button{Point {xb+100,yb+150},50,50,"3-4",[](Address, Address pw){reference_to<Button_window>(pw).b34();}});
    
    menu4.attach(new Button{Point {xb+150,yb},50,50,"4-1",[](Address, Address pw){reference_to<Button_window>(pw).b41();}});
    menu4.attach(new Button{Point {xb+150,yb+50},50,50,"4-2",[](Address, Address pw){reference_to<Button_window>(pw).b42();}});
    menu4.attach(new Button{Point {xb+150,yb+100},50,50,"4-3",[](Address, Address pw){reference_to<Button_window>(pw).b43();}});
    menu4.attach(new Button{Point {xb+150,yb+150},50,50,"4-4",[](Address, Address pw){reference_to<Button_window>(pw).b44();}});
   
    attach(out_xy);
    attach(menu1);
    attach(menu2);
    attach(menu3);
    attach(menu4);
}
    void Button_window::b11() {get_xy(menu1.selection[0].loc);}
    void Button_window::b12() {get_xy(menu1.selection[1].loc);}
    void Button_window::b13() {get_xy(menu1.selection[2].loc);}
    void Button_window::b14() {get_xy(menu1.selection[3].loc);}

    void Button_window::b21() {get_xy(menu2.selection[0].loc);}
    void Button_window::b22() {get_xy(menu2.selection[1].loc);}
    void Button_window::b23() {get_xy(menu2.selection[2].loc);}
    void Button_window::b24() {get_xy(menu2.selection[3].loc);}

    void Button_window::b31() {get_xy(menu3.selection[0].loc);}
    void Button_window::b32() {get_xy(menu3.selection[1].loc);}
    void Button_window::b33() {get_xy(menu3.selection[2].loc);}
    void Button_window::b34() {get_xy(menu3.selection[3].loc);}

    void Button_window::b41() {get_xy(menu4.selection[0].loc);}
    void Button_window::b42() {get_xy(menu4.selection[1].loc);}
    void Button_window::b43() {get_xy(menu4.selection[2].loc);}
    void Button_window::b44() {get_xy(menu4.selection[3].loc);}
   

    
    void Button_window::get_xy(Point p) {
            ostringstream os;
                    os << '(' << p.x << ',' << p.y << ')';
                    out_xy.put(os.str());
                    redraw();
   }

int main()
	try 
	{
		Button_window b_win {Point{100,100},800,600,"My window#2", 4,4};
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

