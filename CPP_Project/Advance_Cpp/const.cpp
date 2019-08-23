#include <iostream>

using namespace std;

// const : a complie time constraint that an object can not be modified
int main()
{
    const int i = 9;

    const int *p1 = &i;// data is const, pointer is not
    cout << "pointer to i:" << p1 << endl;
    p1++;

    int* const p2 = 0; // pointer to integer is const, data is not

    const int* const p3 = &i; // both data and pointer are const

    // If const is on the left of *, data is const
    // If const is on the right of *, pointer is const
    cout << "I value: " << i << endl;
    cout << "pointer to i increased: " << p1 << endl;
    cout << "const pointer p2: " << p2 << endl;
    return 0;
}