#include <iostream>

using namespace std;

int add(int a, int b)
{
	return a + b;
}
int  substract(int a, int b)
{
	return a - b;
}


int main()
{
	// Declare a function operator variable number operation
	int (*operation)(int, int);

	// Assign the address of the "add" fucntion to function pointer
	operation = &add;
	int result = operation(3, 2);
	cout << "add result: " << result << endl;

	// Assign the address of the "substract" fucntion to function pointer
	operation = &substract;
	result = operation(3, 2);
	cout << "substract result: " << result << endl;

	return 0;
}