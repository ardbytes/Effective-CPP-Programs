#include <iostream>
#include <vector>

using namespace std;

int main()
{
 vector<int>vec;
 for ( int i = 0; i < 10; i++)
 {
  vec.push_back(i*10);
 }
 
 const std::vector<int>::iterator iterpc = vec.begin();
 
 *iterpc = 10;
 cout << *iterpc << endl;
 
 // iterpc++;
 // Error!! Pointer is constant
 
 std::vector<int>::const_iterator citerp = vec.begin();
 
 // *citerp = 10;
 // Error!! What iterator points to is constant
 
 citerp++;
 cout << *citerp++;
}

/* TODO:
 * a). mutable
 * b). calling const qualified member functions from within non-const member functions
 */

