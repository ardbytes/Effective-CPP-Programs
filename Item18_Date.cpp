// Item 18: Make interfaces easy to use correctly and hard to use incorrectly
#include <iostream>
using namespace std;

struct Day {
	explicit Day (int d):
			val(d){}
	int val;
};

class Month 
{
public:

	static Month Jan() { return Month(1); }
	static Month Feb() { return Month(2); }
	static Month Mar() { return Month(3); }
	static Month Apr() { return Month(4); }
	static Month May() { return Month(5); }
	static Month Jun() { return Month(6); }
	static Month Jul() { return Month(7); }
	static Month Aug() { return Month(8); }
	static Month Sep() { return Month(9); }
	static Month Oct() { return Month(10); }
	static Month Nov() { return Month(11); }
	static Month Dec() { return Month(12); }
	
	int getVal () {return val;}
	
private:	
	
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
 cout << iDay.val << "/" <<iMonth.getVal() << "/" << iYear.val << endl;
}

int main ( )
{
 Date d ( Month::Jul(), Day(12), Year(1984));
 d.ToString();
}

/*
 Notes:
 
 a). tr1::shared_ptr has a deleter feature that is not present in auto_ptr.
 
 b). tr1::shared_ptr eliminates "cross-DLL problem".
 
 */

