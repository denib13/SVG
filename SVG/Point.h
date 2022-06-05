#pragma once

class Point
{
	double x;
	double y;
public:
	Point();
	Point(double xVal, double yVal);

	double getX() const;
	double getY() const;
	
	void setX(double xVal);
	void setY(double yVal);

	void print() const;
};