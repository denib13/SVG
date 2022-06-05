#pragma once
#include "Shape.h"
#include "Point.h"

class Rectangle : public virtual Shape
{
	Point topLeft;
	double height;
	double width;
	double rx;
	double ry;
public:
	Rectangle(double x, double y, double height, double width, double rx, double ry);
	~Rectangle() = default;
	
	Shape* clone() const override;
	void print() const override;
};