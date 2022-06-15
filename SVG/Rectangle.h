#pragma once
#include "Shape.h"
#include "Point.h"
#include "MyString.h"

class Rectangle : public virtual Shape
{
	Point topLeft;
	double height;
	double width;
	MyString fill;
public:
	Rectangle(double x, double y, double height, double width, const char* fill);
	~Rectangle() = default;
	
	Shape* clone() const override;
	void print() const override;
};