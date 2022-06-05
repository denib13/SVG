#include "Circle.h"
#include <iostream>

Circle::Circle(double x, double y, double radius) : center(x,y)
{
	this->radius = radius;
}

Shape* Circle::clone() const
{
	return new Circle(*this);
}

void Circle::print() const
{
	center.print();
	std::cout << " " << radius;
}
