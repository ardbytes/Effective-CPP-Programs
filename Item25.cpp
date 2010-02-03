#include <algorithm>
#include <iostream>
using namespace std;

class Rational
{
 public:
 	Rational (int numerator=1, int denominator=1):iNumerator(numerator),iDenominator(denominator){}
	
	int Numerator() const { return iNumerator; }
	int Denominator() const { return iDenominator; }
	
	Rational ( Rational& rhs );
	
//	  Rational operator*(const Rational& rhs);
	
 private:
 	int iNumerator;
	int iDenominator;	 
		
};
/*
Rational Rational::operator*(const Rational& rhs)
{
 return Rational( this->Numerator() * rhs.Numerator(), this->Denominator() * rhs.Denominator() );
}
*/

Rational operator*(const Rational& lhs, const Rational& rhs)
{
 return Rational( lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator() );
}

Rational::Rational ( Rational& rhs)
{
 swap (*this, rhs);
}

int main()
{
 int a = 10, b = 20;
 cout << a << " " << b << endl;
 std::swap (a,b);
 cout << a << " " << b << endl;
 Rational aRational(3,2);
 Rational bRational(aRational);
}


