/*
how to move data from this thread to other thread
in this example, return result from child thread to parent thread
*/

#include <future>
#include <iostream>

using namespace std;
std::mutex mu;
std::condition_variable con_var;

int factorial(int N)
{
	int res = 1;
	for (size_t i = 0; i < N; i++)
	{
		res *= (i + 1);
	}
	cout << "result" << res << endl;

	return res;
}

int factorial_promiste(std::future<int> &f)
{
	int res = 1;
	int N = f.get();
	for (size_t i = 0; i < N; i++)
	{
		res *= (i + 1);
	}
	cout << "result" << res << endl;

	return res;
}
int main()
{
	int x;
	// not sure if this follow function create or not create new thead
	// std::future<int> fu = std::async(factorial, 4);

	// create new thread
	//std::future<int> fu = std::async(std::launch::async, factorial, 4);

	// use the same thread
	//std::future<int> fu = std::async(std::launch::deferred, factorial, 4);
	//x = fu.get();
	// Above is to get value from child thread to parent thread

	// Below to promise to value from main thread to child thread
	std::this_thread::sleep_for(chrono::milliseconds(10));
	std::promise<int> p;
	std::future<int> f = p.get_future();
	p.set_value(4);
	std::future<int> new_fu = std::async(std::launch::async, factorial_promiste, std::ref(f));
	int h = new_fu.get();

	// if we dont set value
	p.set_exception(std::make_exception_ptr(std::runtime_error("This is runtime error caused by human")));
	cout << "Get from child" << h << endl;
	return 0;
}