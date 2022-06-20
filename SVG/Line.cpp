#include <iostream>
#include "Line.h"
using namespace std;

Line::Line(double startX, double startY, double endX, double endY) : start(startX, startY), end(endX, endY)
{
}

Shape* Line::clone() const
{
	return new Line(*this);
}

void Line::print() const
{
	std::cout << "line ";
	start.print();
	std::cout << " ";
	end.print();
}

void Line::writeShapeToFile(std::ostream& stream) const
{
	stream << *this;
}

void Line::translateVertical(double value)
{
	if(start.getY() != 0 || value >= 0)
		start.setY(start.getY() + value);
	if(end.getY() != 0 || value >= 0)
		end.setY(end.getY() + value);
}

void Line::translateHorizontal(double value)
{
	if(start.getX() != 0 || value >= 0)
		start.setX(start.getX() + value);
	if(end.getX() != 0 || value >= 0)
		end.setX(end.getX() + value);
}

const Point& Line::getStart() const
{
	return start;
}

const Point& Line::getEnd() const
{
	return end;
}

ostream& operator<<(ostream& stream, const Line& line)
{
	stream << "line x1=\"" << line.start.getX() << "\" y1=\"" << line.start.getY() <<
		"\" x2=\"" << line.end.getX() << "\" y2=\"" << line.end.getY() << "\"";
	return stream;
}
