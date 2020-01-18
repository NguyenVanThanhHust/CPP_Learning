#include <algorithm>
#include <iostream>
#include <vector>
#include <tbb/tbb.h>

using std::cout;
using std::endl;

void print_function(int v)
{
    cout<<v<<endl;
}

void figure_2_06(int N, const std::vector<int> &a)
{
    tbb::parallel_for(0, N, 1, [a](int i){
        print_function(a[i]);
    });
}

int main()
{
    const int N = 1000;
    std::vector<int> v(N, 0);
    int i = 0;
    std::generate(v.begin(), v.end(), [&i]() { return i++; });
    figure_2_06(N, v);
}