#include <vector>
#include <tbb/tbb.h>
#include <iostream>

using std::cout;
using std::endl;

void print_fucntion(int v)
{
    cout<<"v: "<< v<<endl;    
}
void sidebar_pfor_lambda(int N, const std::vector<int> &a)
{
    tbb::parallel_for(0, N, 1, [&a](int i)
    {
        print_fucntion(a[i]);
    });
}

int main()
{
    std::vector<int> v = {4, 5, 6, 7, 8};
    sidebar_pfor_lambda(5, v);
    return 0;
}
