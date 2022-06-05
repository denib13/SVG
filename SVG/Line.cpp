#include "Line.h"
#include <iostream>

Line::Line(double startX, double startY, double endX, double endY) : start(startX, startY), end(endX, endY)
{
}

Shape* Line::clone() const
{
	return new Line(*this);
}

void Line::print() const
{
	start.print();
	std::cout << " ";
	end.print();
}
