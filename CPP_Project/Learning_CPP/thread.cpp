#include <iostream>
#include <thread>

static bool s_Finished = false;
void DoWork()
{
    using namespace std::literals::chrono_literals;
    std::cout << "This thread has id = " << std::this_thread::get_id() << std::endl;
    while (!s_Finished)
    {
        std::cout << "Working..." << std::endl;
        std::this_thread::sleep_for(1s);
    }
   
}

int main()
{
    //create new thread "worker", run function "DoWork"
    std::thread worker(DoWork);
    std::cin.get();
    s_Finished = true;
    // Stop this thread
    worker.join();
    std::cout << "This thread has id = " << std::this_thread::get_id() << std::endl;

    std::cin.get();

}