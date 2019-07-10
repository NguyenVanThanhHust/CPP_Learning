//this example to learn how to use smart pointer in c++
#include <iostream>
#include <string>
#include <memory>

class Entity
{
public:
	Entity();
	~Entity();
	void Print_entity();
private:

};

Entity::Entity()
{
	std::cout << "Create Entity" << std::endl;
}

Entity::~Entity()
{
	std::cout << "Destroy Entity" << std::endl;
}

void Entity::Print_entity()
{
	std::cout << "Print some function in class entity" << std::endl;
}

//difference between shared pointer and unique pointer is that you can not copy unique pointer
//but you can copy shared pointer, don't use weak pointer
int main()
{
	{
		std::shared_ptr<Entity> e0;
		{

			std::shared_ptr<Entity> shared_entity = std::make_shared<Entity>();
			e0 = shared_entity;
		}
	}

	std::cin.get();
}