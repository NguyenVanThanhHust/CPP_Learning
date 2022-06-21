#include <iostream>

struct Point
{
	int x;
	int y;
};

class Shape
{
public:
	virtual Point center() const = 0;
	virtual void move(Point to) = 0;
	virtual void rotate(int angle) = 0;
	virtual void draw() = 0;
	virtual ~Shape() {};
};

class Circle:public Shape
{
public:
	Circle(Point p, int r);
	Point center() const override;
	void move(Point to) override;
	void rotate(int angle) override;
	void draw() override ;
	~Circle();

private:
	Point x;
	int radius;
};

Circle::Circle(Point p, int r)
{
	x = p;
	radius = r;
}

Circle::~Circle()
{
}

Point Circle::center() const
{
	return x;
}
void Circle::move(Point to)
{
	x = to;
}

void Circle::rotate(int angle)
{
	// do nothing because this is circle
}

void Circle::draw()
{
	std::cout << x.x << " " << x.y << std::endl;
	std::cout << radius << std::endl;
}

int main()
{
	Point p = { 1, 2 };
	Circle c_example(p, 5);
	c_example.draw();
	return 0;
}
