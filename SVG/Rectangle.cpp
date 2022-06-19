#include "Rectangle.h"
#include "Circle.h"
#include <iostream>

Rectangle::Rectangle(double x, double y, double width, double height, const char* fill)
	: topLeft(x,y), fill(fill)
{
	this->height = height;
	this->width = width;
}

Shape* Rectangle::clone() const
{
	return new Rectangle(*this);
}

void Rectangle::print() const
{
	std::cout << "rectangle ";
	topLeft.print();
	std::cout << " " << width << " " << height << " " << fill;
}

void Rectangle::writeShapeToFile(std::ostream& stream) const
{
	stream << *this;
}

void Rectangle::translateVertical(double value)
{
	topLeft.setY(topLeft.getY() + value);
}

void Rectangle::translateHorizontal(double value)
{
	topLeft.setX(topLeft.getX() + value);
}

bool Rectangle::containsShape(Shape* shape) const
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

bool Rectangle::containsRectangle(const Rectangle* rect) const
{
	bool containsTopLeft = containsPoint(rect->getTopLeft().getX(), rect->getTopLeft().getY());
	bool containsDownLeft = containsPoint(rect->getTopLeft().getX(),
		rect->getTopLeft().getY() - rect->getHeight());
	bool containsTopRight = containsPoint(rect->getTopLeft().getX() + rect->getWidth(),
		rect->getTopLeft().getY());
	bool containsDownRight = containsPoint(rect->getTopLeft().getX() + rect->getWidth(),
		rect->getTopLeft().getY() - rect->getHeight());
	
	return(containsTopLeft && containsTopRight && containsDownLeft && containsDownRight);
}

bool Rectangle::containsCircle(const Circle* circle) const
{
	bool containsTopPoint = containsPoint(circle->getCenter().getX(),
		circle->getCenter().getY() + circle->getRadius());
	bool containsDownPoint = containsPoint(circle->getCenter().getX(),
		circle->getCenter().getY() - circle->getRadius());
	bool containsLeftPoint = containsPoint(circle->getCenter().getX()
		- circle->getRadius(), circle->getCenter().getY());
	bool containsRightPoint = containsPoint(circle->getCenter().getX()
		+ circle->getRadius(), circle->getCenter().getY());
	
	return(containsTopPoint && containsDownPoint && containsLeftPoint && containsRightPoint);
}

bool Rectangle::containsLine(const Line* line) const
{
	return(containsPoint(line->getStart().getX(), line->getStart().getY())
		&& containsPoint(line->getEnd().getX(),line->getEnd().getY()));
}

bool Rectangle::containsPoint(double x, double y) const
{
	return (topLeft.getX() <= x && x <= topLeft.getX() + width
		&& topLeft.getY() - height <= y && y <= topLeft.getY());
}

double Rectangle::getHeight() const
{
	return height;
}

double Rectangle::getWidth() const
{
	return width;
}

const Point& Rectangle::getTopLeft() const
{
	return topLeft;
}

std::ostream& operator<<(std::ostream& stream, const Rectangle& rect)
{
	stream << "rect x=\"" << rect.topLeft.getX() << "\" y=\"" << rect.topLeft.getY() <<
		"\" width=\"" << rect.width << "\" height=\"" << rect.height << "\" fill=\"" << rect.fill << "\"";
	return stream;
}
