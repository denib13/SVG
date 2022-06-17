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
	Shape* operator[](size_t index) const;
	friend std::ostream& operator<<(std::ostream& stream, const ShapeCollection& col);

	size_t getCount() const;

	void addShape(const Shape& newShape);
	void emptyCollection();
	void deleteAtIndex(size_t index);
};