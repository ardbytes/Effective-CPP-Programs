//Item 7: Declare destructors virtual in polymorphic base classes 

#include <iostream>
#include <string>
using namespace std;

class Animal
{
 public:
	// Destructor declared virtual
 	virtual ~Animal() = 0;
	virtual void makeSound()=0;
 private:
 	int age;	
	
};

// See Notes at the end
Animal::~Animal() {}

class Dog : public Animal
{
 public:
 	Dog():str("Wow Wow") {}
	void makeSound() { cout << str << endl;}
 private:
 	string str;
};

int main()
{
 // Base class pointer to a derived class object
 Animal *a1 = new Dog();
 
 a1->makeSound();

 // See Notes below
 delete a1;
 a1 = NULL;
}

/* Notes:
   1). 'delete a1' would call the derived Dog's destructor only because Animal's destructor is virtual	  
   2). Dog's destructor would destroy the Dog part of a1 and then call Animal's destructor.
   3). That's why you need a definition for Animal's destructor even though its pure virtual.
*/

/* Notes:
	1). Polymorphic base classes should declare virtual destructors.
	    If a class has any virtual functions, it should have a virtual destructor.
		Like Animal class above
		
	2). Classes not designed to be base classes or not designed to be used polymorphically 
		should not declare virtual destructors.
		Like boost::noncopyable in Item 6.
*/	  	  

