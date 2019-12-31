#include <iostream>
#include <memory>

using std::cout;
using std::endl;

void printValues(int i, int j, int k, int l)
{
    cout<<"i: "<<i<<" j: "<<j<<" k: "<<k<<" l: "<<l <<endl;
}
int main()
{
    int i = 1, j = 10, k = 100, l = 1000;
    auto lambdaExpression = [i, &j](int k0, int &l0) -> int{
        j = 2 * j;
        k0 = 2 * k0;
        l0 = 2 * l0;
        return i + j + k0 + l0;
    };

    printValues(i, j, k, l);
    cout<<"First call returned: "<<lambdaExpression(k, l) <<endl;

    printValues(i, j, k, l);
    cout<<"Second call returned: "<<lambdaExpression(k, l) <<endl;

    printValues(i, j, k, l);
    return 0;
}