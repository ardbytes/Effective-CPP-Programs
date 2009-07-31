// Item 11: Handle assignment to self in operator=
#include <iostream>

using namespace std;

#define MAX_COLORS 20
class Widget
{
 public:
 	Widget ( int seed );
	~Widget ( );
 	Widget& operator=( const Widget& rhs );
	void ToString ( );
    Widget( const Widget& rhs );
 private:
	int *colorPallete;
};

void Widget::ToString()
{
 int i = 0;
 for ( i = 0; i < MAX_COLORS; i++ )
 {
 cout << "colorPallete[" << i << "]: " << colorPallete[i] << endl;
 }
}

Widget::Widget ( int seed ):
	colorPallete ( new int[MAX_COLORS])
	{
	 int i = 0;
	 for ( i = 0; i < MAX_COLORS; i++ )
	 {
	  colorPallete[i] = seed + i;
	 }
	}
	
Widget::Widget( const Widget& rhs ):
	colorPallete( new int[MAX_COLORS] )
{
	std::copy ( rhs.colorPallete, rhs.colorPallete + MAX_COLORS, colorPallete );
}
   
Widget& Widget::operator=( const Widget& rhs )
{
	Widget tmp(rhs);
	
	std::swap ( colorPallete, tmp.colorPallete );	
	
	return *this; 
}

Widget::~Widget()
{
 delete[] colorPallete;
}	 

	
int main()
{
 Widget b(10);
 Widget a(20);
 b.ToString();
 b = b; 
 cout << endl << "After: " << endl;
 b.ToString();
}

/* Notes:
   1). Refer to Item 29 for copy/swap technique.
*/

