//String.h
//All definitions are in "String.cpp"
#pragma once
#include <new>				//for bad_alloc
#include <iostream>
using namespace std;

class String 
{
private:
	char* string_;				//Array of char
	size_t length_;			//A logical line length
public:
	//Default Constructor and destructor
	String();
	~String();

	//Constructor with size of line
	String(size_t n);

	//Constructor with line
	String(const char* string);

	//The constructor with nSYMBOLS times taken the symbol of SYMBOL 
	String(size_t nSymbols, char symbol);

	//The copy constructor
	String(const String& string);



	//Get the length of the line
	size_t getLength();



	//Overload operator <<
	friend ostream& operator<<(ostream&, const String&);

	//Overload operator >>
	friend istream& operator>>(istream&, String&);

	//Overload operator +
	String operator+(const String& string);

	//Overload operator +=
	String operator+=(const String& string);

	//Overload operator =
	String operator=(const String& string);

	//Overload operator ==
	bool operator==(const String& string);

	//Overload operator <
	bool operator<(const String& string);

	//Overload operator >
	bool operator>(const String& string);


	//Function reported, if the string is empty
	bool isEmpty();

	//Function allocates memory for a base object
	inline void Memory();

	//Function allocates memory for the selected object
	friend void MemoryTo(String& temp);

	//Function inserts a row add in the original row on the n-th symbol
	friend void insertString(String &original, const String &add, size_t n);

	//Function cuts out a piece of string from n to k
	friend void cutString(String &string, size_t n, size_t k);

	//Function looks for a string WHAT in row WHERE, and outputs the symbol number 
	friend void findString(const String &where, const String &what);

	//Function changes lowercase characters to uppercase after the gap
	friend void toUppercaseFirsts(String& string);

	//Function changes all capital letters to lowercase
	friend void toLowercaseAll(String& string);

	//Function converts the object`s name to the standard form
	friend void standardizeName(String& string);

	//Function converts the object`s position to the standard form
	friend void standardizePosition(String& string);
};

//Exception classes
class SizeWrongException			//Incorrect row size
{
private:
	int n_;	 		
public:
	SizeWrongException(int i) : n_(i) { }
	int getValue() { return n_; }
};

class EmptyObjectsException { /* ... */ };	//Working with empty objects

class DataWrongException { /* ... */ };	//Selected values do not fit criteria

