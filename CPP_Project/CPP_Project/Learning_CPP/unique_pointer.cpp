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
int main()
{
	{
		std::unique_ptr<Entity> entity(new Entity());
		entity->Print_entity();
	}
	std::cin.get();
}