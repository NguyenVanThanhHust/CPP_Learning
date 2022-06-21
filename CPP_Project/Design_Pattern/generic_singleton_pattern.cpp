/*This is implementation of Singleton design pattern*/

#include <iostream>
#include <string>

#include "generic_singleton_pattern.h"

using namespace std;

struct  StrSingleton: public Singleton<string, StrSingleton>{};

class TestClass
{
public:
	void test()
	{
		*mStrSingleton = "Hello world";
	}
	friend ostream &operator<<(ostream &o, const TestClass &t)
	{
		o<<*t.mStrSingleton;
		return o;
	}
private: 
	StrSingleton mStrSingleton;
};

int main()
{
	TestClass test;
	for (int i = 0; i < 100000; ++i)
	{
		test.test();
	}
	cout<<test<<endl;
	std::cin.get();
	return 0;
}