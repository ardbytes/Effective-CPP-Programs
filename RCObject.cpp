#include <iostream.h>

// Implements reference counting ( Item 29 ). From More Effective C++

// Corrected the flaw is Reference.cpp.

// Also implements a base class for reference counting called RCObject

// The reference count is now modified manually by the client classes by calling
// addReference and removeReference at appropriate places.

// See also:
//	> Reference.cpp*
//	> AutoRCObject.cpp


class RCObject
{
 public:
  RCObject();
  RCObject( const RCObject& rhs );
  RCObject& operator=( const RCObject& rhs );
  virtual ~RCObject () = 0;
  
  void addReference ();
  void removeReference();
  
  void markUnshareable();
  bool isShareable() const;
  
  bool isShared ()const;
  
 private:
  int refCount;
  bool shareable;
};

RCObject::RCObject()
 :refCount(0), shareable(true) {}
 
RCObject::RCObject( const RCObject& )
 :refCount(0), shareable(true){}
 
RCObject& RCObject::operator=( const RCObject& )
{ return *this; }

RCObject::~RCObject() {}

void RCObject::addReference() { refCount++; }

void RCObject::removeReference() 
{ if ( --refCount == 0 ) delete this; }

void RCObject::markUnshareable ( )
 { shareable = false; }
 
bool RCObject::isShareable() const
 { return shareable; }
 
bool RCObject::isShared() const
 { return refCount > 1; }
 
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
  struct StringValue: public RCObject
  {
   char *data;
   StringValue( const char *initValue );
   ~StringValue ( );
  };
 StringValue *value;		
};

String::StringValue::StringValue ( const char *initValue )
{
 data = new char [strlen (initValue) + 1];
 strcpy(data, initValue);
 this->addReference();
}

String::StringValue::~StringValue()
{
 delete [] data;
}

String::String( const char *initValue )
 :value ( new StringValue ( initValue ) )
 {
 value->addReference();
 }
 
String::String( const String& rhs )
{
 if ( rhs.value->isShareable() )
  {
  value = rhs.value;
  }
 else
  {
  value = new StringValue (rhs.value->data);
  }
 value->addReference();
}

String& String::operator=( const String& rhs )
{
 if ( value == rhs.value )
  return *this;
  
 value->removeReference();
 
 if ( rhs.value->isShareable() )
  {
  value = rhs.value;
  }
 else
  {
  value = new StringValue ( rhs.value->data );
  }
 return *this;
}

const char& String::operator [] ( int index ) const
{
 return value->data[index];
}

char& String::operator[] ( int index )
{
 if ( value->isShared( ) )
 {
  value->removeReference();
  value = new StringValue ( value->data );
 }
 value->markUnshareable();
 return value->data[index]; 
}

void String::Print()
{
 cout << "Data: " << value->data << endl;
 cout << "Shared: " << value->isShared() << endl;
 cout << "Shareable: " << value->isShareable() << endl << endl;
}

String::~String()
{
 value->removeReference();
}

int main ()
{
 String s1("More Effective C++");
 char *p = &s1[1];
 s1.Print();
 
 String s2 ("Hello");
 s2 = s1;
 *p = 'x';
 s2.Print();
}

