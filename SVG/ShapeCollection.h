#pragma once
#include "Shape.h"

class ShapeCollection
{
	Shape** shapes;
	size_t count;
	size_t capacity;

	void resize();
	void free();
	void copyFrom(const ShapeCollection& other);
public:
	ShapeCollection(const ShapeCollection& other);
	ShapeCollection(ShapeCollection&& other);
	~ShapeCollection();

	ShapeCollection& operator=(const ShapeCollection& other);
	ShapeCollection& operator=(ShapeCollection&& other);

	void addShape(const Shape& newShape);
};