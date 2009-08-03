#include <iostream.h>

// Proxy Classes ( Item 30 ). From More Effective C++

// Adds a proxy class to AutoRCObject.cpp to distinguish between 
// read usage and write usage of operator[]

// References
//	> Item 1: Distinguish between pointers and references
//	> Item 2: Prefer C++-style class.
//	> Item 5: Be wary of user-defined conversion functions.
//	> Item 7: Gives a list of overloadable operators and otherwise
//	> Item 17: Lazy evaluation.
//	> Item 19: Understand the origin of temporary objects.
//	> Item 29: Reference Counting

// See also:
//	> Reference.cpp*
//	> RCObject.cpp
//	> AutoRCObject.cpp

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
  class CharProxy
  {
   public:
    CharProxy ( String& str, int index );
	
	CharProxy& operator= (const CharProxy& rhs);
	CharProxy& operator= (char c);
	
	char * operator&();
	const char * operator&() const;
	
	operator char() const;
   private:
    String& theString;
	int charIndex;
  };
  const CharProxy operator[] (int index)const; // See Item 1
  CharProxy operator[] (int index); // See Item 1
  
  friend class CharProxy;
  
  
  String ( const char *initValue = "" );
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

String::CharProxy::CharProxy(String& str, int index)
 :theString(str), charIndex(index)
{
}

String::CharProxy& String::CharProxy::operator= (const CharProxy& rhs)
{
 if ( theString.value->isShared())
 {
  theString.value = new StringValue(theString.value->data);
 }
 theString.value->data[charIndex] = rhs.theString.value->data[rhs.charIndex];
 return *this;
}

String::CharProxy& String::CharProxy::operator= (char c)
{
 if ( theString.value->isShared() )
  {
  theString.value = new StringValue(theString.value->data);
  }
 theString.value->data[charIndex] = c;
 return *this; 
}

char * String::CharProxy::operator&()
{
 if ( theString.value->isShared() )
 {
  theString.value = new StringValue(theString.value->data);
 }
 theString.value->markUnshareable();
 
 return &(theString.value->data[charIndex]);
}

const char * String::CharProxy::operator&() const
{
 return &(theString.value->data[charIndex]);
}


String::CharProxy::operator char() const
{
 return theString.value->data[charIndex];
}

const String::CharProxy String::operator[](int index)const
{
 return CharProxy(const_cast<String&>(*this), index);
}

String::CharProxy String::operator[] (int index)
{
 return CharProxy(*this, index);
}
  
String::String( const char *initValue )
 :value ( new StringValue ( initValue ) )
 {}
 
void String::Print()
{
 cout << "Data: " << value->data << endl;
 cout << "Shared: " << value->isShared() << endl;
 cout << "Shareable: " << value->isShareable() << endl << endl;
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

