#include <iostream>
#include <thread>

using namespace std;

void threadFn(int value)
{
    cout << "Value => " << value << endl;
}

int main()
{
    int localValue = 100;
    thread t1{ threadFn, localValue };
    t1.join();
    std::cin.get();
    return 0;
}
