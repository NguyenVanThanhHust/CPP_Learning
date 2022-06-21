#include <iostream>

/*
Simplified 
lvalue : an object that occupies some identifiable location in memory
rvalue : any object that is not a lvalue

lvalue = logical address value , rvalue = register value
*/
int main()
{
    // Examples
    int i; // i is a lvalue
    int *p = &i; // i's address is identifiable
    i = 2; // 2 is an rvalue
    return 0;
}