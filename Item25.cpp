//Item 25: Consider support for a non-throwing swap

#include <algorithm>
#include <iostream>
using namespace std;

class Rational
{
 public:
 	Rational (int numerator=1, int denominator=1):iNumerator(numerator),iDenominator(denominator){}
	
	int Numerator() const { return iNumerator; }
	int Denominator() const { return iDenominator; }
	
 private:
 	int iNumerator;
	int iDenominator;
};

Rational operator*(const Rational& lhs, const Rational& rhs)
{
 Rational result( lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator() );
 return result;
}

int main()
{
 int a = 10, b = 20;
 cout << a << " " << b << endl;
 std::swap (a,b);
 cout << a << " " << b << endl;
 Rational aRational(3,2);
 Rational bRational(5,8);
 std::swap(aRational,bRational);
 cout << bRational.Numerator() << endl;
 cout << aRational.Numerator() << endl;
}

