#include <iostream>
#include <string>

class Entity
{
public:
    Entity()
    {
        std::cout << "Hello" << std::endl;
    }
    ~Entity()
    {
        std::cout << "Goodbue" << std::endl;
    }

private:

};

int main()
{
    
    {
        Entity e;
    }
    std::cin.get();
}