// Declare non-member functions when type conversions should apply to all parameters

class Rational
{
 public:
 	Rational (int numerator = 0, int denominator = 1):iNumerator(numerator),iDenominator(denominator){}
	
	int Numerator() const { return iNumerator; }
	int Denominator() const { return iDenominator; }
	
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

int main()
{
 Rational oneFourth(1,4);
 Rational oneTenth(1,10);
 
 Rational oneFourteenth = oneFourth * oneTenth;
 
 Rational half = oneFourth * 2;
 
 Rational one = 4 * oneFourth; 
}

/* Notes:
The this pointer is not subjected to implicit type conversions

If type conversion is needed on all parameters including the this pointer
declare the function to be a non-member

This advice holds good for Object-Oriented C++. In case of Template C++
where Rational is a Template class new issues arise and this is 
discussed in Item 46
*/

