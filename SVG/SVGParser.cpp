#include <iostream>
#include <fstream>
#include "SVGParser.h"

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

void SVGParser::writeSvg(std::fstream& file)
{
	file << "<?xml version=\"1.0\" standalone=\"no\"?>\n";
	file << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n" << "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
	file << "<svg>\n";
	file << shapesList;
	file << "</svg>";
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


SVGParser::SVGParser() : shapesList(), currFilePath(), isFileOpen(false)
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

void SVGParser::run()
{
	CmdType commandType;
	do
	{
		Command command;
		command.takeCommand();
		commandType = command.getType();
		switch (commandType)
		{
		case 0: open(command); break;
		//case 1: close(); break;
		case 2: save(); break;
		case 3: saveas(command); break;
		case 4: help(); break;
		//case 5: exit(); break;
		case 6: print(); break;
		case 7: create(command); break;
		//case 8: erase(command); break;
		//case 9: translate(command); break;
		//case 10: withinRegion(command); break;
		default:
			break;
		}
	} while (!(commandType == CmdType::exitCmd));
}

void SVGParser::open(Command& command)
{
	if (isFileOpen)
	{
		std::cout << "A file is currently open. Close it first before opening new one! \n";
	}
	else
	{
		MyString filePath = command.getFilePath();
		currFilePath = filePath;
		isFileOpen = true;

		std::fstream file(filePath.getString(), std::ios::in);
		if (!file.is_open())
		{
			closeFile(file);
			std::fstream createFile(filePath.getString(), std::ios::out);
			closeFile(createFile);
		}
		else
		{
			std::cout << "Successfully opened " << filePath << "!\n";
			readSvg(file);
			closeFile(file);
		}
	}
}

void SVGParser::save()
{
	if (isFileOpen)
	{
		std::fstream file(currFilePath.getString(), std::ios::out);
		if (!file.is_open())
			std::cout << "Error writing to file! \n";
		else
		{
			writeSvg(file);
			std::cout << "Successfully saved file " << currFilePath << "!\n";
		}
		closeFile(file);
	}
	else
	{
		std::cout << "There is no currently opened file! \n";
	}
}

void SVGParser::saveas(Command& command)
{
	if (isFileOpen)
	{
		MyString filePath = command.getFilePath();
		std::fstream file(filePath.getString(), std::ios::out);
		if (!file.is_open())
			std::cout << "Error writing to file! \n";
		else
		{
			writeSvg(file);
			std::cout << "Successfully saved file " << filePath << "!\n";
		}
		closeFile(file);
	}
	else
	{
		std::cout << "There is no currently opened file! \n";
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

void SVGParser::create(Command& command)
{
	if (isFileOpen)
	{
		MyString figureType = command.getFigureType();
		if (figureType == "rectangle")
			shapesList.addShape(command.getRectangleData());
		else if (figureType == "circle")
			shapesList.addShape(command.getCircleData());
		else if (figureType == "line")
			shapesList.addShape(command.getLineData());
		else
			std::cout << "Invalid figure type! \n";
	}
	else
		std::cout << "Open a file first! \n";
}
