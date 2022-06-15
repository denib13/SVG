#include "ShapeCollection.h"

void ShapeCollection::resize()
{
	capacity *= 2;
	Shape** newShapes = new Shape * [capacity];
	for (size_t i = 0; i < count; i++)
	{
		newShapes[i] = shapes[i];
	}
	delete[] shapes;
	shapes = newShapes;
}

void ShapeCollection::free()
{
	for (size_t i = 0; i < count; i++)
	{
		delete shapes[i];
	}
	delete[] shapes;
}

void ShapeCollection::copyFrom(const ShapeCollection& other)
{
	count = other.count;
	capacity = other.capacity;

	shapes = new Shape * [capacity];
	for (size_t i = 0; i < count; i++)
	{
		shapes[i] = other.shapes[i]->clone();
	}
}

ShapeCollection::ShapeCollection()
{
	count = 0;
	capacity = 4;
	shapes = new Shape * [capacity];
}

ShapeCollection::ShapeCollection(const ShapeCollection& other)
{
	copyFrom(other);
}

ShapeCollection::ShapeCollection(ShapeCollection&& other)
{
	count = other.count;
	capacity = other.capacity;

	shapes = other.shapes;
	other.shapes = nullptr;
}

ShapeCollection::~ShapeCollection()
{
	free();
}

ShapeCollection& ShapeCollection::operator=(const ShapeCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

ShapeCollection& ShapeCollection::operator=(ShapeCollection&& other)
{
	if (this != &other)
	{
		free();
		count = other.count;
		capacity = other.capacity;

		shapes = other.shapes;
		other.shapes = nullptr;
	}
	return *this;
}

size_t ShapeCollection::getCount() const
{
	return count;
}

void ShapeCollection::addShape(const Shape& newShape)
{
	if (count == capacity)
		resize();
	shapes[count++] = newShape.clone();
}
