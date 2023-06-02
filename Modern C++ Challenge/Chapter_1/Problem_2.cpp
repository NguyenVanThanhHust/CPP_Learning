#include <iostream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;

int main()
{
    int x, y;
    cin>>x>>y;
    int tmp;
    int gcd=1;
    if(y >= x)
    {
        tmp = x;
        y = x;
        x = tmp;
    }
    if (x % y == 0)
    {
        cout>>y>>endl;
        return 0;
    }
    
    
    return 0;
}