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
	friend class SVGParser;
	ShapeCollection();
	ShapeCollection(const ShapeCollection& other);
	ShapeCollection(ShapeCollection&& other);
	~ShapeCollection();

	ShapeCollection& operator=(const ShapeCollection& other);
	ShapeCollection& operator=(ShapeCollection&& other);

	size_t getCount() const;

	void addShape(const Shape& newShape);
};