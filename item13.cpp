// Item 13: Use objects to manage resources.
#include <iostream>
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
 std::auto_ptr<Dog> d(createDog(10, "bull dog"));
 d->ToString();
 
 // d is now null d1 points to the Dog object d previously did.
 // Refer notes for more details.
 std::auto_ptr<Dog> d1(d);
 d1->ToString();
 
 // This will fail
 //d->ToString();
}

/*
 Notes:
 
 This odd copying behavior, plus the underlying requirement that resources managed by auto_ptrs 
 must never have more than one auto_ptr pointing to them, means that auto_ptrs aren't the best way to 
 manage all dynamically allocated resources. For example, STL containers require that their contents 
 exhibit "normal" copying behavior, so containers of auto_ptr aren't allowed.
*/

