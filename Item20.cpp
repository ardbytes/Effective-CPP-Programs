// Item 20 - Prefer pass-by-reference-to-const to pass-by-value

#include <string>
#include <iostream>

using namespace std;
class Animal
{
 std::string name;
 int age;
 
 public:
 	Animal ( std::string animalName, int animalAge ):name(animalName),age(animalAge){}
	void printName ( ) const { cout << name << " "; }
	void printAge ( ) const { cout << age << " "; }
	virtual void printBreed()const {cout << "" << " ";}
};

class Dog : public Animal
{

 std::string breed;
 
  public:
 	Dog ( std::string animalName, int animalAge, std::string breedName ):Animal(animalName,animalAge),breed(breedName){}
	void printBreed ( ) const { cout << breed << " "; }
};

void printAnimal ( const Animal& dog ) { dog.printName(); dog.printAge(); dog.printBreed(); cout << endl; }

int main()
{
 Dog scooby("ScoobyDoo",10,"GreatDane");
 printAnimal( scooby ); 
}

/* Notes:
 * 
 * If scooby was passed by value to printAnimal it would have called four constructors
 * ( one for Animal, one for Dog, two for std::string ) and four corresponding destructors
 * after printAnimal returned.
 *
 * Within printAnimal if scooby was passed by value it would behave like an Animal object 
 * and call to printBreed would always call Animal::printBreed. This is called slicing problem
 * that is solved when passed by reference.
 * 
 * References are implemented as pointers ( under the hood ) by compilers. Pointers are always
 * put in registers but the Animal object certainly wouldn't be. That's a performance gain.
 */

