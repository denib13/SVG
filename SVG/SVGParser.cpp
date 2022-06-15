#include <iostream>
#include <fstream>
#include "SVGParser.h"
#include "MyString.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

void SVGParser::readSvg(std::fstream& file)
{
	MyString svgFile;
	file.seekg(0, std::ios::beg);
	while (!file.eof())
	{
		char symbol[2];
		file.get(symbol[0]);
		symbol[1] = '\0';
		if (symbol[0] != '\n' && symbol[0] != '\t')
			svgFile.concat(symbol);
		file.peek();
	}
	int startIndex = svgFile.indexOf("<svg>") + 5;
	int endIndex = svgFile.getSize();
	while(svgFile.charAtIndex(--endIndex) != '<') {}
	while (startIndex != endIndex)
	{
		if (svgFile.charAtIndex(startIndex) == '<')
		{
			startIndex++;
			MyString figureData;
			while (svgFile.charAtIndex(startIndex) != '/')
			{
				figureData.concat(svgFile.substring(startIndex, startIndex + 1));
				startIndex++;
			}
			unsigned firstIntervalIndex = figureData.indexOf(" ");
			MyString figureType = figureData.substring(0, firstIntervalIndex);
			figureData.trim(firstIntervalIndex + 1);

			if (figureType == "rect")
				createRectangle(figureData);
			else if (figureType == "circle")
				createCircle(figureData);
			else if (figureType == "line")
				createLine(figureData);
			else
				std::cout << "Unknown figure type!";
		}
		else
			startIndex++;
	}
}

MyString getProperties(MyString& word)
{
	int quotMarksIndex = word.indexOf("\"");
	word.trim(quotMarksIndex + 1);
	quotMarksIndex = word.indexOf("\"");
	MyString result = word.substring(0, quotMarksIndex);
	word.trim(quotMarksIndex + 1);
	return result;
}

void SVGParser::createRectangle(MyString& figureData)
{
	MyString* properties = new MyString[5];
	for (size_t i = 0; i < 5; i++)
	{
		properties[i] = getProperties(figureData);
	}
	Rectangle newRect(properties[0].toDouble(), properties[1].toDouble(), properties[2].toDouble(),
		properties[3].toDouble(), properties[4].getString());
	shapesList.addShape(newRect);
	delete[] properties;
}

void SVGParser::createCircle(MyString& figureData)
{
	MyString* properties = new MyString[4];
	for (size_t i = 0; i < 4; i++)
	{
		properties[i] = getProperties(figureData);
	}
	Circle newCircle(properties[0].toDouble(), properties[1].toDouble(), properties[2].toDouble(),
		properties[3].getString());
	shapesList.addShape(newCircle);
	delete[] properties;
}

void SVGParser::createLine(MyString& figureData)
{
	MyString* properties = new MyString[4];
	for (size_t i = 0; i < 4; i++)
	{
		properties[i] = getProperties(figureData);
	}
	Line newLine(properties[0].toDouble(), properties[1].toDouble(), properties[2].toDouble(),
		properties[3].toDouble());
	shapesList.addShape(newLine);
	delete[] properties;
}


SVGParser::SVGParser() : shapesList()
{ }

void closeFile(std::fstream& file)
{
	try
	{
		file.close();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << '\n';
	}
}

void SVGParser::open(const char* filePath)
{
	std::fstream file(filePath, std::ios::in);
	if (!file.is_open())
	{
		closeFile(file);
		std::fstream createFile(filePath, std::ios::out);
		closeFile(createFile);
	}
	else
	{
		std::cout << "Successfully opened " << filePath << "!\n";
		readSvg(file);
		closeFile(file);
	}
}

void SVGParser::help()
{
	std::cout << "The following commands are supported: \n";
	std::cout << "open <file>";
	std::cout.width(20);
	std::cout << "opens <file> \n";
	std::cout << "close";
	std::cout.width(42);
	std::cout << "closes currently opened file \n";
	std::cout << "save";
	std::cout.width(44);
	std::cout << "saves the currently open file \n";
	std::cout << "saveas <file>";
	std::cout.width(45);
	std::cout << "saves the currently open file in <file> \n";
	std::cout << "help";
	std::cout.width(38);
	std::cout << "prints this information \n";
	std::cout << "exit";
	std::cout.width(33);
	std::cout << "exists the program \n";
	std::cout << "print";
	std::cout.width(32);
	std::cout << "prints all figures \n";
	std::cout << "create";
	std::cout.width(31);
	std::cout << "creates new figure \n";
	std::cout << "erase <n>";
	std::cout.width(37);
	std::cout << "deletes a figure on index n \n";
	std::cout << "translate [<n>]";
	std::cout.width(65);
	std::cout << "translates the n-th figure or all firures if n is not entered \n";
	std::cout << "within <option>";
	std::cout.width(66);
	std::cout << "prints all figures in the region; option - circle or rectangle \n";
}

void SVGParser::print() const
{
	for (size_t i = 0; i < shapesList.count; i++)
	{
		std::cout << (i + 1) << ". ";
		shapesList.shapes[i]->print();
		std::cout << '\n';
	}
}
