#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using std::endl;
using std::cout;
using std::cin;

class simple_class 
{
public:
    int class_id, number_repeat, sleep_time;
    simple_class(int number_repeat_, int sleep_time_);
    ~simple_class();
    void execute(std::string message);
};

simple_class::simple_class(int class_id_, int number_repeat_, int sleep_time_)
{
    class_id = class_id_;
    number_repeat = number_repeat_;
    sleep_time = sleep_time_;
}

void simple_class::execute(std::string& message)
{
    for (size_t i = 0; i < number_repeat; i++)
    {
        cout<<"class id: " << class_id << " at time: "<< i << " message: "<<message<<endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    }
}

int main()
{

}