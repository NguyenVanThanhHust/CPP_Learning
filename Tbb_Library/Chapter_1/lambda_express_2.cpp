#include <iostream>
#include <vector>

using std::cout;
using std::endl;

void printValues(int i, int j, int k, int l)
{
    cout<<"i: "<<i<<" j: "<<j<<" k: "<<k<<" l: "<<l <<endl;
}

class function_object
{
private:
    int my_i;
    int &my_jRef;
public:
    function_object(int i, int &j): my_i{i}, my_jRef{j} {};

    int operator()(int k0, int &l0)
    {
        my_jRef = 2 * my_jRef;
        k0 = 2 * k0;
        l0 = 2 * l0;
        return my_i + my_jRef + k0 + l0;
    }
};

int main()
{
    int i = 1, j = 10, k = 100, l = 1000;
    function_object f{i,j};
    printValues(i, j, k, l);
    std::cout << "First call returned " << f(k, l) << std::endl;
    printValues(i, j, k, l);
    std::cout << "Second call returned " << f(k, l) << std::endl;
    printValues(i, j, k, l);

    return 0;
}