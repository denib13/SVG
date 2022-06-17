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

void Circle::writeShapeToFile(std::ostream& stream) const
{
	stream << *this;
}

std::ostream& operator<<(std::ostream& stream, const Circle& circle)
{
	stream << "circle cx=\"" << circle.center.getX() << "\" cy=\"" << circle.center.getY() <<
		"\" r=\"" << circle.radius << "\" fill=\"" << circle.fill << "\"";
	return stream;
}
