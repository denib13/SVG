#pragma once

class Shape
{
public:
	virtual ~Shape() = default;
	virtual void print() const = 0;
	virtual Shape* clone() const = 0;
};