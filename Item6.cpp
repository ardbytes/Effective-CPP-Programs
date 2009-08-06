//Item6: Explicitly disallow the use of compiler-generated functions you do not want

#include<boost/noncopyable.hpp>

// Note derivation from boost::noncopyable
class HouseForSale : private boost::noncopyable
{
 private:
 	int propertyId;
 public:
 	HouseForSale( int id );
};

HouseForSale::HouseForSale(int id):
propertyId(id){}

int main()
{
 HouseForSale h1(1);
 //Error!! Inherting from noncopyable disallows copy constructing and assigning.
 //HouseForSale h2(h1); 
}

/* Related Topics:
 * Empty Base class Optimisation (EBO) - Item 39
 */

