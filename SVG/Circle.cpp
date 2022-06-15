#include "Circle.h"
#include <iostream>

Circle::Circle(double x, double y, double radius, const char* fill) : center(x,y), fill(fill)
{
	this->radius = radius;
}

Shape* Circle::clone() const
{
	return new Circle(*this);
}

void Circle::print() const
{
	std::cout << "circle ";
	center.print();
	std::cout << " " << radius << " " << fill;
}
