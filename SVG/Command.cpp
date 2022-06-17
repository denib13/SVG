#include "Command.h"

void Command::setType(const MyString& cmdType)
{
	if (cmdType == "close")
		type = CmdType::close;
	else if (cmdType == "create")
		type = CmdType::create;
	else if (cmdType == "erase")
		type = CmdType::erase;
	else if (cmdType == "exit")
		type = CmdType::exitCmd;
	else if (cmdType == "help")
		type = CmdType::help;
	else if (cmdType == "open")
		type = CmdType::open;
	else if (cmdType == "print")
		type = CmdType::print;
	else if (cmdType == "save")
		type = CmdType::save;
	else if (cmdType == "saveas")
		type = CmdType::saveas;
	else if (cmdType == "translate")
		type = CmdType::translate;
	else if (cmdType == "within")
		type = CmdType::within;
	else
		type = CmdType::help; //default type
}

Command::Command() : cmd()
{
	type = CmdType::help;
}

void Command::takeCommand()
{
	MyString text;
	std::cin >> text;

	if (text.charAtIndex(0) != '<')
	{
		std::cout << "Invalid command format! \n";
	}
	else
	{
		int intervalIndex = text.indexOf(" ");
		if (intervalIndex != -1)
		{
			text.trim(intervalIndex + 1);
			intervalIndex = text.indexOf(" ");
			if (intervalIndex != -1)
			{
				MyString cmdType = text.substring(0, intervalIndex);
				text.trim(intervalIndex + 1);

				cmd = text;
				setType(cmdType);
			}
			else
			{
				setType(text);
			}
		}
		else
			std::cout << "Invalid command format! \n";
	}
}

CmdType Command::getType() const
{
	return type;
}

MyString Command::getFilePath()
{
	//file path is the only argument in this type of command
	return cmd;
}

MyString Command::getFigureType()
{
	return getProperties();
}

Rectangle Command::getRectangleData()
{
	MyString* properties = new MyString[5];
	for (size_t i = 0; i < 5; i++)
	{
		properties[i] = getProperties();
	}
	Rectangle newRectangle(properties[0].toDouble(), properties[1].toDouble(), properties[2].toDouble(),
		properties[3].toDouble(), properties[4].getString());
	delete[] properties;
	return newRectangle;
}

Circle Command::getCircleData()
{
	MyString* properties = new MyString[4];
	for (size_t i = 0; i < 4; i++)
	{
		properties[i] = getProperties();
	}
	Circle newCircle(properties[0].toDouble(), properties[1].toDouble(), properties[2].toDouble(),
		properties[3].getString());
	delete[] properties;
	return newCircle;
}

Line Command::getLineData()
{
	MyString* properties = new MyString[4];
	for (size_t i = 0; i < 4; i++)
	{
		properties[i] = getProperties();
	}
	Line newLine(properties[0].toDouble(), properties[1].toDouble(), properties[2].toDouble(),
		properties[3].toDouble());
	delete[] properties;
	return newLine;
}

MyString Command::getProperties()
{
	int intervalIndex = cmd.indexOfChar(' ');
	if (intervalIndex != -1)
	{
		MyString result = cmd.substring(0, intervalIndex);
		cmd.trim(intervalIndex + 1);
		return result;
	}
	else
		return cmd;
}

