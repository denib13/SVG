#pragma once
#include "Shape.h"
#include "Point.h"
#include "MyString.h"
#include "Line.h"

class Rectangle;

class Circle : public virtual Shape
{
	Point center;
	double radius;
	MyString fill;

	void setRadius(double newRadius);
public:
	Circle(double x, double y, double radius, const char* fill);
	~Circle() = default;

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

	const Point& getCenter() const;
	double getRadius() const;

	friend std::ostream& operator<<(std::ostream& stream, const Circle& circle);
};