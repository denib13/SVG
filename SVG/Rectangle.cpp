#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(double x, double y, double height, double width, const char* fill)
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
	std::cout << " " << height << " " << width << " " << fill;
}
