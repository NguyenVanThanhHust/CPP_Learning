#include <iostream>
#include <thread>

using std::cout;
using std::endl;

void hello()
{
    cout<<"Test hello concurrency" <<endl;
}
int main()
{
    std::thread t(hello);
    t.join();
    return 0;
}