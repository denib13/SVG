#pragma once
#include "Shape.h"
#include "Point.h"

class Line : public virtual Shape
{
	Point start;
	Point end;
public:
	Line(double startX, double startY, double endX, double endY);
	~Line() = default;

	Shape* clone() const override;
	void print() const override;
};