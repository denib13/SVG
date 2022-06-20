#pragma once
#include "ShapeCollection.h"
#include "Command.h"
#include "MyString.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

class SVGParser
{
	ShapeCollection shapesList;
	MyString currFilePath;
	bool isFileOpen;
	bool isSaved;

	void readSvg(std::fstream& file);
	void writeSvg(std::fstream& file) const;
	void createRectangle(MyString& figureData);
	void createCircle(MyString& figureData);
	void createLine(MyString& figureData);
	void shapesWithinRectangle(const Rectangle& rect) const;
	void shapesWithinCircle(const Circle& circle) const;
public:
	SVGParser();

	void run();
	void open(Command& command);
	void close();
	void save();
	void saveas(Command& command);
	void help();
	void exit();
	void print() const;
	void create(Command& command);
	void erase(Command& command);
	void translate(Command& command);
	void withinRegion(Command& command);
};