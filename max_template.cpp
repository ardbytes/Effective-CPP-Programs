#include <iostream>
using namespace std;
template<typename T>
const T& myMax(const T& a, const T& b)
{
 return a > b ? a : b;
}

template const int& max<int>;
int main()
{
 const int a = 10;
 short b = 20;

 int c = myMax(a, b);
 cout << c << endl;
}

