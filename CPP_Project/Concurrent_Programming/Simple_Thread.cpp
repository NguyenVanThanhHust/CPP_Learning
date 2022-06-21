#include <iostream>
#include <thread>

using namespace std;

// a dummy function
void print_function(int k)
{
    for (int i = 0; i < k; i++)
    {
        cout << "This thread using a function pointer as callable" << endl;
    }
}

// A callable object
class thread_object
{
public:
    void operator()(int k)
    {
        for (size_t i = 0; i < k; i++)
        {
            cout << "This thread using a function object" << endl;
        }
    }
};


int main()
{
    cout << "We have 3 thread running independently" << endl;
    
    thread t1(print_function, 5);
    thread t2(thread_object(), 5);
    

    // using a lambda expression
    auto lamda_expression = [](int x)
    {
        for (size_t i = 0; i < x; i++)
        {
            cout << "This thread is using lambda expression" << endl;
        }
    };

    thread t3(lamda_expression, 5);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}