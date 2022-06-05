#pragma once

class Shape
{
public:
	virtual ~Shape() = default;
	virtual void print() const;
	virtual Shape* clone() const;
};