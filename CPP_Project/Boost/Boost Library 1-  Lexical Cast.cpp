#include <boost\lexical_cast.hpp>
#include <iostream>
#include <string>

using boost::lexical_cast;
using boost::bad_lexical_cast;
using std::cout;
using std::endl;

/*
convert string to other data and reverse
*/
int main()
{
	int s = 23;
	std::string str = lexical_cast<std::string>(s);
	cout << "String converted from integer 23: " << str << endl;

	str = "Message: " + lexical_cast<std::string>('A') + '=' + lexical_cast<std::string>(12.3);

	//Convert std::string to an array of char
	std::array<char, 64> msg = lexical_cast<std::array<char, 64>>(1234);
	for (size_t i = 0; i < 64; i++)
	{
		cout << msg[i] << " ";
	}
	cout << endl;

	s = lexical_cast<int>("123");
	cout << s << endl;

	try
	{
		s = lexical_cast<int>("123.56");
	}
	catch (const std::exception&e)
	{
		cout << "Exception: " << e.what() << endl; // bad lexical cast: source type value could not be interpreted as target
	}
	return 0;
}