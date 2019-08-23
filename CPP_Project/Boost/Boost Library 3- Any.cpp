#include <boost\any.hpp>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	boost::any x, y, z;
	x = string("hello");
	y = 5.12;
	z = vector<int>();
	cout << boost::any_cast<string>(x) << endl;
	cout << boost::any_cast<double>(y) << endl;

	boost::any_cast<vector<int>>(z).push_back(23);
	// Actually vector<int> is empty
}