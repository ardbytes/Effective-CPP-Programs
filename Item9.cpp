//Item 9: Never call virtual functions during construction or destruction
#include <iostream>

using namespace std;

class Animal
{
 public:
    Animal();
 	virtual void init ( );
};

void Animal::init()
{
 cout << "Animal ctor" << endl;
}

Animal::Animal()
{
 /* because such calls will never go to a more derived class than that of the 
  * currently executing constructor or destructor
  * Refer notes below for more details.
  */
 init ();
}

class Dog : public Animal
{
 public:
    Dog();
	virtual void init ( );
 private:
 	int age;
};

Dog::Dog()
{
}

void Dog::init()
{
 age = 0;
 cout << "Dog ctor" << endl;
}

int main()
{
 Dog d;
}

/* Notes:
 * There is a good reason for this counter-intuitive behavior:
 * If as expected, virtual functions called during base class construction went down 
 * to derived classes, the derived class functions would almost certainly refer to 
 * local data members, but those data members would not yet have been initialized.
 *
 * Workaround:
 * have derived classes pass necessary construction information up to base class
 * constructors instead.
 */

