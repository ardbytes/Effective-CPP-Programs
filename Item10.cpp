// Item 10: Have assignment operators return a reference to *this
#include <iostream>
using namespace::std;

class Animal
{
 private:
 	int agility;
 public:
 	
	/* Its a convention that assignment operators accepting any unconventional
	 * parameter type return a reference to *this.
	 */
 	Animal& operator=(const Animal& rhs);
	Animal& operator=(int agility);
	Animal& operator+=(const Animal& rhs);
	
	operator int();
};

Animal::operator int()
{
 return this->agility;
}

Animal& Animal::operator=(const Animal& rhs)
{
 this->agility = rhs.agility;
 return *this;
}

Animal& Animal::operator=(int agility)
{
 this->agility = agility;
 return *this;
}

Animal& Animal::operator+=(const Animal& rhs)
{
 this->agility += rhs.agility;
 return *this;
}


int main()
{
 Animal genX;
 Animal genY;
 Animal genZ;
 genX = 10;
 genZ = 20;
 genY = genX;
 genZ += genY;
 
 cout << genX << endl;
 cout << genY << endl;
 cout << genZ << endl;
}

