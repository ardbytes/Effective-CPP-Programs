// This program won't compile. Look below for details.
#include <iostream>
using namespace std;

class Stub
{
 public:
 	int& iVar;

 	Stub(int i);
//  Stub& operator = ( const Stub& rhs);
};

Stub::Stub(int i): iVar(i) { }

/*Stub& Stub::operator = (const Stub& rhs)
{
 this->iVar = rhs.iVar;
 return *this;
}
*/

int main()
{
 int a = 10, b = 20;
 Stub s2(a);
 Stub s1(b);
 
 /* C++ is unsure how to generate an implicit assignment operator without 
  * being illegal or nonsense. Its illegal when:
  * a). Classes contain reference members
  * b). Classes contain const members
  * c). in derived classes that inherit from base classes declaring the copy assignment operator private. 
  */
 s1 = s2;
}	 

