#pragma once
#include "Shape.h"
#include "Point.h"
#include "MyString.h"
#include "Line.h"

class Circle;

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
	void writeShapeToFile(std::ostream& stream) const override;
	void translateVertical(double value) override;
	void translateHorizontal(double value) override;

	bool containsShape(Shape* shape) const;
	bool containsRectangle(const Rectangle* rect) const;
	bool containsCircle(const Circle* circle) const;
	bool containsLine(const Line* line) const;
	bool containsPoint(double x, double y) const;

	double getHeight() const;
	double getWidth() const;
	const Point& getTopLeft() const;

	friend std::ostream& operator<<(std::ostream& stream, const Rectangle& rect);
};