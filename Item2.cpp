/* Main theme of the item is that constS, enumS and inlineS must
 * be preferred to #defineS as much as possible
 */

// #define PI 3.14159

/* Prefer the below declaration to the above #define. Because the #defineS:
 * are not visible to the compiler,
 * is not entered into the symbol table making debugging harder,
 * result in multiple copies of PI wherever they are used in the program,
 * cannot create a class-specific constant as it knows nothing about scope ( discussed later below )
 * cannot provide any kind of encapsulation
 */
const double PI = 3.14159;

// #define "A String"

/* Its better to use constants instead of #defineS remember!!
 * Two replacements for the #define above are given below:
 */
 
const char * const str = "A String";

//Or

#include <string>
using namespace std;

//For class specific constants, constant static member variables serve the purpose well

class Horse
{
//Intentionally left empty
};

class Stable
{
 /* The constant static member 'maxHorses' donot require a definition because:
  * its a constant static integral,
  * we are not taking its address like '&maxHorses'
  */
 static const int maxHorses = 10;
 
 Horse h[maxHorses];
};

// Another alternative is known as the enum hack
// The enum hack is a fundamental technique of TMP ( Item 48 )

class AnotherStable
{

 enum { maxHorses = 10 };
 Horse h[maxHorses];
};

string anotherStr("Another String");

// Alternatives to macros like below are explored

#include <iostream>

template<typename T>
void f(const T& num)
{
 cout << num;
}

// #define CALL_WITH_MAX(a,b) f((a) > (b) ? (a) : (b))

/* Drawbacks with the macro approach: ( assuming a=5 and b=0 )
 * we have to remember to parenthesize all arguments in the macro body, 
 * CALL_WITH_MAX(++a, b); a is incremented twice,
 * CALL_WITH_MAX(++a, b+10); a is incremented once,
 * Hence the number of times a is incremented depends on what its being compared with,
 * There is a way to escape from all this nonsense. Continue reading...
 */
 
/* We can get all the efficiency of a macro plus all the predictable behavior and type
 * safety of a regular function by using a template for an inline function
 */

template<typename T>
void callWithMax(const T& a, const T& b)
{
 f (a > b ? a : b);
}

int main()
{
 int a,b;
 cin >> a;
 cin >> b;
 callWithMax (a,b);
}

