#include <vector>
#include <thread>
#include <iostream>
#include <mutex>
#include <algorithm>
#include <string>

#include <chrono> 
using namespace std::chrono;

int main()
{
    const size_t nloop = 11;
    auto start = high_resolution_clock::now();
    // Serial version
    {
        // Pre loop
        std::cout << "serial:" << std::endl;
        // loop over all items
        for (int i = 0; i<nloop; i++)
        {
            // inner loop
            {
                const int j = i*i;
                std::cout << j << std::endl;
            }
        }
        // Post loop
        std::cout << std::endl;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time of serial : " << duration.count() << std::endl;
   
    
    // Parallel version
    // number of threads
    auto start_parallel = high_resolution_clock::now();
    const size_t nthreads = std::thread::hardware_concurrency();
    {
        // Pre loop
        std::cout << "parallel (" << nthreads << " threads):" << std::endl;
        std::vector<std::thread> threads(nthreads);
        std::mutex critical;
        for (int t = 0; t<nthreads; t++)
        {
            threads[t] = std::thread(std::bind(
                [&](const int bi, const int ei, const int t)
            {
                // loop over all items
                for (int i = bi; i<ei; i++)
                {
                    // inner loop
                    {
                        const int j = i*i;
                        // (optional) make output critical
                        std::lock_guard<std::mutex> lock(critical);
                        std::cout << j << std::endl;
                    }
                }
            }, t*nloop / nthreads, (t + 1) == nthreads ? nloop : (t + 1)*nloop / nthreads, t));
        }
        std::for_each(threads.begin(), threads.end(), [](std::thread& x) {x.join(); });
        auto stop_parallel = high_resolution_clock::now();
        auto duration_parallel = duration_cast<microseconds>(stop_parallel - start_parallel);
        std::cout << "Time of parallel : " << duration_parallel.count() << std::endl;

        // Post loop
        std::cout << std::endl;
    }
}