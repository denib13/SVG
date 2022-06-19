#pragma once
#include <iostream>
using namespace std;

class Shape
{
public:
	virtual ~Shape() = default;
	virtual void print() const = 0;
	virtual Shape* clone() const = 0;
	virtual void writeShapeToFile(ostream& stream) const = 0;
	virtual void translateVertical(double value) = 0;
	virtual void translateHorizontal(double value) = 0;
};