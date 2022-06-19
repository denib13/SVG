#include "ShapeCollection.h"
#include <exception>
#include <iostream>

const unsigned DEFAULT_CAPACITY = 4;

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
	capacity = DEFAULT_CAPACITY;
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

Shape* ShapeCollection::operator[](size_t index) const
{
	if (index < 0 || index >= count)
		throw std::exception("Index out of range!");
	return shapes[index]->clone();
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

void ShapeCollection::emptyCollection()
{
	free();
	count = 0;
	capacity = DEFAULT_CAPACITY;
	shapes = new Shape * [capacity];
}

void ShapeCollection::deleteAtIndex(size_t index)
{
	if (index < 0 || index >= count)
		throw std::exception("Index out of range!");
	else
	{
		delete shapes[index];
 		for (size_t i = index; i < count - 1; i++)
		{
			shapes[i] = shapes[i + 1];
		}
		count--;
	}
}

std::ostream& operator<<(std::ostream& stream, const ShapeCollection& col)
{
	for (size_t i = 0; i < col.count; i++)
	{
		stream << "\t <";
		col.shapes[i]->writeShapeToFile(stream);
		stream << "/>\n";
	}
	return stream;
}
