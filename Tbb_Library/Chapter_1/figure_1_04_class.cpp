#include <iostream>
#include <tbb/tbb.h>

using std::cout;
using std::endl;

void print_function(const std::string &s)
{
    cout<<s<<endl;
}
class printClass
{
private:
    const std::string &myString;
public:
    printClass(const std::string &s): myString{s} {};
    void operator()(std::string s) const{
        print_function(myString);
    } 
};

int main()
{
    std::string s1 = "Hello", s2 = "TBB!";
    tbb::parallel_invoke(
        printClass(s1),
        printClass(s2)
    );
    return 0;
}