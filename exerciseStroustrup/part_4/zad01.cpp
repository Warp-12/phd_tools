// Zadanie 1: wykonac Drill ze str. 376

#include "std_lib_facilities.hpp"

struct Point
{
	int x;
	int y;
	Point() :x(0), y(0) { }
	Point(int xx, int yy) :x(xx), y(yy) { }
};

bool operator==(const Point& v1, const Point& v2)
{
	return v1.x==v2.x && v1.y==v2.y;
}

bool operator!=(const Point& v1, const Point& v2)
{
	return !(v1==v2);
}

ostream& operator<<(ostream& os, const Point& p)
{
	return os << '(' << p.x << ',' << p.y << ")\n";
}

istream& operator>>(istream& is, Point& p)
{
	int x,y;
	char ch1,ch2,ch3;
	is >> ch1 >> x >> ch2 >> y >> ch3;
	if(!is) return is;
        
        if(ch1!='(' || ch2!=',' || ch3!=')')
	{
        	is.clear(ios_base::failbit);
        	return is;
	}

	p = Point(x,y);
	return is;
}

void print_vector(const vector<Point>& points)
{
	for(int i=0; i<points.size(); i++)
	{
		cout << points[i] << '\n';
	}
}

void print_file(const vector<Point>& points, const string& name)
{
	ofstream ost{name.c_str()};	// ost writes to a file named name
	if (!ost) error("can't open output file ",name);
	
	for(int i=0; i<points.size(); i++)
	{
		ost << points[i] << '\n';
	}
}

void fill_from_file(vector<Point>& points,const string& name)
{
	ifstream is{name.c_str()};	// ist reads from the file named name
	if (!is) error("can't open input file ",name);

	Point pp;
	while(is>>pp) points.push_back(pp);
}

void compare(const vector<Point>& vector1, const vector<Point>& vector2)
{
	if(vector1.size() !=vector2.size())  error ("Something's wrong!");
	for(int i=0; i<vector1.size(); i++)
	{
		if(vector1[i] != vector2[i]) error("Something's wrong!");
	}
}

int main()
{
	try
	{
	    
		vector<Point> original_points;
		cout << "Please enter 7 (x,y) pairs:\n";
		for(int i = 0; i<7; ++i)
		{
			Point p;
			cin >> p;
			original_points.push_back(p);
		}
		
			
        
		cout << "Original points: \n";
		print_vector(original_points);
		string filename = "mydata.txt";
		print_file(original_points, filename);

		vector<Point> processed_points;
		fill_from_file(processed_points, filename);
		cout << "Original points: \n";
		print_vector(original_points);
		cout << "Processed points: \n";
		print_vector(processed_points);

		compare(original_points, processed_points);
	}
	catch (exception& e)
	{
        	cerr << "exception: " << e.what() << endl;
	}

	catch (...) 
	{
    		cerr << "exception\n";
	}
}
