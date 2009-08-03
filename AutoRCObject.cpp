#include <iostream.h>

// Implements reference counting ( Item 29 ). From More Effective C++

// Implements a base class for reference counting called RCObject

// The reference count is now modified automatically by the wrapper RCPtr
// that in this case makes pointers to Sting::StringValue smart.

// See also:
//	> Reference.cpp*
//	> RCObject.cpp

class RCObject
{
 protected:
  RCObject();
  RCObject( const RCObject& rhs );
  RCObject& operator=( const RCObject& rhs );
  virtual ~RCObject () = 0;
  
 public: 
  
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

template <class T>
class RCPtr
{
 public:
  RCPtr(T* realPtr=0 );
  RCPtr(const RCPtr& rhs);
  ~RCPtr();
  
  RCPtr& operator=(const RCPtr& rhs);
  
  T* operator->() const;
  T& operator*() const;
  
 private:
  
  T *pointee;
  void init();
};

template<class T>
RCPtr<T>::RCPtr(T *realPtr):pointee(realPtr)
{
 init();
}

template<class T>
RCPtr<T>::RCPtr(const RCPtr& rhs):pointee(rhs.pointee)
{
 init();
}

template<class T>
void RCPtr<T>::init()
{
 if ( pointee == 0 )
  return;
  
 if ( pointee->isShareable() == false )
 {
  pointee = new T(*pointee);
 }
 pointee->addReference();
}

template<class T>
RCPtr<T>& RCPtr<T>::operator=( const RCPtr& rhs )
{
 if ( pointee == rhs.pointee )
  return *this;
  
 if ( pointee )
 {
  pointee->removeReference();
 }
 
 pointee = rhs.pointee;
 init();
 return *this;
}

template<class T>
RCPtr<T>::~RCPtr()
{
 if ( pointee ) pointee->removeReference();
}

template<class T>
T* RCPtr<T>::operator->() const { return pointee; }

template<class T>
T& RCPtr<T>::operator*() const { return *pointee; }

class String
{
 public:
  String ( const char *initValue = "" );
  const char& operator [] ( int index ) const;
  char& operator[] ( int index );
  void Print ( );
 private:
  struct StringValue: public RCObject
  {
   char *data;
   StringValue( const char *initValue );
   StringValue( const StringValue& rhs );
   ~StringValue ( );
  };
 RCPtr<StringValue> value;	  	  
};

String::StringValue::StringValue ( const char *initValue )
{
 data = new char [strlen (initValue) + 1];
 strcpy(data, initValue);
}

String::StringValue::StringValue( const StringValue& rhs )
{
 data = new char[strlen(rhs.data) + 1];
 strcpy(data, rhs.data);
}

String::StringValue::~StringValue()
{
 delete [] data;
}

String::String( const char *initValue )
 :value ( new StringValue ( initValue ) )
 {}
 
const char& String::operator [] ( int index ) const
{
 return value->data[index];
}

char& String::operator[] ( int index )
{
 if ( value->isShared( ) )
 {
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

int main ()
{
 String s1("More Effective C++");
 String s2("Hello");
 cout << s1[1] << endl;
 char *p = &s1[1];
 s2 = s1;
 *p = 'x';
 s1.Print();
 s2.Print();
}

