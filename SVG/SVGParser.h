#pragma once
#include "ShapeCollection.h"
#include "MyString.h"

class SVGParser
{
	ShapeCollection shapesList;

	void readSvg(std::fstream& file);
	void createRectangle(MyString& figureData);
	void createCircle(MyString& figureData);
	void createLine(MyString& figureData);
public:
	SVGParser();

	void open(const char* filePath);
	void close();
	void save();
	void saveas();
	void help();
	void exit();
	void print() const;
	void create();
	void erase();
	void translate();
	void withinRegion();
};