#include <iostream>
#include <tbb/tbb.h>

int main()
{
    tbb::parallel_invoke(
        []() {std::cout<<"hello"<<std::endl;},
        []() {std::cout<<" world"<<std::endl;}
    );
    return 0;
}