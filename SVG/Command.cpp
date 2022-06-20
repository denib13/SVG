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

	if (text.charAtIndex(0) != '>')
	{
		std::cout << "Invalid command format! \n";
	}
	else
	{
		text.trim(1);
		text.cutIntervalsInBeginning();
		int intervalIndex = text.indexOfChar(' ');
		if (intervalIndex != -1)
		{
			setType(text.substring(0, intervalIndex));
			text.trim(intervalIndex + 1);
			cmd = text;
		}
		else
		{
			setType(text);
		}
	}
}

CmdType Command::getType() const
{
	return type;
}

MyString Command::getFilePath()
{
	return getProperties();
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
	cmd.cutIntervalsInBeginning();
	int intervalIndex = cmd.indexOfChar(' ');
	if (intervalIndex != -1)
	{
		MyString result = cmd.substring(0, intervalIndex);
		cmd.trim(intervalIndex + 1);
		return result;
	}
	else
	{
		MyString result = cmd;
		cmd = "";
		return result;
	}
}

int Command::getEraseIndex()
{
	MyString eraseIndexString = getProperties();
	if (eraseIndexString == "" || eraseIndexString == " ")
		return -1;
	else
		return atoi(eraseIndexString.getString());
}

int Command::getTranslateIndex()
{
	cmd.cutIntervalsInBeginning();
	int intervalIndex = cmd.indexOfChar(' ');
	if (intervalIndex != -1)
	{
		MyString resultString = cmd.substring(0, intervalIndex);
		int result = atoi(resultString.getString());
		if (result != 0 || (result == 0 && resultString.charAtIndex(0) == '0'))
		{
			cmd.trim(intervalIndex + 1);
			return result;
		}
		else
			return -1; //no index of figure to translate --> translate all
	}
	else
	{
		//wrong command format
		int result = atoi(cmd.getString());
		cmd = "";
		return result;
	}
}

MyString Command::getTranslateProperty()
{
	cmd.cutIntervalsInBeginning();
	int equalsSignIndex = cmd.indexOfChar('=');
	if (equalsSignIndex == -1)
		return "";
	else
	{
		MyString resultString = cmd.substring(0, equalsSignIndex);
		resultString.cutIntervalsAtEnd();
		return resultString;
	} 
}

double Command::getTranslatePropertyValue()
{
	cmd.cutIntervalsInBeginning();
	int equalsSignIndex = cmd.indexOfChar('=');
	if (equalsSignIndex != -1)
	{
		cmd.trim(equalsSignIndex + 1);
		cmd.cutIntervalsInBeginning();
		int intervalIndex = cmd.indexOfChar(' ');
		if (intervalIndex != -1)
		{
			MyString resultString = cmd.substring(0, intervalIndex);
			cmd.trim(intervalIndex + 1);
			return resultString.toDouble();
		}
		else
		{
			MyString resultString = cmd;
			cmd = "";
			return resultString.toDouble();
		}
	}
	else
		return 0; //wrong command format - no equals sign
}

