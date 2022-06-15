#pragma once
#include "Shape.h"
#include "Point.h"
#include "MyString.h"

class Circle : public virtual Shape
{
	Point center;
	double radius;
	MyString fill;
public:
	Circle(double x, double y, double radius, const char* fill);
	~Circle() = default;

	Shape* clone() const override;
	void print() const override;
};