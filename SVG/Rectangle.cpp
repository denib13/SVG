#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(double x, double y, double width, double height, const char* fill)
	: topLeft(x,y), fill(fill)
{
	this->height = height;
	this->width = width;
}

Shape* Rectangle::clone() const
{
	return new Rectangle(*this);
}

void Rectangle::print() const
{
	std::cout << "rectangle ";
	topLeft.print();
	std::cout << " " << width << " " << height << " " << fill;
}

void Rectangle::writeShapeToFile(std::ostream& stream) const
{
	stream << *this;
}

std::ostream& operator<<(std::ostream& stream, const Rectangle& rect)
{
	stream << "rect x=\"" << rect.topLeft.getX() << "\" y=\"" << rect.topLeft.getY() <<
		"\" width=\"" << rect.width << "\" height=\"" << rect.height << "\" fill=\"" << rect.fill << "\"";
	return stream;
}
