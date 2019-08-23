#include <iostream>
#include <time.h>
#include <random>
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

float Q_rsqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long *)&y;                       // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1);               // what the fuck? 
    y = *(float *)&i;
    y = y * (threehalfs - (x2 * y * y));   // 1st iteration
                                           //	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}

void Function()
{
    Timer timer;
    for (size_t i = 0; i < 10000; i++)
    {
        double lower_bound = 0;
        double upper_bound = 10000;
        std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
        std::default_random_engine re;
        double a_random_double = unif(re);
        double result = Q_rsqrt(a_random_double);
    }
}

void Fucntion2()
{
    Timer timer;
    for (size_t i = 0; i < 10000; i++)
    {
        double lower_bound = 0;
        double upper_bound = 10000;
        std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
        std::default_random_engine re;
        double a_random_double = unif(re);
        double result = 1 / std::sqrt(a_random_double);
    }
}
int main()
{
    
    Function();
    Fucntion2();
    
    std::cin.get();
}