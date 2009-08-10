// Item 18: Make interfaces easy to use correctly and hard to use incorrectly
#include <iostream>
using namespace std;

struct Day {
	explicit Day (int d):
			val(d){}
	int val;
};

struct Month {
	explicit Month (int m):
			val(m){}
	int val;
};

struct Year {
	explicit Year (int y):
			val(y){}
	int val;
};

class Date
{
 public:
 	Date (const Month& m, const Day& d, const Year& y):
		iMonth(m),
		iDay(d),
		iYear(y) 
		{}
		
	void ToString( );
		
 private:
 	Month iMonth;
	Day iDay;
	Year iYear;	    
};

void Date::ToString( )
{
 cout << iDay.val << "/" <<iMonth.val << "/" << iYear.val << endl;
}

int main ( )
{
 Date d ( Month(1), Day(1), Year(2010));
 d.ToString();
}

