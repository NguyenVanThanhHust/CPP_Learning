#include <boost\variant.hpp>
#include <iostream>
#include <string>

using namespace std;
int main()
{
	boost::variant<string, float> u1, u2, u3;
	u1 = 2.0;
	u2 = "Hello";
	cout << u1 << " " << u2 << " " << u3 << endl;

	return 0;
}