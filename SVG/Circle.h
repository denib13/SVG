#pragma once
#include "Shape.h"
#include "Point.h"

class Circle : public virtual Shape
{
	Point center;
	double radius;
public:
	Circle(double x, double y, double radius);
	~Circle() = default;

	Shape* clone() const override;
	void print() const override;
};