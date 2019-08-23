#include <iostream>
#include <deque>
#include <mutex>
#include <chrono>
#include <thread>

using namespace std;

std::deque<int> d;
std::mutex mu;
std::condition_variable cond_var;

/*
We create 2 function, one proceduce data and the other consume data
*/

// Producer
void producer_function()
{
	int count = 10;
	while (count > 0)
	{
		std::unique_lock<std::mutex> locker(mu);
		cout << "T1 is push front: " << count << endl;
		d.push_front(count);
		locker.unlock();
		cond_var.notify_one(); // Notify one waiting thread, if there is one
		std::this_thread::sleep_for(chrono::seconds(1));
		count--;
	}
}

// Consumer
void consumer_function()
{
	int data = 0;
	while (data != 1)
	{
		//std::unique_lock<std::mutex> locker(mu);
		//if (!d.empty())
		//{
		//	data = d.back();
		//	d.pop_back();
		//	locker.unlock();
		//	cout << "T2 got a value from T1" << data << endl;
		//}
		std::unique_lock<std::mutex> locker(mu);
		cond_var.wait(locker, []() {return !d.empty(); });
		data = d.back();
		d.pop_back();
		locker.unlock();
		cout << "T2 got a value from T1: " << data << endl;
	}
}

int main()
{
	
	std::thread t1(producer_function);
	std::thread t2(consumer_function);

	t1.join();
	t2.join();
	return 0;
}