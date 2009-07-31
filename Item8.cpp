#include <stdlib.h>
#include <iostream>
using namespace std;

class DestructorDemo
{
 public:
 	DestructorDemo();
	void Erase();
	~DestructorDemo();
 private:
 	int *a;	   
};

DestructorDemo::DestructorDemo():
a(0)
{
 a = (int*)malloc(sizeof(int));
}

void DestructorDemo::Erase() 
{
 free(a);
 a = 0;
}

DestructorDemo::~DestructorDemo() 
{
 if ( a )
 {
  cout << "Throwing an exception" << endl;
  
  // See notes below
  throw 10;
 }
}

int main()
{
 DestructorDemo dd;
}

/* Notes:
 * 1). Destructors should never emit exceptions. If functions called in a destructor may throw, 
   the destructor should catch any exceptions, then swallow them or terminate the program.
 *
 * 2). If class clients need to be able to react to exceptions thrown during an operation, 
   the class should provide a regular (i.e., non-destructor) function that performs the operation.
 */  


