#pragma once
#include <iostream>
class MyString
{
	char* str;
	size_t size;

	void copyFrom(const MyString& other);
	void free();

public:
	MyString();
	MyString(const char* string);
	MyString(const MyString& other);
	MyString(MyString&& other);
	~MyString();

	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other);

	size_t getSize() const;
	const char* getString() const;
	void setString(const char* string);

	void concat(const MyString& other);

	//returns -1 if word is smaller, 0 if they are the same and 1 if word is bigger
	int compare(const char* word);

	friend std::ostream& operator<<(std::ostream& stream, const MyString& string);
	friend std::istream& operator>>(std::istream& stream, MyString& string);

	int indexOf(const MyString& element) const;
	int indexOfChar(char symbol) const;
	MyString substring(unsigned startIndex, unsigned endIndex) const;
	char charAtIndex(unsigned index) const;

	//shortens the string so the new one begins from the index
	void trim(unsigned index);
	double toDouble() const;
	void cutIntervalsInBeginning();
	void cutIntervalsAtEnd();
};
bool operator==(const MyString& lhs, const MyString& rhs);