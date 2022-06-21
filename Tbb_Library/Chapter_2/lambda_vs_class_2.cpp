#include <vector>
#include <tbb/tbb.h>
#include <iostream>

using std::cout;
using std::endl;

void print_fucntion(int v)
{
    cout<<"v: "<< v<<endl;    
}

class Body
{
private:
    const std::vector<int> &myVector;
public:
    Body(const std::vector<int> &v) : myVector{v} {};
    void operator()(int i) const {
        print_fucntion(myVector[i]);
    }
};

void sidebar_pfor_function(int N, const std::vector<int> &a)
{
    tbb::parallel_for(0, N, 1, Body(a));
}

int main()
{
    std::vector<int> v = {4, 5, 6, 7, 8};
    sidebar_pfor_function(5, v);
    return 0;
}