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

ostream& operator<<(ostream& stream, const Line& line)
{
	stream << "line x1=\"" << line.start.getX() << "\" y1=\"" << line.start.getY() <<
		"\" x2=\"" << line.end.getX() << "\" y2=\"" << line.end.getY() << "\"";
	return stream;
}
