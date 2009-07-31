// Theme:
/* 'const' allows you to communicate to both compilers and other programmers 
 * that a value should remain invariant
 */
 
/* This source file would discuss the various contexts const can be used and
 * what they mean in those context
 */
 
char goodCommunity[] = "Building43";

char evilCommunity[] = "AlQaeda";

char *p = goodCommunity; //non-const pointer to non-const data

const char *pcstr = goodCommunity; //non-const pointer to const data

char * const cpstr = goodCommunity; //const pointer to non-const data

const char * const cpcstr = goodCommunity; //const pointer to const data

#include <iostream>

using namespace std;

int main()
{
 *(p+1) = 'g';
 cout << "Pointer: " << p << endl;
 p = evilCommunity;
 cout << "Pointer: " << p << endl;
 
 // *(pcstr+1) = 'g';
 //Error!! Data is constant cannot be changed
 pcstr = evilCommunity;
 cout << "Pointer to Constant String: " << pcstr << endl; 
 
 *(cpstr+1) = 'g';
 cout << "Constant pointer to string: " << cpstr << endl;
 // cpstr = evilCommunity;
 // Error!! Constant pointer to string. Pointer cannot point to anything else.
 
 //*(cpcstr+1) = 'g';
 //Error!! String is constant; cannot be changed
 //cpcstr = evilCommunity;
 // Error!! Constant pointer to constant string. Pointer cannot point to anything else.
}

