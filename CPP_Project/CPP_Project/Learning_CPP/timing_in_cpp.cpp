#include <iostream>
#include <chrono>
#include <thread>

struct Timer
{
    std::chrono::time_point < std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;

    Timer()
    {
        start = std::chrono::high_resolution_clock::now();

    }
    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        float m = duration.count()*1000.0f;
        std::cout << "Timer took " << m << " ms" << std::endl;
    }
};
void Function()
{
    Timer timer;
    for (int i = 0; i < 100; i++)
    {
        //std::cout << "Hello" << std::endl; // took 47ms
        std::cout << "Hello \n"; // took 74ms, wtf?
    }
}

int main()
{/*
    auto start = std::chrono::high_resolution_clock::now();

    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(1s);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> duration = end - start;
    std::cout << duration.count() << std::endl;
*/
    Function();
    std::cin.get();
    return 0;
}