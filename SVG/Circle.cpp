#include "Circle.h"
#include "Rectangle.h"
#include <iostream>

Circle::Circle(double x, double y, double radius, const char* fill) : center(x,y), fill(fill)
{
	this->radius = radius;
}

Shape* Circle::clone() const
{
	return new Circle(*this);
}

void Circle::print() const
{
	std::cout << "circle ";
	center.print();
	std::cout << " " << radius << " " << fill;
}

void Circle::writeShapeToFile(std::ostream& stream) const
{
	stream << *this;
}

void Circle::translateVertical(double value)
{
	center.setY(center.getY() + value);
}

void Circle::translateHorizontal(double value)
{
	center.setX(center.getX() + value);
}

bool Circle::containsShape(Shape* shape) const
{
	Rectangle* rectPtr = dynamic_cast<Rectangle*>(shape);
	if (rectPtr == nullptr)
	{
		Circle* circlePtr = dynamic_cast<Circle*>(shape);
		if (circlePtr == nullptr)
		{
			Line* linePtr = dynamic_cast<Line*>(shape);
			return containsLine(linePtr);
		}
		else
			return containsCircle(circlePtr);
	}
	else
		return containsRectangle(rectPtr);
}

bool Circle::containsRectangle(const Rectangle* rect) const
{
	bool containsTopLeft = containsPoint(rect->getTopLeft().getX(), rect->getTopLeft().getY());
	bool containsDownLeft = containsPoint(rect->getTopLeft().getX(),
		rect->getTopLeft().getY() - rect->getHeight());
	bool containsTopRight = containsPoint(rect->getTopLeft().getX() + rect->getWidth(),
		rect->getTopLeft().getY());
	bool containsDownRight = containsPoint(rect->getTopLeft().getX() + rect->getWidth(),
		rect->getTopLeft().getY() - rect->getHeight());

	return(containsTopLeft && containsDownLeft && containsTopRight && containsDownRight);
}

bool Circle::containsCircle(const Circle* circle) const
{
	bool containsTopPoint = containsPoint(circle->getCenter().getX(),
		circle->getCenter().getY() + circle->getRadius());
	bool containsDownPoint = containsPoint(circle->getCenter().getX(),
		circle->getCenter().getY() - circle->getRadius());
	bool containsLeftPoint = containsPoint(circle->getCenter().getX() - circle->getRadius(),
		circle->getCenter().getY());
	bool containsRightPoint = containsPoint(circle->getCenter().getX() + circle->getRadius(),
		circle->getCenter().getY());

	return(containsTopPoint && containsDownPoint && containsLeftPoint && containsRightPoint);
}

bool Circle::containsLine(const Line* line) const
{
	return(containsPoint(line->getStart().getX(), line->getStart().getY())
		&& containsPoint(line->getEnd().getX(), line->getEnd().getY()));
}

bool Circle::containsPoint(double x, double y) const
{
	return(((x - center.getX()) * (x - center.getX()) +
		(y - center.getY()) * (y - center.getY())) <= radius * radius);
}

const Point& Circle::getCenter() const
{
	return center;
}

double Circle::getRadius() const
{
	return radius;
}

std::ostream& operator<<(std::ostream& stream, const Circle& circle)
{
	stream << "circle cx=\"" << circle.center.getX() << "\" cy=\"" << circle.center.getY() <<
		"\" r=\"" << circle.radius << "\" fill=\"" << circle.fill << "\"";
	return stream;
}
