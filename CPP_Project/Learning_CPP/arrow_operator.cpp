#include <iostream>
#include <string>

class Entity
{
public:
    void Print() const
    {
        std::cout << "Hello" << std::endl;
    }

private:


};
//overload operator ->
class ScopedPtr
{
public:
   
    ScopedPtr(Entity *entity) :m_Obj(entity)
    {

    }
    ~ScopedPtr()
    {
        delete m_Obj;
    }

    // now is overload part 
    Entity* operator->()
    {
        return m_Obj;
    }
private:
    Entity *m_Obj;

};


int main()
{
    Entity e;
    e.Print();

    Entity *ptr = &e;
    ptr->Print();

    ScopedPtr entiry = new Entity();
    entiry->Print();
    std::cin.get();

}