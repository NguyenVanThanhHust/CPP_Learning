#include <iostream>

using std::cout;
using std::endl;
using std::cin;

class Dog
{
public:
    Dog();
    ~Dog();
    void setAge(const int &a);
private:
    
public:
    int age;
    std::string name;
};

Dog::Dog()
{
    age = 3;
    name = "dummy";
}

Dog::~Dog()
{
}

void Dog::setAge(const int &a)
{
    age = a;
}
int main()
{
    Dog d;
    int i = 9;
    d.setAge(i);
    cout << "i value :" << i << endl;
    cout << "dog age: " << d.age << endl;

    return 0;
}