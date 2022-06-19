#pragma once
#include "Shape.h"
#include "Point.h"
using namespace std;

class Line : public virtual Shape
{
	Point start;
	Point end;
public:
	Line(double startX, double startY, double endX, double endY);
	~Line() = default;

	Shape* clone() const override;
	void print() const override;
	void writeShapeToFile(std::ostream& stream) const override;
	void translateVertical(double value) override;
	void translateHorizontal(double value) override;

	friend std::ostream& operator<<(std::ostream& stream, const Line& line);
};