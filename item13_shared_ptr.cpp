// Item 13: Use objects to manage resources.
#include <iostream>
#include <boost/tr1/memory.hpp>
using namespace std;

class Dog
{
 public:
 	Dog ( int aAge=0, string aBreed="" );
 	~Dog();
 	void ToString ( );
 private:
 	int age;
	string *breed;
};

Dog::Dog ( int aAge, string aBreed ):
	age ( aAge ),
	breed ( new string (aBreed))
	{}
	
void Dog::ToString ( )
{
 cout << "Age: " << age << "; Breed: " << *breed << endl; 
}

Dog::~Dog()
{
 delete breed;
 cout << "Deleted Dog" << endl;
}

Dog* createDog( int age, string breed )
{
 return new Dog ( age, breed );
}

int main()
{
 std::tr1::shared_ptr<Dog> d(createDog(10, "bull dog"));
 d->ToString();
  
 std::tr1::shared_ptr<Dog> d1(d);
 d1->ToString();
 
 /* Notice here that the copying behavior is more intuitive
  * On copy constructing d1 from d, d is not set to null like auto_ptr did.
  * Refer to notes for details
  */
 d->ToString();
}

/* Notes:
  An alternative to auto_ptr is a reference-counting smart pointer (RCSP). 
  An RCSP is a smart pointer that keeps track of how many objects point to a 
  particular resource and automatically deletes the resource when nobody is 
  pointing to it any longer. As such, RCSPs offer behavior that is similar to 
  that of garbage collection. Unlike garbage collection, however, 
  RCSPs can't break cycles of references (e.g., two otherwise unused objects 
  that point to one another).
*/  

/*
 * Look at boost::scoped_array and boost::shared_array
 */

