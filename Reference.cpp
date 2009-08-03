#include <iostream.h>

// Implements reference counting ( Item 29 ). From More Effective C++

// Not perfect. The program output actually shows the flaw

// The solution is to add a flag to mark it unsharable whenever the 
// non-const operator[] is called

// References:
//	> Item 8: Understand the different meanings of new and delete.
//	> Item 9: Use destructors to avoid memory leak.
//	> Item 16: Remember the 80/20 rule.
//	> Item 17: ( Lazy Evaluation ).
//	> Item 18: Amortize the cost of expected computations. 
//	> Item 25: Virtualizing constructors and non-member functions.
//	> Item 27: Requiring or prohibiting heap based objects.
//	> Item 28: Smart pointers.
//	> Item 30 (Proxy Classes ) to distinguish read usage from write usage in operator[].
//	> Item 32: Program in the future tense.
//	> Item 33:	Make non-leaf classes abstract.
//	> Item E11: Declare a copy constructor and assignment operator for classes with dynamic allocated memory.
//	> Item E14: Make sure base classes have virtual destructors.
//	> Item E15: Have operator= return a reference to *this.
//	> Item E16: Assign to all data members in operator=.
//	> Item E17: Check for assignment to self in operator=.

// See also:
//	> RCObject.cpp
//	> AutoRCObject.cpp


class String
{
 public:
  String ( const char *initValue = "" );
  String ( const String& rhs );
  ~String();	
  String& operator=( const String& rhs );
  const char& operator [] ( int index ) const;
  char& operator[] ( int index );
  void Print ( );
 private:
  struct StringValue
  {
   int refCount;
   char *data;
		
   StringValue( const char *initValue );
   ~StringValue ( );
  };
 StringValue *value;		
};

String::StringValue::StringValue ( const char *initValue )
 :refCount(1)
{
 data = new char [strlen (initValue) + 1];
 strcpy(data, initValue);
}
 
String::StringValue::~StringValue()
{
 delete [] data;
}

String::String( const char *initValue )
 :value ( new StringValue ( initValue ) )
 {}
 
String::String( const String& rhs )
 :value ( rhs.value )
{
 ++value->refCount; 
}

String& String::operator=( const String& rhs )
{
 if ( value == rhs.value )
  return *this;
  
 if ( --value->refCount == 0 )
  delete value;
  
 value = rhs.value;
 ++value->refCount; 
 return *this;
}

const char& String::operator [] ( int index ) const
{
 return value->data[index];
}

char& String::operator[] ( int index )
{
 if ( value->refCount > 1 )
 {
  --value->refCount;
  value = new StringValue ( value->data );
 }
 return value->data[index]; 
}

void String::Print()
{
 cout << value->data;
 cout << endl;
}

String::~String()
{
 if ( --value->refCount == 0 ) delete value;
}
 
int main ()
{
 String s1("More Effective C++");
 
 char *p = &s1[1];
 
 String s2 = s1;
  
 s1.Print();
 s2.Print();
 
 *p = 'x';
 
 s1.Print();
 s2.Print();
 
 return 0;
}

