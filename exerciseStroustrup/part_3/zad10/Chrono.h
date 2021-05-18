#include "std_lib_facilities.hpp"

#ifndef CHRONO_H    
#define CHRONO_H    

namespace Chrono {

enum class Day {
    sunday, monday, tuesday, wednesday, thursday, friday, saturday
};

enum class Month {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

Month operator+(const Month& m, int n);
Month operator-(const Month& m, int n);
Month& operator+=(Month& m, int n);

bool operator<(const Month& m, int n);
bool operator>(const Month& m, int n);

class Date {
public:
    class Invalid {};               

    Date(int yy, Month mm, int dd);
    Date();                         

    
    int day() const { return d; }
    Month month() const { return m; }
    int year() const { return y; }


    void add_day(int n);
    void add_month(int n);
    void add_year(int n);
private:
    int y;          
    Month m;
    int d;          
};

bool is_date(int y, Month m, int d);    
bool leapyear(int y);                   


bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);

ostream& operator<<(ostream& os, const Date& d);
istream& operator>>(istream& is, Date& dd);

Day day_of_week(const Date& d);    
Date next_Sunday(const Date& d);    
Date next_weekday(const Date& d);  

} 

#endif
