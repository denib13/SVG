#pragma once
#include "MyString.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

enum CmdType
{
	open = 0, 
	close = 1,
	save = 2,
	saveas = 3,
	help = 4,
	exitCmd = 5,
	print = 6,
	create = 7,
	erase = 8,
	translate = 9,
	within = 10
};

class Command
{
	CmdType type;
	MyString cmd;

	void setType(const MyString& cmdType);
public:
	Command();
	void takeCommand();
	CmdType getType() const;

	MyString getFilePath();
	MyString getFigureType();
	Rectangle getRectangleData();
	Circle getCircleData();
	Line getLineData();
	MyString getProperties();
};