#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(double x, double y, double height, double width, double rx, double ry)
	: topLeft(x,y)
{
	this->height = height;
	this->width = width;
	this->rx = rx;
	this->ry = ry;
}

Shape* Rectangle::clone() const
{
	return new Shape(*this);
}

void Rectangle::print() const
{
	topLeft.print();
	std::cout << " " << height << " " << width << " " << rx << " " << ry;
}
