#include <iostream>
#include "MyString.h"
#pragma warning(disable:4996)

void MyString::free()
{
	delete[] str;
}

void MyString::copyFrom(const MyString& other)
{
	size = other.size;
	str = new char[size + 1];
	strcpy(str, other.str);
}

MyString::MyString()
{
	str = new char[1];
	str[0] = '\0';
	size = 0;
}

MyString::MyString(const char* string)
{
	size = strlen(string);
	str = new char[size + 1];
	strcpy(str, string);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString::MyString(MyString&& other)
{
	size = other.size;
	str = other.str;

	other.str = nullptr;
}

MyString::~MyString()
{
	free();
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

MyString& MyString::operator=(MyString&& other)
{
	if (this != &other)
	{
		free();
		size = other.size;
		str = other.str;

		other.str = nullptr;
	}
	return *this;
}

size_t MyString::getSize() const
{
	return size;
}

const char* MyString::getString() const
{
	return str;
}

void MyString::setString(const char* string)
{
	free();
	size = strlen(string);
	str = new char[size + 1];
	strcpy(str, string);
}

void MyString::concat(const MyString& other)
{
	char* result = new char[size + other.size + 1];

	strcpy(result, str);
	strcat(result, other.str);

	free();
	str = result;
	size += other.size;
}

int MyString::compare(const char* word)
{
	return strcmp(str, word);
}

bool isPrefix(const char* word, const char* prefix)
{
	unsigned wordLength = strlen(word);
	unsigned prefixLength = strlen(prefix);
	if (prefixLength > wordLength)
		return false;
	for (size_t i = 0; i < prefixLength; i++)
	{
		if (word[i] != prefix[i])
			return false;
	}
	return true;
}

int MyString::indexOf(const MyString& element) const
{
	for (size_t i = 0; i < size - element.size + 1; i++)
	{
		if (isPrefix(str + i, element.str))
			return i;
	}
	return -1;
}

int MyString::indexOfChar(char symbol) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (str[i] == symbol)
			return i;
	}
	return -1;
}

MyString MyString::substring(unsigned startIndex, unsigned endIndex) const
{
	if (startIndex > endIndex)
		throw std::exception("Start index cannot be bigger than end index!");
	if (endIndex >= size || endIndex < 0)
		throw std::exception("Invalid end index!");

	char* substring = new char[endIndex - startIndex + 1];
	for (size_t i = startIndex; i < endIndex; i++)
	{
		substring[i - startIndex] = str[i];
	}
	substring[endIndex - startIndex] = '\0';
	MyString result(substring);
	delete[] substring;
	return result;
}

char MyString::charAtIndex(unsigned index) const
{
	if (index < 0 || index >= size)
		throw std::exception("Invalid index!");
	return str[index];
}

void MyString::trim(unsigned index)
{
	if (index < 0 || index >= size)
		throw std::exception("Invalid index");
	char* newString = new char[size - index + 1];
	for (size_t i = index; i < size; i++)
	{
		newString[i - index] = str[i];
	}
	newString[size - index] = '\0';
	delete[] str;
	str = newString;
}

double MyString::toDouble() const
{
	double result = atof(str);
	return result;
}

void MyString::cutIntervalsInBeginning()
{
	int lastIntervalIndex = -1;
	for (size_t i = 0; i < size; i++)
	{
		if (str[i] == ' ')
			lastIntervalIndex = i;
		else
			break;
	}
	if (lastIntervalIndex != -1)
		trim(lastIntervalIndex + 1);
}

void MyString::cutIntervalsAtEnd()
{
	int lastIntervalIndex = -1;
	for (size_t i = size - 1; i >= 0; i--)
	{
		if (str[i] == ' ')
			lastIntervalIndex = i;
		else
			break;
	}
	if (lastIntervalIndex != -1)
		setString(substring(0, lastIntervalIndex).getString());
}

std::ostream& operator<<(std::ostream& stream, const MyString& string)
{
	stream << string.str;
	return stream;
}

std::istream& operator>>(std::istream& stream, MyString& string)
{
	char input[256];
	stream.getline(input, 255);
	string.setString(input);
	return stream;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
	return (strcmp(lhs.getString(), rhs.getString()) == 0);
}
