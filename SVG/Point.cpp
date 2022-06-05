#include "Point.h"
#include <iostream>

Point::Point()
{
	x = y = 0;
}

Point::Point(double xVal, double yVal)
{
	setX(xVal);
	setY(yVal);
}

double Point::getX() const
{
	return x;
}

double Point::getY() const
{
	return y;
}

void Point::setX(double xVal)
{
	xVal = (xVal < 0) ? (xVal * (-1)) : xVal;
	x = xVal;
}

void Point::setY(double yVal)
{
	yVal = (yVal < 0) ? (yVal * (-1)) : yVal;
	y = yVal;
}

void Point::print() const
{
	std::cout << x << " " << y;
}
